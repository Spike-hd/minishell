/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:38:06 by spike             #+#    #+#             */
/*   Updated: 2025/01/14 16:59:59 by hduflos          ###   ########.fr       */
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

int	error_handle(char *s)
{
	printf("%s", s);
	return (1);
}
