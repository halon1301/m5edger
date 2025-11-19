//
// Created by falconx on 2025-10-29.
//

#include "edge.h"
#include "RunningAverage.h"

// Set the pressure offset
float pressureOffset = 0.0;
float pressureMax = 1723.689;
float pressureMin = 0.0;
/*
static void edging_control_init() {
    running_average_init(&arousal_state.average, Config.pressure_smoothing);
    output_state.output_mode = MANUAL_CONTROL;
    output_state.vibration_mode = Config.vibration_mode;
    output_state.motor_speed = 0.0f;
}*/