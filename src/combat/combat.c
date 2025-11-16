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
    printf("\n%s┌────────────────────── CREATURES MARINES ──────────────────────┐%s\n", 
           CYAN, RESET);
    
    int i;
    for (i = 0; i < nb; i++) {
        if (creatures[i].vivant == 1) {
            // emoji
            char* emoji = "🐠";
            if (strstr(creatures[i].nom, "Kraken")) emoji = "🐙";
            else if (strstr(creatures[i].nom, "Requin")) emoji = "🦈";
            else if (strstr(creatures[i].nom, "Meduse")) emoji = "🪼";
            else if (strstr(creatures[i].nom, "Crabe")) emoji = "🦀";
            else if (strstr(creatures[i].nom, "Poisson")) emoji = "🐠";
            
            printf("%s│ %s %s%s", CYAN, emoji, GRAS, RESET);
            printf("%s%-20s ", creatures[i].nom, CYAN);
            printf("(%d/%d PV)", creatures[i].pv, creatures[i].pv_max);
            
            // effet special
            if (strcmp(creatures[i].effet, "aucun") != 0) {
                printf(" [%s%s%s]", JAUNE, creatures[i].effet, CYAN);
            }
            
            printf("%s%s\n", CYAN, RESET);
        }
    }
    
    printf("%s└───────────────────────────────────────────────────────────────┘%s\n", 
           CYAN, RESET);
}

