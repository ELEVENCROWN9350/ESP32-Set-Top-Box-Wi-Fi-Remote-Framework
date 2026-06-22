#include <WiFi.h>
#include <WebServer.h>
#include <esp_wifi.h> // Needed for disabling Wi-Fi power save mode

const char* ssid = "KRB";
const char* password = "ravi123#";

WebServer server(80);

const int TX_PIN = 5;

// --------------------
// Signal functions
// --------------------

void pullLow(unsigned int us) {
  pinMode(TX_PIN, OUTPUT);
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(us);
}

void releaseLine(unsigned int us) {
  pinMode(TX_PIN, INPUT);
  delayMicroseconds(us);
}

void sendRawCommand(uint16_t raw[], int len) {
  int startIndex = (raw[0] < 100) ? 1 : 0;
  for (int i = startIndex; i < len; i += 2) {
    pullLow(raw[i]);
    if (i + 1 < len)
      releaseLine(raw[i + 1]);
  }
  pinMode(TX_PIN, INPUT);
}

// --------------------
// IR Command Arrays
// --------------------

void sendPowerCommand() {
  uint16_t raw[] = {2, 9134, 4426, 692, 444, 690, 1578, 662, 468, 690, 444, 690, 444, 690, 444, 690, 444, 690, 444, 690, 444, 690, 1578, 660, 474, 688, 1580, 636, 1632, 636, 1630, 690, 444, 690, 1578, 688, 1578, 638, 1632, 662, 470, 690, 1578, 688, 444, 690, 444, 690, 444, 690, 444, 690, 444, 690, 444, 688, 1580, 660, 474, 688, 1578, 660, 1608, 688, 1602, 638, 1606, 638, 42098, 9136, 2158, 716};
  sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
}

void sendOKCommand() {
  uint16_t raw[] = {2, 9138, 4424, 688, 446, 662, 1606, 662, 472, 662, 472, 662, 470, 688, 446, 662, 472, 662, 472, 688, 446, 662, 1608, 660, 472, 662, 1608, 684, 1584, 634, 1632, 662, 472, 686, 1580, 688, 446, 664, 1606, 662, 1606, 662, 472, 684, 448, 662, 472, 662, 472, 686, 448, 686, 1582, 636, 500, 660, 472, 662, 1604, 688, 1582, 636, 1632, 660, 1628, 664, 1582, 660, 42076, 9136, 2158, 688};
  sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
}

void sendUpCommand() {
  uint16_t raw[] = {2, 9116, 4446, 668, 468, 666, 1602, 688, 446, 664, 468, 664, 468, 666, 468, 666, 468, 664, 468, 666, 468, 666, 1604, 664, 468, 664, 1604, 638, 1630, 636, 1630, 662, 470, 664, 1602, 664, 468, 666, 1602, 664, 1606, 638, 1630, 638, 494, 664, 468, 640, 494, 638, 494, 638, 1630, 614, 520, 614, 520, 614, 520, 614, 1676, 592, 1654, 614, 1656, 610, 1656, 588, 42148, 9112, 2182, 692};
  sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
}

void sendDownCommand() {
  uint16_t raw[] = {2, 9136, 4426, 664, 472, 686, 1582, 660, 472, 662, 472, 686, 448, 686, 446, 662, 470, 662, 472, 686, 448, 662, 1606, 662, 472, 662, 1604, 688, 1582, 660, 1606, 660, 472, 662, 1604, 688, 446, 664, 1604, 688, 446, 688, 1580, 688, 446, 686, 446, 688, 444, 688, 446, 664, 1606, 686, 446, 688, 1582, 686, 444, 688, 1580, 662, 1626, 640, 1604, 688, 1580, 638};
  sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
}

void sendLeftCommand() {
  uint16_t raw[] = {2, 9136, 4426, 662, 474, 660, 1608, 684, 450, 684, 450, 684, 450, 684, 450, 660, 474, 660, 474, 660, 472, 686, 1586, 634, 500, 682, 1586, 658, 1610, 632, 1632, 682, 452, 658, 1630, 638, 474, 682, 1606, 638, 474, 660, 1630, 638, 1608, 634, 520, 638, 472, 686, 468, 642, 1606, 686, 468, 666, 1604, 662, 468, 666, 468, 642, 1626, 666, 1606, 638, 1610, 658};
  sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
}

