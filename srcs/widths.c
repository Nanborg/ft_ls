/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 19:22:02 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 21:30:21 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Return nbr of digits of n */
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

/* Return len of owner / or uid */
int	ft_owner_len(uid_t uid)
{
	struct passwd	*pw;

	pw = getpwuid(uid);
	if (pw)
		return (ft_strlen(pw->pw_name));
	return (ft_numlen(uid));
}

int	ft_group_len(gid_t gid)
{
	struct group	*gr;

	gr = getgrgid(gid);
	if (gr)
		return (ft_strlen(gr->gr_name));
	return (ft_numlen(gid));
}

/* Max out each width with entry values */
static void	ft_update_widths(t_entry *entry, t_widths *w)
{
	if (ft_numlen(entry->st.st_nlink) > w->nlink)
		w->nlink = ft_numlen(entry->st.st_nlink);
	if (ft_owner_len(entry->st.st_uid) > w->owner)
		w->owner = ft_owner_len(entry->st.st_uid);
	if (ft_group_len(entry->st.st_gid) > w->group)
		w->group = ft_group_len(entry->st.st_gid);
	if (ft_numlen(entry->st.st_size) > w->size)
		w->size = ft_numlen(entry->st.st_size);
}

/* Compute the collumn widths of entries */
t_widths	ft_get_widths(t_list *entries)
{
	t_widths	w;

	w = (t_widths){0, 0, 0, 0};
	while (entries)
	{
		ft_update_widths(entries->content, &w);
		entries = entries->next;
	}
	return (w);
}
