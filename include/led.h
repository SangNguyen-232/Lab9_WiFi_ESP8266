#pragma once
#include <Arduino.h>

#define LED_GPIO2 2
#define LED_GPIO5 5

void led_init();
void led_set(uint8_t pin, bool on);
