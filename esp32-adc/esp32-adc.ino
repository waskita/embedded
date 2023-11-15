int counter;  // how many iterations
int time_begin = 0;
int time_end = 0;
int duration;
const int PIN_OUTPUT = 19;
int sensorPin = 34;  // select the input pin for the potentiometer

void setup() {
  Serial.begin(115200);
  counter = 0;
  pinMode(PIN_OUTPUT, OUTPUT);
  Serial.println("start benchmark");
}
//---------------------------------------------------
void loop() {
  int data = 0;
  int value;  // angka yang ditulis
  value = 0;  // minimum value

  data = analogRead(sensorPin);
  //  Serial.println(data);
  //  delay(1000);
  digitalWrite(PIN_OUTPUT, HIGH);

  data = analogRead(sensorPin);
  //Serial.println(data);
  //delay(1000);
  digitalWrite(PIN_OUTPUT, LOW);

  counter = counter + 1;
  if (counter >= 10000) {
    float period;
    int time_now = millis();
    counter = 0;
    duration = time_now - time_begin;
    period = duration / 10000.0 / 2;
    Serial.print("period (ms): ");
    Serial.println(period);
    //  prepare next round
    time_begin = time_now;
  }
}
