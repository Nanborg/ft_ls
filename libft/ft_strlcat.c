/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:20:45 by nicolsan          #+#    #+#             */
/*   Updated: 2024/10/07 11:41:13 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *source, size_t destsize)
{
	size_t	dest_len;
	size_t	source_len;
	size_t	i;

	dest_len = 0;
	source_len = 0;
	i = 0;
	while (source[source_len] != '\0')
		source_len++;
	while (dest_len < destsize && dest[dest_len] != '\0')
		dest_len++;
	if (dest_len == destsize)
		return (destsize + source_len);
	while (source[i] != '\0' && (dest_len + i) < (destsize - 1))
	{
		dest[dest_len + i] = source[i];
		i++;
	}
	if ((dest_len + i) < destsize)
		dest[dest_len + i] = '\0';
	return (dest_len + source_len);
}
