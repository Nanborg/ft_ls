/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:11:22 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Compare deux noms selon l'ordre des octets
int	ft_cmp_name(const char *a, const char *b)
{
	return (ft_strncmp(a, b, ft_strlen(a) + 1));
}

// Compare les dates de modification, nanosecondes comprises
// Place la plus recente en premier
static int	ft_cmp_time(t_entry *a, t_entry *b)
{
	time_t	ta;
	time_t	tb;

	ta = a->st.st_mtim.tv_sec;
	tb = b->st.st_mtim.tv_sec;
	if (ta != tb)
		return ((tb > ta) - (tb < ta));
	ta = a->st.st_mtim.tv_nsec;
	tb = b->st.st_mtim.tv_nsec;
	return ((tb > ta) - (tb < ta));
}

// Compare deux entrees selon -t et -r
// Renvoie si leur ordre doit etre inverse
static int	ft_must_swap(t_list *a, t_list *b, t_options *opts)
{
	int	cmp;

	cmp = 0;
	if (opts->t)
		cmp = ft_cmp_time(a->content, b->content);
	if (cmp == 0)
		cmp = ft_cmp_name(((t_entry *)a->content)->name,
				((t_entry *)b->content)->name);
	if (opts->r)
		return (cmp < 0);
	return (cmp > 0);
}

// Trie la liste selon les options
// Departage les dates identiques par le nom
void	ft_sort_entries(t_list **entries, t_options *opts)
{
	t_list	*cur;
	t_list	*next;
	void	*tmp;

	cur = *entries;
	while (cur)
	{
		next = cur->next;
		while (next)
		{
			if (ft_must_swap(cur, next, opts))
			{
				tmp = cur->content;
				cur->content = next->content;
				next->content = tmp;
			}
			next = next->next;
		}
		cur = cur->next;
	}
}
