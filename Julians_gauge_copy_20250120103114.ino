/* Tank in on A0, Fed from a 200 ohm resistor from the 5V rail.
 A 2N7000 FET is employed to drive the gauge. It's gate it fed from A0, via a 100 ohm resistor. The gauge output is connected from the drain via a 4.7 ohm resistor
 The FET source is connected to GND
*/
int raw;
uint32_t value;
int calZero = 10;
float calSpan = 0.8888;
void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 100; i++) {
    value = value + analogRead(A0);
    delay(1);
  }
  raw = value / 100;
  float volts = (raw * 5.0) / 1024.0;
  float resistance = (volts * 200) / (5 / volts) + calZero * calSpan;
  float tankPercent = 103 + -0.905 * resistance + (0.00197 * pow(resistance, 2));
  int PWM = (120 + 1.05 * tankPercent) + (0.00229 * pow(tankPercent, 2));
  analogWrite(3, PWM);
  value = 0;
  delay(100);
}
