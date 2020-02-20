bool edge_a = false;
const int rpm_pin = 3;
const int vics_signal_out = 4;
int rpm = 0;
unsigned long _time = 0;
unsigned long period = 0;
unsigned long falling_edge_a = 0;
unsigned long falling_edge_b = 0;


void setup() {
  pinMode(rpm_pin, INPUT);
  pinMode(vics_signal_out, OUTPUT);
}

void loop() {
  //take the period starting from falling edge to falling edge. 
  //a certain period should represent a curtain RPM. 
  if (rpm_pin == HIGH && edge_a == false){
   //assume valid edge, set edge_a
   falling_edge_a = millis();
   edge_a = true;
   continue;
  }
  else if(rpm_pin == HIGH && edge_a == true){
   falling_edge_b = millis()
   edge_a = false;
   period = calc_period(falling_edge_a, falling_edge_b);
  }
}

unsigned long calc_period(unsigned long edge_a, unsigned long edge_b){
  
}
