/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:11:42 by spike             #+#    #+#             */
/*   Updated: 2025/01/13 15:55:17 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quote(char *s, int i, int c) // c represente la quote
{
	int	n;
	int	count;

	n = 0;
	count = 0;
	while (n < i)
	{
		if (s[n] == c)
			count++;
		n++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

int	count_args(char *s, int *v)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != ';')
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != 0 && s[i] != ';' && !is_in_quote(s, i, "'") && !is_in_quote(s, i, '"')) // si je ne suis pas dans une quote je compte
			count++;
		while (s[i] != ' ' && s[i] != '\0' && s[i] != ';')
			i++;
	}
	if (s[i] == ';')
		*v = 1;
	return (count);
}

char **first_parsing(char *str, int *v)
{
	int		i;
	char	**result;
	int		words;

	words = count_args(str, v);
	i = 0;
	while (str[i])
	{

	}
}

int main(void)
{
	char *rl;
	int	v;
	char **lines; // => va etre notre tableau qui va stocker la commande et les options
	rl = readline("Minishell > ");

	// i va etre un flag pour nous indiquer si il y a des (;)
	v = 0;
	lines = first_parsing(rl, &v);

	return (0);
}
