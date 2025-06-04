#include <Arduino.h>

#define PIN_DI 34
#define PIN_GI 35
#define PIN_GI 36
#define PIN_GE 39
#define Bouton_Vert 32
#define Bouton_Blue 33

void setup()
{
  Serial.begin(115200);

  pinMode(PIN_DI, INPUT);
  pinMode(PIN_GI, INPUT);
  pinMode(PIN_GI, INPUT);
  pinMode(PIN_GE, INPUT);
  pinMode(Bouton_Vert, INPUT);
  pinMode(Bouton_Blue, INPUT);
}

void loop()
{
  int val1 = analogRead(PIN_DI);
  int val2 = analogRead(PIN_GI);
  int val3 = analogRead(PIN_GI);
  int val4 = analogRead(PIN_GE);
  char boutonVert = digitalRead(Bouton_Vert);
  char boutonBlue = digitalRead(Bouton_Blue);

  Serial.print("CNY70_1: ");
  Serial.print(val1);

  Serial.print(" | CNY70_2: ");
  Serial.print(val2);

  Serial.print(" | CNY70_3: ");
  Serial.print(val3);

  Serial.print(" | CNY70_4: ");
  Serial.print(val4);

  Serial.print(" | Bouton Vert: ");
  Serial.print(boutonVert == LOW ? "Appuye" : "Relache");
  Serial.print(" | Bouton Blue: ");
  Serial.println(boutonBlue == LOW ? "Appuye" : "Relache");

  delay(100);
}