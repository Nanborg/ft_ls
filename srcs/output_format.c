/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 13:16:00 by nicolsan          #+#    #+#             */
/*   Updated: 2026/10/30 13:16:00 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Affiche le nombre d'espaces demande
void	ft_put_spaces(int n)
{
	while (n > 0)
	{
		ft_putchar_fd(' ', 1);
		n--;
	}
}

// Affiche un entier positif sans le convertir en int
void	ft_put_ulong(unsigned long n)
{
	if (n >= 10)
		ft_put_ulong(n / 10);
	ft_putchar_fd('0' + n % 10, 1);
}
