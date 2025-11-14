#ifndef COMBAT_H
#define COMBAT_H

#include "../joueur/joueur.h"
#include "../creatures/creatures.h"

// resultat d'une attaque
typedef struct {
    int degats;
    int oxygene_utilise;
    int fatigue_ajoutee;
    int critique;
} ResultatAttaque;

// afficher interface combat
void afficher_combat(Plongeur* p, CreatureMarine* creatures, int nb, int prof);

// menu actions
void afficher_menu(Plongeur* p, int attaques_restantes);

// attaquer
ResultatAttaque attaquer(Plongeur* p, CreatureMarine* c, int prof);

// calcul degats
int calculer_degats(int attaque, int defense, int variable);

// animation
void animation_attaque(char* attaquant, char* cible, int degats);

// compter vivants
int compter_vivants(CreatureMarine* creatures, int nb);

// choisir cible
int choisir_cible(CreatureMarine* creatures, int nb);

// tour de combat
int faire_tour(Plongeur* p, CreatureMarine* creatures, int nb, int prof);

#endif