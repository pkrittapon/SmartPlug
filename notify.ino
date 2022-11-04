float todayCost;
float yesterdayCost = 0.00;

void sendCostDaily() {
  if (getTime("hour") == 6 && getTime("minute") == 30 && getTime("second") == 0) {
    EEPROM.get(60, yesterdayCost);
    todayCost = pureCost - yesterdayCost;
    LINE.notify(("Electricity Cost of ")
    + String(getTime("day")) + ("/")
    + String(getTime("month")) + ("/")
    + String(getTime("year"))
    + ("\nTotal : ") + String(todayCost)
    + (" Baht"));
    Serial.println("ma");
    yesterdayCost = todayCost;
    EEPROM.put(60, yesterdayCost); 
    EEPROM.commit();
  }
}
