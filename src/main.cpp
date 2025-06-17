#include "MOTEUR.h"
#include <Arduino.h>

// Partie Initialisation des Pins

#define PIN_GI 34
#define PIN_GE 35
#define PIN_DE 36
#define PIN_DI 39
#define SDA 21
#define SCL 22

int erreur = 0;
int correction = 0;
float Kp = 0.05; // Coefficient de proportionnalité pour la correction

// Partie Fonctionenment

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_DI, INPUT);
  pinMode(PIN_GI, INPUT);
  pinMode(PIN_DE, INPUT);
  pinMode(PIN_GE, INPUT);
  setup_moteur_pwm(20000, 10);
  moteur_droit(511);
  moteur_gauche(511);
}


void loop()
{
  int DroiteInterieur = abs(4095 - analogRead(PIN_DI));
  int GaucheInterieur = abs(4095 - analogRead(PIN_GI));
  int DroiteExterieur = abs(4095 - analogRead(PIN_DE));
  int GaucheExterieur = abs(4095 - analogRead(PIN_GE));

  erreur = DroiteInterieur - GaucheInterieur;
  correction = Kp * erreur;

  moteur_droit(511 + correction);
  moteur_gauche(511 - correction);

  Serial.print("Droite Interieur: ");
  Serial.print(DroiteInterieur);
  Serial.print(" | Gauche Interieur: ");
  Serial.print(GaucheInterieur);
  Serial.print(" | Erreur: ");
  Serial.print(erreur);
  Serial.print(" | Correction: ");
  Serial.println(correction);
}