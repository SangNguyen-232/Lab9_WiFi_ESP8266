#pragma once
#include <Arduino.h>

extern float current_temperature;
extern uint32_t current_light;

/*
 * Khởi tạo các cấu hình cần thiết cho việc giao tiếp.
 */
void comm_init();

/*
 * Cập nhật trạng thái giao tiếp và nhận dữ liệu sensor.
 */
void comm_update();
