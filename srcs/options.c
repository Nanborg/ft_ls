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

/* Set the option matching char */
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

/* Parse one "-xyz" arg */
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

/* Return the first non-option index */
int	ft_parse_options(int argc, char **argv, t_options *opts)
{
	int	i;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1])
	{
		if (ft_strncmp(argv[i], "--", 3) == 0)
			return (i + 1);
		if (ft_parse_one(argv[i], opts) == -1)
			return (-1);
		i++;
	}
	return (i);
}
