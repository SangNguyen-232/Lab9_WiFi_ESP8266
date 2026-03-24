#pragma once
#include <Arduino.h>

#define LED_GPIO2 2
#define LED_GPIO5 5

extern bool led2_auto_blink;

/*
 * Thiết lập các chân GPIO cho LED.
 */
void led_init();

/*
 * Điều khiển trạng thái bật/tắt của một LED.
 */
void led_set(uint8_t pin, bool on);

/*
 * Cập nhật hiệu ứng hoặc trạng thái tự động của LED.
 */
void led_update();
