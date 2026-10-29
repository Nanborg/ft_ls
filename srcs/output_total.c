/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_total.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:58:58 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/29 19:05:23 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Print "total N" */
void	ft_print_total(t_list *entries)
{
	t_entry	*entry;
	long	total;

	total = 0;
	while (entries)
	{
		entry = entries->content;
		total += entry->st.st_blocks;
		entries = entries->next;
	}
	ft_putstr_fd("total ", 1);
	ft_putnbr_fd(total / 2, 1);
	ft_putstr_fd("\n", 1);
}
