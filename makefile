# Nom de l'exécutable
TARGET = roguelike

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -O2

# Librairies à lier (ordre important pour MinGW)
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# Fichiers sources
SRC = main.c drawing_function.c settings.c

# Règle par défaut : compile tout
all: $(TARGET).exe

# Compilation
$(TARGET).exe: $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LIBS)

# Nettoyage des fichiers générés
clean:
	rm -f $(TARGET).exe

# Compilation + exécution
run: $(TARGET).exe
	./$(TARGET).exe
