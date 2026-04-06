#pragma once
#include <Arduino.h>

const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>ESP8266 Web Control</title>
    <style>
        body { font-family: Arial, sans-serif; background: #f2f2f2; text-align: center; }
        .card { background: #ffffff; width: 340px; margin: 30px auto; padding: 20px; border-radius: 8px; box-shadow: 0 2px 8px rgba(0,0,0,0.2); }
        h2 { margin-bottom: 15px; color: #333; }
        .sensor { margin-bottom: 20px; font-size: 18px; color: #444; background: #f9f9f9; padding: 10px; border-radius: 5px; }
        .section { margin-top: 15px; padding-top: 10px; border-top: 1px solid #eee; text-align: left; }
        .section p { font-weight: bold; margin-bottom: 5px; text-align: center; }
        .controls { text-align: center; }
        input { width: 90%; padding: 8px; margin: 5px 0; border: 1px solid #ccc; border-radius: 4px; }
        button { width: 90px; height: 35px; margin: 5px; font-size: 14px; cursor: pointer; border: none; border-radius: 4px; background: #007bff; color: white; }
        .btn-full { width: 95%; background: #28a745; margin-top: 10px; }
        b { color: #007bff; }
    </style>
</head>
<body>
    <div class="card">
        <h2>ESP8266 Dashboard</h2>
        
        <div class="sensor">
            <p>Nhiệt độ: <b><span id="temp">--</span> &deg;C</b></p>
            <p>Ánh sáng: <b><span id="light">--</span> &#37;</b></p>
        </div>
        
        <div class="section">
            <p>WiFi Configuration</p>
            <input type="text" id="ssid" placeholder="WiFi Name (SSID)">
            <input type="password" id="pass" placeholder="Password">
            <button class="btn-full" onclick="saveWifi()">Connect to WiFi</button>
        </div>

        <div class="section controls">
            <p>LED GPIO2 (Auto: <span id="auto_status">ON</span>)</p>
            <button onclick="fetch('/led?pin=2&state=on')">ON</button>
            <button onclick="fetch('/led?pin=2&state=off')">OFF</button>
            <button onclick="fetch('/auto?state=on').then(()=>document.getElementById('auto_status').innerText='ON')">AUTO</button>
        </div>
        
        <div class="section controls">
            <p>LED GPIO5</p>
            <button onclick="fetch('/led?pin=5&state=on')">ON</button>
            <button onclick="fetch('/led?pin=5&state=off')">OFF</button>
        </div>
    </div>

    <script>
        function saveWifi() {
            var ssid = document.getElementById('ssid').value;
            var pass = document.getElementById('pass').value;
            if(!ssid) { alert("Please enter SSID"); return; }
            fetch('/config_wifi?ssid=' + encodeURIComponent(ssid) + '&pass=' + encodeURIComponent(pass))
                .then(res => res.text())
                .then(txt => alert(txt));
        }

        function updateSensor() {
            fetch('/sensor').then(res => res.json()).then(data => {
                document.getElementById('temp').innerText = data.temperature;
                document.getElementById('light').innerText = data.light;
            });
        }
        setInterval(updateSensor, 2000);
        updateSensor();
    </script>
</body>
</html>
)rawliteral";