void sendRightCommand() {
  uint16_t raw[] = {2, 9138, 4426, 688, 448, 662, 1606, 660, 474, 684, 446, 686, 448, 662, 472, 662, 470, 664, 470, 686, 448, 662, 1608, 660, 472, 660, 1608, 660, 1608, 682, 1606, 640, 494, 640, 1606, 660, 474, 660, 1606, 636, 498, 660, 472, 686, 1582, 662, 472, 684, 448, 662, 472, 662, 1608, 660, 472, 684, 1580, 664, 1628, 664, 448, 662, 1608, 636, 1632, 660, 1606, 662};
  sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
}

void sendMuteCommand() {
  uint16_t raw[] = {2, 9136, 4426, 684, 450, 684, 1586, 632, 520, 662, 450, 684, 448, 662, 474, 660, 492, 642, 492, 642, 492, 642, 1612, 630, 500, 658, 1608, 684, 1586, 658, 1610, 632, 502, 682, 1606, 638, 474, 660, 472, 686, 468, 642, 492, 666, 1582, 686, 468, 642, 472, 686, 468, 666, 1586, 632, 1656, 636, 1630, 638, 1630, 612, 500, 682, 1606, 1654, 638, 1630, 638, 42076, 9110, 2184, 686};
  sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
}

void sendRecallCommand() {
  uint16_t raw[] = {2, 9114, 4450, 664, 472, 660, 1608, 660, 474, 660, 472, 662, 472, 662, 472, 686, 448, 662, 472, 686, 448, 662, 1606, 662, 472, 660, 1606, 662, 1606, 636, 1632, 660, 472, 686, 1584, 660, 472, 660, 472, 686, 1584, 636, 1632, 660, 1606, 636, 520, 640, 472, 686, 448, 686, 1584, 634, 1630, 662, 472, 662, 472, 686, 448, 662, 1608, 660, 1606, 660, 1608, 660, 42072, 9140, 2154, 692};
  sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
}

void sendMenuCommand() {
  uint16_t raw[] = {2, 9134, 4424, 664, 472, 662, 1604, 688, 446, 662, 472, 662, 472, 686, 446, 662, 472, 686, 448, 662, 472, 686, 1582, 686, 448, 662, 1608, 682, 1582, 660, 1606, 662, 472, 686, 1580, 686, 1582, 660, 1606, 636, 1632, 660, 1606, 658, 1608, 684, 448, 686, 446, 662, 472, 662, 472, 662, 472, 662, 472, 662, 472, 662, 470, 686, 446, 688, 1580, 662, 1606, 638, 1630, 660, 42076, 9138, 2158, 688};
  sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
}

void sendExitCommand() {
  uint16_t raw[] = {2, 9134, 4426, 664, 472, 662, 1604, 662, 472, 686, 446, 662, 472, 686, 448, 686, 446, 686, 448, 686, 448, 686, 1604, 664, 448, 686, 1582, 660, 1628, 640, 1608, 684, 448, 686, 1582, 684, 1584, 636, 1632, 660, 474, 660, 472, 660, 1608, 660, 474, 660, 472, 662, 472, 686, 448, 684, 448, 662, 1608, 636, 1634, 658, 474, 684, 1582, 636, 1632, 686, 1582, 636, 42102, 9136, 2160, 664};
  sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
}

