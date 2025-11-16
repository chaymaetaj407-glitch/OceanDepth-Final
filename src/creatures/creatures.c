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
                type_creature = (rand() % 3) + 1;
            } else if (profondeur < 500) {
                int choix = rand() % 3;
                if (choix == 0) type_creature = 0;
                else if (choix == 1) type_creature = 1;
                else type_creature = 3;
            } else {
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
                    strcpy(creatures[i].effet, "Frénésie sanguinaire");
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
                    creatures[i].atk_min = 12;
                    creatures[i].atk_max = 18;
                    creatures[i].defense = 3;
                    creatures[i].vitesse = 4;
                    strcpy(creatures[i].effet, "Charge perforante");
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
                    strcpy(creatures[i].effet, "Étreinte tentaculaire");
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
                    strcpy(creatures[i].effet, "Carapace durcie");
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

int appliquer_competence_creature(CreatureMarine* creature, int degats_base) {
    int degats_finaux = degats_base;
    
    // Poisson-Epee : "Charge perforante"
    if (strstr(creature->nom, "Poisson-Épée")) {
        return degats_finaux;
    }
    
    // Meduse : "Piqure paralysante"
    if (strstr(creature->nom, "Méduse")) {
        int chance = rand() % 100;
        if (chance < 25) {
            printf("%s⚡ La Méduse vous paralyse avec ses tentacules ! ⚡%s\n", 
                   "\033[35m", "\033[0m");
            return -1;
        }
        return degats_finaux;
    }
    
    // Kraken : "Etreinte tentaculaire"
    if (strstr(creature->nom, "Kraken")) {
        creature->attaques_consecutives++;
        if (creature->attaques_consecutives >= 2) {
            printf("%s🐙 Le Kraken vous ensérre de ses tentacules ! 🐙%s\n", 
                   "\033[35m", "\033[0m");
            printf("%sIl attaque 2 fois consécutivement !%s\n", 
                   "\033[33m", "\033[0m");
            creature->attaques_consecutives = 0;
            return degats_finaux * 2;
        }
        return degats_finaux;
    }
    
    // Requin : "Frenesie sanguinaire"
    if (strstr(creature->nom, "Requin")) {
        if (creature->pv < creature->pv_max / 2) {
            printf("%s🦈 Le Requin entre en FRÉNÉSIE SANGUINAIRE ! 🦈%s\n", 
                   "\033[31m", "\033[0m");
            printf("%sSes attaques sont 30%% plus puissantes !%s\n", 
                   "\033[33m", "\033[0m");
            degats_finaux = (int)(degats_finaux * 1.3);
        }
        return degats_finaux;
    }
    
    // Crabe : "Carapace durcie"
    if (strstr(creature->nom, "Crabe")) {
        return degats_finaux;
    }

    return degats_finaux;
}