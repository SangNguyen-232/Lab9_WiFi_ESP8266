#include "web_server.h"
#include "led.h"
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

// Hàm sinh dữ liệu nhiệt độ giả định (25-40 độ C)
int fake_temperature() {
    return random(25, 41);
}

// Hàm sinh dữ liệu độ ẩm giả định (50-90%)
int fake_humidity() {
    return random(50, 91);
}

/* ===== Giao diện HTML với CSS Card và JavaScript cập nhật sensor ===== */
const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>ESP8266 Web Control</title>
    <style>
        body { font-family: Arial, sans-serif; background: #f2f2f2; text-align: center; }
        .card { background: #ffffff; width: 320px; margin: 50px auto; padding: 20px; border-radius: 8px; box-shadow: 0 2px 8px rgba(0,0,0,0.2); }
        h2 { margin-bottom: 15px; color: #333; }
        .sensor { margin-bottom: 20px; font-size: 18px; color: #444; background: #f9f9f9; padding: 10px; border-radius: 5px; }
        .sensor p { margin: 5px 0; }
        .section { margin-top: 15px; padding-top: 10px; border-top: 1px solid #eee; }
        button { width: 90px; height: 35px; margin: 5px; font-size: 14px; cursor: pointer; border: none; border-radius: 4px; background: #007bff; color: white; transition: 0.3s; }
        button:hover { background: #0056b3; }
        .btn-auto { background: #28a745; width: 130px; }
        .btn-auto:hover { background: #218838; }
        b { color: #007bff; }
    </style>
</head>
<body>
    <div class="card">
        <h2>ESP8266 Web Control</h2>
        
        <div class="sensor">
            <p>Nhiệt độ: <b><span id="temp">--</span> &deg;C</b></p>
            <p>Độ ẩm: <b><span id="hum">--</span> &#37;</b></p>
        </div>
        
        <div class="section">
            <p><b>LED GPIO2 (On-board)</b></p>
            <button onclick="fetch('/led?pin=2&state=on')">ON</button>
            <button onclick="fetch('/led?pin=2&state=off')">OFF</button>
            <br>
            <button class="btn-auto" onclick="fetch('/auto?state=on')">Turn Auto ON</button>
        </div>
        
        <div class="section">
            <p><b>LED GPIO5 (External)</b></p>
            <button onclick="fetch('/led?pin=5&state=on')">ON</button>
            <button onclick="fetch('/led?pin=5&state=off')">OFF</button>
        </div>
    </div>

    <script>
        function updateSensor() {
            fetch('/sensor')
                .then(res => res.json())
                .then(data => {
                    document.getElementById('temp').innerText = data.temperature;
                    document.getElementById('hum').innerText = data.humidity;
                })
                .catch(err => console.error('Error fetching sensor data:', err));
        }
        // Cập nhật dữ liệu mỗi 2 giây
        setInterval(updateSensor, 2000);
        // Gọi ngay lần đầu khi load trang
        updateSensor();
    </script>
</body>
</html>
)rawliteral";

void web_server_init() {
    // Khởi tạo hạt giống cho hàm random
    randomSeed(millis());

    // Endpoint trang chính
    server.on("/", []() {
        server.send_P(200, "text/html", MAIN_page);
    });

    // Endpoint điều khiển LED
    server.on("/led", []() {
        uint8_t pin = server.arg("pin").toInt();
        String state = server.arg("state");
        led_set(pin, state == "on");
        server.send(200, "text/plain", "OK");
    });

    // Endpoint bật lại chế độ tự động cho LED 2
    server.on("/auto", []() {
        String state = server.arg("state");
        led2_auto_blink = (state == "on");
        server.send(200, "text/plain", "Auto Mode Updated");
    });

    // Endpoint cung cấp dữ liệu cảm biến (JSON)
    server.on("/sensor", []() {
        int t = fake_temperature();
        int h = fake_humidity();
        
        String json = "{";
        json += "\"temperature\":" + String(t) + ",";
        json += "\"humidity\":" + String(h);
        json += "}";
        
        server.send(200, "application/json", json);
    });

    server.begin();
}

void web_server_loop() {
    server.handleClient();
}
