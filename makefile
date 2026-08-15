# Nom de l'exécutable
TARGET = roguelike

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -O2 -Iinclude


# Librairies à lier
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

# Dossiers
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = .

# Executables à compiler
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/drawing_function.c \
      $(SRC_DIR)/settings.c \
      $(SRC_DIR)/fps_utils.c \
      $(SRC_DIR)/paths.c \
	  $(SRC_DIR)/main_menu.c\
	  $(SRC_DIR)/poll_events.c\
	  $(SRC_DIR)/ui.c \
	  $(SRC_DIR)/image_loader.c \
	  $(SRC_DIR)/menu.c \
	  $(SRC_DIR)/menu_ingame.c \
	  $(SRC_DIR)/button.c

# Fichiers objets (dans le dossier build)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Règle par défaut : compile tout
all: $(BIN_DIR)/$(TARGET).exe

# Créer le dossier build s'il n'existe pas
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilation des fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link de l'exécutable
$(BIN_DIR)/$(TARGET).exe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Nettoyage des fichiers générés
clean:
	rm -f $(BIN_DIR)/$(TARGET).exe
	rm -rf $(BUILD_DIR)

# Nettoyage + recompilation
rebuild: clean all

# Compilation + exécution
run: $(BIN_DIR)/$(TARGET).exe
	./$(BIN_DIR)/$(TARGET).exe

# Afficher les fichiers .o
show:
	@echo "Sources: $(SRC)"
	@echo "Objets: $(OBJ)"


test:
	make clean run

# Pour Windows
run-win: $(BIN_DIR)/$(TARGET).exe
	$(BIN_DIR)/$(TARGET).exe

.PHONY: all clean rebuild run show run-win