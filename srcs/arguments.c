/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 12:56:48 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Print one dir arg, header if many */
int	ft_print_dir(char *path, t_options *opts, int header)
{
	t_list	*list;
	int		ret;

	if (header)
	{
		ft_putstr_fd(path, 1);
		ft_putendl_fd(":", 1);
	}
	list = NULL;
	ret = 0;
	if (ft_read_directory(path, opts, &list) == -1)
		ret = 2;
	ft_sort_entries(&list, opts);
	if (opts->l && ret == 0)
		ft_print_total(list);
	ft_print_entries(list, opts);
	if (opts->upper_r && ft_recursive_display(list, opts))
		ret = 2;
	ft_free_entries(&list);
	return (ret);
}

/* Print each directory arg, with header if many */
int	ft_dispatch_arguments(int argc, char **argv, int idx, t_options *opts)
{
	int	ret;
	int	printed;
	int	many;

	ft_sort_arguments(argc, argv, idx, opts);
	ret = ft_print_files(argc, argv, idx, opts);
	printed = ft_has_file(argc, argv, idx);
	many = (argc - idx > 1 || opts->upper_r);
	while (idx < argc)
	{
		if (ft_path_exists(argv[idx]) && ft_is_dir(argv[idx]))
		{
			if (printed)
				ft_putchar_fd('\n', 1);
			if (ft_print_dir(argv[idx], opts, many))
				ret = 2;
			printed = 1;
		}
		idx++;
	}
	return (ret);
}
