/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_av.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:16:43 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/18 19:04:30 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	count_args(char *s)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	while (s[i])
	{
		// Ignorer les espaces
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
		{
			count++; // Détecte un nouvel argument
			if (s[i] == '\'' || s[i] == '"')
			{
				quote = s[i];
				i++;
				// Parcourir jusqu'à la fin des guillemets ou de la chaîne
				while (s[i] != quote && s[i] != '\0')
					i++;
				if (s[i] == quote)
					i++; // Avancer après le guillemet fermant
			}
			// Gérer le reste de l'argument non entre guillemets
			while (s[i] != ' ' && s[i] != '\0' && s[i] != '\'' && s[i] != '"')
				i++;
		}
	}
	printf(" count ==== %d\n", count);
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
		quote_prompt(result, index);
	return (result);
}
