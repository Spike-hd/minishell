/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:12:50 by spike             #+#    #+#             */
/*   Updated: 2025/01/16 17:36:34 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* verifie si les quotes se ferment correctement */
int	quote(char *s)
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

int	check_error_quote(char **str, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (quote(str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
int	quote_prompt(char **result, int index)
{
	char	*qline;
	char	*temp;

	while (check_error_quote(result, index))
	{
		qline = readline("quote> ");
		if (!qline)
			return (error_handle("problem with readline fct\n"));
		temp = ft_strjoin(result[index - 1], qline);
		free(result[index - 1]);
		free(qline);
		if (!temp)
			return (error_handle("malloc error during quote completion\n"));

		result[index - 1] = temp;
	}
	return (0);
}
