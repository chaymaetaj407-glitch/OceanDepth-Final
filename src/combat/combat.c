#include "combat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RESET   "\033[0m"
#define ROUGE   "\033[31m"
#define VERT    "\033[32m"
#define JAUNE   "\033[33m"
#define BLEU    "\033[34m"
#define CYAN    "\033[36m"
#define GRAS    "\033[1m"

void afficher_combat(Plongeur* p, CreatureMarine* creatures, int nb, int prof) {
    afficher_plongeur(p, prof);
    
    // liste des creatures
    printf("\n%s┌────────────────────── CRÉATURES MARINES ──────────────────────┐%s\n", 
           CYAN, RESET);
    
    int i;
    for (i = 0; i < nb; i++) {
        if (creatures[i].vivant == 1) {
            char* emoji = "🐠";
            if (strstr(creatures[i].nom, "Kraken")) emoji = "🐙";
            else if (strstr(creatures[i].nom, "Requin")) emoji = "🦈";
            else if (strstr(creatures[i].nom, "Méduse")) emoji = "🪼";
            else if (strstr(creatures[i].nom, "Crabe")) emoji = "🦀";
            else if (strstr(creatures[i].nom, "Poisson")) emoji = "🐠";
            
            printf("%s│ %s %s%s", CYAN, emoji, GRAS, RESET);
            printf("%s%-20s ", creatures[i].nom, CYAN);
            printf("(%d/%d PV)", creatures[i].pv, creatures[i].pv_max);
            printf(" [%s%s%s]", JAUNE, creatures[i].effet, CYAN);
            printf("%s%s", CYAN, RESET);
            printf("%s | %s%s\n", CYAN, GRAS, RESET);
        }
    }
    
    printf("%s└───────────────────────────────────────────────────────────────┘%s\n", 
           CYAN, RESET);
}

void afficher_menu(Plongeur* p, int attaques_restantes) {
    printf("\n%s╔════════════════ ACTIONS DISPONIBLES ═══════════════╗%s\n", 
           VERT, RESET);
    printf("%s║%s 1 - Attaquer avec harpon (%d attaque%s restante%s)    %s║%s\n", 
           VERT, RESET, 
           attaques_restantes, 
           attaques_restantes > 1 ? "s" : "",
           attaques_restantes > 1 ? "s" : "",
           VERT, RESET);
    printf("%s║%s 2 - Utiliser compétence marine                     %s║%s\n", 
           VERT, RESET, VERT, RESET);
    printf("%s║%s 3 - Consommer objet                                %s║%s\n", 
           VERT, RESET, VERT, RESET);
    printf("%s║%s 4 - Terminer le tour                               %s║%s\n", 
           VERT, RESET, VERT, RESET);
    printf("%s╚════════════════════════════════════════════════════╝%s\n", 
           VERT, RESET);
    printf("> ");
}

// calcul simple: attaque - defense
int calculer_degats(int attaque, int defense, int variable) {
    int degats = attaque;
    
    // ajouter variation si demande
    if (variable == 1) {
        int variation = (rand() % 11) - 5;
        degats = degats + variation;
    }
    
    degats = degats - defense;
    
    // min 1
    if (degats < 1) degats = 1;
    
    return degats;
}

// Calcul des degats d'une creature avec ses competences speciales
int calculer_degats_creature(CreatureMarine* c, int defense_joueur) {
    // Degats de base
    int degats = (c->atk_min + c->atk_max) / 2;
    degats = degats + (rand() % 6) - 3;
    
    // Applique la competence de la creature
    int resultat_competence = appliquer_competence_creature(c, degats);
    
    if (resultat_competence == -1) {
        return -1;
    }
    
    degats = resultat_competence;
    
    int defense_finale = defense_joueur;
    
    if (strstr(c->nom, "Poisson-Épée")) {
        defense_finale = defense_joueur - 2;
        if (defense_finale < 0) defense_finale = 0;
        printf("%s⚔️  Le Poisson-Épée perce votre défense ! ⚔️%s\n", 
               JAUNE, RESET);
    }
    
    degats = degats - defense_finale;
    
    if (degats < 1) degats = 1;
    
    return degats;
}

