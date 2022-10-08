/*
Mengukur posisi relatif rotary encoder dengan INT0 dan INT1

Perkabelan:
D2: INT0 ke kabel rotary encoder warna hijau 
D3: INT1 ke kabel rotary encoder warna putih
5V: ke kabel rotary encoder warna merah (5 volt)
GND: ke kabel rotary encoder warna hitam

*/
int state=0;
long int posisi=0;

void ISR_INT0(){
  int pinA,pinB;
  pinA=digitalRead(2);
  pinB=digitalRead(3);
  if(pinA==LOW && pinB==LOW){
    posisi--; // CCW
  }
  if(pinA==LOW && pinB==HIGH){
    posisi++; 
  }
  if(pinA==HIGH&& pinB==LOW){
    posisi++; // CCW
  }
  if(pinA==HIGH && pinB==HIGH){
    posisi--; // CCW
  }
}

void ISR_INT1(){
  int pinA,pinB;
  pinA=digitalRead(2);
  pinB=digitalRead(3);
  if(pinA==LOW && pinB==LOW){
    posisi++; // CCW
  }
  if(pinA==LOW && pinB==HIGH){
    posisi--; 
  }
  
  if(pinA==HIGH&& pinB==LOW){
    posisi--; // CCW
  }
  if(pinA==HIGH && pinB==HIGH){
    posisi++; // CCW
  }
}

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // untuk indikator
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), ISR_INT0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), ISR_INT1, CHANGE);
}

void loop() {
  if(state==0){
    state=1;
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }else{
    state=0;
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
  }
  Serial.print("posisi ");
  Serial.print(posisi);
  Serial.println("");
  delay(1000);
}
