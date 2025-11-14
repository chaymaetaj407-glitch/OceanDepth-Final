#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "creatures.h"

void generer_creatures(CreatureMarine creatures[4], int profondeur) {
    int nb_creatures;
    
    // Nombre de creatures selon la profondeur
    if (profondeur < 100) {
        nb_creatures = 1;
    } else if (profondeur < 250) {
        nb_creatures = 1 + (rand() % 2);
    } else if (profondeur < 500) {
        nb_creatures = 1 + (rand() % 3);
    } else {
        nb_creatures = 2 + (rand() % 2);
    }
    
    int pv_min, pv_max;
    int type_creature;
    
    for (int i = 0; i < 4; i++) {
        if (i < nb_creatures) {
            creatures[i].id = i + 1;
            creatures[i].vivant = 1;
            
            // Selection de la créature selon la profondeur
            if (profondeur < 50) {
                type_creature = 2;
            } else if (profondeur < 100) {
                type_creature = (rand() % 2) + 1;
            } else if (profondeur < 250) {
                // Moyen (100-250m)
                type_creature = (rand() % 3) + 1;
            } else if (profondeur < 500) {
                // Profond (250-500m)
                int choix = rand() % 3;
                if (choix == 0) type_creature = 0;
                else if (choix == 1) type_creature = 1;
                else type_creature = 3;
            } else {
                // Très profond (500+)
                type_creature = rand() % 4;
                if (type_creature == 2) type_creature = 4;
            }
            
            switch(type_creature) {
                case 0:
                    strcpy(creatures[i].nom, "Requin-Tigre");
                    pv_min = 120;
                    pv_max = 180;
                    creatures[i].pv_max = pv_min + rand() % (pv_max - pv_min + 1);
                    creatures[i].pv = creatures[i].pv_max;
                    creatures[i].atk_min = 25;
                    creatures[i].atk_max = 40;
                    creatures[i].defense = 15;
                    creatures[i].vitesse = 3;
                    strcpy(creatures[i].effet, "aucun");
                    break;
                
                case 1:
                    strcpy(creatures[i].nom, "Méduse Bleue");
                    pv_min = 60;
                    pv_max = 100;
                    creatures[i].pv_max = pv_min + rand() % (pv_max - pv_min + 1);
                    creatures[i].pv = creatures[i].pv_max;
                    creatures[i].atk_min = 15;
                    creatures[i].atk_max = 25;
                    creatures[i].defense = 8;
                    creatures[i].vitesse = 7;
                    strcpy(creatures[i].effet, "Paralysie");
                    break;
                    
                case 2:
                    strcpy(creatures[i].nom, "Poisson-Épée");
                    pv_min = 20;
                    pv_max = 40;
                    creatures[i].pv_max = pv_min + rand() % (pv_max - pv_min + 1);
                    creatures[i].pv = creatures[i].pv_max;
                    creatures[i].atk_min = 8;
                    creatures[i].atk_max = 15;
                    creatures[i].defense = 3;
                    creatures[i].vitesse = 4;
                    strcpy(creatures[i].effet, "aucun");
                    break;
                    
                case 3:
                    strcpy(creatures[i].nom, "Kraken");
                    pv_min = 70;
                    pv_max = 90;
                    creatures[i].pv_max = pv_min + rand() % (pv_max - pv_min + 1);
                    creatures[i].pv = creatures[i].pv_max;
                    creatures[i].atk_min = 18;
                    creatures[i].atk_max = 28;
                    creatures[i].defense = 10;
                    creatures[i].vitesse = 8;
                    strcpy(creatures[i].effet, "aucun");
                    break;
                    
                case 4:
                    strcpy(creatures[i].nom, "Crabe Géant");
                    pv_min = 80;
                    pv_max = 120;
                    creatures[i].pv_max = pv_min + rand() % (pv_max - pv_min + 1);
                    creatures[i].pv = creatures[i].pv_max;
                    creatures[i].atk_min = 12;
                    creatures[i].atk_max = 20;
                    creatures[i].defense = 20;
                    creatures[i].vitesse = 2;
                    strcpy(creatures[i].effet, "aucun");
                    break;
            }
        } else {
            creatures[i].id = -1;
            creatures[i].vivant = 0;
            strcpy(creatures[i].nom, "");
            creatures[i].pv_max = 0;
            creatures[i].pv = 0;
            creatures[i].atk_min = 0;
            creatures[i].atk_max = 0;
            creatures[i].defense = 0;
            creatures[i].vitesse = 0;
            strcpy(creatures[i].effet, "");
        }
    }
}

void afficher_creature(CreatureMarine creature) {
    if (creature.vivant && creature.id != -1) {
        printf("\n=== %s ===\n", creature.nom);
        printf("PV: %d/%d\n", creature.pv, creature.pv_max);
        printf("Attaque: %d-%d\n", creature.atk_min, creature.atk_max);
        printf("Defense: %d\n", creature.defense);
        printf("Vitesse: %d\n", creature.vitesse);
        if (strcmp(creature.effet, "aucun") != 0) {
            printf("Effet special: %s\n", creature.effet);
        }
    }
}