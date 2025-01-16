/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:11:42 by spike             #+#    #+#             */
/*   Updated: 2025/01/16 19:48:37 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/* Fonction de test pour voir si les av sont bien tries (il faudra delete) */
void	print_split_result(char **lines)
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
		printf("lines[%d]: %s\n", i, lines[i]);
		i++;
	}
	printf("Total arguments: %d\n", i);
}

void print_all(t_args *args)
{
    int i = 0;

    while (i < args->ac)
    {
        printf("Argument [%d]:\n", i);
        printf("  av = %s\n", args->av[i]);
        printf("  was_in_quote = %d\n", args->was_in_quote[i]);
        printf("  pipe = %d\n", args->pipe[i]);
        printf("  redirect_output = %d\n", args->redirect_output[i]);
        printf("  append_redirect = %d\n", args->append_redirect[i]);
        printf("  redirect_input = %d\n", args->redirect_input[i]);
        printf("  heredoc = %d\n", args->heredoc[i]);
		printf("\n\n");
        i++;
    }
    printf("\n");
}



/* Cette fonction sert simplement a alleger le main mais peut etre qu'on peut tout mettre dans le main */
int	parse_and_exec(char *rl, t_args *args, int error)
{
	args->av = init_av(rl, &error);
	if (error)
			error_handle("problem with quotes or with malloc\n");
	//print_split_result(args->av); // DEL
	else
	{
		init_all(args);
		print_all(args); // DEL
		free_args_struct(&args);
		// exec
	}
	// free_all(rl, args->av); // -> attention il faudra free d'autres choses
	return (0);
}

int	main(void)
{
	char	*rl;
	t_args	*args;

	printf("%s\n\n\n", MINISHELL_TEST);

	args = malloc(sizeof(t_args));
	if (!args)
		return (error_handle("problem with args allocation\n"));
	while(1)
	{
		rl = readline (COMPUTER " Minishell > " RESET);
		if (!rl)
			return (error_handle("problem with rl fct\n"));
		parse_and_exec(rl, args, 0);
	}
	return (0);
}
