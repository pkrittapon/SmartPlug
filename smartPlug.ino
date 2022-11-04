#define BLYNK_PRINT Serial

#include <time.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TridentTD_LineNotify.h>
#include <PZEM004Tv30.h>
#include <EEPROM.h>

#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define relay1 D3
#define relay2 D5
#define relay3 D6
#define relay4 D7

#define pzem_rx D2
#define pzem_tx D1


PZEM004Tv30 pzem(pzem_rx, pzem_tx);

BlynkTimer timer;

int timezone = 7 * 3600; //set timezone
int dst = 0; //set Date Swing Time

float voltage, current, power, energy, frequency, pf;

// Blynk Auth Token
char auth[] = "m5OPODgKSimGWrpyYbDH14x5mDHwfAh6";

// WiFi
char ssid[] = "Tenda_6DBD";
char pass[] = "51647649";
char lineToken[] = "LbGh90YFg5brkraCxWAtxjf4te4pAuUGV7rwZfgiS3J";

bool state1 = 0;
bool state2 = 0;
bool state3 = 0;
bool state4 = 0;
bool buttonState1 = 0;
bool buttonState2 = 0;
bool buttonState3 = 0;
bool buttonState4 = 0;

bool blynkState1 = 0;
bool blynkState2 = 0;
bool blynkState3 = 0;
bool blynkState4 = 0;

int count = 0;
int count_table = 0;
float cost_old = 0;
float cost_total = 0;
float cost_today = 0;
String currentDate, currentTime;

int Hour, Minute, Second;

WidgetLED led1(V0);
WidgetLED led2(V1);
WidgetLED led3(V2);
WidgetLED led4(V3);

int openHour1, openHour2, openHour3, openHour4;
int openMinute1, openMinute2, openMinute3, openMinute4;
int closeHour1, closeHour2, closeHour3, closeHour4;
int closeMinute1, closeMinute2, closeMinute3, closeMinute4;

void controlRelay(int ch, bool state) {
  if (ch == 1) {
    if (state == 1) {
      state1 = 1;
      led1.on();
    }
    else {
      state1 = 0;
      led1.off();
    }
  }
  if (ch == 2) {
    if (state == 1) {
      state2 = 1;
      led2.on();
    }
    else {
      state2 = 0;
      led2.off();
    }
  }
  if (ch == 3) {
    if (state == 1) {
      state3 = 1;
      led3.on();
    }
    else {
      state3 = 0;
      led3.off();
    }
  }
  if (ch == 4) {
    if (state == 1) {
      state4 = 1;
      led4.on();
    }
    else {
      state4 = 0;
      led4.off();
    }
  }
  digitalWrite(relay1, !state1);
  digitalWrite(relay2, !state2);
  digitalWrite(relay3, !state3);
  digitalWrite(relay4, !state4);
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(256);
  EEPROM.get(30, count_table);
  Serial.setDebugOutput(true);
  //  setSyncInterval(10 * 60);
  //  pinMode(buttonPin1, INPUT_PULLUP);
  //  pinMode(buttonPin2, INPUT_PULLUP);
  //  pinMode(buttonPin3, INPUT_PULLUP);
  //  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  //  attachInterrupt(buttonPin1, checkButton1, FALLING);
  //  attachInterrupt(buttonPin2, checkButton2, FALLING);
  //  attachInterrupt(buttonPin3, checkButton3, FALLING);
  //  attachInterrupt(buttonPin4, checkButton4, FALLING);
  Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);
  LINE.setToken(lineToken);
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");     //ดึงเวลาจาก Server
  Blynk.syncAll();
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void EEPROM_count() {
  count_table++;
  EEPROM.put(30, count_table); // put data EEPROM
  EEPROM.commit();
}
unsigned long lastAlert = 0;
bool isNormalCurrent() {
  current = pzem.current();
  //  current = 9.6;
  if (current < 9.0) {
    return true;
  }
  else {
    if (current < 9.5) {
      if (millis() - lastAlert > 10000) {
        //        LINE.notify("ขณะนี้กระแสคือ " + String(current) + " A\nถ้ากระแสเกิน 9.5 A จะปิดสวิตช์เพื่อความปลอดภัย");
        lastAlert = millis();
      }
      return true;
    }
    else {
      //      LINE.notify("ขณะนี้กระแสคือ " + String(current) +"A\nกระแสสูงเกินไป ปิดสวิตช์ทุกช่องเพิ่อความปลอดภัย");
      return false;
    }
  }
}

//ดูdatasheet pzemไว้ตอบคำถาม
void loop() {
  ArduinoOTA.handle();
  Blynk.run();
  readVA();
  calCost();
  auto_OnOff();
//  if (isNormalCurrent()) { //uncomment when connect pzem-004t ไม่แน่ใจว่าปิดแล้วเริ่มใหม่จะปิดอยู่มั้ย
//    digitalWrite(relay1, !state1);
//    digitalWrite(relay2, !state2);
//    digitalWrite(relay3, !state3);
//    digitalWrite(relay4, !state4);
//  }
//  else {
//    digitalWrite(relay1, HIGH);
//    digitalWrite(relay2, HIGH);
//    digitalWrite(relay3, HIGH);
//    digitalWrite(relay4, HIGH);
//    led1.off();
//    led2.off();
//    led3.off();
//    led4.off();
//  }
  resetTable();
  sendCostDaily();
}
