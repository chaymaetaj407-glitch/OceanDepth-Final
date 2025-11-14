# Makefile pour OceanDepth - Etape 2
# Fait par: TAJ, ASSIA, JORDAN

CC = gcc
CFLAGS = -Wall -std=c99 -Isrc
LDFLAGS = -lm

# Nom du programme
TARGET = oceandepths

# Repertoires
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Fichiers sources
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/joueur/joueur.c \
          $(SRC_DIR)/combat/combat.c \
          $(SRC_DIR)/creatures/creatures.c

# Fichiers objets
OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/joueur.o \
          $(OBJ_DIR)/combat.o \
          $(OBJ_DIR)/creatures.o

# Regle par defaut
all: $(BUILD_DIR)/$(TARGET)
	@echo ""
	@echo "Compilation reussie !"
	@echo "Pour lancer: ./$(BUILD_DIR)/$(TARGET)"
	@echo ""

# Creer l executable
$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	@echo "Creation de l'executable..."
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compiler les fichiers .c en .o
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compilation de main.c..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/joueur.o: $(SRC_DIR)/joueur/joueur.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compilation de joueur.c..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/combat.o: $(SRC_DIR)/combat/combat.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compilation de combat.c..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/creatures.o: $(SRC_DIR)/creatures/creatures.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compilation de creatures.c..."
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer
clean:
	@echo "Nettoyage..."
	rm -rf $(BUILD_DIR)
	@echo "Nettoyage termine !"

# Recompiler tout
rebuild: clean all

# Lancer le jeu
run: all
	./$(BUILD_DIR)/$(TARGET)

# Verification memoire
valgrind: all
	@echo "Verification memoire avec valgrind..."
	valgrind --leak-check=full ./$(BUILD_DIR)/$(TARGET)

# Aide
help:
	@echo "Commandes disponibles:"
	@echo "  make         - Compiler"
	@echo "  make clean   - Nettoyer"
	@echo "  make rebuild - Nettoyer et recompiler"
	@echo "  make run     - Compiler et lancer"
	@echo "  make valgrind - Verifier la memoire"
	@echo "  make help    - Afficher cette aide"

.PHONY: all clean rebuild run valgrind help