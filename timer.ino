BLYNK_WRITE(V41) {
  TimeInputParam t(param);  // Process start time
  openHour1 = t.getStartHour();
  openMinute1 = t.getStartMinute();
  closeHour1 = t.getStopHour();
  closeMinute1 = t.getStopMinute();
  Serial.println("Ch1 On Time : " + String(openHour1) + ":" + String(openMinute1));
  Serial.println("Ch1 Off Time : " + String(closeHour1) + ":" + String(closeMinute1));
}

BLYNK_WRITE(V42) {
  TimeInputParam t(param);  // Process start time
  openHour2 = t.getStartHour();
  openMinute2 = t.getStartMinute();
  closeHour2 = t.getStopHour();
  closeMinute2 = t.getStopMinute();
  Serial.println("Ch2 On Time : " + String(openHour2) + ":" + String(openMinute2));
  Serial.println("Ch2 Off Time : " + String(closeHour2) + ":" + String(closeMinute2));
}

BLYNK_WRITE(V43) {
  TimeInputParam t(param);  // Process start time
  openHour3 = t.getStartHour();
  openMinute3 = t.getStartMinute();
  closeHour3 = t.getStopHour();
  closeMinute3 = t.getStopMinute();
  Serial.println("Ch3 On Time : " + String(openHour3) + ":" + String(openMinute3));
  Serial.println("Ch3 Off Time : " + String(closeHour3) + ":" + String(closeMinute3));
}

BLYNK_WRITE(V44) {
  TimeInputParam t(param);  // Process start time
  openHour4 = t.getStartHour();
  openMinute4 = t.getStartMinute();
  closeHour4 = t.getStopHour();
  closeMinute4 = t.getStopMinute();
  Serial.println("Ch4 On Time : " + String(openHour4) + ":" + String(openMinute4));
  Serial.println("Ch4 Off Time : " + String(closeHour4) + ":" + String(closeMinute4));
}

int key1 = 0, key2 = 0, key3 = 0, key4 = 0;
void auto_OnOff() {
  if ((openHour1 == getTime("hour")) && (openMinute1 == getTime("minute")) && key1 == 0) {
    digitalWrite(relay1,LOW);
    LINE.notify("Auto open Ch1");
    key1 = 1;
  }
  if ((closeHour1 == getTime("hour")) && (closeMinute1 == getTime("minute")) && key1 == 1) {
    digitalWrite(relay1,HIGH);
    LINE.notify("Auto close Ch1");
    key1 = 0;
  }

  if ((openHour2 == getTime("hour")) && (openMinute2 == getTime("minute")) && key2 == 0) {
    digitalWrite(relay2,LOW);
    LINE.notify("Auto open Ch2");
    key2 = 1;
  }
  if ((closeHour2 == getTime("hour")) && (closeMinute2 == getTime("minute")) && key2 == 1) {
    digitalWrite(relay2,HIGH);
    LINE.notify("Auto close Ch2");
    key2 = 0;
  }

  if ((openHour3 == getTime("hour")) && (openMinute3 == getTime("minute")) && key3 == 0) {
    digitalWrite(relay3,LOW);
    LINE.notify("Auto open Ch3");
    key3 = 1;
  }
  if ((closeHour3 == getTime("hour")) && (closeMinute3 == getTime("minute")) && key3 == 1) {
    digitalWrite(relay3,HIGH);
    LINE.notify("Auto close Ch3");
    key3 = 0;
  }

  if ((openHour4 == getTime("hour")) && (openMinute4 == getTime("minute")) && key4 == 0) {
    digitalWrite(relay4,LOW);
    LINE.notify("Auto open Ch4");
    key4 = 1;
  }
  if ((closeHour4 == getTime("hour")) && (closeMinute4 == getTime("minute")) && key4 == 1) {
    digitalWrite(relay4,HIGH);
    LINE.notify("Auto close Ch4");
    key4 = 0;
  }
}
