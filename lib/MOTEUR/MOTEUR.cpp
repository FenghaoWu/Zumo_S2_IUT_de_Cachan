#include "MOTEUR.h"
#include <Arduino.h>

#define PWM_Gauche 5
#define TOR_Gauche 18
#define TOR_Droite 17
#define PWM_Droite 16

int resolution_moteur = 10;
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
    // int complement_pwm;
    // complement_pwm = pwm - (pow(2, resolution_moteur) - 1);
    // complement_pwm = abs(complement_pwm);
    // ledcWrite(PWM_CHANNEL_2_DROITE, complement_pwm);

    ledcWrite(PWM_CHANNEL_1_DROITE, pwm);
    digitalWrite(TOR_Droite, HIGH);
}

void moteur_gauche(int pwm)
{
    // int complement_pwm;
    // complement_pwm = pwm - (pow(2, resolution_moteur) - 1);
    // complement_pwm = abs(complement_pwm); // Ensure complement_pwm is positive
    // ledcWrite(PWM_CHANNEL_0_GAUCHE, complement_pwm);
    
    ledcWrite(PWM_CHANNEL_0_GAUCHE, pwm);
    digitalWrite(TOR_Gauche, HIGH);
}
