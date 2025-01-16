/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:44:07 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/16 10:58:52 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_av(char ***av, int ac)
{
	int	i;

	if (!*av)
		return;
	i = 0;
	while (i < ac)
	{
		free((*av)[i]);
		i++;
	}
	free(*av);
	*av = NULL;
}

void	free_int_table(int **tab)
{
	if (*tab)
	{
		free(*tab);
		*tab = NULL;
	}
}

int	free_args_struct(t_args **args)
{
	if (!*args)
		return (-1);
	if ((*args)->av)
		free_av(&((*args)->av), (*args)->ac);
	if ((*args)->was_in_quote)
		free_int_table(&((*args)->was_in_quote));
	if ((*args)->pipe)
		free_int_table(&((*args)->pipe));
	if ((*args)->redirect_output)
		free_int_table(&((*args)->redirect_output));
	if ((*args)->append_redirect)
		free_int_table(&((*args)->append_redirect));
	if ((*args)->redirect_input)
		free_int_table(&((*args)->redirect_input));
	if ((*args)->heredoc)
		free_int_table(&((*args)->heredoc));
	free(*args);
	*args = NULL;
	return (0);
}

