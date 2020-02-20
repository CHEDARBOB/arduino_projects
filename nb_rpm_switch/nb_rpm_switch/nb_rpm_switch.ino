bool edge_a = false;
const int rpm_pin = 3;
const int vics_signal = 4;
const int vics_LED = LED_BUILTIN;
const int desired_rpm = 5200;
int rpm = 0;
unsigned long period = 0;
unsigned long falling_edge_a = 0;
unsigned long falling_edge_b = 0;

unsigned long calc_rpm(unsigned long edge_a, unsigned long edge_b){
  //period of 11.5 ms == 5217 rpm
  unsigned long _period = edge_b - edge_a;
  int _rpm = 60000/period;
  return rpm
}

void open_valve(int _rpm){
  if(_rpm > desired_rpm){
    digitalWrite(vics_signal, HIGH)
    digitalWrite(vics_LED, HIGH)
  }
  else{
    digitalWrite(vics_signal, LOW)
    digitalWrite(vics_LED, LOW)
  }
}
void setup() {
  pinMode(rpm_pin, INPUT);
  pinMode(vics_signal, OUTPUT);
  pinMode(vics_LED, OUTPUT);
  digitalWrite(vics_LED, LOW);
}

void loop() {
  //take the period starting from falling edge to falling edge. 
  //a certain period should represent a curtain RPM.
  //assume valid edge, set edge_a 
  if(rpm_pin == HIGH){
    if(edge_a == false){
       falling_edge_a = millis();
       edge_a = true;
    }
    else{
      falling_edge_b = millis()
      edge_a = false;
    }
  }
  //pin is low AND both edges are valid. 
  //Check rpm and open valve if desired rpm is reached.
  if(rpm_pin == LOW && (falling_edge_a < falling_edge_b)){
    rpm = calc_rpm(falling_edge_a, falling_edge_b);
    open_valve(rpm);
  }
}
