/*
 Kendali posisi sederhana
*/


const int IN1=11;
const int IN2=10; // pin untuk kendali arah motor
const int PWM=9; // pin untuk PWM

const int analogInPin = A0;
long int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int state=0;
long int posisi=0;
long int kecepatan=0;
int pinA;
int pinB;


void ISR_INT0(){
  pinA=digitalRead(2);
  pinB=digitalRead(3);
  if(pinA==LOW && pinB==LOW){
    posisi--; // CCW
    kecepatan--;
  }
  if(pinA==LOW && pinB==HIGH){
    posisi++; 
    kecepatan++;
  }
  if(pinA==HIGH&& pinB==LOW){
    posisi++; // CCW
    kecepatan++;
  }
  if(pinA==HIGH && pinB==HIGH){
    posisi--; // CCW
    kecepatan--;
  }
}

void ISR_INT1(){
  pinA=digitalRead(2);
  pinB=digitalRead(3);
  if(pinA==LOW && pinB==LOW){
    posisi++; // CCW
    kecepatan++;
  }
  if(pinA==LOW && pinB==HIGH){
    posisi--; 
    kecepatan--;
  }
  
  if(pinA==HIGH&& pinB==LOW){
    posisi--; // CCW
    kecepatan--;
  }
  if(pinA==HIGH && pinB==HIGH){
    posisi++; // CCW
    kecepatan++;
  }
}

void motor_power(int power){
  int pwm_value;
  pwm_value=abs(power);
  if(pwm_value<0)
    pwm_value=0;
  if(pwm_value>255)
    pwm_value=255;      
  if(power>0){
    digitalWrite(IN1,LOW);  // turn off
    digitalWrite(IN2,HIGH);  // turn off
    analogWrite(PWM, pwm_value);
  } else if(power<0){
    digitalWrite(IN1,HIGH);  // turn off
    digitalWrite(IN2,LOW);  // turn off
    analogWrite(PWM, pwm_value);
  }else{
    digitalWrite(IN1,LOW);  // turn off        
    digitalWrite(IN2,LOW);  // turn off
  }
}

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), ISR_INT0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), ISR_INT1, CHANGE);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);

   pinMode(IN1, OUTPUT);
   pinMode(IN2, OUTPUT);
   pinMode(PWM, OUTPUT);

}

void loop() {
  float Kp=5;
  float Ki=0.0001;
  static float error_integral=0;
  int target;
  float control;
  float error;
  // print the results to the Serial Monitor:

sensorValue=0;
//posisi=0;
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  if(state==0){
    state=1;
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }else{
    state=0;
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
  }

 sensorValue = analogRead(analogInPin);  
 target=sensorValue*2;
  error=target-posisi;
  error_integral=error_integral+error;
  control=error*Kp+error_integral*Ki;
  motor_power(control);

if(1){
  int i;
  char buffer[100];
  int length;
  sprintf(buffer,"%d %d %d %f %f\n",target,kecepatan,posisi,control,error_integral);
  length=strlen(buffer);
  for(i=0;i<length;i++){
//    fifo_put(&fs,buffer[i]);
  }
  
}
  kecepatan=0;
  delay(1);
}
