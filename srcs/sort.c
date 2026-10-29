/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 11:37:02 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Compare two names in byte order */
static int	ft_cmp_name(const char *a, const char *b)
{
	return (ft_strncmp(a, b, ft_strlen(a) + 1));
}

/* Return if a and b must be swapped */
static int	ft_must_swap(t_list *a, t_list *b, t_options *opts)
{
	int	cmp;

	cmp = ft_cmp_name(((t_entry *)a->content)->name,
		((t_entry *)b->content)->name);
	if (opts->r)
		return (cmp < 0);
	return (cmp > 0);
}

/* Sort the list of names in byte order */
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
