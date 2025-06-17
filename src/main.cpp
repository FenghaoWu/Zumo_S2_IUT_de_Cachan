#include "MOTEUR.h"
#include <Arduino.h>

// Partie Initialisation des Pins

#define PIN_GI 34
#define PIN_GE 35
#define PIN_DE 36
#define PIN_DI 39
#define SDA 21
#define SCL 22

// #define Bouton_Vert 32
// #define Bouton_Bleu 33

// Partie Fonctionenment

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_DI, INPUT);
  pinMode(PIN_GI, INPUT);
  pinMode(PIN_DE, INPUT);
  pinMode(PIN_GE, INPUT);

  setup_moteur_pwm(20000, 10);
  // pinMode(Bouton_Vert, INPUT);
  // pinMode(Bouton_Bleu, INPUT);
}

void loop()
{
  int DroiteInterieur = analogRead(PIN_DI);
  int GaucheInterieur = analogRead(PIN_GI);
  int DroiteExterieur = analogRead(PIN_DE);
  int GaucheExterieur = analogRead(PIN_GE);

  // char BoutonVert = digitalRead(Bouton_Vert);
  // char BoutonBleu = digitalRead(Bouton_Bleu);

  moteur_droit(800);
  moteur_gauche(800);

  delay(2500);
  // moteur_droit(0);
  // moteur_gauche(0);
  // delay(2500);

  // ledcWrite(PWM_CHANNEL_2_DROITE, 0);
  // ledcWrite(PWM_CHANNEL_3_DROITE, 1020);
}