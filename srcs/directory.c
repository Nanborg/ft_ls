/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:10:09 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Recoit un dossier et un nom
// Renvoie le chemin dossier/nom dans une nouvelle chaine
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

// Copie le nom et le chemin dans l'entree
// Renvoie -1 si une allocation echoue
static int	ft_fill_name(t_entry *entry, char *path, const char *name)
{
	entry->name = ft_strdup(name);
	entry->path = ft_strdup(path);
	if (!entry->name || !entry->path)
		return (-1);
	return (0);
}

// Remplit le nom et le chemin de l'entree
// Lit aussi ses metadonnees si les options le demandent
static int	ft_directory_entry(t_entry *entry, char *path,
	const char *name, t_options *opts)
{
	if (!opts->l && !opts->t && !opts->upper_r)
		return (ft_fill_name(entry, path, name));
	if (ft_fill_name(entry, path, name) == -1)
		return (-1);
	if (lstat(path, &entry->st) == -1)
		ft_ls_error(path);
	return (0);
}

// Cree une entree du dossier et l ajoute a la liste
// Renvoie -1 si sa creation echoue
int	ft_add_entry(t_list **list, const char *dir,
	const char *name, t_options *opts)
{
	t_entry	*entry;
	t_list	*node;
	char	*full_path;

	full_path = ft_make_path(dir, name);
	entry = ft_calloc(1, sizeof(*entry));
	node = ft_lstnew(entry);
	if (!full_path || !entry || !node
		|| ft_directory_entry(entry, full_path, name, opts) == -1)
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
