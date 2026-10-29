/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 22:10:12 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Long format with -l, else name */
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

/* Return the type letter of mode */
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

/* Fill str with the rwx chars of mode */
static void	ft_perm_chars(mode_t mode, char *str)
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
}

/* Build the 10-char string of mode -rw-r--r-- */
static void	ft_mode_string(mode_t mode, char *str)
{
	str[0] = ft_type_char(mode);
	ft_perm_chars(mode, str + 1);
	str[10] = '\0';
}

/* Print owner name / uid */
static void	ft_put_owner(uid_t uid)
{
	struct passwd	*pw;

	pw = getpwuid(uid);
	if (pw)
		ft_putstr_fd(pw->pw_name, 1);
	else
		ft_putnbr_fd(uid, 1);
}

/* Print groupe name / gid */
static void	ft_put_group(gid_t gid)
{
	struct group	*gr;

	gr = getgrgid(gid);
	if (gr)
		ft_putstr_fd(gr->gr_name, 1);
	else
		ft_putnbr_fd(gid, 1);
}

/* Print n spaces */
void	ft_put_spaces(int n)
{
	while (n > 0)
	{
		ft_putchar_fd(' ', 1);
		n--;
	}
}

/* Print size, (major, minor) */
/* Print size, or "major, minor" for a device */
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

/* Print one entry in long format, columns padded by w */
void	ft_print_long(t_entry *entry, t_width *w)
{
	char	str[11];
	char	*date;

	ft_mode_string(entry->st.st_mode, str);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(" ", 1);
	ft_put_spaces(w->nlink - ft_numlen(entry->st.st_nlink));
	ft_putnbr_fd(entry->st.st_nlink, 1);
	ft_putstr_fd(" ", 1);
	ft_put_owner(entry->st.st_uid);
	ft_put_spaces(w->owner - ft_owner_len(entry->st.st_uid));
	ft_putstr_fd(" ", 1);
	ft_put_group(entry->st.st_gid);
	ft_put_spaces(w->group - ft_group_len(entry->st.st_gid));
	ft_putstr_fd(" ", 1);
	ft_print_size(entry, w);
	ft_putstr_fd(" ", 1);
	date = ctime(&entry->st.st_mtime);
	write(1, date + 4, 12);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(entry->name, 1);
	ft_putstr_fd("\n", 1);
}
