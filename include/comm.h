#pragma once
#include <Arduino.h>

extern int current_temperature;
extern int current_humidity;

/*
 * Khởi tạo các cấu hình cần thiết cho việc giao tiếp.
 */
void comm_init();

/*
 * Cập nhật trạng thái giao tiếp và nhận dữ liệu sensor.
 */
void comm_update();
