/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:39:58 by nicolsan          #+#    #+#             */
/*   Updated: 2024/10/15 15:14:30 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nb_of_members, size_t size)
{
	void	*ptr;

	if (size != 0 && nb_of_members > (size_t)-1 / size)
		return (NULL);
	if (nb_of_members == 0 || size == 0)
		return (malloc(1));
	ptr = malloc(size * nb_of_members);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nb_of_members * size);
	return (ptr);
}
