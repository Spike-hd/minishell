/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:41:30 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/07 11:12:33 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	msg(char *msg, int endl, int is_error, int value)
{
	if (!msg)
		return (ERROR);
	printf("%s", RESET_COLOR);
	if (is_error == TRUE)
		printf("%sError : ", RED);
	printf("%s (%d)", msg, value);
	if (endl == TRUE)
		printf("\n");
	printf("%s", RESET_COLOR);
	return (value);
}

int	print_ascii_art(void)
{
	printf("%s", ASCII_L1);
	printf("%s", ASCII_L2);
	printf("%s", ASCII_L3);
	printf("%s", ASCII_L4);
	printf("%s", ASCII_L5);
	printf("%s", ASCII_L6);
	printf("%s", RESET_COLOR);
	return (738);
}
