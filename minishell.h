/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:12:17 by spike             #+#    #+#             */
/*   Updated: 2025/01/15 13:42:06 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_args
{
	int				index;
	char			**av;
	bool			metacharacters;
	int				*was_in_quote; // tableau d'int de taille index qui represente pour chaque index l'argument : 1 si meta 0 sinon
}				t_args;

// --------------ERROR-------------
void	*error_malloc(char **result, int index, int *error);
int		check_error_quote(char **result, int index);
int		error_handle(char *s);
void	free_all(char *rl, char **lines);

// -------------PARSE 1 --------------
char	**first_parsing(char *str, int *semicolon, int *error);
int		quote(char *s);
int		quote_v2(char *s, int limit);


#endif
