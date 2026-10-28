/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:08:59 by nicolsan          #+#    #+#             */
/*   Updated: 2024/10/07 11:19:52 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *source, size_t lendest)
{
	size_t	len;

	len = 0;
	if (lendest > 0)
	{
		while (len < (lendest - 1) && source[len] != '\0')
		{
			dest[len] = source[len];
			len++;
		}
		dest[len] = '\0';
	}
	while (source[len] != '\0')
	{
		len++;
	}
	return (len);
}