void animation_attaque(char* attaquant, char* cible, int degats) {
    printf("\n");
    printf("%s╔════════════════════ COMBAT SOUS-MARIN ════════════════════╗%s\n", 
           BLEU, RESET);
    printf("%s║%s %s attaque %s avec le harpon !           %s║%s\n", 
           BLEU, RESET, attaquant, cible, BLEU, RESET);
    printf("%s║                                                           ║%s\n", 
           BLEU, RESET);
    printf("%s║%s    PLONGEUR    %sVS%s      CRÉATURE                             %s║%s\n", 
           BLEU, RESET, ROUGE, RESET, BLEU, RESET);
    printf("%s║%s       🤿         %s🎯%s         🦈                            %s║%s\n", 
           BLEU, RESET, JAUNE, RESET, BLEU, RESET);
    printf("%s║%s    ════════►   ◄════════                                   %s║%s\n", 
           BLEU, RESET, BLEU, RESET);
    printf("%s║                                                          ║%s\n", 
           BLEU, RESET);
    printf("%s║%s 💥 Dégâts infligés: %s%d points%s                              %s║%s\n", 
           BLEU, RESET, ROUGE, degats, RESET, BLEU, RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n", 
           BLEU, RESET);
    printf("\n");
}

ResultatAttaque attaquer(Plongeur* p, CreatureMarine* c, int prof) {
    ResultatAttaque resultat;
    resultat.degats = 0;
    resultat.oxygene_utilise = 0;
    resultat.fatigue_ajoutee = 0;
    resultat.critique = 0;
    resultat.paralysie_activee = 0;
    
    // check si vivante
    if (c->vivant == 0) return resultat;
    
    // calcul degats
    resultat.degats = calculer_degats(p->attaque, c->defense, 1);
    
    // Crabe Geant : "Carapace durcie"
    if (strstr(c->nom, "Crabe Géant")) {
        int reduction = (int)(resultat.degats * 0.2);
        resultat.degats = resultat.degats - reduction;
        if (resultat.degats < 1) resultat.degats = 1;
        printf("\n%s🛡️  La carapace du Crabe absorbe %d dégâts ! 🛡️%s\n", 
               CYAN, reduction, RESET);
    }
    
    // coup critique 10%
    int chance = rand() % 100;
    if (chance < 10) {
        resultat.critique = 1;
        resultat.degats = (int)(resultat.degats * 1.5);
        printf("%s✨ COUP CRITIQUE ! ✨%s\n", JAUNE, RESET);
    }
    
    // afficher
    animation_attaque("Le Plongeur", c->nom, resultat.degats);
    
    // infliger degats
    c->pv = c->pv - resultat.degats;
    if (c->pv <= 0) {
        c->pv = 0;
        c->vivant = 0;
        printf("%s💀 %s a été vaincu !%s\n", VERT, c->nom, RESET);
    } else {
        // riposte
        printf("%s%s riposte ! 🦈%s\n", ROUGE, c->nom, RESET);
        int degats_riposte = calculer_degats_creature(c, p->defense);
        
        // Si la fonction retourne -1, joueur paralysé
        if (degats_riposte == -1) {
            resultat.paralysie_activee = 1;
            degats_riposte = calculer_degats((c->atk_min + c->atk_max) / 2, p->defense, 1);
        }
        
        perdre_vie(p, degats_riposte);
    }
    
    // Consommation oxygene
    resultat.oxygene_utilise = calculer_conso_oxygene(prof, 0);
    int etat_oxy = perdre_oxygene(p, resultat.oxygene_utilise);
    
    if (etat_oxy == 1) {
        printf("%s💡 Conseil: Terminez vite le combat ou restaurez votre oxygène !%s\n", 
               JAUNE, RESET);
    } else if (etat_oxy == 2) {
        printf("%s☠️  DANGER IMMINENT ! Vous perdrez 5 PV à chaque tour !%s\n", 
               ROUGE, RESET);
    }
    
    // fatigue
    resultat.fatigue_ajoutee = 1;
    augmenter_fatigue(p, resultat.fatigue_ajoutee);
    
    return resultat;
}

int compter_vivants(CreatureMarine* creatures, int nb) {
    int count = 0;
    int i;
    for (i = 0; i < nb; i++) {
        if (creatures[i].vivant == 1) count++;
    }
    return count;
}

