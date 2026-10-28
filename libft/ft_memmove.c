/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:14:19 by nicolsan          #+#    #+#             */
/*   Updated: 2024/10/11 13:41:01 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)source;
	if (len == 0 || source == dest)
		return (dest);
	if (source < dest)
	{
		while (len--)
			d[len] = s[len];
	}
	else
	{
		while (len --)
		{
			*d++ = *s++;
		}
	}
	return (dest);
}
