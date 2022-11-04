unsigned long presentReadVA;
unsigned long prevoiusReadVA = 0;

void readVA() {
  presentReadVA = millis();
  if (presentReadVA - prevoiusReadVA > 2000) {
    voltage = pzem.voltage();
    if (voltage != NAN) {
      //      Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
      Blynk.virtualWrite(V15, voltage);
    } else {
      //      Serial.println("Error reading voltage");
    }

    current = pzem.current();
    if (current != NAN) {
      //      Serial.print("Current: "); Serial.print(current); Serial.println("A");
      Blynk.virtualWrite(V16, current);
    } else {
      //      Serial.println("Error reading current");
    }

    power = pzem.power();
    if (power != NAN) {
      //      Serial.print("Power: "); Serial.print(power); Serial.println("W");
      Blynk.virtualWrite(V17, power);
    } else {
      //      Serial.println("Error reading power");
    }

    energy = pzem.energy();
    if (energy != NAN) {
      //      Serial.print("Energy: "); Serial.print(energy, 3); Serial.println("kWh");
      Blynk.virtualWrite(V18, energy);
      //      Blynk.virtualWrite(V9, (voltage*current*pf));
    } else {
      //      Serial.println("Error reading energy");
    }

    frequency = pzem.frequency();
    if (frequency != NAN) {
      //      Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
      Blynk.virtualWrite(V19, frequency);
    } else {
      //      Serial.println("Error reading frequency");
    }

    pf = pzem.pf();
    if (pf != NAN) {
      //      Serial.print("PF: "); Serial.println(pf);
      Blynk.virtualWrite(V14, pf);
    } else {
      //      Serial.println("Error reading power factor");
    }
    //    Serial.println();
    prevoiusReadVA = presentReadVA;
  }
}
