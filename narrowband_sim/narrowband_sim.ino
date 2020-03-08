/*
int adc_res = 1023;
int lean_voltage = ; //mV
int rich_voltage = ; //mV
int max_duty_cycle = 255;
int max_wideband_voltage = 5000; //mV
int max_narrowband_voltage = 1000; //mV
*/

int analog_pin = A0;
int analog_out = 6;
int ox_val = 0;
int offset_ox_val = 0;
float temp = 0;
int o2_signal = 0;
float magnitude = 0;
//Wideband magic numbers
int stoich = 637; //14.7
float afr_range = 20;

float set_magnitude(int afr){
 temp = stoich - afr;
 magnitude = (temp / afr_range);
 return abs(magnitude);
}
void set_narrow_signal(int val){
  //rich
  if(val < stoich){
    o2_signal = 160*set_magnitude(val);
    if(o2_signal < 120){
      o2_signal = 130;
    }
  }
  //lean
  else{
    o2_signal = 40-(40*set_magnitude(val));
  }
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
  ox_val = analogRead(analog_pin);
  Serial.print(ox_val);
  if(ox_val < (stoich - afr_range)){
    offset_ox_val = stoich - afr_range;
    set_narrow_signal(offset_ox_val);
  }
  else if(ox_val > (stoich + afr_range)){
    offset_ox_val = stoich + afr_range;
    set_narrow_signal(offset_ox_val);
  }
  else{
    set_narrow_signal(ox_val);
  }
}
