/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:11:42 by spike             #+#    #+#             */
/*   Updated: 2025/01/14 13:21:25 by spike            ###   ########.fr       */
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
	return (count % 2 == 0);
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
			if (is_in_quote(s, i, '\'') || is_in_quote(s, i, '"'))
			{
				quote = s[i];
				i++;
				while (s[i] != quote && s[i] != '\0')
					i++;
			}
			else
				i++;
		}
	}
	if (s[i] == ';')
		*semicolon = 1;
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
	if (check_error_quote(result, index, 0))
		*error = 1;
	return (result);
}
