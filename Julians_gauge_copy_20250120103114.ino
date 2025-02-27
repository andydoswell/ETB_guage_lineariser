/* Tank in on A0, Fed from a 200 ohm resistor from the 5V rail.
 A 2N7000 FET is employed to drive the gauge. It's gate is fed from A0, via a 100 ohm resistor. The gauge output is connected from the drain via a 4.7 ohm resistor
 The FET source is connected to GND
*/
int raw;
uint32_t value;
int calZero = 10;
float calSpan = 0.8888;
void setup() {
  pinMode(A0, INPUT);
}

void loop() {
  for (int i = 0; i <= 99; i++) {
    value += analogRead(A0);
    delay(1);
  }

  value = value / 100;
  float volts = (value * 5.0) / 1024.0;
  float r = (volts * 200) / (5 - volts);
  float tankPercent = 104 + -0.94 * r + (2.76E-3 * pow(r, 2)) + (-2.95E-6 * pow(r, 3));
  int PWM = (120 + -5.24E-3 * tankPercent) + (0.0311 * pow(tankPercent, 2)) + (-1.97E-4 * pow(tankPercent, 3));
  PWM = constrain(PWM, 0, 255);
  analogWrite(3, PWM);
}
