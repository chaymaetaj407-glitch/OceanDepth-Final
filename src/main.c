#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "joueur/joueur.h"
#include "combat/combat.h"

#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define VERT    "\033[32m"
#define GRAS    "\033[1m"

// creer des creatures de test
// TODO: remplacer par la vraie fonction de l'etape 1
void creer_test_creatures(CreatureMarine* creatures, int* nb) {
    // requin
    creatures[0].id = 1;
    sprintf(creatures[0].nom, "Requin-Tigre");
    creatures[0].pv_max = 89;
    creatures[0].pv = 89;
    creatures[0].atk_min = 15;
    creatures[0].atk_max = 25;
    creatures[0].defense = 3;
    creatures[0].vitesse = 8;
    sprintf(creatures[0].effet, "aucun");
    creatures[0].vivant = 1;
    
    // meduse
    creatures[1].id = 2;
    sprintf(creatures[1].nom, "Meduse Bleue");
    creatures[1].pv_max = 34;
    creatures[1].pv = 34;
    creatures[1].atk_min = 8;
    creatures[1].atk_max = 15;
    creatures[1].defense = 1;
    creatures[1].vitesse = 5;
    sprintf(creatures[1].effet, "paralysie");
    creatures[1].vivant = 1;
    
    // poisson-epee
    creatures[2].id = 3;
    sprintf(creatures[2].nom, "Poisson-Epee");
    creatures[2].pv_max = 78;
    creatures[2].pv = 78;
    creatures[2].atk_min = 18;
    creatures[2].atk_max = 28;
    creatures[2].defense = 4;
    creatures[2].vitesse = 7;
    sprintf(creatures[2].effet, "aucun");
    creatures[2].vivant = 1;
    
    *nb = 3;
}

void afficher_titre() {
    printf("\n");
    printf("%s%s╔════════════════════════════════════════════════════════════════╗%s\n", 
           GRAS, CYAN, RESET);
    printf("%s%s║                                                                ║%s\n", 
           GRAS, CYAN, RESET);
    printf("%s%s║           🌊  OCEANDEPTH - ETAPE 2 DEMO  🤿                   ║%s\n", 
           GRAS, CYAN, RESET);
    printf("%s%s║              Systeme d'Attaque du Plongeur                     ║%s\n", 
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
    
    // creer creatures
    CreatureMarine creatures[10];
    int nb_creatures = 0;
    creer_test_creatures(creatures, &nb_creatures);
    
    int profondeur = 120;
    
    printf("%s\n🏊 Vous plongez a -%dm de profondeur...%s\n", CYAN, profondeur, RESET);
    printf("%s🦈 Des creatures marines vous reperent !%s\n\n", CYAN, RESET);
    
    // boucle combat
    int combat_actif = 1;
    int numero_tour = 1;
    
    while (combat_actif == 1) {
        printf("\n%s%s═══════════════════ TOUR %d ═══════════════════%s\n", 
               GRAS, CYAN, numero_tour, RESET);
        
        combat_actif = faire_tour(&joueur, creatures, nb_creatures, profondeur);
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
