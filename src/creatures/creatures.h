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
    char effet[20];
    int vivant;
} CreatureMarine;

// Genere des creatures selon la profondeur
void generer_creatures(CreatureMarine creatures[4], int profondeur);

// Affiche les infos d'une creature
void afficher_creature(CreatureMarine creature);

#endif