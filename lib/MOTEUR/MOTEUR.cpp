#include "MOTEUR.h"
#include <Arduino.h>

#define PWM_Gauche 18
#define TOR_Gauche 5
#define TOR_Droite 16
#define PWM_Droite 17
#define AVANCER true
#define RECULER false
int resolution_moteur = 10; //PWM qui varie de 0 à 1023
const int PWM_CHANNEL_0_GAUCHE = 0;
const int PWM_CHANNEL_1_DROITE = 1;

void setup_moteur_pwm(float frequence_pwm, float resolution_pwm)
{
    resolution_moteur = resolution_pwm;
    ledcSetup(PWM_CHANNEL_0_GAUCHE, frequence_pwm, resolution_pwm);
    ledcSetup(PWM_CHANNEL_1_DROITE, frequence_pwm, resolution_pwm);
    ledcAttachPin(PWM_Gauche, PWM_CHANNEL_0_GAUCHE);
    ledcAttachPin(PWM_Droite, PWM_CHANNEL_1_DROITE);
    pinMode(TOR_Gauche, OUTPUT);
    pinMode(TOR_Droite, OUTPUT);
}

void moteur_droit(int pwm)
{
    if(pwm >1023)   {

        pwm= 1023;
    }
    if(pwm <0)   {

        pwm= 0;
    }

    ledcWrite(PWM_CHANNEL_1_DROITE, pwm);
    digitalWrite(TOR_Droite, AVANCER);
}

void moteur_gauche(int pwm)
{    
    ledcWrite(PWM_CHANNEL_0_GAUCHE, pwm);
    digitalWrite(TOR_Gauche, AVANCER);
}