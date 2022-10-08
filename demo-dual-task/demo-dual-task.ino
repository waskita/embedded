// menguji apakah semua lampu dapat dinyalakan dan dimatikan.
// menguji durasi dummy job

#include "Arduino_FreeRTOS.h"
#include <semphr.h>

#define LED_1_A 7
#define LED_1_B 6
#define LED_2_A 5
#define LED_2_B 4
#define LED_3_A 3
#define LED_3_B 2

TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;

static void TaskDummy1(void *pvParameters) // Main Red LED Flash
{
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (1)
  {
    dummy_job(LED_1_A, LED_1_B, 40000);
    vTaskDelayUntil( &xLastWakeTime, ( 1000 / portTICK_PERIOD_MS ) );
  }
}

static void TaskDummy2(void *pvParameters) // Main Red LED Flash
{
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  while (1)
  {
    dummy_job(LED_2_A, LED_2_B, 5000);
    vTaskDelayUntil( &xLastWakeTime, ( 400 / portTICK_PERIOD_MS ) );
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_1_A, OUTPUT);
  pinMode(LED_1_B, OUTPUT);
  pinMode(LED_2_A, OUTPUT);
  pinMode(LED_2_B, OUTPUT);
  pinMode(LED_3_A, OUTPUT);
  pinMode(LED_3_B, OUTPUT);

  xTaskCreate(
    TaskDummy1
    ,  "TaskDummy1"  // A name just for humans
    ,  100  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &xHandle1 );

  xTaskCreate( // lebih tinggi prioritasnya, lebih cepat delaynya
    TaskDummy2
    ,  "TaskDummy2"  // A name just for humans
    ,  100  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &xHandle1 );

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
  delay(1000);
  digitalWrite(LED_3_A, HIGH);  // cek apakah loop() dijalanakn
  digitalWrite(LED_3_A, LOW);
}
