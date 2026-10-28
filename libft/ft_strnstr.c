/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:56:42 by nicolsan          #+#    #+#             */
/*   Updated: 2024/10/07 10:27:16 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystk, const char *ndl, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*ndl == '\0')
	{
		return ((char *)haystk);
	}
	while (i < len && haystk[i] != '\0')
	{
		j = 0;
		while (ndl[j] != '\0' && (i + j) < len && haystk[i + j] == ndl[j])
		{
			j++;
		}
		if (ndl[j] == '\0')
		{
			return ((char *)&haystk[i]);
		}
		i++;
	}
	return (NULL);
}
