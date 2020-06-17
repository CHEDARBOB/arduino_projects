//rpm variables
bool edge_a = true;
bool edge_b = false;
bool reset = false;
const int rpm_pin = 3;
const int vics_signal = 4;
const int vics_LED = LED_BUILTIN;
const int desired_rpm = 4200;
int rpm_signal = LOW;
int rpm = 0;
unsigned long rising_edge_a = 0;
unsigned long rising_edge_b = 0;
/////////////////////////////////
/////////////////////////////////
// afr variables
int analog_pin = A0;
int analog_out = 9;
int analog_val = 0;
int count = 0;
int o2_signal = 0;
float _vol = 0.0;
float afr = 0.0;
//Wideband magic numbers
float aem_vol_num = 2.375;
float mod_vol_num = 2.6;
float aem_offset_num = 7.3125;
float mod_offset_num = 0;
float nar_voltage = 0.0;
float afr_range = 1024;
/////////////////////////
/////////////////////////
//afr helper functions
float calc_afr(float voltage){
 afr = (mod_vol_num * voltage) + aem_offset_num;
 if(afr < 14.30){
   afr = 14.30;
 }
 else if(afr > 14.50){
  afr = 15.00;
 }
 Serial.print(" ");
 Serial.println(afr);
 return afr;
}
void set_narrow_signal(float _afr){
  //Serial.print(" ");
  //nar_voltage = abs((-1.0*_afr) + 15.20); //14.3 -- 15.0
  nar_voltage = abs((-1.214*_afr) + 18.314); //14.3 -- 15.0
  //nar_voltage = abs((-1.0*_afr) + 15.2); //14.2 -- 15.2
  //Serial.print(nar_voltage);
  //Serial.print(" ");
  o2_signal = 255*nar_voltage;
  Serial.print(nar_voltage);
  analogWrite(analog_out, o2_signal);
}
/////////////////////////////////
/////////////////////////////////
// rpm helper functions
// Calculate rpm based on half rotation (180deg). 
unsigned long calc_rpm(unsigned long _edge_a, unsigned long _edge_b){
  //period of 5.979 ms = ~5000 rpm
  float _period = _edge_b - _edge_a;
  int _rpm = ((60000*1000)/(_period*2));
  //Serial.print("rpm: ");
  //Serial.println(_rpm);
  return _rpm;
}
void open_valve(int _rpm){
  if(_rpm > desired_rpm){
    digitalWrite(vics_signal, LOW);
    digitalWrite(vics_LED, LOW);
  }
  else{
    digitalWrite(vics_signal, HIGH);
    digitalWrite(vics_LED, HIGH);
  }
}

void setup() {
  Serial.begin(9600);
  //startup
  int count = 0;
  while(count < 25){
    set_narrow_signal(14.90);
    delay(550);
    set_narrow_signal(14.3);
    delay(500);
    count++;
  }
  ///////////////////
  pinMode(rpm_pin, INPUT);
  pinMode(vics_signal, OUTPUT);
  pinMode(vics_LED, OUTPUT);
  digitalWrite(vics_LED, HIGH);
  digitalWrite(vics_signal, HIGH);
  //////////////////////////////
  //////////////////////////////
  analogReference(DEFAULT);
  pinMode(analog_out, OUTPUT);
}
/*
 * rpm_signal fires twice per engine revolution. 
 * take the period from rising edge to rising edge. 
 * 
 * Four states: 
 * First, HIGH rpm signal save current time in microseconds.
 * Second, LOW rpm signal, this ensures the system does not duplicate 
 * data for a singleton rpm signal.
 * Third, Following rpm HIGH signal. save current time in microseconds.
 * This represents the engine has traveled 180 degrees.
 * Fourth, following LOW rpm signal. bool states are reset and rpm is calculated.
 * VICS signal is set to LOW or HIGH based on engine rpm.
 */
void loop() {
  //afr control
  //610 ~= 14.39 rich condition
  //637 ~= 14.7 stoich
  //665 ~= 15.03 lean condition
  analog_val = analogRead(analog_pin);
  //Serial.print(analog_val);
  //Serial.print(" "); 
  _vol = (analog_val / afr_range) * 5;
  //Serial.print(_vol);
  afr = calc_afr(_vol);
  set_narrow_signal(afr);
  /////////////////////////////////
  /////////////////////////////////
  //rpm control
  //Serial.print("rpm signal: ");
  //Serial.println(digitalRead(rpm_pin));
  //state 0, set rising_edge_a.
  rpm_signal = !digitalRead(rpm_pin);
  //Serial.println(rpm_signal); 
  if(rpm_signal == HIGH && (edge_a == true && edge_b == false && reset == false)){
    rising_edge_a = micros();
    edge_a = false;
  }
  //state 1, low signal
  else if(rpm_signal == LOW && (edge_a == false && edge_b == false && reset == false)){ 
    edge_b = true;
  }
  //state 2, following High signal, set rising_edge_b (1/2 engine rotation)
  else if(rpm_signal == HIGH && (edge_a == false && edge_b == true && reset == false)){
    rising_edge_b = micros();
    edge_b = false;
    reset = true;
  }
  //state 3, reset, calculate/check rpm to open/close VICS valve.
  else if(rpm_signal == LOW && (edge_a == false && edge_b == false && reset == true)){
    edge_a = true;
    reset = false;
    //rpm pin is LOW and both edges are valid. 
    //If overflow: entire sample ignored.
    if(rising_edge_a < rising_edge_b){
      rpm = calc_rpm(rising_edge_a, rising_edge_b);
      open_valve(rpm);
    }
  }
}
