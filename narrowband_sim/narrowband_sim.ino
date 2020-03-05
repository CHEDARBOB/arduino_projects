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
int rich = 628;
int lean = 646;
int stoich = 637;
//Narrow max AFR
int rich_max = 611; 
int lean_max = 662; 
int range = lean_max - rich_max;

void set_narrow_signal(int val){
  //mixture is rich
  if(val < rich){
    Serial.print("rich ");
    
    temp = 135;
    if(val < rich_max){
      temp = 195;
    }
    analogWrite(analog_out, temp);
  }
  //mixture is lean
  else if(val > lean){
    Serial.print("Lean ");
    //Serial.println(val);
    temp = 10;
    if(val > lean_max){
      temp = 0;
    }
    analogWrite(analog_out, temp);
  }   
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
  Serial.println(ox_val);
  ox_val = analogRead(analog_pin);
  if(ox_val > 350){
    set_narrow_signal(ox_val);
  }
  else{
    analogWrite(analog_out, 85);
  }
}
