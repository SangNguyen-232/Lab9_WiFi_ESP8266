#include "web_server.h"
#include "config.h"
#include "led.h"
#include "comm.h"
#include "wifi_manager.h"
#include "index_html.h"
#include <ESP8266WebServer.h>

ESP8266WebServer server(WEB_SERVER_PORT);

/*
 * Khởi tạo Web Server, thiết lập các điểm cuối (endpoints) và bắt đầu lắng nghe yêu cầu.
 */
void web_server_init() {
    randomSeed(millis());

    server.on("/", []() {
        Serial.println("[HTTP][GET] Serving Root Page (/)");
        server.send_P(200, "text/html", MAIN_page);
    });

    server.on("/led", []() {
        uint8_t pin = server.arg("pin").toInt();
        String state = server.arg("state");
        Serial.printf("[HTTP][CMD] LED Control: GPIO%d -> %s\n", pin, state.c_str());
        led_set(pin, state == "on");
        server.send(200, "text/plain", "OK");
    });

    server.on("/auto", []() {
        led2_auto_blink = (server.arg("state") == "on");
        Serial.printf("[HTTP][CMD] LED2 Auto-Blink: %s\n", led2_auto_blink ? "ON" : "OFF");
        server.send(200, "text/plain", "OK");
    });

    server.on("/config_wifi", []() {
        target_ssid = server.arg("ssid");
        target_pass = server.arg("pass");
        request_connect_wifi = true; 
        Serial.printf("[HTTP][CONFIG] WiFi Credentials updated. Target: %s\n", target_ssid.c_str());
        server.send(200, "text/plain", "ESP is trying to connect to: " + target_ssid);
    });

    server.on("/sensor", []() {
        String json = "{\"temperature\":" + String(current_temperature) + ",\"light\":" + String(current_light) + "}";
        server.send(200, "application/json", json);
    });

    server.begin();
    Serial.println("[HTTP] Web Server Started");
}

/*
 * Xử lý các yêu cầu HTTP từ client trong vòng lặp chính.
 */
void web_server_loop() {
    server.handleClient();
}
