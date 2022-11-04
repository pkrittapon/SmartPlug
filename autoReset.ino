int selectReset;
BLYNK_WRITE(V31)
{
  selectReset = param.asInt(); // Get value v31 Selector
}
int dateReset;

BLYNK_WRITE(V33)
{
  dateReset = param.asInt(); // Get value v33 Date Input
}


BLYNK_WRITE(V34) { // Input time ดึงค่าเวลา
  TimeInputParam t(param);
  Hour = t.getStartHour();
  Minute = t.getStartMinute();
  Second = t.getStartSecond();
}

void Check_time() {
  // You can call hour(), minute(), ... at any time
  // Please see Time library examples for details

  if (count == 0 && (getTime("hour") == Hour && (getTime("minute") == Minute))) { //time compare
    EEPROM.get(0, cost_old); //Get data EEPROM
    cost_today = cost_total - cost_old;
    Blynk.virtualWrite(V30, "add", count_table, String(count_table) + " | " + currentDate + " - " + currentTime + " cost : " + cost_today + " Baht", 0); //add data to table
    EEPROM_count();
    cost_old = cost_total; // set cost_total to cost_old
    EEPROM.put(0, cost_old); // put data EEPROM
    EEPROM.commit();
    if ((getTime("day") == dateReset && selectReset == 1)) { //auto reset kWh
      Blynk.virtualWrite(V30, "add", count_table, String(count_table) + " | " +  currentDate + " - " + currentTime + " Bill : " + cost_total + " Baht", 0); //add data to table
      EEPROM_count();
      unsigned long present = millis();
      while ((millis() - present <= 500)) {
        if (millis() - present >= 500) {
          pzem.resetEnergy();
          cost_old = 0;
        }
      }
      count = 1;
    } else if ((getTime("minute") != Minute && count > 0)) {
      count = 0;
    }
  }
}
