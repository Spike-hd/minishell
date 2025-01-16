/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_av.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:16:43 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/16 15:34:52 by hduflos          ###   ########.fr       */
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
	char	quote;
	int		in_quote;

	in_quote = 0;
	// Ignorer les espaces
	while (s[*i] == ' ')
		(*i)++;
	if (s[*i] == '\0')
		return (0); // Plus d'arguments

	*start = *i; // Marquer le début de l'argument
	while (s[*i] != '\0')
	{
		// Vérifier les guillemets
		if ((s[*i] == '\'' || s[*i] == '"') && !in_quote)
		{
			quote = s[*i];
			in_quote = 1;
			(*i)++;
			continue;
		}
		else if (s[*i] == quote && in_quote)
		{
			in_quote = 0;
			(*i)++;
			break; // Fin de la séquence entre guillemets
		}
		// Fin d'un argument non entre guillemets
		else if (!in_quote && s[*i] == ' ')
			break;
		(*i)++;
	}
	return (1); // Argument trouvé
}


// int	count_args(char *s)
// {
// 	int		i;
// 	int		count;
// 	char	quote;
// 	int		in_quote;

// 	count = 0;
// 	i = 0;
// 	in_quote = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == ' ')
// 			i++;
// 		if (s[i] != '\0')
// 		{
// 			count++;
// 			if ((s[i] == '\'' || s[i] == '"') && !in_quote)
// 			{
// 				quote = s[i];
// 				in_quote = 1;
// 				i++;
// 				while (s[i] != quote && s[i] != '\0')
// 					i++;
// 				if (s[i] == quote)
// 				{
// 					printf("u see me? IN QUOTE ? %d\n", in_quote);
// 					in_quote = 0;
// 				}
// 			}
// 			while (s[i] != ' ' && s[i] != '\0' && (!in_quote || s[i] != quote))
// 				i++;
// 		}
// 	}
// 	printf("IN QUOTE ? %d // count ================= %d\n", in_quote, count);
// 	if (in_quote == 1)
// 		printf("pb args\n");
// 	return (count);
// }


int	count_args(char *str)
{
	int		i;
	int		count;
	char	quote;
	int		in_quote;

	count = 0;
	i = 0;
	in_quote = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0')
		{
			count++;
			if ((str[i] == '\'' || str[i] == '"') && !in_quote)
			{
				quote = str[i];
				i++;
				in_quote = 1;
				while (str[i] != quote && str[i])
					i++;
				if (str[i] == '\0')
				{
					printf("end here normally %d // count ================= %d\n", in_quote, count);
					return (count);
				}
				if (str[i] == quote)
				{
					printf("u see me? IN QUOTE ? %d\n", in_quote);
					in_quote = 0;
				}
			}
			while (str[i] != ' ' && str[i] != '\0' && (!in_quote || str[i] != quote))
				i++;

			}
	}
	printf("IN QUOTE ? %d // count ================= %d\n", in_quote, count);
	if (in_quote == 1)
		printf("pb args\n");
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
