/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:12:17 by spike             #+#    #+#             */
/*   Updated: 2025/01/16 17:32:28 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"


#define RESET_COLOR "\033[0m"

// Définition d'une fonction qui génère un code de couleur basé sur un indice
#define COLOR(i) "\033[38;5;" #i "m"  // Utilisation des couleurs 256 disponibles en ANSI

#define MINISHELL_TEST  \
  COLOR(33) "            _         _       _            _  _\n" \
  COLOR(39) "           (_)       (_)     | |          | || |\n" \
  COLOR(45) " _ __ ___   _  _ __   _  ___ | |__    ___ | || |\n" \
  COLOR(51) "| '_ ` _ \\ | || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n" \
  COLOR(57) "| | | | | || || | | || |\\__ \\| | | ||  __/| || |\n" \
  COLOR(63) "|_| |_| |_||_||_| |_||_||___/|_| |_| \\___||_||_|" RESET_COLOR




typedef struct s_args
{
	int		ac;
	char	**av;
	int		*was_in_quote; // tableau d'int de taille index qui represente pour chaque index l'argument : 1 si meta 0 sinon
	int		*pipe; // |
	int		*redirect_output; // >
	int		*append_redirect; // >>
	int		*redirect_input; // <
	int		*heredoc; // <<
}				t_args;

// --------------ERROR-------------
void	*error_malloc(char **result, int index, int *error);
int		error_handle(char *s);
void	free_all(char *rl, char **lines);

// --------------ERROR 2------------
int	free_args_struct(t_args **args);

// Special case if quote are not even
int	quote_prompt(char **result, int index);
int	check_error_quote(char **str, int index);
int	quote(char *s);

// -------------PARSE 1 --------------
char	**init_av(char *str, int *error);
int		quote(char *s);

// -------------PARSE 2 --------------
int	init_all(t_args *args);

#endif
