/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 21:48:46 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Verifie que l'entree est un dossier a parcourir
// Exclut les liens symboliques, . et ..
static int	ft_is_subdir(t_entry *entry)
{
	if (!S_ISDIR(entry->st.st_mode))
		return (0);
	if (ft_strncmp(entry->name, ".", 2) == 0)
		return (0);
	if (ft_strncmp(entry->name, "..", 3) == 0)
		return (0);
	return (1);
}

// Parcourt les sous-dossiers dans l'ordre de la liste
// Renvoie 1 si un parcours echoue
int	ft_recursive_display(t_list *entries, t_options *opts)
{
	t_entry	*entry;
	int		ret;

	ret = 0;
	while (entries)
	{
		entry = entries->content;
		if (ft_is_subdir(entry))
		{
			if (ft_print_dir(entry->path, opts, 2))
				ret = 1;
		}
		entries = entries->next;
	}
	return (ret);
}
