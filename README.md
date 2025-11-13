# OceanDepth - Etape 2

## Groupe
- TAJ: Integration et tests
- ASSIA: Module joueur  
- JORDAN: Module combat

## Description

On a fait l'etape 2 du projet OceanDepth. C'est le systeme d'attaque du plongeur.

Le joueur peut attaquer des creatures marines et il faut gerer son oxygene et sa fatigue.

## Comment compiler

```bash
make
```

## Comment lancer

```bash
./build/oceandepths
```

## Ce qu'on a fait

### Module Joueur (ASSIA)
- Structure Plongeur avec vie, oxygene, fatigue, perles
- Fonctions pour initialiser et afficher le plongeur
- Barres de progression pour voir l'etat
- Alertes quand l'oxygene est critique

### Module Combat (JORDAN)
- Systeme d'attaque avec harpon
- Calcul des degats
- Animations de combat
- Gestion de l'oxygene qui diminue
- Systeme de fatigue qui limite les attaques

### Integration (TAJ)
- Assemblage des modules
- Main.c pour faire marcher le tout
- Makefile pour compiler facilement
- Tests avec valgrind

## Comment ca marche

Le plongeur a 3 ressources:
- **Vie**: si ca tombe a 0 c'est game over
- **Oxygene**: diminue a chaque action, si 0 on perd de la vie
- **Fatigue**: limite le nombre d'attaques par tour
  - Fatigue 0-1: 3 attaques max
  - Fatigue 2-3: 2 attaques max  
  - Fatigue 4-5: 1 attaque max

Quand on attaque:
1. On choisit une creature
2. On calcule les degats = attaque - defense
3. On enleve les PV de la creature
4. Elle riposte si elle est encore vivante
5. On consomme de l'oxygene
6. La fatigue augmente

## Tests

On a teste avec valgrind pour verifier qu'il n'y a pas de fuites memoire:

```bash
make valgrind
```

Resultat: Pas de fuites detectees !

## Prochaines etapes

- Etape 3: Faire attaquer les creatures (ordre par vitesse, effets speciaux)
- Etape 4: Systeme de recompenses et inventaire
- Etape 5: Sauvegarde et chargement

## Problemes rencontres

- Au debut on avait des erreurs de compilation a cause des includes
- On a du changer les noms de variables pour eviter les conflits
- Sur Windows ca compile pas facilement, il faut utiliser Linux ou WSL

## Notes

Le code est fait en C avec la norme C99.
On utilise des couleurs ANSI pour rendre l'affichage plus joli.

Date de fin: 13 novembre 2025
