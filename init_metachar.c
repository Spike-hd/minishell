/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_metachar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:44:46 by spike             #+#    #+#             */
/*   Updated: 2025/01/16 11:57:26 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_quote(char *str, int count, int c)
{
	int		i;
	int		j;
	size_t	len;
	char	*res;

	len = ft_strlen(str);
	len -= count;
	printf("count = %d\n\n", count);
	res = malloc(len + 1);
	if (!res)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			res[j] = str[i];
			j++;
			i++;
		}
		else
			i++;

	}
	res[i] = '\0';
	free(str);
	return (res);
}

int	init_was_in_quote(int *quote, char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			count++;
			if (*quote == 0)
				*quote = 1;
		}
		i++;
	}
	if (count != 0)
	{
		str = delete_quote(str, count, c);
		if (!str)
			return (-1);
	}
	return (0);
}

int	init_table(int ac, t_args *args)
{
	args->was_in_quote = (int *)ft_calloc(ac, sizeof(int));
	if (!args->was_in_quote)
		return (-1);
	args->pipe = (int *)ft_calloc(ac, sizeof(int));
	if (!args->pipe)
		return (-1);
	args->redirect_output = (int *)ft_calloc(ac, sizeof(int));
	if (!args->redirect_output)
		return (-1);
	args->append_redirect = (int *)ft_calloc(ac, sizeof(int));
	if (!args->append_redirect)
		return (-1);
	args->redirect_input = (int *)ft_calloc(ac, sizeof(int));
	if (!args->redirect_input)
		return (-1);
	args->heredoc = (int *)ft_calloc(ac, sizeof(int));
	if (!args->heredoc)
		return (-1);
	return (0);
}

void	init_metachar(t_args *args, char *av, int quote, int i)
{
	int	len;

	len = ft_strlen(av);
	if (ft_strncmp(av, "|", len) == 0 && quote == 0 && len == 1)
		args->pipe[i] = 1;
	if (ft_strncmp(av, ">", len) == 0 && quote == 0 && len == 1)
		args->redirect_output[i] = 1;
	if (ft_strncmp(av, ">>", len) == 0 && quote == 0 && len == 2)
		args->append_redirect[i] = 1;
	if (ft_strncmp(av, "<", len) == 0 && quote == 0 && len == 1)
		args->redirect_input[i] = 1;
	if (ft_strncmp(av, "<<", len) == 0 && quote == 0 && len == 2)
		args->heredoc[i] = 1;
}

int	init_all(t_args *args)
{
	int	i;

	i = 0;
	while (args->av[i])
		i++;
	args->ac = i;
	if (init_table(args->ac, args) == -1)
		return (free_args_struct(&args));
	i = 0;
	while (i < args->ac)
	{
		if (init_was_in_quote(&args->was_in_quote[i], args->av[i], '\'') == -1)
			return (free_args_struct(&args));
		if (init_was_in_quote(&args->was_in_quote[i], args->av[i], '"') == -1)
			return (free_args_struct(&args));
		init_metachar(args, args->av[i], args->was_in_quote[i], i);
		i++;
	}
	return (0);
}