void sendNumCommand(int num) {
  if (num == 0) {
    uint16_t raw[] = {2, 9136, 4424, 688, 448, 662, 1630, 638, 472, 686, 446, 662, 472, 662, 472, 686, 446, 662, 472, 662, 470, 662, 1606, 660, 472, 662, 1604, 686, 1582, 662, 1606, 660, 472, 662, 1606, 660, 472, 686, 446, 662, 1628, 638, 1608, 660, 494, 640, 472, 686, 448, 662, 472, 686, 1580, 686, 1584, 660, 472, 660, 472, 662, 1604, 686, 1582, 662, 1606, 686, 1582, 662, 42080, 9138, 2158, 664};
    sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
  } else if (num == 1) {
    uint16_t raw[] = {2, 9136, 4426, 686, 448, 662, 1608, 658, 476, 658, 472, 686, 448, 686, 448, 686, 448, 686, 448, 660, 474, 660, 1606, 686, 448, 662, 1606, 662, 1606, 636, 1632, 660, 474, 660, 1608, 636, 1632, 684, 1604, 638, 474, 684, 1604, 638, 1606, 660, 472, 662, 472, 662, 472, 686, 448, 686, 446, 686, 1582, 660, 472, 660, 472, 686, 1584, 660, 1628, 662, 1584, 636, 42102, 9136, 2158, 662};
    sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
  } else if (num == 2) {
    uint16_t raw[] = {2, 9138, 4422, 690, 444, 688, 1580, 664, 470, 664, 470, 664, 470, 664, 470, 664, 470, 688, 444, 688, 446, 688, 1580, 662, 470, 688, 1580, 662, 1604, 688, 1580, 662, 472, 686, 1582, 662, 1604, 638, 1628, 686, 1580, 662, 1604, 688, 446, 688, 446, 688, 444, 688, 444, 664, 470, 688, 444, 688, 446, 688, 446, 688, 1578, 638, 1628, 664, 1626, 640, 1604, 688, 42042, 9138, 2156, 666};
    sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
  } else if (num == 3) {
    uint16_t raw[] = {2, 9110, 4450, 688, 448, 662, 1606, 660, 472, 686, 448, 686, 448, 662, 472, 662, 472, 660, 472, 686, 448, 686, 1604, 664, 448, 686, 1582, 660, 1608, 658, 1628, 638, 472, 662, 1606, 662, 1608, 634, 1632, 636, 498, 660, 472, 686, 448, 662, 472, 686, 448, 660, 472, 686, 448, 686, 448, 660, 1608, 660, 1628, 664, 1582, 636, 1632, 660, 1608, 660, 1628, 614, 42100, 9138, 2158, 686};
    sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
  } else if (num == 4) {
    uint16_t raw[] = {2, 9134, 4426, 664, 472, 684, 1584, 634, 498, 684, 448, 682, 452, 686, 448, 662, 472, 662, 472, 662, 472, 684, 1582, 662, 472, 662, 1606, 686, 1584, 660, 1608, 634, 498, 686, 1582, 660, 1608, 660, 472, 686, 448, 686, 1580, 662, 1606, 660, 474, 684, 448, 686, 448, 662, 472, 662, 1608, 660, 1608, 684, 448, 662, 472, 686, 1584, 634, 1630, 662, 1608, 658};
    sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
  } else if (num == 5) {
    uint16_t raw[] = {2, 9112, 4450, 688, 448, 662, 1606, 662, 472, 662, 472, 662, 472, 686, 446, 686, 448, 686, 448, 686, 448, 686, 1582, 636, 498, 684, 1586, 634, 1632, 660, 1608, 684, 448, 684, 1584, 660, 1608, 660, 472, 686, 448, 686, 448, 686, 1580, 688, 446, 662, 472, 686, 448, 686, 448, 662, 1608, 660, 1606, 660, 1606, 686, 448, 686, 1582, 686, 1582, 636, 1654, 638, 42080, 9138, 2158, 664};
    sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
  } else if (num == 6) {
    uint16_t raw[] = {2, 9110, 4452, 662, 474, 660, 1610, 658, 496, 638, 474, 660, 474, 684, 450, 660, 474, 660, 474, 660, 474, 686, 1584, 658, 474, 660, 1610, 632, 1656, 662, 1584, 660, 474, 660, 1630, 638, 1628, 638, 474, 660, 474, 684, 448, 662, 472, 660, 474, 660, 492, 642, 492, 664, 450, 660, 1626, 666, 1586, 632, 1656, 638, 1628, 638, 1610, 658, 1630, 638, 1630, 662, 42060, 9110, 2186, 684};
    sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
  } else if (num == 7) {
    uint16_t raw[] = {2, 9136, 4426, 664, 472, 686, 1584, 684, 446, 662, 472, 686, 446, 688, 446, 662, 472, 662, 472, 688, 446, 688, 1582, 660, 474, 660, 1606, 660, 1606, 660, 1606, 660, 472, 662, 1606, 660, 1606, 662, 470, 662, 472, 662, 1606, 660, 472, 662, 472, 662, 470, 688, 446, 686, 448, 662, 1606, 660, 1606, 36, 496, 662, 1606, 660, 1608, 660, 1606, 662, 1604, 662, 42074, 9136, 2158, 664};
    sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
  } else if (num == 8) {
    uint16_t raw[] = {2, 9112, 4450, 688, 446, 662, 1608, 658, 494, 638, 472, 660, 474, 686, 448, 686, 448, 686, 450, 660, 472, 684, 1584, 658, 474, 660, 1608, 660, 1606, 662, 1606, 636, 498, 660, 1608, 658, 1608, 658, 474, 684, 1582, 662, 1608, 684, 1584, 660, 494, 662, 450, 660, 472, 660, 472, 686, 1584, 660, 474, 660, 472, 686, 448, 660, 1608, 660, 1630, 638, 1606, 660, 42076, 9136, 2160, 686};
    sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
  } else if (num == 9) {
    uint16_t raw[] = {2, 9114, 4446, 666, 468, 664, 1604, 638, 496, 662, 470, 664, 470, 664, 468, 640, 494, 640, 494, 638, 494, 640, 1630, 614, 518, 638, 1630, 614, 1652, 638, 1652, 592, 518, 614, 1654, 614, 1674, 592, 520, 614, 1654, 612, 1654, 614, 518, 614, 520, 614, 520, 614, 520, 614, 520, 614, 1654, 614, 520, 614, 520, 614, 1654, 614, 1654, 614, 1652, 614, 1652, 614, 42124, 9116, 2180, 666};
    sendRawCommand(raw, sizeof(raw)/sizeof(raw[0]));
  }
}

