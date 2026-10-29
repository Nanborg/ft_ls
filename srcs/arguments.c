/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 15:35:27 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Verify if path is a directory */
int	ft_is_dir(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

/* Print file as a list of 1 entry */
int	ft_print_file(char *path, t_options *opts)
{
	t_list	*list;
	t_entry	*entry;

	entry = ft_calloc(1, sizeof(*entry));
	list = ft_lstnew(entry);
	if (!entry || !list || ft_fill_entry(entry, path, path) == -1)
	{
		free(list);
		ft_free_entry(entry);
		return (-1);
	}
	ft_print_entries(list, opts);
	ft_free_entries(&list);
	return (0);
}

/* Print file args, report missing ones */
int	ft_print_files(int argc, char **argv, int idx, t_options *opts)
{
	int	ret;

	ret = 0;
	while (idx < argc)
	{
		if (access(argv[idx], F_OK) == -1)
		{
			ft_ls_error(argv[idx]);
			ret = 2;
		}
		else if (!ft_is_dir(argv[idx]))
			ft_print_file(argv[idx], opts);
		idx++;
	}
	return (ret);
}

int	ft_dispatch_arguments(int argc, char **argv, int idx, t_options *opts)
{
	t_list	*list;
	int		ret;
	int		many;

	ret = ft_print_files(argc, argv, idx, opts);
	many = (argc - idx > 1);
	while (idx < argc)
	{
		if (access(argv[idx], F_OK) == 0 && ft_is_dir(argv[idx]))
		{
			if (many)
			{
				ft_putstr_fd(argv[idx], 1);
				ft_putendl_fd(":", 1);
			}
			list = NULL;
			if (ft_read_directory(argv[idx], opts, &list) == -1)
				ret = 2;
			ft_sort_entries(&list, opts);
			ft_print_entries(list, opts);
			ft_free_entries(&list);
		}
		idx++;
	}
	return (ret);
}
