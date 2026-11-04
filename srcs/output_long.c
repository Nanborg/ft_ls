/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_long.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 13:16:00 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:16:00 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <limits.h>
#include <sys/sysmacros.h>

// Affiche le proprietaire et le groupe avec leur alignement
static void	ft_print_owners(t_entry *entry, t_width *w)
{
	struct group	*gr;

	ft_put_owner(entry->st.st_uid);
	ft_put_spaces(w->owner - ft_owner_len(entry->st.st_uid));
	ft_putstr_fd(" ", 1);
	gr = getgrgid(entry->st.st_gid);
	if (gr)
		ft_putstr_fd(gr->gr_name, 1);
	else
		ft_put_ulong(entry->st.st_gid);
	ft_put_spaces(w->group - ft_group_len(entry->st.st_gid));
}

// Affiche la taille du fichier ou les numeros du peripherique
void	ft_print_size(t_entry *entry, t_width *w)
{
	if (S_ISCHR(entry->st.st_mode) || S_ISBLK(entry->st.st_mode))
	{
		ft_put_spaces(w->major - ft_numlen(major(entry->st.st_rdev)));
		ft_putnbr_fd(major(entry->st.st_rdev), 1);
		ft_putstr_fd(", ", 1);
		ft_put_spaces(w->minor - ft_numlen(minor(entry->st.st_rdev)));
		ft_putnbr_fd(minor(entry->st.st_rdev), 1);
		return ;
	}
	ft_put_spaces(w->size - ft_numlen(entry->st.st_size));
	ft_put_ulong(entry->st.st_size);
}

// Recoit une entree
// Affiche la cible si c'est un lien symbolique
void	ft_print_link(t_entry *entry)
{
	char	buf[PATH_MAX];
	ssize_t	len;

	if (!S_ISLNK(entry->st.st_mode))
		return ;
	len = readlink(entry->path, buf, sizeof(buf) - 1);
	if (len == -1)
		return ;
	buf[len] = '\0';
	ft_putstr_fd(" -> ", 1);
	ft_putstr_fd(buf, 1);
}

// Recoit la date de modification
// Affiche l'heure ou l'annee selon son anciennete
static void	ft_print_date(time_t file_time)
{
	time_t	now;
	char	*date;

	now = time(NULL);
	date = ctime(&file_time);
	if (!date)
	{
		ft_putstr_fd("????????????", 1);
		return ;
	}
	if (difftime(now, file_time) < 31556952.0 / 2
		&& difftime(now, file_time) >= 0)
		write(1, date + 4, 12);
	else
	{
		write(1, date + 4, 7);
		ft_putchar_fd(' ', 1);
		write(1, date + 20, 4);
	}
}

// Recoit une entree et les largeurs des colonnes
// Affiche ses informations au format long
void	ft_print_long(t_entry *entry, t_width *w)
{
	char	str[11];

	if (!entry->st.st_mode)
	{
		ft_putstr_fd("-????????? ? ? ? ?            ? ", 1);
		ft_putendl_fd(entry->name, 1);
		return ;
	}
	ft_mode_string(entry->st.st_mode, str);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(" ", 1);
	ft_put_spaces(w->nlink - ft_numlen(entry->st.st_nlink));
	ft_put_ulong(entry->st.st_nlink);
	ft_putstr_fd(" ", 1);
	ft_print_owners(entry, w);
	ft_putstr_fd(" ", 1);
	ft_print_size(entry, w);
	ft_putstr_fd(" ", 1);
	ft_print_date(entry->st.st_mtime);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(entry->name, 1);
	ft_print_link(entry);
	ft_putstr_fd("\n", 1);
}
