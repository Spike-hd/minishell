# Nom de l'exécutable
MINISHELL = minishell

# Répertoires
LIBFT_DIR = libft
OBJ_DIR = objects

# Fichiers sources
SRC_FILES = errors.c main.c init_av.c init_metachar.c errors2.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Bibliothèques et headers
LIBFT = $(LIBFT_DIR)/libft.a
INC = minishell.h $(LIBFT_DIR)/libft.h

# Règle par défaut : compiler les exécutables
all: $(OBJ_DIR) $(LIBFT) $(MINISHELL)

# Créer le répertoire pour les objets
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Créer la bibliothèque libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Créer l'exécutable
$(MINISHELL): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(MINISHELL) $(LIBFT) -lreadline -lncurses -I/usr/local/include -L/usr/local/lib


# Règle pour générer les fichiers objets
$(OBJ_DIR)/%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

# Nettoyage complet (objets + exécutables)
fclean: clean
	rm -f $(MINISHELL)
	make -C $(LIBFT_DIR) fclean

# Recompilation complète
re: fclean all

# Marque que les règles ne sont pas des fichiers
.PHONY: all clean fclean re
