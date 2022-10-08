// menguji apakah semua lampu dapat dinyalakan dan dimatikan.
// menguji durasi dummy job

#define LED_1_A 7
#define LED_1_B 6
#define LED_2_A 5
#define LED_2_B 4
#define LED_3_A 3
#define LED_3_B 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_1_A, OUTPUT);
  pinMode(LED_1_B, OUTPUT);
  pinMode(LED_2_A, OUTPUT);
  pinMode(LED_2_B, OUTPUT);
  pinMode(LED_3_A, OUTPUT);
  pinMode(LED_3_B, OUTPUT);
}
void dummy_job(int LED_A, int LED_B , unsigned int counter) {
  unsigned int i;
  digitalWrite(LED_A, HIGH);
  digitalWrite(LED_B, HIGH);

  for (i = 0; i < counter; i++) {
    digitalWrite(LED_A, HIGH);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_A, LOW);
  }
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
}

void loop() {
  static int counter = 0;
  int begin, end, durasi;
  counter++;
  digitalWrite(LED_2_A, HIGH);
  begin = millis();
  dummy_job(LED_3_A, LED_3_B, 65000);
  end = millis();
  durasi = end - begin;
  digitalWrite(LED_2_A, LOW);
  //dummy_task(10000);
  Serial.print(counter);
  Serial.print(" durasi: ");
  Serial.println(durasi);
  delay(100);
  //  delay(1000);
}
