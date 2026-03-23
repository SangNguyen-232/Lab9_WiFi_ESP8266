#include "led.h"

// Định nghĩa biến điều khiển chế độ nháy tự động (mặc định là true)
bool led2_auto_blink = true;

void led_init() {
    pinMode(LED_GPIO2, OUTPUT);
    pinMode(LED_GPIO5, OUTPUT);

    digitalWrite(LED_GPIO2, HIGH); // Tắt LED 2
    digitalWrite(LED_GPIO5, LOW);  // Tắt LED 5
}

void led_set(uint8_t pin, bool on) {
    if (pin == LED_GPIO2) {
        digitalWrite(pin, on ? LOW : HIGH); // Đảo logic cho LED GPIO2
        // Khi người dùng điều khiển thủ công LED 2, ta tắt chế độ tự động
        led2_auto_blink = false; 
    } else {
        digitalWrite(pin, on ? HIGH : LOW); // Giữ nguyên logic cho LED GPIO5
    }
}
