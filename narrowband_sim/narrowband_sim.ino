int analog_pin = A0;
int analog_out = 6;
int analog_val = 0;
int count = 0;
int o2_signal = 0;
float _vol = 0.0;
float afr = 0.0;
//Wideband magic numbers
float aem_vol_num = 2.375;
float aem_offset_num = 7.3125;
//
float nar_voltage = 0.0;
float afr_range = 1024;

float calc_afr(float voltage){
 afr = (aem_vol_num * voltage) + aem_offset_num;
 if(afr < 14.6){
   afr = 14.6;
 }
 else if(afr > 14.8){
  afr = 14.8;
 }
 Serial.print(" ");
 Serial.print(afr);
 return afr;
}
void set_narrow_signal(float _afr){
  Serial.print(" ");
  nar_voltage = abs((-4.62*_afr) + 68.50);
  Serial.print(nar_voltage);
  Serial.print(" ");
  //Serial.println(nar_voltage);
  o2_signal = 255*nar_voltage;
  Serial.println(o2_signal);
  analogWrite(analog_out, o2_signal);
}
void setup() {
  //delay(20000);
  Serial.begin(115200);
  analogReference(DEFAULT);
  pinMode(analog_out, OUTPUT);
}
/*
 * narrowband sim
 */
void loop() {
  //610 ~= 14.39 rich condition
  //637 ~= 14.7 stoich
  //665 ~= 15.03 lean condition
  analog_val = analogRead(analog_pin); 
  _vol = (analog_val / afr_range) * 5;
  Serial.print(_vol);
  afr = calc_afr(_vol);
  set_narrow_signal(afr);
}
