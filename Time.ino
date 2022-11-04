//เราสามารถดึงค่าต่าง ๆ ที่อยู่ในตัวแปร p_tm มาใช้ได้ดังนี้
//struct tm {
//  int tm_sec; /* วินาที, range 0 to 59 */
//  int tm_min; /* นาที, range 0 to 59 */
//  int tm_hour; /* ชั่วโมง, range 0 to 23 */
//  int tm_mday; /* วันที่, range 1 to 31 */
//  int tm_mon; /* เดือน, range 0 to 11 */
//  int tm_year; /* ปีคริสศักราช ตั้งแต่ 1900 */
//  int tm_wday; /* วัน, range 0 to 6 */
//  int tm_yday; /* วันใน 1 ปี, range 0 to 365 */
//  int tm_isdst; /* daylight saving time */
//};
////เช่น
//p_tm->tm_sec //ได้ค่า วินาที
//p_tm->tm_year //ได้ค่า คริสศักราช
//p_tm->tm_mday // ได้ค่าวันที่ 0-31
unsigned long presentTime;
unsigned long prevoiusTime;
String numDay[] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saterday"};
String numMonth[] = {"january", "february", "march", "april", "june", "july", "august", "september", "october", "november", "december"};

int getTime(String select) {
  presentTime = millis();
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  if (select == "hour") {
    return p_tm->tm_hour;
  }
  else if (select == "minute") {
    return p_tm->tm_min;
  }
  else if (select == "second") {
    return p_tm->tm_sec;
  }
  else if (select == "day") {
    return p_tm->tm_mday;
  }
  else if (select == "month") {
    return (p_tm->tm_mon+1);
  }
  else if (select == "year") {
    return (p_tm->tm_year+1900+543);
  }
}
