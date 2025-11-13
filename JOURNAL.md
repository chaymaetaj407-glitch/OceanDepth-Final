# Journal de Developpement - Groupe JAT

## Equipe
- TAJ: Responsable integration
- ASSIA: Responsable module joueur
- JORDAN: Responsable module combat

---

## Debut du projet (mi-octobre)

### Reunion de groupe initiale
**Presents:** TAJ, ASSIA, JORDAN

On s'est retrouves pour discuter du projet. On a lu le sujet ensemble.

**Decisions prises:**
- TAJ s'occupe de l'integration et tests
- ASSIA gere le module joueur
- JORDAN fait le systeme de combat

---

## Premiere semaine - Structure de base

### TAJ - Setup du projet
**Ce que j'ai fait:**
- Creation de la structure des dossiers (src/, build/)
- Makefile basique pour compiler
- main.c simple pour tester

**Problemes:**
- Le Makefile marchait pas au debut
- Erreurs de syntaxe
- Les includes fonctionnaient pas

**Solutions:**
- J'ai cherche des exemples en ligne
- Corrige les chemins des includes

**Temps:** environ 2h

---

### ASSIA - Module joueur
**Ce que j'ai fait:**
- Fichiers joueur.h et joueur.c
- Structure Plongeur
- Fonction init_plongeur()

**Problemes:**
- J'hesitais sur les attributs a mettre

**Temps:** environ 2-3h

---

### JORDAN - Module combat
**Ce que j'ai fait:**
- Fichiers combat.h et combat.c
- Structure CreatureMarine
- Fonction calculer_degats()

**Problemes:**
- Je savais pas ou mettre la structure

**Temps:** environ 2h

---

## Deuxieme semaine - Developpement

### ASSIA - Barres de progression
**Ce que j'ai fait:**
- Fonction afficher_plongeur()
- Barres de progression

**Problemes:**
- Les barres etaient difficiles a faire
- J'ai essaye plusieurs methodes

**Temps:** environ 4-5h

---

### JORDAN - Systeme d'attaque
**Ce que j'ai fait:**
- Fonction attaquer() complete
- Animation combat
- Coups critiques

**Problemes:**
- Bug: j'oubliais de verifier si creature vivante
- Probleme avec scanf et le buffer

**Solutions:**
- Ajout de if (c->vivant == 1)
- Ajout de while(getchar() != '\n');

**Temps:** environ 3-4h

---

### Pause
(On avait d'autres cours et projets cette semaine)

---

## Troisieme semaine - Integration et tests

### TAJ - Premiere integration
**Ce que j'ai fait:**
- main.c pour assembler les modules
- Creatures de test
- Boucle de combat principale

**Problemes:**
- Plein d'erreurs de compilation
- Types incompatibles partout
- Warnings sur les pointeurs

**Solutions:**
- Ajout de & devant les variables
- Cast des types

**Resultat:** Ca compile mais ca crash au lancement

**Temps:** environ 3-4h

---

### Session debug ensemble
On s'est reunis tous les 3 pour debugger.

**Problemes trouves:**
- Segmentation fault dans afficher_combat()
- Bug dans selection cible
- Oxygene qui descendait trop vite

**Solutions:**
- Corrections des pointeurs
- Ajout verifications
- Ajustement valeurs

**Temps:** environ 3-4h chacun

---

### ASSIA - Finalisation
**Ce que j'ai fait:**
- Fonctions perdre_vie(), perdre_oxygene()
- Fonctions soigner(), remettre_oxygene()
- Fonction attaques_possibles()

**Temps:** environ 2-3h

---

### JORDAN - Finitions combat
**Ce que j'ai fait:**
- Coups critiques
- Riposte creatures
- Consommation oxygene

**Temps:** environ 2-3h

---

### TAJ - Tests finaux
**Ce que j'ai fait:**
- Tests systematiques de toutes les fonctions
- Verification memoire avec valgrind

**Tests effectues:**
- Combat contre 1 creature: OK
- Combat contre 3 creatures: OK
- Test oxygene a 0: OK (perd 5 PV)
- Test vie a 0: OK (message defaite)
- Test victoire: OK

**Verification memoire:**
```bash
valgrind --leak-check=full ./build/oceandepths
```
Resultat: **0 bytes lost** - Aucune fuite memoire !

**Temps:** environ 3-4h

---

## Derniere semaine - Finitions

### Ajustements finaux
On a ameliore:
- Messages d'affichage
- Equilibrage des valeurs
- Commentaires dans le code

**Temps:** environ 2h chacun

---

### TAJ - Documentation
**Ce que j'ai fait:**
- README.md
- Ce journal
- Organisation finale

**Temps:** environ 2h

---

## Bilan

**Temps total approximatif:**
- TAJ: environ 12-14h
- ASSIA: environ 12-14h
- JORDAN: environ 10-12h
**Total: environ 35-40h sur 3-4 semaines**

**Difficultes principales:**
- Erreurs de compilation
- Bugs de segmentation
- Integration des modules

**Points positifs:**
- Le systeme fonctionne bien
- Pas de fuites memoire
- Bonne gestion des ressources

On est contents du resultat !
