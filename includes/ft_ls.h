/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:08:14 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <errno.h>
# include <grp.h>
# include <pwd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <time.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <sys/sysmacros.h>

typedef struct s_options
{
	int		l;
	int		upper_r;
	int		a;
	int		r;
	int		t;
}	t_options;

typedef struct s_entry
{
	char		*name;
	char		*path;
	struct stat	st;
}	t_entry;

typedef struct s_width
{
	int	nlink;
	int	owner;
	int	group;
	int	size;
	int	major;
	int	minor;
}	t_width;

t_width	ft_get_width(t_list *entries);
int		ft_parse_options(int argc, char **argv, t_options *opts);
int		ft_read_directory(const char *path, t_options *opts, t_list **list);
int		ft_fill_entry(t_entry *entry, const char *path, const char *name);
void	ft_print_entries(t_list *entries, t_options *opts);
void	ft_sort_entries(t_list **entries, t_options *opts);
int		ft_cmp_name(const char *a, const char *b);
int		ft_recursive_display(t_list *entries, t_options *opts);
void	ft_ls_error(char *context);
void	ft_free_entries(t_list **entries);
void	ft_free_entry(void *content);
int		ft_is_dir(char *path);
int		ft_print_file(char *path, t_options *opts);
int		ft_print_files(int argc, char **argv, int idx, t_options *opts);
int		ft_dispatch_arguments(int argc, char **argv, int idx, t_options *opts);
int		ft_has_file(int argc, char **argv, int idx);
int		ft_print_dir(char *path, t_options *opts, int header);
void	ft_print_total(t_list *entries);
int		ft_numlen(unsigned long n);
int		ft_owner_len(uid_t uid);
int		ft_group_len(gid_t gid);
void	ft_put_owner(uid_t uid);
void	ft_mode_string(mode_t mode, char *str);
void	ft_perm_chars(mode_t mode, char *str);
void	ft_put_spaces(int n);
void	ft_print_long(t_entry *entry, t_width *w);
void	ft_print_size(t_entry *entry, t_width *w);
void	ft_print_link(t_entry *entry);
void	ft_sort_arguments(int argc, char **argv, int idx, t_options *opts);
int		ft_path_exists(char *path);
void	ft_ls_directory_error(char *path);

#endif
