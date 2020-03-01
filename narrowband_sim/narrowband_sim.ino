int analog_pin = A0;
int analog_out = 9;
int ox_val = 0;
int rich = 563;
int lean = 664;
void set_narrow_signal(int val){
  if(val < rich){
    analogWrite(analog_out, 15); //6% duty cycle
  }
  else if(val > lean){
    analogWrite(analog_out, 46);
  }
  else{
    analogWrite(analog_out, 25);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(analog_out, OUTPUT);
}
/*
 * narrowband sim
 */
void loop() {
  //563 ~= 13.84 rich condition
  //614 ~= 14.7 stoich
  //664 ~= 15.03 lean condition
  ox_val = analogRead(analog_pin);
  Serial.println(ox_val);
  set_narrow_signal(ox_val);
}
