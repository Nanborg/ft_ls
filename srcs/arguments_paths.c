/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 13:16:00 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:16:00 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Verifie si le chemin'est un dossier
// Suit les liens symboliques seulement sans -l
int	ft_is_dir(char *path, t_options *opts)
{
	struct stat	st;

	if (lstat(path, &st) == -1)
		return (0);
	if (S_ISLNK(st.st_mode) && !opts->l
		&& stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

// Verifie que le chemin existe, meme si c'est un lien casse
int	ft_path_exists(char *path)
{
	struct stat	st;

	return (lstat(path, &st) == 0);
}

// Verifie si les arguments contiennent au moins un fichier
int	ft_has_file(int argc, char **argv, int idx, t_options *opts)
{
	while (idx < argc)
	{
		if (ft_path_exists(argv[idx]) && !ft_is_dir(argv[idx], opts))
			return (1);
		idx++;
	}
	return (0);
}
