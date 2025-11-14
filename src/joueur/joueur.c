#include "joueur.h"
#include <stdio.h>
#include <string.h>

// couleurs
#define RESET   "\033[0m"
#define ROUGE   "\033[31m"
#define VERT    "\033[32m"
#define JAUNE   "\033[33m"
#define CYAN    "\033[36m"
#define GRAS    "\033[1m"

void init_plongeur(Plongeur* p) {
    // valeurs de depart
    p->vie = 100;
    p->vie_max = 100;
    p->oxygene = 100;
    p->oxygene_max = 100;
    p->fatigue = 0;
    p->perles = 0;
    p->prof = 0;
    p->attaque = 15;
    p->defense = 5;
}

void afficher_barre(char* nom, int valeur, int max, int taille) {
    // eviter les valeurs bizarres
    if (valeur < 0) valeur = 0;
    if (valeur > max) valeur = max;
    
    // calcul nb carres remplis
    int rempli = (valeur * taille) / max;
    int vide = taille - rempli;
    
    // couleur selon niveau
    char* couleur = VERT;
    if (valeur <= max * 0.3) {
        couleur = ROUGE;  // critique
    } else if (valeur <= max * 0.6) {
        couleur = JAUNE;  // moyen
    }
    
    printf("%s%-10s [", GRAS, nom);
    
    // partie remplie
    printf("%s", couleur);
    int i;
    for (i = 0; i < rempli; i++) {
        printf("█");
    }
    printf("%s", RESET);
    
    // partie vide
    for (i = 0; i < vide; i++) {
        printf("▒");
    }
    
    printf("] %d/%d%s\n", valeur, max, RESET);
}

void afficher_plongeur(Plongeur* p, int profondeur) {
    printf("\n");
    printf("%s╔══════════════════════════════════════════════════════════════╗%s\n", CYAN, RESET);
    printf("%s║  OceanDepths - Profondeur: -%dm          Perles: %d           ║%s\n", 
           CYAN, profondeur, p->perles, RESET);
    printf("%s╚══════════════════════════════════════════════════════════════╝%s\n", CYAN, RESET);
    printf("\n");
    
    // barres
    afficher_barre("Vie", p->vie, p->vie_max, 50);
    afficher_barre("Oxygene", p->oxygene, p->oxygene_max, 50);
    
    // fatigue differente
    printf("%s%-10s [", GRAS, "Fatigue");
    int i;
    for (i = 0; i < p->fatigue; i++) {
        printf("%s█%s", ROUGE, RESET);
    }
    for (i = p->fatigue; i < 5; i++) {
        printf("▒");
    }
    printf("] %d/5%s\n", p->fatigue, RESET);
    
    // alerte oxygene
    if (p->oxygene <= 10) {
        printf("\n%s%s⚠️  ALERTE CRITIQUE - OXYGENE EPUISE ! ⚠️%s\n", GRAS, ROUGE, RESET);
        printf("%sUtilisez une capsule ou remontez !%s\n", ROUGE, RESET);
    }
    
    printf("\n%s~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%s\n", 
           CYAN, RESET);
}

void perdre_vie(Plongeur* p, int degats) {
    // enlever defense
    int degats_reels = degats - p->defense;
    if (degats_reels < 1) degats_reels = 1;
    
    p->vie = p->vie - degats_reels;
    if (p->vie < 0) p->vie = 0;
    
    printf("%sVous perdez %d points de vie ! (PV: %d/%d)%s\n", 
           ROUGE, degats_reels, p->vie, p->vie_max, RESET);
}

int perdre_oxygene(Plongeur* p, int quantite) {
    p->oxygene = p->oxygene - quantite;
    if (p->oxygene < 0) p->oxygene = 0;
    
    printf("%sOxygène consommé: -%d (Reste: %d/%d)%s\n", 
           CYAN, quantite, p->oxygene, p->oxygene_max, RESET);
    
    // si plus d oxygene on perd des pv
    if (p->oxygene == 0) {
        printf("%s⚠️  MANQUE D'OXYGENE ! Vous perdez 5 PV !%s\n", ROUGE, RESET);
        p->vie = p->vie - 5;
        if (p->vie < 0) p->vie = 0;
    }
    
    // retourne 1 si critique
    if (p->oxygene <= 10) return 1;
    return 0;
}

void augmenter_fatigue(Plongeur* p, int valeur) {
    p->fatigue = p->fatigue + valeur;
    if (p->fatigue > 5) p->fatigue = 5;
    
    printf("%sFatigue augmentée: +%d (Total: %d/5)%s\n", 
           JAUNE, valeur, p->fatigue, RESET);
}

void recuperer_fatigue(Plongeur* p, int valeur) {
    int avant = p->fatigue;
    p->fatigue = p->fatigue - valeur;
    if (p->fatigue < 0) p->fatigue = 0;
    
    if (avant > p->fatigue) {
        printf("%sFatigue récupérée: -%d (Total: %d/5)%s\n", 
               VERT, valeur, p->fatigue, RESET);
    }
}

// TODO: verifier si ces valeurs sont bonnes
int attaques_possibles(Plongeur* p) {
    if (p->fatigue <= 1) return 3;
    if (p->fatigue <= 3) return 2;
    return 1;
}

void soigner(Plongeur* p, int montant) {
    int avant = p->vie;
    p->vie = p->vie + montant;
    if (p->vie > p->vie_max) p->vie = p->vie_max;
    
    int gagne = p->vie - avant;
    printf("%s💚 Vous récupérez %d PV ! (Total: %d/%d)%s\n", 
           VERT, gagne, p->vie, p->vie_max, RESET);
}

void remettre_oxygene(Plongeur* p, int montant) {
    int avant = p->oxygene;
    p->oxygene = p->oxygene + montant;
    if (p->oxygene > p->oxygene_max) p->oxygene = p->oxygene_max;
    
    int gagne = p->oxygene - avant;
    printf("%s💧 Oxygène restauré: +%d ! (Total: %d/%d)%s\n", 
           CYAN, gagne, p->oxygene, p->oxygene_max, RESET);
}

int plongeur_vivant(Plongeur* p) {
    if (p->vie > 0) return 1;
    return 0;
}

void gagner_perles(Plongeur* p, int nb) {
    p->perles = p->perles + nb;
    printf("%s💰 Vous gagnez %d perles ! (Total: %d)%s\n", 
           JAUNE, nb, p->perles, RESET);
}
