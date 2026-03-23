#include <Arduino.h>
#include <math.h>

void setup() {
    pinMode(2, OUTPUT);
}

void loop() {
    // Tính toán delay theo hàm sin để tạo hiệu ứng nháy nhanh/chậm
    float time = millis() / 1000.0;
    int blink_delay = 275 + (int)(225 * sin(time));

    digitalWrite(2, LOW);  // Bật LED
    delay(blink_delay);
    digitalWrite(2, HIGH); // Tắt LED
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
