/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:12:17 by spike             #+#    #+#             */
/*   Updated: 2025/01/14 17:01:25 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"


// --------------ERROR-------------
void	*error_malloc(char **result, int index, int *error);
int		check_error_quote(char **result, int index);
int		error_handle(char *s);
void	free_all(char *rl, char **lines);

// -------------PARSE 1 --------------
char	**first_parsing(char *str, int *semicolon, int *error);
int		quote(char *s);

#endif
