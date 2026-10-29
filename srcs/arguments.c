/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 14:00:09 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Verify if path is a directory */
int	ft_is_dir(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

void	ft_dispatch_arguments(int argc, char **argv, t_options *opts)
{
	(void)argc;
	(void)argv;
	(void)opts;
}
