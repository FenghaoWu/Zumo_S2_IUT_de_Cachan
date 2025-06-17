#include "MOTEUR.h"
#include <Arduino.h>

// INITIALISATION

#define PIN_GI 34
#define PIN_GE 35
#define PIN_DE 36
#define PIN_DI 39
#define SDA 21
#define SCL 22

#define PWM_Base 511
#define PWM_Min 0

int erreur, correction = 0;
float Kp = 0.05;

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
  correction = Kp * erreur;

  moteur_droit(PWM_Base - correction);
  moteur_gauche(PWM_Base + correction);

  Serial.print("Gauche Exterieur: ");
  Serial.print(GaucheExterieur);
  Serial.print(" | Gauche Interieur: ");
  Serial.print(GaucheInterieur);
  Serial.print(" | Droite Interieur: ");
  Serial.print(DroiteInterieur);
  Serial.print(" | Droite Exterieur: ");
  Serial.print(DroiteExterieur);
  Serial.print(" | Erreur: ");
  Serial.print(erreur);
  Serial.print(" | moteur droit: ");
  Serial.print(511 + correction);
  Serial.print(" | moteur gauche: ");
  Serial.println(511 - correction);
  delay(100);
}