/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 11:32:17 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Libere le nom, le chemin et l'entree
void	ft_free_entry(void *content)
{
	t_entry	*entry;

	entry = content;
	if (!entry)
		return ;
	free(entry->name);
	free(entry->path);
	free(entry);
}

// Libere toutes les entrees et les maillons de la liste
void	ft_free_entries(t_list **entries)
{
	ft_lstclear(entries, ft_free_entry);
}
