#include <Arduino.h>

// Partie Initialisation des Pins

#define PIN_GI 34
#define PIN_GE 35
#define PIN_DE 36
#define PIN_DI 39
#define PWM_Droite 5
#define PWM_Gauche 16
// #define Bouton_Vert 32
// #define Bouton_Bleu 33

int PWM_FREQUENCY = 5000;
int PWM_RESOLUTION = 8;
int PWM_CHANNEL_1 = 0;
int PWM_CHANNEL_2 = 1;

// Partie Fonctionenment

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_DI, INPUT);
  pinMode(PIN_GI, INPUT);
  pinMode(PIN_DE, INPUT);
  pinMode(PIN_GE, INPUT);
  // pinMode(Bouton_Vert, INPUT);
  // pinMode(Bouton_Bleu, INPUT);
  ledcSetup(PWM_CHANNEL_1, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_2, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(PWM_Droite, PWM_CHANNEL_1);
  ledcAttachPin(PWM_Gauche, PWM_CHANNEL_2);
}

void loop()
{
  int DroiteInterieur = analogRead(PIN_DI);
  int GaucheInterieur = analogRead(PIN_GI);
  int DroiteExterieur = analogRead(PIN_DE);
  int GaucheExterieur = analogRead(PIN_GE);
  // char BoutonVert = digitalRead(Bouton_Vert);
  // char BoutonBleu = digitalRead(Bouton_Bleu);
  if (GaucheInterieur < 2000)
  {
    ledcWrite(PWM_CHANNEL_1, 0); // Stop PWM on right motor
    ledcWrite(PWM_CHANNEL_2, 127); // Start PWM on left motor
  }
  else
  {
    ledcWrite(PWM_CHANNEL_1, 127); // Start PWM on right motor
    ledcWrite(PWM_CHANNEL_2, 127); // Stop PWM on left motor
  }
}