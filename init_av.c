/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_av.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:16:43 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/15 15:39:22 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote(char *s) // va verifier si on se trouve entre des "",
{
	int	i;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			if (double_quote % 2 == 0)
				single_quote++;
		}
		else if (s[i] == '"')
		{
			if (single_quote % 2 == 0)
				double_quote++;
		}
		i++;
	}
	return (single_quote % 2 != 0 || double_quote % 2 != 0);
}


char	*extract_words(char *s, int i, int start)
{
	int		length;
	char	*result;


	length = i - start;
	result = malloc((length + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, length + 1);
	return (result);
}

int	parse_args(char *s, int *i, int *start)
{
	char quote;

	while (s[*i] == ' ')
		(*i)++;
	if (s[*i] == '\0')
		return (0); // => plus d'args juste des espaces

	*start = *i;
	while (s[*i] != ' ' && s[*i] != '\0')
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			quote = s[*i];
			(*i)++;
			while (s[*i] != quote && s[*i] != '\0')
				(*i)++;
			if (s[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	return (1); // => argument trouvé
}

int	count_args(char *s)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != 0)
		{
			count++;
			if (s[i] == '\'' || s[i] == '"')
			{
				quote = s[i];
				i++;
				while (s[i] != quote && s[i] != '\0')
					i++;
			}
			if (s[i] != '\0' && s[i] != ' ')
				i++;
		}
	}
	return (count);
}

/* Cette fonction va comme son nom l'indique initialiser **av avec
av[0] = le programme demandé
av[1], av[2], etc pour les arguments du programme
Les fonctions du haut represente simplement un split particulier à ce projet */
char	**init_av(char *str, int *error)
{
	int		i;
	char	**result;
	int		words;
	int		start;
	int		index;

	words = count_args(str);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	index = 0;
	i = 0;
	while (str[i])
	{
		if (!parse_args(str, &i, &start))
			break ;
		result[index] = extract_words(str, i, start);
		if (!result[index])
			return (error_malloc(result, index, error));
		index++;
	}
	result[index] = NULL;
	if (check_error_quote(result, index))
		*error = 1;
	return (result);
}
