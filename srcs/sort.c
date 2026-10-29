/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:54:23 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 10:23:45 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Compare two names in byte order */
static int	ft_cmp_name(const char *a, const char *b)
{
	return (ft_strncmp(a, b, ft_strlen(a) + 1));
}

/* Sort the list of names in byte order */
void	ft_sort_entries(t_list **entries, t_options *opts)
{
	t_list	*cur;
	t_list	*next;
	void	*tmp;

	(void)opts;
	cur = *entries;
	while (cur)
	{
		next = cur->next;
		while (next)
		{
			if (ft_cmp_name(cur->content, next->content) > 0)
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
