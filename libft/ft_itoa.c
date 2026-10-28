/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:18:37 by nicolsan          #+#    #+#             */
/*   Updated: 2024/10/15 15:15:53 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lenght_num(int n)
{
	int			lenght;
	long long	nb;

	nb = n;
	lenght = 0;
	if (n <= 0)
	{
		lenght = 1;
		nb = -nb;
	}
	while (nb != 0)
	{
		nb = (nb / 10);
		lenght++;
	}
	return (lenght);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		lenght;
	char	*str;

	lenght = lenght_num(n);
	str = (char *)malloc(lenght + 1);
	nb = n;
	if (!str)
		return (NULL);
	str[lenght] = '\0';
	if (nb == 0)
		str[0] = 48;
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--lenght] = (nb % 10) + 48;
		nb = (nb / 10);
	}
	return (str);
}
