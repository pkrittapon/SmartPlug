BLYNK_WRITE(V23) {         //man reset kWh
  int resetManual = param.asInt();
  if (selectReset == 2 && resetManual == 1) {
    pzem.resetEnergy();
    cost_old = 0;
    EEPROM.put(0, cost_old); // put data EEPROM
    EEPROM.commit();
    Blynk.virtualWrite(V30, "add", count_table, String(count_table) + " | " + currentDate + " - " + currentTime + "Man reset kWh", 0); //Add data to table
    EEPROM_count();
  }
}

unsigned long last_time;
bool buttonResetTable;
BLYNK_WRITE(V24) { //reset table
  buttonResetTable = param.asInt();

  if (buttonResetTable == HIGH) {
    last_time = millis();
  }

}

void resetTable() {
  if (buttonResetTable == 1 && millis() - last_time > 5000) { //กดค้าง 5 Sec เพื่อ reset table
    last_time = millis();
    Blynk.virtualWrite(V30, "clr"); //Clear table
    count_table = 0;
    EEPROM.put(30, count_table); // put data EEPROM
    EEPROM.commit();
    Serial.println("Reset");
  }

}