int choisir_cible(CreatureMarine* creatures, int nb) {
    printf("\n%sSélectionnez votre cible:%s\n", GRAS, RESET);
    
    int cibles[10];
    int nb_cibles = 0;
    
    int i;
    for (i = 0; i < nb; i++) {
        if (creatures[i].vivant == 1) {
            cibles[nb_cibles] = i;
            printf("%s[%d]%s %s (%d/%d PV)\n", 
                   JAUNE, nb_cibles + 1, RESET,
                   creatures[i].nom,
                   creatures[i].pv,
                   creatures[i].pv_max);
            nb_cibles++;
        }
    }
    
    printf("%s[0]%s Annuler\n", JAUNE, RESET);
    printf("> ");
    
    int choix;
    if (scanf("%d", &choix) != 1) {
        while (getchar() != '\n');  // vider buffer
        return -1;
    }
    
    if (choix == 0) return -1;
    if (choix < 1 || choix > nb_cibles) {
        printf("%sChoix invalide !%s\n", ROUGE, RESET);
        return -1;
    }
    
    return cibles[choix - 1];
}

int faire_tour(Plongeur* p, CreatureMarine* creatures, int nb, int prof) {
    afficher_combat(p, creatures, nb, prof);
    
    // actions joueur
    int attaques_max = attaques_possibles(p);
    int attaques_faites = 0;
    int joueur_paralyse = 0;
    
    while (attaques_faites < attaques_max) {
        afficher_menu(p, attaques_max - attaques_faites);
        
        int choix;
        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n');
            printf("%sEntrée invalide !%s\n", ROUGE, RESET);
            continue;
        }
        
        if (choix == 1) {
            // attaquer
            int cible = choisir_cible(creatures, nb);
            if (cible >= 0) {
                ResultatAttaque res = attaquer(p, &creatures[cible], prof);
                attaques_faites++;
                
                // Si la Méduse a paralysé le joueur
                if (res.paralysie_activee == 1) {
                    joueur_paralyse = 1;
                }
                
                // check victoire
                if (compter_vivants(creatures, nb) == 0) {
                    printf("\n%s🎉 VICTOIRE ! Toutes les créatures sont vaincues ! 🎉%s\n", 
                           VERT, RESET);
                    return 0;
                }
                
                // check defaite
                if (plongeur_vivant(p) == 0) {
                    printf("\n%s💀 DÉFAITE ! Vous avez succombé aux profondeurs... 💀%s\n", 
                           ROUGE, RESET);
                    return 0;
                }
                
                // Si paralysé, fin du tour
                if (joueur_paralyse == 1) {
                    printf("%s⚡ Vous êtes paralysé ! Vous ne pouvez plus attaquer. ⚡%s\n", 
                           JAUNE, RESET);
                    break;
                }
            }
        } else if (choix == 2) {
            printf("%s⚠️  Compétences non implémentées !%s\n", JAUNE, RESET);
        } else if (choix == 3) {
            printf("%s⚠️  Inventaire non implémenté !%s\n", JAUNE, RESET);
        } else if (choix == 4) {
            printf("%s➡️  Fin du tour...%s\n", CYAN, RESET);
            break;
        } else {
            printf("%sChoix invalide !%s\n", ROUGE, RESET);
        }
    }
    
    // fin du tour
    printf("\n%s--- Fin du tour ---%s\n", CYAN, RESET);
    int cout_tour = calculer_conso_oxygene(prof, 2);
    int etat_oxy = perdre_oxygene(p, cout_tour);
    
    // Afficher info selon etat oxygene
    if (etat_oxy == 2) {
        printf("%s☠️  Vous êtes en train de vous noyer ! Remontez vite !%s\n", 
               ROUGE, RESET);
    }
    
    recuperer_fatigue(p, 1);
    
    if (plongeur_vivant(p) == 0) {
        printf("\n%s💀 DÉFAITE ! Vous avez succombé aux profondeurs... 💀%s\n", 
               ROUGE, RESET);
        return 0;
    }
    
    printf("\n%sAppuyez sur Entrée pour continuer...%s", CYAN, RESET);
    while (getchar() != '\n');
    getchar();
    
    return 1;
}