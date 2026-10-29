/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 13:12:19 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_options	opts;
	t_list		*list;
	int			idx;

	opts = (t_options){0, 0, 0, 0, 0};
	idx = ft_parse_options(argc, argv, &opts);
	if (idx == -1)
		return (1);
	if (idx < argc)
		list = ft_read_directory(argv[idx], &opts);
	else
		list = ft_read_directory(".", &opts);
	ft_sort_entries(&list, &opts);
	ft_print_entries(list, &opts);
	ft_free_entries(&list);
	return (0);
}
