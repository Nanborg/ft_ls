/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:16:58 by nicolsan          #+#    #+#             */
/*   Updated: 2024/10/10 14:06:18 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	debut;
	size_t	fin;

	debut = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[debut] && ft_strchr(set, s1[debut]))
		debut++;
	fin = ft_strlen(s1);
	if (debut == fin)
		return (ft_strdup(""));
	while (fin > debut && ft_strchr(set, s1[fin - 1]))
		fin--;
	return (ft_substr(s1, debut, fin - debut));
}
