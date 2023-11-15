int counter;  // how many iterations
int time_begin = 0;
int time_end = 0;
int duration;

int sensorPin = A0;   // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED

void setup() {
  Serial.begin(115200);
  counter = 0;
  pinMode(2, OUTPUT);
  Serial.println("start benchmark");
}
//---------------------------------------------------
void loop() {
  int value;  // angka yang ditulis
  value = 0;  // minimum value
  analogRead(sensorPin);
  PORTD=0; // langsung akses port supaya lebih cepat
  analogRead(sensorPin);
  PORTD=255;
  counter = counter + 1;
  if (counter >= 10000) {
    float period;
    int time_now = millis();
    counter = 0;
    duration = time_now - time_begin;
    period = duration / 10000.0 /2;
    Serial.print("period (ms): ");
    Serial.println(period);
    //  prepare next round
    time_begin = time_now;
  }
}
