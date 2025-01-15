/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:12:17 by spike             #+#    #+#             */
/*   Updated: 2025/01/15 15:52:52 by spike            ###   ########.fr       */
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
	int		ac;
	char	**av;
	int		metacharacters;
	int		*was_in_quote; // tableau d'int de taille index qui represente pour chaque index l'argument : 1 si meta 0 sinon
}				t_args;

// --------------ERROR-------------
void	*error_malloc(char **result, int index, int *error);
int		check_error_quote(char **result, int index);
int		error_handle(char *s);
void	free_all(char *rl, char **lines);

// -------------PARSE 1 --------------
char	**init_av(char *str, int *error);
int		quote(char *s);


#endif
