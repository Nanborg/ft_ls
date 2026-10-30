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

/* Print owner and group columns */
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
		ft_putnbr_fd(entry->st.st_gid, 1);
	ft_put_spaces(w->group - ft_group_len(entry->st.st_gid));
}

/* Print size, or major and minor for a device */
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
	ft_putnbr_fd(entry->st.st_size, 1);
}

/* Print symlink target */
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

/* Print date in ls long format */
static void	ft_print_date(time_t file_time)
{
	time_t	now;
	char	*date;

	now = time(NULL);
	date = ctime(&file_time);
	if (file_time > now - 6 * 30 * 24 * 60 * 60
		&& file_time < now + 60 * 60)
		write(1, date + 4, 12);
	else
	{
		write(1, date + 4, 7);
		ft_putchar_fd(' ', 1);
		write(1, date + 20, 4);
	}
}

/* Print one entry in long format */
void	ft_print_long(t_entry *entry, t_width *w)
{
	char	str[11];

	ft_mode_string(entry->st.st_mode, str);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(" ", 1);
	ft_put_spaces(w->nlink - ft_numlen(entry->st.st_nlink));
	ft_putnbr_fd(entry->st.st_nlink, 1);
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
