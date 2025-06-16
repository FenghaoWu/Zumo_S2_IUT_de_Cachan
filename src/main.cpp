#include <Arduino.h>

//Partie Initialisation des Pins

#define PIN_DI 34
#define PIN_GI 35
#define PIN_DE 36
#define PIN_GE 39
#define PWM_1 5
#define PWM_2 16
#define Bouton_Vert 32
#define Bouton_Bleu 33

int PWM_FREQUENCY = 5000;
int PWM_RESOLUTION = 8;
int PWM_CHANNEL_1 = 0;
int PWM_CHANNEL_2 = 1;

//Partie Fonctionenment

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_DI, INPUT);
  pinMode(PIN_GI, INPUT);
  pinMode(PIN_DE, INPUT);
  pinMode(PIN_GE, INPUT);
  pinMode(Bouton_Vert, INPUT);
  pinMode(Bouton_Bleu, INPUT);
  ledcSetup(PWM_CHANNEL_1, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_2, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(PWM_1, PWM_CHANNEL_1);
  ledcAttachPin(PWM_2, PWM_CHANNEL_2);
}

void loop()
{
  int val1 = analogRead(PIN_DI);
  int val2 = analogRead(PIN_GI);
  int val3 = analogRead(PIN_DE);
  int val4 = analogRead(PIN_GE);
  char boutonVert = digitalRead(Bouton_Vert);
  char boutonBleu = digitalRead(Bouton_Bleu);
  ledcWrite(PWM_CHANNEL_1, 255);
  ledcWrite(PWM_CHANNEL_2, 255);
}