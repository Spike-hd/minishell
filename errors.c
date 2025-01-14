/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:38:06 by spike             #+#    #+#             */
/*   Updated: 2025/01/13 19:50:46 by spike            ###   ########.fr       */
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

int	check_error_quote(char **result, int index)
{

}
