int rpm_sig_out = 4
void setup() {
  pinMode(rpm_sig_out, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(rpm_sig_out, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(10);
  digitalWrite(rpm_sig_out, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
}
