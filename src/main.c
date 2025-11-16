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
#define ROUGE   "\033[31m"


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
    printf("  • Plongez dans les prodondeurs mystérieuses de l'océan et incarnez un explorateur\n");
    printf("  • Gérez vos ressources : %sPV, Oxygene, Fatigue%s\n", VERT, RESET);
    printf("  • L'oxygene diminue à chaque action\n");
    printf("  • La fatigue limite vos attaques par tour\n");
    printf("  • Vaincez toutes les créatures pour gagner !\n");
    printf("\n%sAppuyez sur Entrée pour commencer...%s\n", CYAN, RESET);
    getchar();
}

int main() {
    srand(time(NULL));

    afficher_titre();
    afficher_instructions();

    // creer joueur
    Plongeur joueur;
    init_plongeur(&joueur);

    CreatureMarine creatures[4];
    int profondeur = 30;
    int continuer = 1;

    printf("%s\n🏊 Vous plongez à -%dm de profondeur...%s\n", CYAN, profondeur, RESET);

    // Generation automatique selon la profondeur
    generer_creatures(creatures, profondeur);

    // Compter les creatures generees
    int nb_creatures = 0;
    for (int i = 0; i < 4; i++) {
        if (creatures[i].vivant == 1) {
            nb_creatures++;
        }
    }

    printf("%s🦈 %d créature%s marine%s vous repère%s !%s\n\n",
           CYAN, nb_creatures,
           nb_creatures > 1 ? "s" : "",
           nb_creatures > 1 ? "s" : "",
           nb_creatures > 1 ? "nt" : "",
           RESET);

    // boucle combat
    int combat_actif = 1;
    int numero_tour = 1;

    while (combat_actif == 1) {
        printf("\n%s%s════════════════════════════════ TOUR %d ════════════════════════════════%s\n",
               GRAS, CYAN, numero_tour, RESET);

        combat_actif = faire_tour(&joueur, creatures, 4, profondeur);
        numero_tour++;

        // securite
        if (numero_tour > 20) {
            printf("%s⚠️  Combat trop long, fin de la demo !%s\n", CYAN, RESET);
            break;
        }
    }
    // resultat du combat
    printf("\n");
    printf("%s%s╔════════════════════════════════════════════════════════════════╗%s\n",
           GRAS, CYAN, RESET);
    printf("%s%s║                      FIN DU COMBAT                             ║%s\n",
           GRAS, CYAN, RESET);
    printf("%s%s╚════════════════════════════════════════════════════════════════╝%s\n",
           GRAS, CYAN, RESET);

    if (plongeur_vivant(&joueur) == 1) {
        printf("\n%s🎉 Félicitations ! Vous avez survécu !%s\n", VERT, RESET);
        printf("%sStatistiques actuelles:%s\n", CYAN, RESET);
        printf("  • PV restants: %d/%d\n", joueur.vie, joueur.vie_max);
        printf("  • Oxygene: %d/%d\n", joueur.oxygene, joueur.oxygene_max);
        printf("  • Perles: %d\n", joueur.perles);
    } else {
        printf("\n%s💀 Vous avez péri dans les profondeurs...%s\n", CYAN, RESET);
        printf("%sMais ne vous découragez pas ! Réessayez !%s\n", CYAN, RESET);
    }
    // choix de profondeur
    int choix;
    printf("\n%s🌊 Que souhaitez-vous faire maintenant ?%s\n", CYAN, RESET);
    printf("  1️⃣  Rester à la même profondeur\n");
    printf("  2️⃣  Explorer plus profondément\n");
    printf("  3️⃣  Remonter à la surface (fin de l'expédition)\n");
    printf("> ");
    if (scanf("%d", &choix) != 1) {
        while (getchar() != '\n');
        choix = 3; // sécurité : quitter si entrée invalide
    }
    while (getchar() != '\n');

    if (choix == 1) {
        printf("%sVous restez à -%dm pour explorer davantage...%s\n", CYAN, profondeur, RESET);
    } else if (choix == 2) {
        profondeur += 50;
        printf("%sVous descendez plus profondément... (-%dm)%s\n", CYAN, profondeur, RESET);
    } else if (choix == 3) {
        printf("%s🚤 Vous remontez à la surface. Mission terminée !%s\n", VERT, RESET);
        continuer = 0;
    } else {
        printf("%sChoix invalide, fin de la mission.%s\n", ROUGE, RESET);
        continuer = 0;
    }

    // Petite pause avant la suite
    printf("\n%sAppuyez sur Entrée pour continuer...%s", CYAN, RESET);
    getchar();
    // resultat
    printf("\n");
    printf("%s%s╔════════════════════════════════════════════════════════════════╗%s\n",
           GRAS, CYAN, RESET);
    printf("%s%s║                      FIN DE LA DEMO                            ║%s\n",
           GRAS, CYAN, RESET);
    printf("%s%s╚════════════════════════════════════════════════════════════════╝%s\n",
           GRAS, CYAN, RESET);

    if (plongeur_vivant(&joueur) == 1) {
        printf("\n%s🎉 Félicitations ! Vous avez survécu !%s\n", VERT, RESET);
        printf("%sStatistiques finales:%s\n", CYAN, RESET);
        printf("  • PV restants: %d/%d\n", joueur.vie, joueur.vie_max);
        printf("  • Oxygene: %d/%d\n", joueur.oxygene, joueur.oxygene_max);
        printf("  • Perles: %d\n", joueur.perles);
    } else {
        printf("\n%s💀 Vous avez péri dans les profondeurs...%s\n", CYAN, RESET);
        printf("%sMais ne vous découragez pas ! Réessayez !%s\n", CYAN, RESET);
    }

    printf("\n");

    return 0;
}