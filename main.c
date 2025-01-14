/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:11:42 by spike             #+#    #+#             */
/*   Updated: 2025/01/14 13:35:10 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*rl;
	int		semicolon;
	int		error;
	char	**lines; // => va etre notre tableau qui va stocker la commande et les options
	while(1)
	{
		rl = readline("Minishell > ");
		if (!rl)
			return (error_handle("problem with rl fct\n"));
		semicolon = 1;
		error = 0;
		while (semicolon)
		{
			lines = first_parsing(rl, &semicolon, &error);
			if (error)
				error_handle("problem with quotes or with malloc\n");
			else{
			/*handle the rest of the logic*/
			}
			if (semicolon)
				rl = handle_substr(rl, lines); // clear lines et substr rl
			else
				free_all(rl, lines);
		}
	}
	return (0);
}
