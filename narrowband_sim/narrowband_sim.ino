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
int ox_val = 0;
int offset_ox_val = 0;
float temp = 0;
int o2_signal = 0;
float aem_vol_num = 2.375;
float aem_offset_num = 7.3125;
float nar_voltage = 0;
float magnitude = 0;
//Wideband magic numbers
int stoich = 637; //14.7
float afr_range = 1024;


float calc_afr(int voltage){
 afr = (aem_vol_num * voltage) + aem_offset_num;
 return afr;
}
void set_narrow_signal(int afr){
  nar_voltage = (-0.77*afr) + 11.77;
  o2_signal = nar_voltage * 255;
  Serial.print(" ");
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
  Serial.print(ox_val);
  _vol = (analog_val / afr_range) * 5;
}
