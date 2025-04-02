/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:43:29 by mathispeyre       #+#    #+#             */
/*   Updated: 2025/03/07 11:13:05 by mathispeyre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(void)
{
	print_ascii_art();
	msg("Hello cub3D World !", TRUE, FALSE, 0);
	return (msg("Exit...", TRUE, FALSE, EXIT_SUCCESS));
}
