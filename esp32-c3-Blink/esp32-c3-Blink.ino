//  blink 2 LED & send data to serial port
// tekan tombol BOOT untuk upload

#define LED_BUILTIN 12
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial.print("Hello!");

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  static int counter = 0;
  counter++;
  if (counter>3){
    counter = 0;
  }
  switch (counter) {
    case 0:
      digitalWrite(12, LOW);  // turn the LED off by making the voltage LOW
      digitalWrite(13, LOW);  // turn the LED off by making the voltage LOW
      break;
    case 1:
      digitalWrite(12, LOW);   // turn the LED off by making the voltage LOW
      digitalWrite(13, HIGH);  // turn the LED off by making the voltage LOW
      break;
    case 2:
      digitalWrite(12, HIGH);  // turn the LED off by making the voltage LOW
      digitalWrite(13, LOW);   // turn the LED off by making the voltage LOW
      break;
    case 3:
      digitalWrite(12, HIGH);  // turn the LED off by making the voltage LOW
      digitalWrite(13, HIGH);  // turn the LED off by making the voltage LOW
      
      break;
    default:
      {
      }
  }
  delay(100);  // wait for a second
  Serial.print("xyz ");
}
