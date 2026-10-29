/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 12:29:04 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_options	opts;
	t_list		*list;

	opts = (t_options){0, 0, 0, 0, 0};
	if (ft_parse_options(argc, argv, &opts) == -1)
		return (1);
	list = ft_read_directory(".", &opts);
	ft_sort_entries(&list, &opts);
	while (list)
	{
		ft_print_long(list->content);
		list = list->next;
	}
	return (0);
}
