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

/* Return if arguments must be swapped */
static int	ft_arg_must_swap(char *a, char *b, t_options *opts)
{
	int	a_dir;
	int	b_dir;
	int	cmp;

	a_dir = ft_is_dir(a);
	b_dir = ft_is_dir(b);
	if (a_dir != b_dir)
		return (a_dir > b_dir);
	cmp = ft_cmp_name(a, b);
	if (opts->r)
		return (cmp < 0);
	return (cmp > 0);
}

/* Sort file arguments before directories */
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
