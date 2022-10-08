// template umum FreeRTOS di Arduino Nano  https://github.com/feilipu/Arduino_FreeRTOS_Library/blob/master/examples/AnalogRead_DigitalRead/AnalogRead_DigitalRead.ino
// contoh pemakaian vTaskDelayUntil dan xTaskGetTickCount dari https://github.com/feilipu/avrfreertos/blob/master/MegaBlink/main.c

#include "Arduino_FreeRTOS.h"
#include <semphr.h>

#define LED1  2
#define LED2  3
#define LED3  4

static void TaskBlinkLED1(void *pvParameters);
static void TaskBlinkLED2(void *pvParameters);
static void TaskBlinkLED3(void *pvParameters);

// task handle diperlukan jika ingin mengakses parameter suatu task. optional
TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;
TaskHandle_t xHandle3 = NULL;

void setup() {
  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  xTaskCreate(
    TaskBlinkLED1
    ,  "TaskBlinkLED1"  // A name just for humans
    ,  100  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &xHandle1 );
  xTaskCreate(
    TaskBlinkLED2
    ,  "TaskBlinkLED2"  // A name just for humans
    ,  100  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &xHandle2 );
  xTaskCreate(
    TaskBlinkLED3
    ,  "TaskBlinkLED3"  // A name just for humans
    ,  100  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &xHandle3  );
}

// menunjukkan loop dapat tetap dijalankan terpisah dari semua task FreeRTOS
void loop() {
  static int counter=0;
  UBaseType_t uxHighWaterMark;
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  Serial.println(counter);
}

static void TaskBlinkLED1(void *pvParameters) // Main Red LED Flash
{
  TickType_t xLastWakeTime;
  /* The xLastWakeTime variable needs to be initialised with the current tick
    count.  Note that this is the only time we access this variable.  From this
    point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
    API function. */
  xLastWakeTime = xTaskGetTickCount();
  while (1)
  {
    digitalWrite(LED1, HIGH);
    vTaskDelayUntil( &xLastWakeTime, ( 100 / portTICK_PERIOD_MS ) );
    digitalWrite(LED1, LOW);
    vTaskDelayUntil( &xLastWakeTime, ( 100 / portTICK_PERIOD_MS ) );
  }
}

static void TaskBlinkLED2(void *pvParameters) // Main Red LED Flash
{
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (1)
  {
    digitalWrite(LED2, HIGH);
    vTaskDelayUntil( &xLastWakeTime, ( 150 / portTICK_PERIOD_MS ) );
    digitalWrite(LED2, LOW);
    vTaskDelayUntil( &xLastWakeTime, ( 150 / portTICK_PERIOD_MS ) );
  }
}

static void TaskBlinkLED3(void *pvParameters) // Main Red LED Flash
{
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (1)
  {
    digitalWrite(LED3, HIGH);
    vTaskDelayUntil( &xLastWakeTime, ( 250 / portTICK_PERIOD_MS ) );
    digitalWrite(LED3, LOW);
    vTaskDelayUntil( &xLastWakeTime, ( 250 / portTICK_PERIOD_MS ) );
  }
}
