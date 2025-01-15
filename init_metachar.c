/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_metachar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:44:46 by spike             #+#    #+#             */
/*   Updated: 2025/01/15 21:37:22 by spike            ###   ########.fr       */
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
			res[j] = str[i];
		i++;
		j++;
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

int	check_metachar(int ac, char **av, t_args *args)
{
	int	i;

	i = 0;
	args->was_in_quote = (int *)malloc(ac * sizeof(int));
	if (!args->was_in_quote)
		return (-1);
	while (i < ac)
	{
		args->was_in_quote[i] = 0;
		init_was_in_quote(&args->was_in_quote[i], av[i], '\'');
		init_was_in_quote(&args->was_in_quote[i], av[i], '"');
	}
}

int	init_metachar(t_args *args)
{
	int	i;

	i = 0;
	while (args->av[i])
		i++;
	args->ac = i;
	if (check_metachar(args->ac, args->av, args) == 1)
}
