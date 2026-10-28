/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 00:02:04 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Return opendir(path) as a list, hidden with (-a) */
t_list	*ft_read_directory(const char *path, t_options *opts)
{
	DIR				*dir;
	struct dirent	*de;
	t_list			*list;

	dir = opendir(path);
	if (!dir)
		return (NULL);
	list = NULL;
	de = readdir(dir);
	while (de)
	{
		if (opts->a || de->d_name[0] != '.')
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(de->d_name)));
		de = readdir(dir);
	}
	closedir(dir);
	return (list);
}
