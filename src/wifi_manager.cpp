#include "wifi_manager.h"
#include "config.h"
#include <ESP8266WiFi.h>
#include "led.h"

String target_ssid = "";
String target_pass = "";
bool request_connect_wifi = false;

/*
 * Khởi tạo chế độ Access Point để người dùng có thể cấu hình thông tin WiFi.
 */
void wifi_init() {
    Serial.println("[WIFI] Starting Access Point mode...");
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    
    Serial.printf("[WIFI] AP SSID: %s, IP: ", AP_SSID);
    Serial.println(WiFi.softAPIP());
    Serial.println("[WIFI] Ready to receive STA credentials.");
}

/*
 * Kiểm tra yêu cầu kết nối WiFi và thực hiện kết nối tới mạng mục tiêu.
 */
void wifi_update() {
    static unsigned long connect_start = 0;
    static bool connecting = false;

    if (request_connect_wifi) {
        request_connect_wifi = false;
        connecting = true;
        connect_start = millis();

        led_set(5, true);

        WiFi.disconnect();
        delay(100);
        WiFi.mode(WIFI_AP_STA);
        WiFi.begin(target_ssid.c_str(), target_pass.c_str());
        Serial.printf("[WIFI] Connecting to: %s\n", target_ssid.c_str());
    }

    if (connecting) {
        if (WiFi.status() == WL_CONNECTED) {
            connecting = false;
            led_set(5, false);
            Serial.println("[WIFI] Connected! IP: " + WiFi.localIP().toString());
        } else if (millis() - connect_start > 10000) {
            connecting = false;
            led_set(5, false);
            Serial.printf("[WIFI][ERROR] Timeout! Status: %d\n", WiFi.status());
        }
    }
}
