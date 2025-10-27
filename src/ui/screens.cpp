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
        Serial.println("test");
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
            lv_obj_set_pos(obj, 99, 84);
            lv_obj_set_size(obj, 85, 84);
            lv_arc_set_value(obj, 25);
            lv_obj_add_event_cb(obj, on_arc_motorSpd_changed, LV_EVENT_VALUE_CHANGED, NULL);
        }
        {
            // lblArousal
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_arousal = obj;
            lv_obj_set_pos(obj, 22, 67);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Arousal");
        }
        {
            // lblMotorSpeed
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_motor_speed = obj;
            lv_obj_set_pos(obj, 99, 67);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Motor Speed");
        }
        {
            // arcArousal
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.arc_arousal = obj;
            lv_obj_set_pos(obj, 6, 84);
            lv_obj_set_size(obj, 85, 84);
            lv_arc_set_value(obj, 25);
        }
        {
            // pnlDenied
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pnl_denied = obj;
            lv_obj_set_pos(obj, 232, 15);
            lv_obj_set_size(obj, 78, 52);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 244, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Denied");
        }
        {
            // lblDeniedVal
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_denied_val = obj;
            lv_obj_set_pos(obj, 257, 33);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
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
