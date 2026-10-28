/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:17:50 by nicolsan          #+#    #+#             */
/*   Updated: 2024/10/07 13:38:50 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	length;
	char	*cpy;
	size_t	i;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	cpy = malloc(length + 1);
	if (cpy == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i <= length)
	{
		cpy[i] = s[i];
		i++;
	}
	return (cpy);
}
