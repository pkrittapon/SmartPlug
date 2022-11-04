//ICACHE_RAM_ATTR void checkButton1() {
//  unsigned long checkHold = millis();
//  buttonState1=digitalRead(buttonPin1);
//  while ( buttonState1 == LOW ) {
//    unsigned long enterKey = millis() - checkHold;
//    buttonState1 = digitalRead(buttonPin1);
////    Serial.println(enterKey);
//    if (enterKey > 125) {
//      state1 = !state1;
//      if (state1) {
//        led1.on();
//      }
//      else {
//        led1.off();
//      }
//      digitalWrite(relay1, !state1);
//      return;
//    }
//  }
//}
//
//ICACHE_RAM_ATTR void checkButton2() {
//  unsigned long checkHold = millis();
//  buttonState2=digitalRead(buttonPin2);
//  while ( buttonState2 == LOW ) {
//    unsigned long enterKey = millis() - checkHold;
//    buttonState2 = digitalRead(buttonPin2);
////    Serial.println(enterKey);
//    if (enterKey > 125) {
//      state2 = !state2;
//      if (state2) {
//        led2.on();
//      }
//      else {
//        led2.off();
//      }
//      digitalWrite(relay2, !state2);
//      return;
//    }
//  }
//}
//
//ICACHE_RAM_ATTR void checkButton3() {
//  unsigned long checkHold = millis();
//  buttonState3=digitalRead(buttonPin3);
//  while ( buttonState3 == LOW ) {
//    unsigned long enterKey = millis() - checkHold;
//    buttonState3 = digitalRead(buttonPin3);
////    Serial.println(enterKey);
//    if (enterKey > 125) {
//      state3 = !state3;
//      if (state3) {
//        led3.on();
//      }
//      else {
//        led3.off();
//      }
//      digitalWrite(relay3, !state3);
//      return;
//    }
//  }
//}
//
//ICACHE_RAM_ATTR void checkButton4() {
//  unsigned long checkHold = millis();
//  buttonState4=digitalRead(buttonPin4);
//  while ( buttonState4 == LOW ) {
//    unsigned long enterKey = millis() - checkHold;
//    buttonState4 = digitalRead(buttonPin4);
////    Serial.println(enterKey);
//    if (enterKey > 125) {
//      state4 = !state4;
//      if (state4) {
//        led4.on();
//      }
//      else {
//        led4.off();
//      }
//      digitalWrite(relay4, !state4);
//      return;
//    }
//  }
//}
