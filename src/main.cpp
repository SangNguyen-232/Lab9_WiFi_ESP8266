#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <math.h>
#include "led.h"
#include "web_server.h"

// Cấu hình WiFi riêng cho ESP (Access Point)
const char* ssid = "thienphucope";
const char* password = "thienphucope";

// Biến điều khiển LED nháy (dùng trong auto mode)
unsigned long last_blink_time = 0;
bool led2_internal_state = false;

void setup() {
    Serial.begin(115200);
    Serial.println();

    // Thiết lập ESP8266 ở chế độ Access Point
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP Address: ");
    Serial.println(myIP);

    led_init();
    web_server_init();
}

void loop() {
    web_server_loop();

    // CHỈ TỰ ĐỘNG NHÁY NẾU CHƯA CÓ ĐIỀU KHIỂN THỦ CÔNG QUA WEB
    if (led2_auto_blink) {
        float time_val = millis() / 1000.0;
        int current_delay = 275 + (int)(225 * sin(time_val));

        if (millis() - last_blink_time >= (unsigned long)current_delay) {
            led2_internal_state = !led2_internal_state;
            
            // Dùng digitalWrite trực tiếp thay vì led_set để không bị tắt cờ auto_blink
            digitalWrite(LED_GPIO2, led2_internal_state ? LOW : HIGH);
            
            last_blink_time = millis();
        }
    }
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
