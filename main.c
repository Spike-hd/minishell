/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:11:42 by spike             #+#    #+#             */
/*   Updated: 2025/01/14 19:52:53 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




void	print_split_result(char **lines, int semicolon)
{
	int i = 0;

	if (!lines)
	{
		printf("Lines is NULL.\n");
		return;
	}

	printf("Split result:\n");
	while (lines[i])
	{
		printf("lines[%d]: %s // semicolon ?= %d\n", i, lines[i], semicolon);
		i++;
	}
	printf("Total arguments: %d\n", i);
}




char	*handle_substr(char *rl, char **lines)
{
	int	i;
	size_t len;
	char *temp;

	i = 0;
	while (rl[i])
	{
		if (rl[i] == ';'&& !quote_v2(rl, i))
			break;
		i++;
	}
	len = ft_strlen(rl);
	if (rl[i] == ';')
	{
		len -= i;
		temp = ft_substr(rl, i + 1, len);
		free_all(rl, lines);
		return (temp);
	}
	free_all(rl, lines);
	return (NULL);
}



int	while_semicolon(char *rl, int semicolon, int error)
{
	char	**lines; // => va etre notre tableau qui va stocker la commande et les options

	while (semicolon)
	{
		printf("\nRL === %s\n", rl); //DEL
		lines = first_parsing(rl, &semicolon, &error);
		if (error)
			error_handle("problem with quotes or with malloc\n");
		//print_split_result(lines, semicolon); // DEL
		else
		{
			check_parsing_and_exec(lines); // ERROR ou pas ?
		/*handle the rest of the logic*/
		}
		if (semicolon)
		{
			rl = handle_substr(rl, lines); // clear lines et substr rl pour la prochaine comamnde
			if (!rl)
			{
				error_handle("pb clearing rl / lines or pb substr");
			}
		}
		else
			free_all(rl, lines);
	}
	return (0);
}

int	main(void)
{
	char	*rl;

	while(1)
	{
		rl = readline("Minishell > ");
		if (!rl)
			return (error_handle("problem with rl fct\n"));
		while_semicolon(rl, 1, 0);
	}
	return (0);
}
