#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>

/* 
 * Khởi tạo MQTT client và các thông số cấu hình ban đầu.
 */
void mqtt_init();

/* 
 * Duy trì kết nối MQTT và gửi dữ liệu định kỳ (mỗi 30s).
 */
void mqtt_update();

/* 
 * Gửi một giá trị lên một feed cụ thể.
 */
void mqtt_publish(const char* feed, float value);

#endif
