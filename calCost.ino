float pureCost;
void calCost() {
  float rate_1 = 0;
  float rate_2 = 0;
  float rate_3 = 0;
  //int x = (int)energy%1;
  if (energy > 0 && energy <= 150) {   //หน่วยที่ 0-150
    rate_1 = energy * 3.2484;
  }
  if (energy > 150) {
    rate_1 = 150 * 3.2484;
  }

  if (energy >= 151 && energy <= 400) { //หน่วยที่ 151-400
    rate_2 = (energy - 150) * 4.2218;
  }
  if (energy > 400) { //เกิน 400
    rate_2 = 250 * 4.2218;
    rate_3 = (energy - 400) * 4.4217;
  }
  float ft = energy * (-0.1532);
  float total_vat = (rate_1 + rate_2 + rate_3 + ft + 38.22) * 0.07;
  float total = (rate_1 + rate_2 + rate_3 + ft + 38.22) + total_vat;
  cost_total = total;
  pureCost = rate_1 + rate_2 + rate_3;
  Blynk.virtualWrite(V20, pureCost, 1);
  Blynk.virtualWrite(V21, total, 1);
}
