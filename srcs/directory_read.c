/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:10:09 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Lit les entrees du dossier ouvert et remplit la liste
// Ignore les noms caches sans -a et signale les erreurs
static int	ft_read_entries(DIR *dir, const char *path,
	t_options *opts, t_list **list)
{
	struct dirent	*de;
	int				ret;

	ret = 0;
	errno = 0;
	de = readdir(dir);
	while (de)
	{
		if ((opts->a || de->d_name[0] != '.')
			&& ft_add_entry(list, path, de->d_name, opts) == -1)
			return (1);
		if (*list && (opts->l || opts->t || opts->upper_r)
			&& !((t_entry *)ft_lstlast(*list)->content)->st.st_mode)
			ret = 1;
		errno = 0;
		de = readdir(dir);
	}
	if (errno)
	{
		ft_ls_directory_error((char *)path);
		ret = 1;
	}
	return (ret);
}

// Ouvre le dossier, lit ses entrees puis le ferme
// Renvoie -1 si l'ouverture echoue, 1 si la lecture est incomplete
int	ft_read_directory(const char *path, t_options *opts, t_list **list)
{
	DIR	*dir;
	int	ret;

	dir = opendir(path);
	if (!dir)
	{
		ft_ls_directory_error((char *)path);
		return (-1);
	}
	ret = ft_read_entries(dir, path, opts, list);
	closedir(dir);
	return (ret);
}
