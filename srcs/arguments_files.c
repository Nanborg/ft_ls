/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 13:16:00 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:16:00 by nicolsan         ###   ########.fr       */
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

/* Verify if path exists, including broken symlinks */
int	ft_path_exists(char *path)
{
	struct stat	st;

	return (lstat(path, &st) == 0);
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
		if (!ft_path_exists(argv[idx]))
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

/* Verify if any arg is a file */
int	ft_has_file(int argc, char **argv, int idx)
{
	while (idx < argc)
	{
		if (ft_path_exists(argv[idx]) && !ft_is_dir(argv[idx]))
			return (1);
		idx++;
	}
	return (0);
}
