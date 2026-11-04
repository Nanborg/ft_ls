/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 00:03:48 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Copie le nom, le chemin et les metadonnees sans suivre les liens
// Renvoie -1 en cas d'echec
int	ft_fill_entry(t_entry *entry, const char *path, const char *name)
{
	entry->name = ft_strdup(name);
	entry->path = ft_strdup(path);
	if (!entry->name || !entry->path)
		return (-1);
	if (lstat(entry->path, &entry->st) == -1)
	{
		ft_ls_error(entry->path);
		return (-1);
	}
	return (0);
}
