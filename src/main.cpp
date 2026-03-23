#include <Arduino.h>
#include <math.h>
#include "led.h"

void setup() {
    led_init(); // Khởi tạo các chân LED theo module
}

void loop() {
    // Tính toán delay theo hàm sin để tạo hiệu ứng nháy nhanh/chậm
    float time = millis() / 1000.0;
    int blink_delay = 275 + (int)(225 * sin(time));

    led_set(LED_GPIO2, true);  // Bật LED bằng module (đã xử lý active-LOW)
    delay(blink_delay);
    led_set(LED_GPIO2, false); // Tắt LED
    delay(blink_delay);
}

// // put function declarations here:
// int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
//   int result = myFunction(2, 3);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }
