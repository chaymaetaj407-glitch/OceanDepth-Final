#ifndef CREATURES_H
#define CREATURES_H

typedef struct {
    int id;
    char nom[30];
    int pv_max;
    int pv;
    int atk_min;
    int atk_max;
    int defense;
    int vitesse;
    char effet[30];
    int vivant;
    int attaques_consecutives;
    int reduction_active;
} CreatureMarine;

// Genere des creatures selon la profondeur
void generer_creatures(CreatureMarine creatures[4], int profondeur);

// Applique la competence speciale d'une creature
int appliquer_competence_creature(CreatureMarine* creature, int degats_base);

#endif