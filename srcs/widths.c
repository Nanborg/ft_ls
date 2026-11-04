/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 19:22:02 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 21:30:21 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Renvoie le nombre de chiffres du nombre recu
int	ft_numlen(unsigned long n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

// Renvoie la longueur du nom du proprietaire ou de son UID
int	ft_owner_len(uid_t uid)
{
	struct passwd	*pw;

	pw = getpwuid(uid);
	if (pw)
		return (ft_strlen(pw->pw_name));
	return (ft_numlen(uid));
}

// Renvoie la longueur du nom du groupe ou de son GID
int	ft_group_len(gid_t gid)
{
	struct group	*gr;

	gr = getgrgid(gid);
	if (gr)
		return (ft_strlen(gr->gr_name));
	return (ft_numlen(gid));
}

// Agrandit les largeurs des colonnes selon l'entree recue
static void	ft_update_width(t_entry *entry, t_width *w)
{
	if (ft_numlen(entry->st.st_nlink) > w->nlink)
		w->nlink = ft_numlen(entry->st.st_nlink);
	if (ft_owner_len(entry->st.st_uid) > w->owner)
		w->owner = ft_owner_len(entry->st.st_uid);
	if (ft_group_len(entry->st.st_gid) > w->group)
		w->group = ft_group_len(entry->st.st_gid);
	if (S_ISCHR(entry->st.st_mode) || S_ISBLK(entry->st.st_mode))
	{
		if (ft_numlen(major(entry->st.st_rdev)) > w->major)
			w->major = ft_numlen(major(entry->st.st_rdev));
		if (ft_numlen(minor(entry->st.st_rdev)) > w->minor)
			w->minor = ft_numlen(minor(entry->st.st_rdev));
	}
	else if (ft_numlen(entry->st.st_size) > w->size)
		w->size = ft_numlen(entry->st.st_size);
}

// Parcourt les entrees
// Renvoie les largeurs necessaires au format long
t_width	ft_get_width(t_list *entries)
{
	t_width	w;

	w = (t_width){0, 0, 0, 0, 0, 0};
	while (entries)
	{
		ft_update_width(entries->content, &w);
		entries = entries->next;
	}
	if (w.major + w.minor + 2 > w.size && w.major)
		w.size = w.major + w.minor + 2;
	return (w);
}
