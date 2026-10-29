/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 13:51:11 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Return new str "dir/name" */
static char	*ft_make_path(const char *dir, const char *name)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, name);
	free(tmp);
	return (path);
}

/* Add one file entry to the list */
static int	ft_add_entry(t_list **list, const char *dir, const char *name)
{
	t_entry	*entry;
	t_list	*node;
	char	*full_path;

	full_path = ft_make_path(dir, name);
	entry = ft_calloc(1, sizeof(*entry));
	node = ft_lstnew(entry);
	if (!full_path || !entry || !node
		|| ft_fill_entry(entry, full_path, name) == -1)
	{
		free(full_path);
		free(node);
		ft_free_entry(entry);
		return (-1);
	}
	free(full_path);
	ft_lstadd_back(list, node);
	return (0);
}

/* Fill list from path, skip hidden unless (-a) */
int	ft_read_directory(const char *path, t_options *opts, t_list **list)
{
	DIR				*dir;
	struct dirent	*de;

	dir = opendir(path);
	if (!dir)
	{
		ft_ls_error((char *)path);
		return (-1);
	}
	*list = NULL;
	de = readdir(dir);
	while (de)
	{
		if ((opts->a || de->d_name[0] != '.')
			&& ft_add_entry(list, path, de->d_name) == -1)
		{
			ft_free_entries(list);
			closedir(dir);
			return (-1);
		}
		de = readdir(dir);
	}
	closedir(dir);
	return (0);
}
