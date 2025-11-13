#ifndef JOUEUR_H
#define JOUEUR_H

// structure du plongeur
typedef struct {
    int vie;
    int vie_max;
    int oxygene;
    int oxygene_max;
    int fatigue;        // de 0 a 5
    int perles;         // argent
    int prof;           // profondeur actuelle
    int attaque;
    int defense;
} Plongeur;

// init le plongeur au debut
void init_plongeur(Plongeur* p);

// afficher son etat
void afficher_plongeur(Plongeur* p, int profondeur);

// enlever des pv
void perdre_vie(Plongeur* p, int degats);

// consommer de l'oxygene
int perdre_oxygene(Plongeur* p, int quantite);

// gestion fatigue
void augmenter_fatigue(Plongeur* p, int valeur);
void recuperer_fatigue(Plongeur* p, int valeur);

// nb attaques possibles selon fatigue
int attaques_possibles(Plongeur* p);

// soigner
void soigner(Plongeur* p, int montant);
void remettre_oxygene(Plongeur* p, int montant);

// check si vivant
int plongeur_vivant(Plongeur* p);

// gagner des perles
void gagner_perles(Plongeur* p, int nb);

// afficher barre de progression
void afficher_barre(char* nom, int valeur, int max, int taille);

#endif
