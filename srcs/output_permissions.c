/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_permissions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 13:16:00 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:16:00 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Ajoute les lettres s, S, t ou T selon les droits speciaux
static void	ft_special_perm_chars(mode_t mode, char *str)
{
	if (mode & S_ISUID)
	{
		if (mode & S_IXUSR)
			str[2] = 's';
		else
			str[2] = 'S';
	}
	if (mode & S_ISGID)
	{
		if (mode & S_IXGRP)
			str[5] = 's';
		else
			str[5] = 'S';
	}
	if (mode & S_ISVTX)
	{
		if (mode & S_IXOTH)
			str[8] = 't';
		else
			str[8] = 'T';
	}
}

// Recoit les permissions du fichier
// Remplit les neuf caracteres rwx
void	ft_perm_chars(mode_t mode, char *str)
{
	const char	*rwx = "rwxrwxrwx";
	int			i;

	i = 0;
	while (i < 9)
	{
		if (mode & (1 << (8 - i)))
			str[i] = rwx[i];
		else
			str[i] = '-';
		i++;
	}
	ft_special_perm_chars(mode, str);
}
