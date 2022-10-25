// lampu kedip 0,5 Hz dengan model FSM dan FreeRTOS

#include "Arduino_FreeRTOS.h"

#define ON    100
#define OFF   101

#define LED_OUTPUT 3
int state = OFF;
TaskHandle_t xHandle1 = NULL;

void fsm_init(int *state) {
  *state = OFF;
}

void fsm(int  *state, int *out) {
  switch (*state) {
    case ON: {
        *state = OFF;
        *out = 0;
        break;
      }
    case OFF: {
        *state = ON;
        *out = 1; // nyalakan output
        break;
      }
  }
}

void fsm_output(int output_value) {
  if (output_value == 1) {
    digitalWrite(LED_OUTPUT, HIGH);
  } else {
    digitalWrite(LED_OUTPUT, LOW);
  }
}

void setup() {
  int output = 0;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_OUTPUT, OUTPUT);
  Serial.begin(115200);

  Serial.print("portTICK_PERIOD_MS: ");
  Serial.print(portTICK_PERIOD_MS);
  Serial.println();

  fsm_init(&state);
  fsm_output(output);

  xTaskCreate(
    TaskFSM
    ,  "TaskFSM"  // A name just for humans
    ,  100  // stacksize
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &xHandle1 );
}

static void TaskFSM(void *pvParameters) 
{
  TickType_t xLastWakeTime;
  /* The xLastWakeTime variable needs to be initialised with the current tick
    count.  Note that this is the only time we access this variable.  From this
    point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
    API function. */
  xLastWakeTime = xTaskGetTickCount();
  while (1)
  {
    int output = 0;
    fsm(&state, &output);
    if (output == 1) {
      digitalWrite(LED_OUTPUT, HIGH);
    } else {
      digitalWrite(LED_OUTPUT, LOW);
    }
    Serial.print("state: ");
    Serial.print(state);
    Serial.print(" output: ");
    Serial.print( output);
    Serial.println();
    vTaskDelayUntil( &xLastWakeTime, ( 1000 / portTICK_PERIOD_MS ) ); // perioda 1 detik
  }
}

void loop() { // lampu kedip main loop 1 Hz
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);                       //
  digitalWrite(LED_BUILTIN, HIGH);
}
