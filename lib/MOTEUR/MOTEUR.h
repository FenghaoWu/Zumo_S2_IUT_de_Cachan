#ifndef _MOTEUR_H
#define _MOTEUR_H

void setup_moteur_pwm(float frequence_pwm, float resolution_pwm);
void moteur_droit(int pwm);
void moteur_gauche(int pwm);

#endif