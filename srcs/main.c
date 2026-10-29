/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 14:04:28 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_options	opts;
	t_list		*list;
	int			idx;
	char		*path;

	opts = (t_options){0, 0, 0, 0, 0};
	idx = ft_parse_options(argc, argv, &opts);
	if (idx == -1)
		return (1);
	path = ".";
	if (idx < argc)
		path = argv[idx];
	list = NULL;
	if (access(path, F_OK) == -1)
	{
		ft_ls_error(path);
		return (2);
	}
	if (!ft_is_dir(path))
	{
		ft_putendl_fd(path, 1);
		return (0);
	}
	if (ft_read_directory(path, &opts, &list) == -1)
		return (2);
	ft_sort_entries(&list, &opts);
	ft_print_entries(list, &opts);
	ft_free_entries(&list);
	return (0);
}
