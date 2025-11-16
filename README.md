# OceanDepth

## Groupe
- **Chaymae** : Integration et tests
- **Assia** : Module joueur  
- **Jordan** : Module combat / monstres

## 📖 Description du projet

OceanDepth est un jeu de simulation de plongée sous-marine en mode texte. Le joueur incarne un plongeur qui doit explorer les profondeurs océaniques, affronter des créatures marines dangereuses et gérer ses ressources vitales (vie, oxygène, fatigue) pour survivre.

Le projet implémente actuellement un système de combat complet avec génération dynamique de créatures selon la profondeur, compétences spéciales et gestion avancée des ressources.

## 🚀 Installation et lancement

### Compilation
```bash
make
```

### Exécution
```bash
make run
```
ou
```bash
./build/oceandepths
```

### Nettoyage
```bash
make clean
```

## 🎮 Fonctionnalités implémentées (version courte)

### Module Joueur (Assia)

- Statistiques complètes (PV, attaque, défense).
- Gestion de l’oxygène, de la fatigue et des alertes visuelles.
- Affichage du statut avec barres de progression colorées.
- Consommation d’oxygène variable selon la profondeur.
- Limite d’actions par tour via le système de fatigue.

### Module Créatures (Jordan)

- Génération procédurale selon la profondeur.
- 5 créatures aux comportements et compétences uniques.
- Difficulté progressive en fonction de la zone explorée.

### Module Combat (Jordan)

- Attaques au harpon, coups critiques et ripostes automatiques.
- Intégration complète des compétences spéciales ennemies.
- Gestion de l’initiative et animations de combat.
- Consommation d’oxygène dynamique selon les actions.

### Integration (Chaymae)
- Architecture modulaire claire (joueur, combat, créatures).
- Boucle de jeu gérant les tours, victoire/défaite.
- Makefile optimisé, interface en couleurs ANSI.

## 🎯 Mécaniques de jeu

### Ressources du joueur :
- Vie (100) : si 0 → Game Over.
- Oxygène (100) : Diminue considérablement selon la profondeur.
  - Attaque : 2 à 5
  - Compétence : 5 à 8
  - Fin de tour : 2 à 4
  - Pénalité de -5 PV/tour à 0.
- Fatigue (0–5) : limite les attaques disponibles.
  - 0–1 → 3 actions/ tour
  - 2–3 → 2 actions
  - 4–5 → 1 action
  - -1 fatigue en fin de tour

### Progression
Plus on descend, plus on affronte de créatures puissantes et variées (1 à 3 par zone).

## 🧪 Tests et validation

### Tests mémoire
```bash
make valgrind
```
✅ Aucune fuite mémoire détectée

Resultat: Pas de fuites detectees !

## 📁 Structure du projet
```
oceandepth/
├── Makefile
├── README.md
├── src/
│   ├── main.c
│   ├── joueur/
│   │   ├── joueur.h
│   │   └── joueur.c
│   ├── combat/
│   │   ├── combat.h
│   │   └── combat.c
│   └── creatures/
│       ├── creatures.h
│       └── creatures.c
└── build/
    ├── obj/
    └── oceandepths
```

## 🔮 Fonctionnalités à venir

### Prochaines étapes prévues
- [X] Compétences spéciales du joueur
- [ ] Système d'inventaire et objets consommables
- [ ] Récompenses et butin après combat (perles, équipement)
- [ ] Système de progression et d'amélioration
- [ ] Sauvegarde et chargement de parties
- [ ] Exploration multi-niveaux

## 📝 Notes techniques

- **Langage**: C (norme C99)
- **Affichage**: Couleurs ANSI et caractères Unicode
- **Nombres aléatoires**: `rand()` initialisé avec `srand(time(NULL))`
- **Gestion mémoire**: Aucune allocation dynamique (structures statiques)

## 📅 Informations du projet

- **Date de réalisation**: 16 Novembre 2025
