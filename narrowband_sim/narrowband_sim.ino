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
//Wideband magic numbers
int rich = 583;
int lean = 646;
int stoich = 614;
//Narrow max AFR
int rich_max = 358; 
int lean_max = 920; 
int range = lean_max - rich_max;

void set_narrow_signal(int val){
  Serial.println(val);
  if(val < rich){
    analogWrite(analog_out, 42); //~850mV duty cycle
  }
  else if(val > lean){
    analogWrite(analog_out, 9); //~175 mV
  }
  else{
    analogWrite(analog_out, 25); 
  }
}
void set_variable_narrow_signal(int val){
  
}
void setup() {
  Serial.begin(9600);
  pinMode(analog_out, OUTPUT);
}
/*
 * narrowband sim
 */
void loop() {
  //583 ~= 14.07 rich condition
  //614 ~= 14.7 stoich
  //646 ~= 14.98 lean condition
  ox_val = analogRead(analog_pin);
  set_narrow_signal(ox_val);
}
