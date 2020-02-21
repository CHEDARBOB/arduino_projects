bool edge_a = false;
const int rpm_pin = 3;
const int vics_signal = 4;
const int vics_LED = LED_BUILTIN;
const int desired_rpm = 5200;
int rpm = 0;
int rpm_signal = HIGH;
unsigned long period = 0;
unsigned long falling_edge_a = 0;
unsigned long falling_edge_b = 0;

unsigned long calc_rpm(unsigned long _edge_a, unsigned long _edge_b){
  //period of 5.979 ms = ~5000 rpm
  float _period = _edge_b - _edge_a;
  int _rpm = ((60000*1000)/(_period*2));
  return rpm;
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
}

void loop() {
  //take the period starting from falling edge to falling edge. 
  //a certain period should represent a curtain RPM.
  //assume valid edge, set edge_a
  rpm_signal = digitalRead(rpm_pin); 
  if(rpm_signal == HIGH){
    if(edge_a == false){
       falling_edge_a = micros();
       edge_a = true;
    }
    else{
      falling_edge_b = micros();
      edge_a = false;
    }
  }
  //pin is low AND both edges are valid. This should account for overflow as well.
  //Check rpm and open valve if desired rpm is reached.
  if(rpm_signal == LOW && (falling_edge_a < falling_edge_b)){
    rpm = calc_rpm(falling_edge_a, falling_edge_b);
    open_valve(rpm);
  }
}
