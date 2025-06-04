#include <Arduino.h>

#define PIN_DI 34
#define PIN_GI 35
#define PIN_GI 36
#define PIN_GE 39

void setup()
{
  Serial.begin(115200);

  pinMode(PIN_DI, INPUT_PULLDOWN);
  pinMode(PIN_GI, INPUT_PULLDOWN);
  pinMode(PIN_GI, INPUT_PULLDOWN);
  pinMode(PIN_GE, INPUT_PULLDOWN);
}

void loop()
{
  int val1 = analogRead(PIN_DI);
  int val2 = analogRead(PIN_GI);
  int val3 = analogRead(PIN_GI);
  int val4 = analogRead(PIN_GE);

  Serial.print("CNY70_1: ");
  Serial.print(val1);

  Serial.print(" | CNY70_2: ");
  Serial.print(val2);

  Serial.print(" | CNY70_3: ");
  Serial.print(val3);

  Serial.print(" | CNY70_4: ");
  Serial.println(val4);

  delay(10);
}