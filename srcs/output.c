/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:11:46 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Affiche chaque nom ou ses informations avec -l
void	ft_print_entries(t_list *entries, t_options *opts)
{
	t_entry	*entry;
	t_width	w;

	w = ft_get_width(entries);
	while (entries)
	{
		entry = entries->content;
		if (opts->l)
			ft_print_long(entry, &w);
		else
			ft_putendl_fd(entry->name, 1);
		entries = entries->next;
	}
}

// Renvoie la lettre correspondant au type du fichier
static char	ft_type_char(mode_t mode)
{
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
	return ('-');
}

// Recoit le type et les permissions du fichier
// Construit la chaine comme -rw-r--r--
void	ft_mode_string(mode_t mode, char *str)
{
	str[0] = ft_type_char(mode);
	ft_perm_chars(mode, str + 1);
	str[10] = '\0';
}

// Affiche le nom du proprietaire ou son UID si le nom est inconnu
void	ft_put_owner(uid_t uid)
{
	struct passwd	*pw;

	pw = getpwuid(uid);
	if (pw)
		ft_putstr_fd(pw->pw_name, 1);
	else
		ft_put_ulong(uid);
}
