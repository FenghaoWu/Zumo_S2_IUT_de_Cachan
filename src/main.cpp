#include "MOTEUR.h"
#include <Arduino.h>

// INITIALISATION

#define PIN_GI 34
#define PIN_GE 35
#define PIN_DE 36
#define PIN_DI 39
// #define SDA 21
// #define SCL 22

#define PWM_Base 511
#define PWM_Min 0

float erreur;
float erreur_precedente = 0;

float correction = 0;
float Kp = 1.5;
float Kd = 0;
// FONCTIONNEMENT

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_DI, INPUT);
  pinMode(PIN_GI, INPUT);
  pinMode(PIN_DE, INPUT);
  pinMode(PIN_GE, INPUT);
  setup_moteur_pwm(20000, 10);
  moteur_droit(PWM_Min);
  moteur_gauche(PWM_Min);
}

void loop()
{
  int DroiteInterieur = abs(analogRead(PIN_DI));
  int GaucheInterieur = abs(analogRead(PIN_GI));
  int DroiteExterieur = abs(analogRead(PIN_DE));
  int GaucheExterieur = abs(analogRead(PIN_GE));

  erreur = GaucheInterieur - DroiteInterieur;
  correction = Kp * erreur + Kd * (erreur - erreur_precedente);
  erreur_precedente = erreur;
  // if (GaucheExterieur > 3000 && DroiteExterieur > 3000)
  // {
  //   moteur_droit(0);
  //   moteur_gauche(0);
  // }
  // else
  // {
  moteur_droit(PWM_Base - correction);
  moteur_gauche(PWM_Base + correction);
  // }
  // Serial.print("Gauche Exterieur: ");
  // Serial.print(GaucheExterieur);
  // Serial.print(" | Gauche Interieur: ");
  // Serial.print(GaucheInterieur);
  // Serial.print(" | Droite Interieur: ");
  // Serial.print(DroiteInterieur);
  // Serial.print(" | Droite Exterieur: ");
  // Serial.print(DroiteExterieur);
  // Serial.print(" | Erreur: ");
  // Serial.print(erreur);
  // Serial.print(" | moteur droit: ");
  // Serial.print(PWM_Base - correction);
  // Serial.print(" | moteur gauche: ");
  // Serial.println(PWM_Base + correction);
  // delay(100);                                 temps en milliseconde

}