// --------------------
// Webpage (Optimized JavaScript)
// --------------------

String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body { font-family: Arial, sans-serif; text-align: center; background-color: #1e1e1e; margin: 0; padding: 20px; color: white; }
.remote-body { width: 260px; background-color: #2b2b2b; margin: 0 auto; padding: 25px 15px; border-radius: 35px; box-shadow: 0px 8px 25px rgba(0,0,0,0.6); border: 2px solid #3a3a3a; }
.row-3 { display: grid; grid-template-columns: repeat(3, 1fr); gap: 12px; margin-bottom: 15px; align-items: center; }
button { background-color: #444; color: #ddd; border: none; padding: 10px 5px; font-size: 14px; font-weight: bold; border-radius: 6px; cursor: pointer; box-shadow: inset 0px 1px 3px rgba(255,255,255,0.2), 0px 3px 5px rgba(0,0,0,0.4); user-select: none; -webkit-user-select: none; }
button:active { transform: scale(0.95); background-color: #666; }

.btn-power { background-color: #d9534f; color: white; border-radius: 50%; width: 45px; height: 45px; padding: 0; justify-self: start; }
.btn-mute { background-color: #555; font-size: 11px; border-radius: 50%; width: 42px; height: 42px; padding: 0; }
.btn-recall { background-color: #555; font-size: 10px; border-radius: 50%; width: 42px; height: 42px; padding: 0; }

.dpad-container { position: relative; width: 160px; height: 160px; margin: 20px auto; background: #3a3a3a; border-radius: 50%; box-shadow: inset 0 4px 10px rgba(0,0,0,0.5); }
.dpad-btn { position: absolute; background: transparent; box-shadow: none; border: none; color: #aaa; font-size: 20px; padding: 0; width: 45px; height: 45px; }
.dpad-btn:active { color: white; }
.btn-up { top: 5px; left: 58px; }
.btn-down { bottom: 5px; left: 58px; }
.btn-left { top: 58px; left: 5px; }
.btn-right { top: 58px; right: 5px; }
.btn-ok { position: absolute; top: 53px; left: 53px; width: 54px; height: 54px; border-radius: 50%; background: #4f4f4f; color: white; font-size: 16px; box-shadow: 0 3px 6px rgba(0,0,0,0.4); }

.label { font-size: 11px; color: #888; text-transform: uppercase; margin-top: -10px; margin-bottom: 10px; font-weight: bold; }
</style>
</head>
<body>

<div class="remote-body">
  <div class="row-3">
    <button class="btn-power" onclick="sendCmd('/power')">⏻</button>
    <div></div>
    <div></div>
  </div>
  
  <div class="row-3">
    <button class="btn-mute" onclick="sendCmd('/mute')">Mute</button>
    <div></div>
    <button class="btn-recall" onclick="sendCmd('/recall')">Recall</button>
  </div>

  <div class="label" style="margin-top: 5px;">CH+</div>
  <div class="dpad-container">
    <button class="dpad-btn btn-up" onclick="sendCmd('/up')">▲</button>
    <button class="dpad-btn btn-left" onclick="sendCmd('/left')">◀</button>
    <button class="btn-ok" onclick="sendCmd('/ok')">OK</button>
    <button class="dpad-btn btn-right" onclick="sendCmd('/right')">▶</button>
    <button class="dpad-btn btn-down" onclick="sendCmd('/down')">▼</button>
  </div>
  <div class="label">CH-</div>

  <div class="row-3">
    <button onclick="sendCmd('/menu')">MENU</button>
    <div></div>
    <button onclick="sendCmd('/exit')">EXIT</button>
  </div>

  <div class="row-3"><button onclick="sendCmd('/num1')">1</button><button onclick="sendCmd('/num2')">2</button><button onclick="sendCmd('/num3')">3</button></div>
  <div class="row-3"><button onclick="sendCmd('/num4')">4</button><button onclick="sendCmd('/num5')">5</button><button onclick="sendCmd('/num6')">6</button></div>
  <div class="row-3"><button onclick="sendCmd('/num7')">7</button><button onclick="sendCmd('/num8')">8</button><button onclick="sendCmd('/num9')">9</button></div>
  <div class="row-3"><div></div><button onclick="sendCmd('/num0')">0</button><div></div></div>
</div>

<script>
// Queue system to prevent multi-tap dropouts
let commandQueue = [];
let isSending = false;

function sendCmd(endpoint) {
  commandQueue.push(endpoint);
  processQueue();
}

async function processQueue() {
  if (isSending || commandQueue.length === 0) return;
  isSending = true;
  
  const endpoint = commandQueue.shift();
  try {
    // "keepalive" prevents the browser from stalling on back-to-back taps
    await fetch(endpoint, { keepalive: true });
  } catch (err) {
    console.error("Transmission failed", err);
  }
  
  // Artificial gap between macro numbers to let the TV process them safely
  setTimeout(() => {
    isSending = false;
    processQueue();
  }, 120); 
}
</script>

</body>
</html>
)rawliteral";

// --------------------
// Web Handlers
// --------------------

void handleRoot()  { server.send(200, "text/html", page); }
void handlePower() { server.send(200, "text/plain", "OK"); sendPowerCommand(); }
void handleOK()    { server.send(200, "text/plain", "OK"); sendOKCommand(); }
void handleUp()    { server.send(200, "text/plain", "OK"); sendUpCommand(); }
void handleDown()  { server.send(200, "text/plain", "OK"); sendDownCommand(); }
void handleLeft()  { server.send(200, "text/plain", "OK"); sendLeftCommand(); }
void handleRight() { server.send(200, "text/plain", "OK"); sendRightCommand(); }
void handleMute()  { server.send(200, "text/plain", "OK"); sendMuteCommand(); }
void handleRecall(){ server.send(200, "text/plain", "OK"); sendRecallCommand(); }
void handleMenu()  { server.send(200, "text/plain", "OK"); sendMenuCommand(); }
void handleExit()  { server.send(200, "text/plain", "OK"); sendExitCommand(); }

void handleNum0() { server.send(200, "text/plain", "OK"); sendNumCommand(0); }
void handleNum1() { server.send(200, "text/plain", "OK"); sendNumCommand(1); }
void handleNum2() { server.send(200, "text/plain", "OK"); sendNumCommand(2); }
void handleNum3() { server.send(200, "text/plain", "OK"); sendNumCommand(3); }
void handleNum4() { server.send(200, "text/plain", "OK"); sendNumCommand(4); }
void handleNum5() { server.send(200, "text/plain", "OK"); sendNumCommand(5); }
void handleNum6() { server.send(200, "text/plain", "OK"); sendNumCommand(6); }
void handleNum7() { server.send(200, "text/plain", "OK"); sendNumCommand(7); }
void handleNum8() { server.send(200, "text/plain", "OK"); sendNumCommand(8); }
void handleNum9() { server.send(200, "text/plain", "OK"); sendNumCommand(9); }

// --------------------
// Setup
// --------------------

void setup() {
  Serial.begin(115200);
  pinMode(TX_PIN, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // CRITICAL FIX: Disables Wi-Fi modem sleep, keeping the ping snappy
  esp_wifi_set_ps(WIFI_PS_NONE);

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/power", handlePower);
  server.on("/ok", handleOK);
  server.on("/up", handleUp);
  server.on("/down", handleDown);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/mute", handleMute);
  server.on("/recall", handleRecall);
  server.on("/menu", handleMenu);
  server.on("/exit", handleExit);
  
  server.on("/num0", handleNum0);
  server.on("/num1", handleNum1);
  server.on("/num2", handleNum2);
  server.on("/num3", handleNum3);
  server.on("/num4", handleNum4);
  server.on("/num5", handleNum5);
  server.on("/num6", handleNum6);
  server.on("/num7", handleNum7);
  server.on("/num8", handleNum8);
  server.on("/num9", handleNum9);

  server.begin();
  Serial.println("Server Started");
}

void loop() {
  server.handleClient();
}