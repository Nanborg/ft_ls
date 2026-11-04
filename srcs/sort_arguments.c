/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 13:16:00 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:16:00 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Recoit deux chemins et compare leurs dates de modification
// Renvoie 0 si les dates sont egales ou la lecture echoue
static int	ft_arg_time(char *a, char *b)
{
	struct stat	sa;
	struct stat	sb;

	if (lstat(a, &sa) == -1 || lstat(b, &sb) == -1)
		return (0);
	if (sa.st_mtim.tv_sec != sb.st_mtim.tv_sec)
		return ((sb.st_mtim.tv_sec > sa.st_mtim.tv_sec)
			- (sb.st_mtim.tv_sec < sa.st_mtim.tv_sec));
	return ((sb.st_mtim.tv_nsec > sa.st_mtim.tv_nsec)
		- (sb.st_mtim.tv_nsec < sa.st_mtim.tv_nsec));
}

// Place les fichiers avant les dossiers
// Compare ensuite selon le nom ou la date et applique -r
static int	ft_arg_must_swap(char *a, char *b, t_options *opts)
{
	int	a_dir;
	int	b_dir;
	int	cmp;

	a_dir = ft_is_dir(a, opts);
	b_dir = ft_is_dir(b, opts);
	if (a_dir != b_dir)
		return (a_dir > b_dir);
	cmp = 0;
	if (opts->t)
		cmp = ft_arg_time(a, b);
	if (cmp == 0)
		cmp = ft_cmp_name(a, b);
	if (opts->r)
		return (cmp < 0);
	return (cmp > 0);
}

// Trie les arguments sur place selon les options
// Garde les fichiers avant les dossiers
void	ft_sort_arguments(int argc, char **argv, int idx, t_options *opts)
{
	int		i;
	int		j;
	char	*tmp;

	i = idx;
	while (i < argc)
	{
		j = i + 1;
		while (j < argc)
		{
			if (ft_arg_must_swap(argv[i], argv[j], opts))
			{
				tmp = argv[i];
				argv[i] = argv[j];
				argv[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
