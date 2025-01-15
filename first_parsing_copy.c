/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing_copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:16:43 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/15 13:48:46 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_v2(char *s, int limit) // va verifier si on se trouve entre des "",
{
	int	i;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (s[i] && i < limit)
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
			if (s[i] != '\0' && s[i] != ' ') // Avancer dans le reste
				i++;
		}
	}
	return (count);
}


char	**first_parsing(char *str, int *error) // il faudrait surement que cette fonction gere toute la structure
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


int	parse_and_exec(char *rl, t_args *args, int error)
{
	char **av;
	av = first_parsing(rl, &error);
	if (error)
			error_handle("problem with quotes or with malloc\n");
	else
	{
		new_parsing(av);
		// exec ?
	}
	free_all(rl, av);
	return (0);
}




int	main(void)
{
	char	*rl;
	t_args	*args; // => a faire;
	while(1)
	{
		rl = readline("Minishell > ");
		if (!rl)
			return (error_handle("problem with rl fct\n"));
		parse_and_exec(rl, args, 0);
	}
	return (0);
}
