

double pi = 3.1415926535;
double pipi = pi * pi;
int aco=1<<ACO;




void setup(){

  //initialize comparator
  DDRD=0;
  PORTD=0;
  ACSR=0;
  ADCSRB=0;
  
  //
  Serial.begin(115200);
  pinMode(11, OUTPUT);
  Serial.println("ACO inductance meter");
  delay(500);  
}




void loop(){

unsigned long timeout=1000000;
unsigned long t=0;
unsigned long total;
  
digitalWrite(11, HIGH); 
delay(50);        //charge the inductor.
digitalWrite(11,LOW);

//next three while loops wait for full wave to start and finish
//aco is a bit within ACSR register that represents output of the comparator

while((ACSR & aco)&& t<timeout) {t++;}


unsigned long start = micros();
while(!(ACSR & aco)&& t<timeout) {t++;}
while((ACSR & aco)&& t<timeout) {t++;}
total=micros() - start-4;

double C=1.0;      //capacitor is in uF 
double T=total;    // T is in us

double total2 = (T*T) / ( 4.0 * pipi * C);

total2*=0.001;      //convert to mH

if(t>=timeout){
  Serial.println("timeout");
}else{
  Serial.print(total);
  Serial.print("us  ");
  Serial.print(total2,3);  
  Serial.println("mH  ");
  delay(1000);
  }
}

















  
