//--------------------------BIBLIOTHEQUES--------------------------//

#include "MOTEUR.h"
#include <Arduino.h>
#include <Wire.h>
#include <Wifi.h>
#include "Adafruit_TCS34725.h"
#include <ModbusIP_ESP8266.h>

//--------------------INITIALISATION DES PINS--------------------//

#define PIN_BP0 32 // déclaration bouton BP0
#define PIN_BP1 33 // déclaration bouton BP1
#define PIN_GI 34
#define PIN_GE 35
#define PIN_DE 36
#define PIN_DI 39
#define PWM_Base 511
#define PWM_Min 0
#define I2C_SDA 22
#define I2C_SCL 21

//--------------------INITIALISATION DES VARIABLES--------------------//

float erreur;
float erreur_precedente = 0;
float correction = 0;
float Kp = 1.5;
float Kd = 2.0;
int etat = 0;
int seuil = 1000;
unsigned long TempsAttente = 0;
uint16_t R, G, B, C, reg;
int rouge, vert, bleu;
int couleur = 0; // 0 = INCONNUE, 1 = ROUGE, 2 = BLEU
const char *ssid = "Wifi_Test";
const char *password = "12345678";

//--------------------INITIALISATION SPECIALE--------------------//

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
IPAddress plcIP(192, 168, 0, 104);
ModbusIP mb;

//--------------------FONCTIONNEMENT INITIALISATION--------------------//

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
  pinMode(PIN_BP0, INPUT_PULLDOWN);
  pinMode(PIN_BP1, INPUT_PULLDOWN);
  Wire.begin(I2C_SDA, I2C_SCL);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connexion au WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnecté au WiFi");
  Serial.println("Adresse IP: " + WiFi.localIP().toString());
  delay(1000);

  mb.server();
  mb.addHreg(40000, 0);
  mb.addCoil(40001);
}

//--------------------FONCTIONNEMENT EXECUTION--------------------//

void loop()
{
  int DroiteInterieur = abs(analogRead(PIN_DI));
  int GaucheInterieur = abs(analogRead(PIN_GI));
  int DroiteExterieur = abs(analogRead(PIN_DE));
  int GaucheExterieur = abs(analogRead(PIN_GE));
  int boutonvert = digitalRead(PIN_BP0);
  int boutonbleu = digitalRead(PIN_BP1);

  switch (etat)
  {
  case 0: // Phase attente de demarrage

    Serial.println("Registre: " + String(reg));

    if (boutonvert == 1)
    {
      etat = 1;
    }
    else
    {
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

    tcs.getRawData(&R, &G, &B, &C); // R rouge, G vert, B bleu et C luminosité
    rouge = (float)R / C * 255.0;
    vert = (float)G / C * 255.0;
    bleu = (float)B / C * 255.0;

    if (rouge > bleu && rouge < 95)
    {
      couleur = 1; // 1 = ROUGE
    }
    else if (bleu > rouge)
    {
      couleur = 2; // 2 = BLEU
    }
    else
    {
      couleur = 0; // 0 = INCONNUE
    }

    mb.Coil(40001, couleur); // Envoie de la couleur au PLC
    reg = mb.Hreg(40000); // Lecture depuis le PLC
    mb.task(); // Mise à jour de la valeur du registre pour la variable reg afin de pouvoir l'utiliser dans le switch

    switch(reg)
    {
      case 0:

        etat = 2;

        break;

      case 1:

        etat = 3;

        break;
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