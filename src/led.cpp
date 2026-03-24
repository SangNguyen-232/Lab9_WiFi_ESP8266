#include "led.h"
#include "config.h"
#include <math.h>

bool led2_auto_blink = true;

static unsigned long last_blink_time = 0;
static bool led2_internal_state = false;

/*
 * Khởi tạo các chân GPIO cho LED và thiết lập trạng thái ban đầu.
 */
void led_init() {
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);

    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW);
}

/*
 * Thiết lập trạng thái bật hoặc tắt cho một LED cụ thể.
 */
void led_set(uint8_t pin, bool on) {
    if (pin == LED1_PIN) {
        digitalWrite(pin, on ? LOW : HIGH);
        led2_auto_blink = false; 
    } else {
        digitalWrite(pin, on ? HIGH : LOW);
    }
}

/*
 * Cập nhật trạng thái nháy tự động của LED 2 dựa trên thời gian.
 */
void led_update() {
    if (led2_auto_blink) {
        float time_val = millis() / 1000.0;
        int current_delay = 275 + (int)(225 * sin(time_val));
        if (millis() - last_blink_time >= (unsigned long)current_delay) {
            led2_internal_state = !led2_internal_state;
            digitalWrite(LED1_PIN, led2_internal_state ? LOW : HIGH);
            last_blink_time = millis();
        }
    }
}
