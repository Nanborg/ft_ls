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

// Cree une entree depuis le chemin recu et l ajoute a la liste
// Renvoie -1 en cas d'echec
static int	ft_add_file(char *path, t_list **files)
{
	t_list	*node;
	t_entry	*entry;

	entry = ft_calloc(1, sizeof(*entry));
	node = ft_lstnew(entry);
	if (!entry || !node || ft_fill_entry(entry, path, path) == -1)
	{
		free(node);
		ft_free_entry(entry);
		return (-1);
	}
	ft_lstadd_back(files, node);
	return (0);
}

// Verifie le chemin et collecte ses informations si necessaire
// Renvoie 2 en cas d'erreur
static int	ft_collect_file(char *path, t_options *opts, t_list **files)
{
	if (!ft_path_exists(path))
	{
		ft_ls_error(path);
		return (2);
	}
	if ((opts->l || !ft_is_dir(path, opts))
		&& ft_add_file(path, files) == -1)
		return (2);
	return (0);
}

// Calcule les largeurs avec tous les arguments collectes
// Affiche seulement les fichiers
static void	ft_print_file_arguments(t_list *files, t_options *opts)
{
	t_width	width;
	t_entry	*entry;

	width = ft_get_width(files);
	while (files)
	{
		entry = files->content;
		if (!ft_is_dir(entry->path, opts))
		{
			if (opts->l)
				ft_print_long(entry, &width);
			else
				ft_putendl_fd(entry->name, 1);
		}
		files = files->next;
	}
}

// Collecte puis affiche les fichiers passes en arguments
// Renvoie 2 si un argument a provoque une erreur
int	ft_print_files(int argc, char **argv, int idx, t_options *opts)
{
	t_list	*files;
	int		ret;

	files = NULL;
	ret = 0;
	while (idx < argc)
	{
		if (ft_collect_file(argv[idx], opts, &files))
			ret = 2;
		idx++;
	}
	ft_print_file_arguments(files, opts);
	ft_free_entries(&files);
	return (ret);
}
