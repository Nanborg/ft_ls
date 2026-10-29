/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 14:13:19 by nicolsan         ###   ########.fr       */
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

void	ft_dispatch_arguments(int argc, char **argv, t_options *opts)
{
	(void)argc;
	(void)argv;
	(void)opts;
}
