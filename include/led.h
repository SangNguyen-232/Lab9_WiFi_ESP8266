#pragma once
#include <Arduino.h>

#define LED_GPIO2 2
#define LED_GPIO5 5

// Biến toàn cục để kiểm soát chế độ tự động của LED 2
extern bool led2_auto_blink;

void led_init();
void led_set(uint8_t pin, bool on);