void afficher_menu(Plongeur* p, int attaques_restantes) {
    printf("\n%s╔════════════════ ACTIONS DISPONIBLES ═══════════════╗%s\n",
           VERT, RESET);
    printf("%s║%s 1 - Attaquer avec harpon (%d attaque%s restante%s)%s║%s\n",
           VERT, RESET,
           attaques_restantes,
           attaques_restantes > 1 ? "s" : "",
           attaques_restantes > 1 ? "s" : "",
           VERT, RESET);
    printf("%s║%s 2 - ⚡ Décharge Électrique (18 oxygène, Dégâts–30)%s  ║%s\n",
           VERT, RESET, VERT, RESET);
    printf("%s║%s 3 - 🌀 Tourbillon Aquatique (22 oxygène, -2 vitesse)%s║%s\n",
           VERT, RESET, VERT, RESET);
    printf("%s║%s 4 - Consommer objet                                %s║%s\n",
           VERT, RESET, VERT, RESET);
    printf("%s║%s 5 - Terminer le tour                               %s║%s\n",
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

void animation_attaque(char* attaquant, char* cible, int degats) {
    printf("\n");
    printf("%s╔════════════════════ COMBAT SOUS-MARIN ════════════════════╗%s\n",
           BLEU, RESET);
    printf("%s║%s %s attaque %s avec le harpon ! %s                       ║%s\n",
           BLEU, RESET, attaquant, cible, BLEU, RESET);
    printf("%s║                                                            ║%s\n",
           BLEU, RESET);
    printf("%s║%s    PLONGEUR    %sVS%s      CRÉATURE                       %s║%s\n",
           BLEU, RESET, ROUGE, RESET, BLEU, RESET);
    printf("%s║%s       🤿         %s🎯%s         🦈                           %s║%s\n",
           BLEU, RESET, JAUNE, RESET, BLEU, RESET);
    printf("%s║%s    ════════►   ◄════════                                %s║%s\n",
           BLEU, RESET, BLEU, RESET);
    printf("%s║                                                            ║%s\n",
           BLEU, RESET);
    printf("%s║%s 💥 Dégâts infligés: %s%d points%s                           %s║%s\n",
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

    // check si vivante
    if (c->vivant == 0) return resultat;

    // calcul degats
    resultat.degats = calculer_degats(p->attaque, c->defense, 1);

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
        int degats_riposte = calculer_degats((c->atk_min + c->atk_max) / 2, p->defense, 1);
        perdre_vie(p, degats_riposte);
    }

    // conso oxygene
    resultat.oxygene_utilise = 2 + (prof / 100);
    perdre_oxygene(p, resultat.oxygene_utilise);

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

// FIXME: ameliorer cette fonction plus tard
int faire_tour(Plongeur* p, CreatureMarine* creatures, int nb, int prof) {
    afficher_combat(p, creatures, nb, prof);

    // actions joueur
    int attaques_max = attaques_possibles(p);
    int attaques_faites = 0;

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
                attaquer(p, &creatures[cible], prof);
                attaques_faites++;

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
            }
        } else if (choix == 2) {
            // Compétence : Décharge Électrique
            int cout_oxygene = 18;

            if (p->oxygene < cout_oxygene) {
                printf("%s❌ Pas assez d'oxygène pour utiliser la Décharge Électrique !%s\n", ROUGE, RESET);
            } else {
                printf("%s⚡ Vous utilisez Décharge Électrique ! ⚡%s\n", JAUNE, RESET);

                // Consommation d'oxygène
                perdre_oxygene(p, cout_oxygene);

                // Dégâts de zone
                int total_victimes = 0;
                for (int i = 0; i < nb; i++) {
                    if (creatures[i].vivant == 1) {
                        int degats = 20 + rand() % 11; // 20–30
                        creatures[i].pv -= degats;
                        printf("%s💥 %s subit %d dégâts électriques !%s\n",
                               CYAN, creatures[i].nom, degats, RESET);
                        if (creatures[i].pv <= 0) {
                            creatures[i].pv = 0;
                            creatures[i].vivant = 0;
                            printf("%s💀 %s est foudroyé !%s\n", VERT, creatures[i].nom, RESET);
                        }
                        total_victimes++;
                    }
                }

                augmenter_fatigue(p, 2); // plus fatigant qu’une attaque normale

                if (compter_vivants(creatures, nb) == 0) {
                    printf("\n%s🎉 VICTOIRE ! Toutes les créatures sont éliminées ! 🎉%s\n",
                           VERT, RESET);
                    return 0;
                }

                if (plongeur_vivant(p) == 0) {
                    printf("\n%s💀 Vous avez succombé après l’effort ! 💀%s\n", ROUGE, RESET);
                    return 0;
                }
            }
        } else if (choix == 3) {
            printf("%s⚠️  Inventaire non implementé !%s\n", JAUNE, RESET);
        } else if (choix == 4) {
            // 🌀 Tourbillon Aquatique
            int cout_oxygene = 22;

            if (p->oxygene < cout_oxygene) {
                printf("%s❌ Pas assez d'oxygène pour lancer le Tourbillon Aquatique !%s\n", ROUGE, RESET);
            } else {
                printf("%s🌀 Vous invoquez un Tourbillon Aquatique !%s\n", CYAN, RESET);

                // Consomme l'oxygène
                perdre_oxygene(p, cout_oxygene);

                // Mélange les ennemis vivants
                int vivant_indices[10];
                int nb_vivants = 0;
                for (int i = 0; i < nb; i++) {
                    if (creatures[i].vivant == 1) {
                        vivant_indices[nb_vivants++] = i;
                    }
                }

                // Mélange simple (Fisher-Yates)
                for (int i = nb_vivants - 1; i > 0; i--) {
                    int j = rand() % (i + 1);
                    if (i != j) {
                        CreatureMarine temp = creatures[vivant_indices[i]];
                        creatures[vivant_indices[i]] = creatures[vivant_indices[j]];
                        creatures[vivant_indices[j]] = temp;
                    }
                }

                // Réduction de la vitesse de chaque ennemi vivant
                for (int i = 0; i < nb; i++) {
                    if (creatures[i].vivant == 1) {
                        creatures[i].vitesse -= 2;
                        if (creatures[i].vitesse < 0) creatures[i].vitesse = 0;
                    }
                }

                printf("%s🌪️ Les ennemis sont désorientés ! Leur vitesse diminue de 2.%s\n", JAUNE, RESET);
                augmenter_fatigue(p, 1);
            }
        }
        else {
            printf("%sChoix invalide !%s\n", ROUGE, RESET);
        }
    }

    // fin du tour
    printf("\n%s--- Fin du tour ---%s\n", CYAN, RESET);
    int cout = 2 + (prof / 150);
    perdre_oxygene(p, cout);

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