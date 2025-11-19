#include <Arduino.h>
#include <M5Unified.h>
#include <lvgl.h>
#include "ui/ui.h"
#include <Wire.h>
#include <Adafruit_MPRLS.h>
#include <Adafruit_NeoPixel.h>
#include "lib/edge.h"




// Set up UI Constants
const int displayHorizonal = 320;
const int displayVertical = 240;

unsigned long currentTime;
unsigned long bootTime = 0;

// Initialize Display stuff
lv_display_t *display;
lv_indev_t *indev;
static lv_draw_buf_t *draw_buf1;

#define RESET_PIN  -1  // set to any GPIO pin # to hard-reset on begin()
#define EOC_PIN    -1  // set to any GPIO pin to read end-of-conversion by pin
auto mpr = Adafruit_MPRLS(RESET_PIN, EOC_PIN);

// Display flushing
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    lv_draw_sw_rgb565_swap(px_map, w*h);
    M5.Display.pushImageDMA<uint16_t>(area->x1, area->y1, w, h, (uint16_t *)px_map);
    lv_disp_flush_ready(disp);
}

uint32_t my_tick_function() {
    return(esp_timer_get_time() / 1000LL);
}

void my_touchpad_read(lv_indev_t * drv, lv_indev_data_t * data) {
    M5.update();
    auto count = M5.Touch.getCount();
    if (count == 0) {
        data->state = LV_INDEV_STATE_RELEASED;
    } else {
        auto touch = M5.Touch.getDetail(0);
        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = touch.x;
        data->point.y = touch.y;
    }
}

static void event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *label = reinterpret_cast<lv_obj_t *>(lv_event_get_user_data(e));

    switch (code)
    {
    case LV_EVENT_PRESSED:
        lv_label_set_text(label, "The last button event:\nLV_EVENT_PRESSED");
        break;
    case LV_EVENT_CLICKED:
        lv_label_set_text(label, "The last button event:\nLV_EVENT_CLICKED");
        break;
    case LV_EVENT_LONG_PRESSED:
        lv_label_set_text(label, "The last button event:\nLV_EVENT_LONG_PRESSED");
        break;
    case LV_EVENT_LONG_PRESSED_REPEAT:
        lv_label_set_text(label, "The last button event:\nLV_EVENT_LONG_PRESSED_REPEAT");
        break;
    default:
        break;
    }
}

void setup() {
    Serial.begin(115200);
    auto cfg = M5.config();
    M5.begin(cfg);
    Wire.begin();
    Serial.println("Startup");
     /* Pin config, none of these are used at the moment
    pinMode(remoteUserPin, INPUT);
    pinMode(flowUpPin, INPUT);
    pinMode(flowDownPin, INPUT);
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    */
    M5.Display.setEpdMode(epd_mode_t::epd_fast);
    if (M5.Display.width() < M5.Display.height()) {
        M5.Display.setRotation(M5.Display.getRotation() ^ 1);
    }
    lv_init();
    lv_tick_set_cb(my_tick_function);
    display = lv_display_create(displayHorizonal, displayVertical);
    lv_display_set_flush_cb(display, my_disp_flush);
    static lv_color_t buf1[displayHorizonal * 15];
    lv_display_set_buffers(display, buf1, nullptr, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_touchpad_read);
    ui_init();
    if (! mpr.begin()) {
        Serial.println("Failed to communicate with MPRLS sensor, check wiring?");
        while (1) {
            delay(10);
        }
    }
    Serial.println("Initialization complete");
    bootTime = millis();

}

void loop() {
    M5.update();
    lv_task_handler();
    // Need to read the pressure sensor, we'll break this out later to create a nice event loop
    float pressure_hPa = mpr.readPressure();
    Serial.print("Pressure (hPa): "); Serial.println(pressure_hPa);
    lv_label_set_text_fmt(objects.lbl_pressureVal, "%.2f", pressure_hPa);
    currentTime = millis();
    delay(1000);
}