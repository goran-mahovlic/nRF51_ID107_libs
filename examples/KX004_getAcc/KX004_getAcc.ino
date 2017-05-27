/*
 * Simple 
 */

#include "KX022.h"

KX022 acc(acc);

void setup() {
  // put your setup code here, to run once:
  acc.init();
}

void loop() {
  Serial.println((float)acc.getAccel(0));
  Serial.println((float)acc.getAccel(1));
  Serial.println((float)acc.getAccel(2));
  delay(2000);
}
