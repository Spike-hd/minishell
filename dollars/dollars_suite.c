/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_suite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:18:07 by spike             #+#    #+#             */
/*   Updated: 2025/01/18 19:13:00 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_strings(char *before, char *after, char *exp)
{
	if (before)
		free(before);
	if (after)
		free(after);
	if (exp)
		free(exp);
	return (-1);
}

char	*build_new_av(char *before, char *expansion, char *after)
{
	char	*new_av;
	size_t	total_len;

	total_len = ft_strlen(before) + ft_strlen(expansion) + ft_strlen(after);

	new_av = malloc(total_len + 1);
	if (!new_av)
		return (NULL);

	ft_strcpy(new_av, before);
	ft_strcat(new_av, expansion);
	ft_strcat(new_av, after);

	return (new_av);
}

int	split_av(char *av, int start, char **before, char **after)
{
	int	len;
	int	i;

	*before = ft_substr(av, 0, start);
	if (!*before)
		return (-1);

	i = start + 1;
	len = 0;
	while (av[i] && av[i] != ' ' && av[i] != '"' && av[i] != '$')
	{
		len++;
		i++;
	}

	*after = ft_substr(av, start + 1 + len, ft_strlen(av) - (start + 1 + len));
	if (!*after)
	{
		free(*before);
		return (-1);
	}

	return (0);
}

int	find_variable_start(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '$' && !inside_single_quote(av, i))
			return (i); // Retourne la position du premier '$' valide
		i++;
	}
	return (-1); // Aucun '$' valide trouvé
}

int	replace_av(char *substr, char **av, int start)
{
	char	*before;
	char	*after;
	char	*expansion;
	char	*new_av;

	// Trouver le '$' valide
	start = find_variable_start(*av);
	if (start == -1)
		return (-1);

	// Découper la chaîne en parties
	if (split_av(*av, start, &before, &after) == -1)
		return (-1);

	expansion = check_expansion(substr);
	if (!expansion)
		return (free_strings(before, after, expansion));

	new_av = build_new_av(before, expansion, after);
	free_strings(before, after, expansion);
	if (!new_av)
		return (-1);

	free(*av);
	*av = new_av;
	return (0);
}
