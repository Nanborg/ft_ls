/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 15:40:59 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_options	opts;
	int			idx;

	opts = (t_options){0, 0, 0, 0, 0};
	idx = ft_parse_options(argc, argv, &opts);
	if (idx == -1)
		return (1);
	if (idx >= argc)
		return (ft_dispatch_arguments(1, (char *[]){".", NULL}, 0, &opts));
	return (ft_dispatch_arguments(argc, argv, idx, &opts));
}
