
const int button1 = 2;
const int button2 = 3;
const int led = 13;
int bu1 = 0;
int bu2 = 0;

void setup() {
 pinMode(led,OUTPUT);
 pinMode(button1,INPUT_PULLUP);
 pinMode(button2,INPUT_PULLUP);
}

void loop() {
  bu1=digitalRead(button1);
  bu2=digitalRead(button2);
  if (bu1==LOW){
    digitalWrite(led,0);
    }
  else if (bu2==LOW){
   digitalWrite(led,1);
  }
}
