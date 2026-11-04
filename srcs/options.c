/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:02:12 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Active l option correspondant au caractere recu
// Renvoie -1 si elle est inconnue
static int	ft_set_option(char c, t_options *opts)
{
	if (c == 'l')
		opts->l = 1;
	else if (c == 'R')
		opts->upper_r = 1;
	else if (c == 'a')
		opts->a = 1;
	else if (c == 'r')
		opts->r = 1;
	else if (c == 't')
		opts->t = 1;
	else
		return (-1);
	return (0);
}

// Lit les lettres d'un argument comme -lart
// Renvoie -1 si une option'est inconnue
static int	ft_parse_one(const char *arg, t_options *opts)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (ft_set_option(arg[i], opts) == -1)
		{
			ft_putstr_fd("ft_ls: invalid option -- '", 2);
			write(2, &arg[i], 1);
			ft_putstr_fd("'\n", 2);
			ft_putstr_fd("Try 'ls --help' for more information.\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

// Deplace une option avant les chemins
// Conserve l'ordre des autres arguments
static void	ft_move_option(char **argv, int from, int to)
{
	char	*option;

	option = argv[from];
	while (from > to)
	{
		argv[from] = argv[from - 1];
		from--;
	}
	argv[to] = option;
}

// Lit les options, meme apres un chemin, et les place au debut
// Arrete au separateur -- et renvoie l'indice du premier chemin
int	ft_parse_options(int argc, char **argv, t_options *opts)
{
	int	i;
	int	idx;

	i = 1;
	idx = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1])
		{
			if (ft_strncmp(argv[i], "--", 3) == 0)
			{
				ft_move_option(argv, i, idx);
				return (idx + 1);
			}
			if (ft_parse_one(argv[i], opts) == -1)
				return (-1);
			ft_move_option(argv, i, idx++);
		}
		i++;
	}
	return (idx);
}
