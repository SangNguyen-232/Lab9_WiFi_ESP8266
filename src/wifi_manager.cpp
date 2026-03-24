#include "wifi_manager.h"
#include "config.h"
#include <ESP8266WiFi.h>

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
    if (request_connect_wifi) {
        request_connect_wifi = false;
        
        Serial.print("[WIFI] Connecting to target network: ");
        Serial.println(target_ssid);
        
        WiFi.begin(target_ssid.c_str(), target_pass.c_str());
        
        unsigned long start_time = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - start_time < 10000) {
            delay(500);
            Serial.print(".");
        }

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("\n[WIFI] Connected successfully!");
            Serial.print("[WIFI] Station IP: ");
            Serial.println(WiFi.localIP());
        } else {
            Serial.println("\n[WIFI][ERROR] Connection failed! Timeout.");
        }
    }
}
