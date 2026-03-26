#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>

extern String target_ssid;
extern String target_pass;
extern bool request_connect_wifi;

/*
 * Khởi tạo các thiết lập WiFi ban đầu.
 */
void wifi_init();

/*
 * Quản lý và duy trì trạng thái kết nối WiFi.
 */
void wifi_update();
