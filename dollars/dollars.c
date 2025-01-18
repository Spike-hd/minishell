/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:29:23 by spike             #+#    #+#             */
/*   Updated: 2025/01/18 19:03:47 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inside_single_quote(char *av, int limit)
{
	int	i;
	int	count;

	if (limit == -1)
		limit = ft_strlen(av);

	i = 0;
	count = 0;
	while (i < limit)
	{
		if (av[i] == '\'')
			count++;
		i++;
	}
	return (count % 2 != 0);
}

int	count_dollars(char *av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (av[i])
	{
		if (av[i] == '$' && !inside_single_quote(av, i));
			count++;
		i++;
	}
	return (count);
}

char	*substr_dollar(char *av)
{
	int	i;
	int	start;
	char *sub_av;

	i = 0;
	while (av[i])
	{
		if (av[i] == '$' && !inside_single_quote(av, i))
			break ;
		i++;
	}
	start = i;
	while (av[i])
	{
		if (av[i] == '$' || av[i] == '"' || av[i] == ' ')
			break ;
		i++;
	}
	sub_av = ft_substr(av, start, i - start);
	if (!sub_av)
		return (NULL);
	return (sub_av);
}

int	dollars(t_args *args)
{
	int	i;
	int dollars;
	char *sub_av;

	i = 0;
	while (i < args->ac)
	{
		dollars = count_dollars(args->av[i]);
		while (dollars--)
		{
			if (!inside_single_quote(args->av[i], -1))
			{
				sub_av = substr_dollar(args->av[i]);
				if (!sub_av)
					return (error_handle("pb with $"));
				if (replace_av(sub_av, &args->av[i], 0) == -1)
					return (error_handle("pb with $"));
			}
		}
		i++;
	}
	return (0);
}
