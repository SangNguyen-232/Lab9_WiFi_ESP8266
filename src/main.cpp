#include <Arduino.h>

int led_counter = 0;
int led_status = HIGH;

void setup() {
    pinMode(2, OUTPUT);
}

void loop() {
    led_counter++;
    if (led_counter == 100) {
        led_counter = 0;
        led_status = !led_status;
        digitalWrite(2, led_status);
    }
    delay(10);
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