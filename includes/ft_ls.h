/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 00:30:41 by nicolsan         ###   ########.fr       */
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

int		ft_parse_options(int argc, char **argv, t_options *opts);
void	ft_dispatch_arguments(int argc, char **argv, t_options *opts);
t_list	*ft_read_directory(const char *path, t_options *opts);
int		ft_fill_entry(t_entry *entry, const char *path, const char *name);
void	ft_print_entries(t_list *entries, t_options *opts);
void	ft_sort_entries(t_list **entries, t_options *opts);
void	ft_recursive_display(t_list *entries, t_options *opts);
void	ft_ls_error(const char *context);
void	ft_free_entries(t_list **entries);
void	ft_print_long(t_entry *entry);

#endif
