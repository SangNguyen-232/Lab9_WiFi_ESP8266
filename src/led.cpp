#include "led.h"

void led_init() {
    pinMode(LED_GPIO2, OUTPUT);
    pinMode(LED_GPIO5, OUTPUT);

    digitalWrite(LED_GPIO2, HIGH); // active-LOW (Tắt LED ban đầu)
    digitalWrite(LED_GPIO5, LOW);  // active-HIGH (Tắt LED ban đầu)
}

void led_set(uint8_t pin, bool on) {
    if (pin == LED_GPIO2) {
        digitalWrite(pin, on ? LOW : HIGH); // Đảo logic cho LED GPIO2
    } else {
        digitalWrite(pin, on ? HIGH : LOW); // Giữ nguyên logic cho các chân khác
    }
}
