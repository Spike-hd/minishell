NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

 SRC_DIR = srcs
OBJ_DIR = objects

FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalpha.c ft_isalnum.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strchr.c \
		ft_strjoin.c ft_strdup.c ft_striteri.c ft_strlcat.c ft_strlcpy.c \
		ft_strlen.c ft_strmapi.c ft_strnstr.c ft_strncmp.c ft_strrchr.c \
		ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_split.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

 SRC = $(addprefix $(SRC_DIR)/, $(FILES))
 OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

 all: $(NAME)

 $(NAME): $(OBJ)
		@echo "Creating library $(NAME)..."
		ar rcs $(NAME) $(OBJ)
		@echo "$(NAME) successfully created!"

 $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

 clean:
		rm -rf $(OBJ_DIR)

 fclean: clean
		rm -f $(NAME)

 re: fclean all

 .PHONY: all clean fclean re

