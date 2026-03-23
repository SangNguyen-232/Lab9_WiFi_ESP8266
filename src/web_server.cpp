#include "web_server.h"
#include "led.h"
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>ESP8266 LED Control</title>
</head>
<body style="text-align: center;">
    <h2>ESP8266 Web Control</h2>
    
    <p>LED GPIO2 (On-board)</p>
    <button onclick="fetch('/led?pin=2&state=on')">ON</button>
    <button onclick="fetch('/led?pin=2&state=off')">OFF</button>
    <button onclick="fetch('/auto?state=on')">Turn Auto ON</button>
    
    <p>LED GPIO5 (External)</p>
    <button onclick="fetch('/led?pin=5&state=on')">ON</button>
    <button onclick="fetch('/led?pin=5&state=off')">OFF</button>
</body>
</html>
)rawliteral";

void web_server_init() {
    server.on("/", []() {
        server.send_P(200, "text/html", MAIN_page);
    });

    server.on("/led", []() {
        uint8_t pin = server.arg("pin").toInt();
        String state = server.arg("state");
        led_set(pin, state == "on");
        server.send(200, "text/plain", "OK");
    });

    // Thêm endpoint để bật lại chế độ tự động cho LED 2
    server.on("/auto", []() {
        String state = server.arg("state");
        led2_auto_blink = (state == "on");
        server.send(200, "text/plain", "Auto Mode Updated");
    });

    server.begin();
}

void web_server_loop() {
    server.handleClient();
}
