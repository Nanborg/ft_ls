/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 12:56:48 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Lit, trie et affiche un dossier selon les options
// Parcourt aussi ses sous-dossiers avec -R
int	ft_print_dir(char *path, t_options *opts, int header)
{
	t_list	*list;
	int		ret;

	list = NULL;
	ret = ft_read_directory(path, opts, &list);
	if (ret == -1)
		return (2);
	if (header == 2)
		ft_putchar_fd('\n', 1);
	if (header)
	{
		ft_putstr_fd(path, 1);
		ft_putendl_fd(":", 1);
	}
	ft_sort_entries(&list, opts);
	if (opts->l)
		ft_print_total(list);
	ft_print_entries(list, opts);
	if (opts->upper_r && ft_recursive_display(list, opts))
		ret = 1;
	ft_free_entries(&list);
	return (ret);
}

// Affiche un dossier passe en argument
// Conserve le code d'erreur le plus eleve
static int	ft_argument_dir(char *path, t_options *opts, int header, int ret)
{
	int	status;

	status = ft_print_dir(path, opts, header);
	if (status > ret)
		return (status);
	return (ret);
}

// Trie les arguments puis affiche les fichiers et les dossiers
// Renvoie le code de sortie
int	ft_dispatch_arguments(int argc, char **argv, int idx, t_options *opts)
{
	int	ret;
	int	printed;
	int	many;

	ft_sort_arguments(argc, argv, idx, opts);
	ret = ft_print_files(argc, argv, idx, opts);
	printed = ft_has_file(argc, argv, idx, opts);
	many = (argc - idx > 1 || opts->upper_r);
	while (idx < argc)
	{
		if (ft_path_exists(argv[idx]) && ft_is_dir(argv[idx], opts))
		{
			ret = ft_argument_dir(argv[idx], opts, many + printed, ret);
			printed = 1;
		}
		idx++;
	}
	return (ret);
}
