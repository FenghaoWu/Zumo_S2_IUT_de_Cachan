#include "MOTEUR.h"
#include <Arduino.h>

#define PWM_Gauche_A 5
#define PWM_Gauche_B 18
#define PWM_Droite_A 17
#define PWM_Droite_B 16

// const int PWM_FREQUENCY = 20000;
int resolution_moteur = 10;
const int PWM_CHANNEL_0_GAUCHE = 0;
const int PWM_CHANNEL_1_GAUCHE = 1;
const int PWM_CHANNEL_2_DROITE = 2;
const int PWM_CHANNEL_3_DROITE = 3;

// Config parametre pwm
void setup_moteur_pwm(float frequence_pwm, float resolution_pwm)
{
    resolution_moteur = resolution_pwm;

    ledcSetup(PWM_CHANNEL_0_GAUCHE, frequence_pwm, resolution_pwm);
    ledcSetup(PWM_CHANNEL_1_GAUCHE, frequence_pwm, resolution_pwm);
    ledcSetup(PWM_CHANNEL_2_DROITE, frequence_pwm, resolution_pwm);
    ledcSetup(PWM_CHANNEL_3_DROITE, frequence_pwm, resolution_pwm);
    ledcAttachPin(PWM_Gauche_A, PWM_CHANNEL_0_GAUCHE);
    ledcAttachPin(PWM_Gauche_B, PWM_CHANNEL_1_GAUCHE);
    ledcAttachPin(PWM_Droite_B, PWM_CHANNEL_2_DROITE);
    ledcAttachPin(PWM_Droite_A, PWM_CHANNEL_3_DROITE);
}

void moteur_droit(int pwm)
{
    int complement_pwm;
    complement_pwm = pwm - (pow(2, resolution_moteur) - 1);
    complement_pwm = abs(complement_pwm); // Ensure complement_pwm is positive

    ledcWrite(PWM_CHANNEL_2_DROITE, complement_pwm);
    ledcWrite(PWM_CHANNEL_3_DROITE, pwm);
    // Serial.print("PWM Droit: ");
    // Serial.print(pwm);
    // Serial.print(" Complement PWM Droit: ");
    // Serial.print(complement_pwm);
    // Serial.println();
}

void moteur_gauche(int pwm)
{
    int complement_pwm;
    complement_pwm = pwm - (pow(2, resolution_moteur) - 1);
    complement_pwm = abs(complement_pwm); // Ensure complement_pwm is positive

    ledcWrite(PWM_CHANNEL_0_GAUCHE, complement_pwm);
    ledcWrite(PWM_CHANNEL_1_GAUCHE, pwm);
    // Serial.print("PWM Gauche: ");
    // Serial.print(pwm);
    // Serial.print(" Complement PWM Gauche: ");
    // Serial.print(complement_pwm);
    // Serial.println();
}
