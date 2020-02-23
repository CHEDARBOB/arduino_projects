bool edge_a = true;
bool edge_b = false;
bool reset = false;
const int rpm_pin = 3;
const int vics_signal = 4;
const int vics_LED = LED_BUILTIN;
const int desired_rpm = 5200;
int rpm = 0;
int rpm_signal = LOW;
unsigned long rising_edge_a = 0;
unsigned long rising_edge_b = 0;

// Calculate rpm based on half rotation (180deg). 
unsigned long calc_rpm(unsigned long _edge_a, unsigned long _edge_b){
  //period of 5.979 ms = ~5000 rpm
  float _period = _edge_b - _edge_a;
  int _rpm = ((60000*1000)/(_period*2));
  return _rpm;
}
void open_valve(int _rpm){
  if(_rpm > desired_rpm){
    digitalWrite(vics_signal, HIGH);
    digitalWrite(vics_LED, HIGH);
  }
  else{
    digitalWrite(vics_signal, LOW);
    digitalWrite(vics_LED, LOW);
  }
}

void setup() {
  pinMode(rpm_pin, INPUT);
  pinMode(vics_signal, OUTPUT);
  pinMode(vics_LED, OUTPUT);
  digitalWrite(vics_LED, LOW);
  digitalWrite(vics_signal, LOW);
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
  //state 0, set rising_edge_a.
  rpm_signal = digitalRead(rpm_pin); 
  if(rpm_signal == HIGH && (edge_a == true && edge_b == false && reset == false)){
    rising_edge_a = micros();
    edge_a = false;
  }
  //state 1, LOW signal
  else if(rpm_signal == LOW && (edge_a == false && edge_b == false && reset == false)){ 
    edge_b = true;
  }
  //state 2, following HIGH signal set rising_edge_b (1/2 engine rotation)
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
    //If overflow, entire sample ignored.
    if(rising_edge_a < rising_edge_b){
      rpm = calc_rpm(rising_edge_a, rising_edge_b);
      open_valve(rpm);
    }
  }
}
