#include "MOTEUR.h"
#include <Arduino.h>

// INITIALISATION

#define PIN_BP0 32  // déclaration bouton BP0
#define PIN_BP1 33  // déclaration bouton BP1
#define PIN_GI 34
#define PIN_GE 35
#define PIN_DE 36
#define PIN_DI 39
// #define SDA 21
// #define SCL 22

#define PWM_Base 1000//511
#define PWM_Min 0 

float erreur;
float erreur_precedente = 0;
float correction = 0;
float Kp = 0.7;
float Kd = 3;
int etat=0;
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
  pinMode(PIN_BP0, INPUT_PULLDOWN);   // BP0 en entré
  pinMode(PIN_BP1, INPUT_PULLDOWN);   // BP1 en entré

}

void loop()
{
  int DroiteInterieur = abs(analogRead(PIN_DI));
  int GaucheInterieur = abs(analogRead(PIN_GI));
  int DroiteExterieur = abs(analogRead(PIN_DE));
  int GaucheExterieur = abs(analogRead(PIN_GE));
  int boutonvert = digitalRead(PIN_BP0);
  int boutonbleu = digitalRead(PIN_BP1);

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
  Serial.print("Bouton 0:");
  Serial.print(boutonvert);
  Serial.print(" | Bouton 1:");
  Serial.println(boutonbleu);
  switch (etat)
  {
    case 0 :

    if (boutonvert == 1) // modifier par moi pour faire les boutons
    {
      etat = 1;
    }
    break;
    case 1 :
  moteur_droit(PWM_Base - correction);
  moteur_gauche(PWM_Base + correction);
  // modifier par moi pour faire les boutons
   if (boutonbleu == 1)
  {
    etat = 2; 
  }
  break;
    case 2 :
  moteur_droit(0);
  moteur_gauche(0);
  etat = 0;
  break;
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


 // pour arreter les moteurs pendant 5s si les 2 capteurs exterrieurs captes la ligne
  //if (PIN_GE && PIN_DE)
   // {
      //delay(5000);
    //}
 
  } 
}
