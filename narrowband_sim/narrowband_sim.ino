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
int temp = 0;
int o2_signal = 0;
int magnitude = 0;
//Wideband magic numbers
int rich = 630; //AFR ~14.6
int rich_2 = 576; //14
int lean = 644; //AFR ~14.8
int lean_2 = 662; //15
int stoich = 637; //14.7
int afr_range = 100;

//if lean offset = 1. Rich, offset = 0.
int set_magnitude(int offset, int afr){
  temp = abs(stoich - afr);
  magnitude = offset - (afr_range / temp);
  return abs(magnitude);
}
void set_narrow_signal(int val){
  //rich
  if(val < stoich){
    o2_signal = 200*set_magnitude(0, val);
  }
  //lean
  else{
    o2_signal = 255*set_magnitude(1, val);
  }
  Serial.print(" ");
  Serial.println(o2_signal);
  analogWrite(o2_signal, analog_out);
}
void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT);
  pinMode(analog_out, OUTPUT);
}
/*
 * narrowband sim
 */
void loop() {
  //583 ~= 14.07 rich condition
  //614 ~= 14.7 stoich
  //646 ~= 14.98 lean condition
  Serial.print(ox_val);
  ox_val = analogRead(analog_pin);
  if(ox_val < (stoich - afr_range)){
    offset_ox_val = stoich - 100;
    set_narrow_signal(offset_ox_val);
  }
  else if(ox_val > (stoich + afr_range)){
    offset_ox_val = stoich + 100;
    set_narrow_signal(offset_ox_val);
  }
  else{
    set_narrow_signal(ox_val);
  }
}
