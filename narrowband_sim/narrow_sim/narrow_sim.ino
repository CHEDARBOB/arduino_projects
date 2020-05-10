int analog_out = 9;

void setup() {
  // put your setup code here, to run once:
  analogReference(DEFAULT);
  pinMode(analog_out, OUTPUT);
}

void loop() {
  //analogWrite(analog_out, 30);
  //delay(1000);
  analogWrite(analog_out, 127);
  delay(2000);
  //analogWrite(analog_out, 180);
  //delay(1000);
  analogWrite(analog_out, 255);
  delay(2000);
  //analogWrite(analog_out, 0);

}
