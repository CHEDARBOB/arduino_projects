/*
int adc_res = 1023;
int lean_voltage = ; //mV
int rich_voltage = ; //mV
int max_duty_cycle = 255;
int max_wideband_voltage = 5000; //mV
int max_narrowband_voltage = 1000; //mV
*/

int analog_pin = A0;
int analog_out = 9;
int analog_val = 0;
int offset_ox_val = 0;
float temp = 0;
int o2_signal = 0;
float _vol = 0.0;
float afr = 0.0;
float aem_vol_num = 2.375;
float aem_offset_num = 7.3125;
float nar_voltage = 0.0;
float magnitude = 0;
//Wideband magic numbers
int stoich = 637; //14.7
float afr_range = 1024;


float calc_afr(float voltage){
 afr = (aem_vol_num * voltage) + aem_offset_num;
 if(afr < 14.0){
   afr = 14;
 }
 else if(afr > 15.2){
  afr = 15.2;
 }
 Serial.print(" ");
 Serial.print(afr);
 return afr;
}
void set_narrow_signal(float _afr){
  Serial.print(" ");
  nar_voltage = (-0.83*_afr) + 12.67;
  //Serial.println(nar_voltage);
  o2_signal = 242*nar_voltage;
  Serial.println(o2_signal);
  analogWrite(analog_out, o2_signal);
}
void setup() {
  //delay(20000);
  Serial.begin(9600);
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
