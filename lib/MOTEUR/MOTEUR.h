#ifndef _MOTEUR_H
#define _MOTEUR_H
#define PWM_GAUCHE 5
#define TOR_GAUCHE 18
#define TOR_DROITE 17
#define PWM_DROITE 16

// const int PWM_FREQUENCY = 20000;
#define PWM_RESOLUTION  10
#define PWM_CHANNEL_GAUCHE 0
#define PWM_CHANNEL_DROITE 1

void setup_moteur_pwm(float frequence_pwm, float resolution_pwm);
void moteur_droit(int pwm);
void moteur_gauche(int pwm);

#endif