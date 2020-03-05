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
int temp = 0;
//Wideband magic numbers
int rich = 660;
int lean = 670;
int stoich = 614;
//Narrow max AFR
int rich_max = 630; 
int lean_max = 700; 
int range = lean_max - rich_max;

void set_narrow_signal(int val){
  //mixter is rich
  if(val < rich){
    temp = 135;
    //Serial.print("rich ");
    //Serial.println(val);
    if(val < rich_max){
      temp = 195;
    }
    analogWrite(analog_out, temp);
  }
  //mixter is lean
  else if(val > lean){
    //Serial.print("Lean ");
    temp = 20;
    //Serial.println(val);
    if(val > lean_max){
      temp = 0;
    }
    analogWrite(analog_out, temp);
  }   
}
void set_variable_narrow_signal(int val){
  
}
void setup() {
  //Serial.begin(9600);
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
  
  ox_val = analogRead(analog_pin);
  if(ox_val > 350){
    set_narrow_signal(ox_val);
  }
  else{
    analogWrite(analog_out, 85);
  }
}
