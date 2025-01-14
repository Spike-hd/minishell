/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:38:06 by spike             #+#    #+#             */
/*   Updated: 2025/01/14 13:35:07 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*error_malloc(char **result, int index, int *error)
{
	while (index--)
	{
		if (result[index])
			free(result[index]);
	}
	free(result);
	*error = 1;
	return (NULL);
}

void	free_all(char *rl, char **lines)
{
	int	index;

	index = 0;
	while (lines[index])
	{
		free(lines[index]);
		index++;
	}
	free(lines);
	free(rl);
}

int	check_error_quote(char **str, int index, int i)
{
	int j;
	int single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (i < index)
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == '\'')
			{
				if (double_quote % 2 == 0)
					single_quote++;
			}
			else if (str[i][j] == '"')
			{
				if (single_quote % 2 == 0)
					double_quote++;
			}
		}
		i++;
	}
	return (single_quote % 2 != 0 || double_quote % 2 != 0);
}

int	error_handle(char *s)
{
	printf("%s", s);
	return (1);
}
