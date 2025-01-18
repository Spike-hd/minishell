/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:38:06 by spike             #+#    #+#             */
/*   Updated: 2025/01/18 19:04:18 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	free_all(char *rl, char **av)
{
	int	index;

	index = 0;
	while (av[index])
	{
		free(av[index]);
		index++;
	}
	free(av);
	free(rl);
}

int	error_handle(char *s)
{
	printf("%s", s);
	return (1);
}

