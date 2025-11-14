#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "joueur/joueur.h"
#include "combat/combat.h"
#include "creatures/creatures.h"

#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define VERT    "\033[32m"
#define GRAS    "\033[1m"

void afficher_titre() {
    printf("\n");
    printf("%s%s╔════════════════════════════════════════════════════════════════╗%s\n",
           GRAS, CYAN, RESET);
    printf("%s%s║                                                                ║%s\n",
           GRAS, CYAN, RESET);
    printf("%s%s║                          OCEANDEPTH                            ║%s\n",
           GRAS, CYAN, RESET);
    printf("%s%s║                         Projet Final                           ║%s\n",
           GRAS, CYAN, RESET);
    printf("%s%s║                                                                ║%s\n",
           GRAS, CYAN, RESET);
    printf("%s%s╚════════════════════════════════════════════════════════════════╝%s\n",
           GRAS, CYAN, RESET);
    printf("\n");
}

void afficher_instructions() {
    printf("%sℹ️  INSTRUCTIONS :%s\n", CYAN, RESET);
    printf("  • Gerez vos ressources : %sPV, Oxygene, Fatigue%s\n", VERT, RESET);
    printf("  • L'oxygene diminue a chaque action\n");
    printf("  • La fatigue limite vos attaques par tour\n");
    printf("  • Vaincez toutes les creatures pour gagner !\n");
    printf("\n%sAppuyez sur Entree pour commencer...%s\n", CYAN, RESET);
    getchar();
}

int main() {
    // init random
    srand(time(NULL));

    afficher_titre();
    afficher_instructions();

    // creer joueur
    Plongeur joueur;
    init_plongeur(&joueur);

    CreatureMarine creatures[4];
    int profondeur = 120;

    printf("%s\n🏊 Vous plongez a -%dm de profondeur...%s\n", CYAN, profondeur, RESET);

    // Generation automatique selon la profondeur
    generer_creatures(creatures, profondeur);

    // Compter les creatures generees
    int nb_creatures = 0;
    for (int i = 0; i < 4; i++) {
        if (creatures[i].vivant == 1) {
            nb_creatures++;
        }
    }

    printf("%s🦈 %d creature%s marine%s vous repere%s !%s\n\n",
           CYAN, nb_creatures,
           nb_creatures > 1 ? "s" : "",
           nb_creatures > 1 ? "s" : "",
           nb_creatures > 1 ? "nt" : "",
           RESET);

    // boucle combat
    int combat_actif = 1;
    int numero_tour = 1;

    while (combat_actif == 1) {
        printf("\n%s%s═══════════════════ TOUR %d ═══════════════════%s\n",
               GRAS, CYAN, numero_tour, RESET);

        combat_actif = faire_tour(&joueur, creatures, 4, profondeur);
        numero_tour++;

        // securite
        if (numero_tour > 20) {
            printf("%s⚠️  Combat trop long, fin de la demo !%s\n", CYAN, RESET);
            break;
        }
    }

    // resultat
    printf("\n");
    printf("%s%s╔════════════════════════════════════════════════════════════════╗%s\n",
           GRAS, CYAN, RESET);
    printf("%s%s║                      FIN DE LA DEMO                            ║%s\n",
           GRAS, CYAN, RESET);
    printf("%s%s╚════════════════════════════════════════════════════════════════╝%s\n",
           GRAS, CYAN, RESET);

    if (plongeur_vivant(&joueur) == 1) {
        printf("\n%s🎉 Felicitations ! Vous avez survecu !%s\n", VERT, RESET);
        printf("%sStatistiques finales:%s\n", CYAN, RESET);
        printf("  • PV restants: %d/%d\n", joueur.vie, joueur.vie_max);
        printf("  • Oxygene: %d/%d\n", joueur.oxygene, joueur.oxygene_max);
        printf("  • Perles: %d\n", joueur.perles);
    } else {
        printf("\n%s💀 Vous avez peri dans les profondeurs...%s\n", CYAN, RESET);
        printf("%sMais ne vous decouragez pas ! Reessayez !%s\n", CYAN, RESET);
    }

    printf("\n");

    return 0;
}