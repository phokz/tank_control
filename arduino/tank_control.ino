    /* tank_control - ESP8266 Webserver with serial output of params POSTED on 
     * /set.php URL. 
     * It servers html5 page on / and /ship_control.js and /ship_ontrol.css
     * Serial TX pin connected to Arduino Nano RX pin.
     * 
     * ESP Serial runs at 115200.
     * 
     * connected to grbl on simple cnc shield
     * 
     * Based on ESP8266Webserver
     * 
     * Tested with ESP8266 ESP-01
     * Arduino IDE 1.8.0 - 1.8.6
     * Version 1.0 Thu Aug 30 2018 Josef Liska <josef.liska@virtualmaster.com>
    */
    
    #include <ESP8266WiFi.h>
    #include <WiFiClient.h>
    #include <ESP8266WebServer.h>
     
    const char* ssid     = "Leba";
    const char* password = "hodnepisku";
     
    ESP8266WebServer server(80);
    
    String html_str =     "<!DOCTYPE html>\n"
    "<html>\n"
    "  <head>\n"
    "    <meta content='text/html; charset=UTF-8' http-equiv='Content-Type'>\n"
    "    <meta charset='utf-8'>\n"
    "    <meta content='width=device-width, initial-scale=1' name='viewport'>\n"
    "    <style>\n"
    "      html, body {    height: 100%;    margin: 0;    min-height: 100%;    padding: 0px;}\n"
    "      #wrapper {    height: 100%;    width: 100%;}\n"
    "      .row { height: 30%; margin-left: 30% }\n"
    "      .m6 { width: 60% }\n"
    "      button { width: 30%; height: calc(100vh/4); font-size: calc(100vh/10); }\n"
    "      \n"
    "      @font-face {\n"
    "        font-family: 'icomoon';\n"
    "        src: url('data:application/x-font-ttf;base64,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') format('truetype');\n"
    "        font-weight: normal;\n"
    "        font-style: normal;\n"
    "      }\n"
    "      \n"
    "      [class^=\"icon-\"], [class*=\" icon-\"] {\n"
    "        /* use !important to prevent issues with browser extensions that change fonts */\n"
    "        font-family: 'icomoon' !important;\n"
    "        speak: none;\n"
    "        font-style: normal;\n"
    "        font-weight: normal;\n"
    "        font-variant: normal;\n"
    "        text-transform: none;\n"
    "        line-height: 1;\n"
    "      \n"
    "        /* Better Font Rendering =========== */\n"
    "        -webkit-font-smoothing: antialiased;\n"
    "        -moz-osx-font-smoothing: grayscale;\n"
    "      }\n"
    "      \n"
    "      .icon-rocket:before {\n"
    "        content: \"\\e9a5\";\n"
    "      }\n"
    "      .icon-stop2:before {\n"
    "        content: \"\\ea1e\";\n"
    "      }\n"
    "      .icon-arrow-up-left:before {\n"
    "        content: \"\\ea31\";\n"
    "      }\n"
    "      .icon-arrow-up:before {\n"
    "        content: \"\\ea32\";\n"
    "      }\n"
    "      .icon-arrow-up-right:before {\n"
    "        content: \"\\ea33\";\n"
    "      }\n"
    "      .icon-arrow-right:before {\n"
    "        content: \"\\ea34\";\n"
    "      }\n"
    "      .icon-arrow-down-right:before {\n"
    "        content: \"\\ea35\";\n"
    "      }\n"
    "      .icon-arrow-down:before {\n"
    "        content: \"\\ea36\";\n"
    "      }\n"
    "      .icon-arrow-down-left:before {\n"
    "        content: \"\\ea37\";\n"
    "      }\n"
    "      .icon-arrow-left:before {\n"
    "        content: \"\\ea38\";\n"
    "      }\n"
    "    </style>\n"
    "    <title>Tank control</title>\n"
    "    <script>\n"
    "      var TANK = TANK || {};\n"
    "      document.addEventListener('DOMContentLoaded', function(event) {\n"
    "      TANK.mode = document.getElementById('mode');\n"
    "      TANK.unit = document.getElementById('unit');\n"
    "      TANK.x = document.getElementById('x');\n"
    "      TANK.y = document.getElementById('y');\n"
    "      TANK.go = document.getElementById('go');\n"
    "      TANK.xhr = function(url, data, options) {\n"
    "        options = options || {};\n"
    "        var request = new XMLHttpRequest();\n"
    "        request.open('POST', url, true);\n"
    "        request.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');\n"
    "        request.onreadystatechange = function () {\n"
    "          if (this.readyState === 4) {\n"
    "            if (this.status >= 200 && this.status < 400) {\n"
    "              options.success && option.success(parse(this.responseText));\n"
    "            } else {\n"
    "              options.error && options.error(this.status);\n"
    "            }\n"
    "          }\n"
    "        };\n"
    "        request.send(data);\n"
    "      }\n"
    "      TANK.button = function(event) {\n"
    "        console.log(event.target);\n"
    "        var x = parseFloat(event.target.dataset['x'])\n"
    "        var y = parseFloat(event.target.dataset['y'])\n"
    "        TANK.x.value = 'X'+x\n"
    "        TANK.y.value = 'Y'+y\n"
    "        TANK.click_go();\n"
    "      }\n"
    "      TANK.click_go = function() {\n"
    "        TANK.xhr('/set.php','mode='+TANK.mode.value+'&unit='+TANK.unit.value+'&x='+TANK.x.value+'&y='+TANK.y.value, {});\n"
    "      }\n"
    "      TANK.go.addEventListener('click', TANK.click_go);\n"
    "      var i = 0;\n"
    "      var nodes = document.querySelectorAll('.d')\n"
    "      var n = nodes.length\n"
    "      for (i=0; i<n; i++) {\n"
    "        nodes[i].addEventListener('click', TANK.button);\n"
    "      }\n"
    "      \n"
    "      });\n"
    "    </script>\n"
    "  </head>\n"
    "  <body>\n"
    "    <div class='container' id='wrapper'>\n"
    "      <div class='row'>\n"
    "        <div class='m6'>\n"
    "          <button class='d' data-x='1' data-y='0.73'>\n"
    "            <span class='icon-arrow-up-left'></span>\n"
    "          </button>\n"
    "          <button class='d' data-x='1' data-y='1'>\n"
    "            <span class='icon-arrow-up'></span>\n"
    "          </button>\n"
    "          <button class='d' data-x='0.73' data-y='1'>\n"
    "            <span class='icon-arrow-up-right'></span>\n"
    "          </button>\n"
    "        </div>\n"
    "      </div>\n"
    "      <div class='row'>\n"
    "        <div class='m6'>\n"
    "          <button class='d' data-x='0.73' data-y='-0.73'>\n"
    "            <span class='icon-arrow-left'></span>\n"
    "          </button>\n"
    "          <button>\n"
    "            <span class='icon-stop2'></span>\n"
    "          </button>\n"
    "          <button class='d' data-x='-0.73' data-y='0.73'>\n"
    "            <span class='icon-arrow-right'></span>\n"
    "          </button>\n"
    "        </div>\n"
    "      </div>\n"
    "      <div class='row'>\n"
    "        <div class='m6'>\n"
    "          <button class='d' data-x='-1' data-y='-0.73'>\n"
    "            <span class='icon-arrow-down-left'></span>\n"
    "          </button>\n"
    "          <button class='d' data-x='-1' data-y='-1'>\n"
    "            <span class='icon-arrow-down'></span>\n"
    "          </button>\n"
    "          <button class='d' data-x='-0.73' data-y='-1'>\n"
    "            <span class='icon-arrow-down-right'></span>\n"
    "          </button>\n"
    "        </div>\n"
    "      </div>\n"
    "    </div>\n"
    "    <div class='foo'>\n"
    "      <input id='mode' name='mode' size='6' type='text' value='G91'>\n"
    "      <br>\n"
    "      <input id='unit' name='unit' size='6' type='text' value='G21'>\n"
    "      <br>\n"
    "      <input id='x' name='x' size='10' type='text' value='X-1'>\n"
    "      <br>\n"
    "      <input id='y' name='y' size='10' type='text' value='Y-1'>\n"
    "      <br>\n"
    "      <button id='go'>send</button>\n"
    "    </div>\n"
    "  </body>\n"
    "</html>\n";
                
    void handle_root() {

      server.send(200, "text/html", html_str);
      delay(100);
    }

    void handle_set() {
      String message = "";
      for (uint8_t i=0; i<server.args(); i++){
        if (i > 0) {
          message += " ";
        }
        message += server.arg(i);
      }
      message += "\r\n";
      server.send(200, "text/plain", message);
      Serial.print(message);
    }
     
    void setup(void)
    {
      // You can open the Arduino IDE Serial Monitor window to see what the code is doing
      Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable
           
      // Connect to WiFi network
      WiFi.begin(ssid, password);
      Serial.print("CONNECTING");
     
      // Wait for connection
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.print("CONNECTED TO");
      Serial.println(ssid);
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
       
      server.on("/", handle_root);
      server.on("/set.php",handle_set);
      
      server.begin();
    }
     
    void loop(void)
    {
      server.handleClient();
    }
    
