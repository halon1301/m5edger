#include <string.h>
#include <M5Unified.h>
#include <Arduino.h>
#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"


#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;
int motorSpeed;


static void on_arc_motorSpd_changed(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *target = static_cast<lv_obj_t*>(lv_event_get_target(e));
        int16_t value = lv_arc_get_value(target);
        motorSpeed = value;
        Serial.println(value);
    }
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // arcMotorSpd
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.arc_motor_spd = obj;
            lv_obj_set_pos(obj, 169, 106);
            lv_obj_set_size(obj, 119, 112);
            lv_arc_set_value(obj, 25);
            lv_obj_add_event_cb(obj, on_arc_motorSpd_changed, LV_EVENT_VALUE_CHANGED, NULL);
        }
        {
            // lblArousal
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_arousal = obj;
            lv_obj_set_pos(obj, 53, 84);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Arousal");
        }
        {
            // lblMotorSpeed
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_motor_speed = obj;
            lv_obj_set_pos(obj, 182, 84);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Motor Speed");
        }
        {
            // arcArousal
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.arc_arousal = obj;
            lv_obj_set_pos(obj, 22, 106);
            lv_obj_set_size(obj, 115, 112);
            lv_arc_set_value(obj, 25);
        }
        {
            // pnlDenied
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pnl_denied = obj;
            lv_obj_set_pos(obj, 121, 16);
            lv_obj_set_size(obj, 78, 52);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 133, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Denied");
        }
        {
            // lblDeniedVal
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_denied_val = obj;
            lv_obj_set_pos(obj, 0, -78);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0");
        }
        {
            // lblRunState
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_run_state = obj;
            lv_obj_set_pos(obj, 0, 102);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Off");
        }
        {
            // pnlPressure
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pnl_pressure = obj;
            lv_obj_set_pos(obj, 209, 16);
            lv_obj_set_size(obj, 79, 52);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 217, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Pressure");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 288, 34);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "hPa");
        }
        {
            // lblPressure
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_pressureVal = obj;
            lv_obj_set_pos(obj, 235, 34);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "0");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
