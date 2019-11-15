volatile int bleled;
volatile int ledblin;
volatile int ledblinkp;
volatile boolean ledstate;
void setup(){
  bleled = 0;
  ledblinkp = millis();
  ledblin = 0;
  ledstate = false;
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
}
void loop(){
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  if (digitalRead(2) == LOW) {
    bleled = 1;
    ledstate = true;
  }
  if (digitalRead(3) == LOW) {
    bleled = 2;
  }
  if (bleled == 2) {
    digitalWrite(13,LOW);
  }
  ledblin = millis();
  if (ledblin - ledblinkp >= 500) {
    ledstate = !ledstate;
    ledblinkp = ledblin;
    if (bleled == 1 && ledstate == true) {
      digitalWrite(13,HIGH);
    } else {
      digitalWrite(13,LOW);
    }
  }
}
