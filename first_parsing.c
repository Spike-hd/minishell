/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:11:42 by spike             #+#    #+#             */
/*   Updated: 2025/01/14 17:00:55 by hduflos          ###   ########.fr       */
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

int	count_args(char *s, int *semicolon, int i)
{
	int		count;
	char	quote;

	count = 0;
	while (s[i] && s[i] != ';')
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != 0 && s[i] != ';')
		{
			count++;
			if (s[i] == '\'' || s[i] == '"')
			{
				quote = s[i];
				i++;
				while (s[i] != quote && s[i] != '\0')
					i++;
			}
			if (s[i] != '\0' && s[i] != ' ' && s[i] != ';') // Avancer dans le reste
				i++;
		}
	}

	// Gérer `semicolon`
	if (s[i] == ';')
	{
		*semicolon = 1; // Il reste un point-virgule à gérer
		printf("Do you see me ? s[i] = %c\n", s[i]);
	}
	else
	{
		*semicolon = 0; // Fin de chaîne sans point-virgule
		printf("Do you see me (null) ? s[i] = %c\n", s[i]);
	}
	return (count);
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
	printf("TEST DUBUG %s", s);

	while (s[*i] == ' ')
		(*i)++;
	if (s[*i] == '\0' || s[*i] == ';')
		return (0); // => plus d'args juste des espaces

	*start = *i;
	while (s[*i] != ' ' && s[*i] != '\0' && s[*i] != ';')
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
char	**first_parsing(char *str, int *semicolon, int *error)
{
	int		i;
	char	**result;
	int		words;
	int		start;
	int		index;

	words = count_args(str, semicolon, 0);
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
