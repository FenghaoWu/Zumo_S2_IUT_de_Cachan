#include "MOTEUR.h"
#include <Arduino.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

// INITIALISATION

#define PIN_BP0 32 // déclaration bouton BP0
#define PIN_BP1 33 // déclaration bouton BP1
#define PIN_GI 34
#define PIN_GE 35
#define PIN_DE 36
#define PIN_DI 39

#define PWM_Base 511 // 511
#define PWM_Min 0

float erreur;
float erreur_precedente = 0;
float correction = 0;
<<<<<<< HEAD
float Kp = 1.5;
float Kd = 3;
int etat = 0;
// int coeff_stop_moteur = 1;
int seuil = 1000;
unsigned long TempsAttente = 0;
=======
float Kp = 1.3;
float Kd = 3;
int etat = 0;
int coeff_stop_moteur = 1;
int seuil = 1000;
>>>>>>> 8876f3e4877fbecc12758fcbee6cce60e0226263

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
  pinMode(PIN_BP0, INPUT_PULLDOWN); // BP0 en entré
  pinMode(PIN_BP1, INPUT_PULLDOWN); // BP1 en entré
<<<<<<< HEAD
  lcd.begin(16, 2);
}
=======
>>>>>>> 8876f3e4877fbecc12758fcbee6cce60e0226263

  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.print("hello, world!");
  delay(1000);
}
void loop()
{
  int DroiteInterieur = abs(analogRead(PIN_DI));
  int GaucheInterieur = abs(analogRead(PIN_GI));
  int DroiteExterieur = abs(analogRead(PIN_DE));
  int GaucheExterieur = abs(analogRead(PIN_GE));
  int boutonvert = digitalRead(PIN_BP0);
  int boutonbleu = digitalRead(PIN_BP1);

<<<<<<< HEAD
  switch (etat)
  {
  case 0: // Phase attente de demarrage (Violet)

    lcd.clear();
    lcd.setRGB(180, 0, 255);
    lcd.setCursor(0, 0);
    lcd.print("------PRET------");
    lcd.setCursor(0, 1);
    lcd.print("Attente BP_Vert");

    if (boutonvert == 1)
    {
      lcd.clear();
      etat = 1;
    }
    else
    {
      lcd.clear();
      moteur_droit(PWM_Min);
      moteur_gauche(PWM_Min);
    }

    break;

  case 1: // Phase de suivi de ligne

    erreur = GaucheInterieur - DroiteInterieur;
    correction = Kp * erreur + Kd * (erreur - erreur_precedente);
    erreur_precedente = erreur;

    moteur_droit(PWM_Base - correction);
    moteur_gauche(PWM_Base + correction);

    if ((GaucheExterieur < seuil) && (DroiteExterieur < seuil))
    {
      TempsAttente = millis();
      etat = 3;
    }

    if (boutonbleu == 1) // Bouton bleu pour arret d'urgence
    {
      etat = 4;
    }

    break;

  case 2: // Phase d'amortissement

    moteur_droit(255);
    moteur_gauche(255);

    if (millis() - TempsAttente >= 300)
    {
      etat = 1;
    }

    if (boutonbleu == 1) // Bouton bleu pour arret d'urgence
    {
      etat = 4;
    }

    break;

  case 3: // Phase arrivee et communication

    moteur_droit(PWM_Min);
    moteur_gauche(PWM_Min);

    if (millis() - TempsAttente >= 3000)
    {
      TempsAttente = millis();
      etat = 2;
    }

    if (boutonbleu == 1) // Bouton bleu pour arret d'urgence
    {
      etat = 4;
    }

    break;

  case 4: // Phase arret d'urgence

    moteur_droit(PWM_Min);
    moteur_gauche(PWM_Min);
    etat = 0;

    break;
  }
}
=======
  erreur = GaucheInterieur - DroiteInterieur;
  correction = Kp * erreur + Kd * (erreur - erreur_precedente);
  erreur_precedente = erreur;

  // Serial.print("\n DE:");
  // Serial.print(DroiteExterieur);
  // delay(500);
  // Serial.print("\n GE:");
  // Serial.println(GaucheExterieur);
  // delay(500);
  // Serial.print("\n DI:");
  // Serial.print(DroiteInterieur);
  // delay(500);
  // Serial.print("\n GI:");
  // Serial.println(GaucheInterieur);
  // delay(500);

  // Serial.print("\n BP0:");
  // Serial.println(boutonvert);
  // delay(500);
  // Serial.print("\n BP1:");
  // Serial.println(boutonbleu);
  // delay(500);

  // delay(100); // temps de cycle
  switch (etat)
  {
  case 0:
    // etat = 0;
    // if (boutonvert == 1)
    // {
      etat = 1;
    // }

    lcd.setRGB(255, 255, 0);
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(" PRET");

    lcd.clear();

    break;

  case 1:
    // if (boutonbleu == 1)
    // {
    //   etat = 2;
    // }
    if ((GaucheExterieur < seuil) && (DroiteExterieur < seuil))
    {
      etat = 3;
    }
    break;

  case 3:
    // delay(5000);
    coeff_stop_moteur = 0;
    lcd.setRGB(255, 0, 0);
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(" ARRIVE");

    lcd.clear();

    // etat = 1;
    break;
  }

  moteur_droit((PWM_Base - correction) * coeff_stop_moteur);
  moteur_gauche((PWM_Base + correction) * coeff_stop_moteur);
}

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
// if (PIN_GE && PIN_DE)
// {
// delay(5000);
//}

// if (GaucheExterieur > 3000 && DroiteExterieur > 3000)
// {
//   moteur_droit(0);
//   moteur_gauche(0);
// }
// else
// {
>>>>>>> 8876f3e4877fbecc12758fcbee6cce60e0226263
