/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolsan <nicolsan@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:13:24 by nicolsan          #+#    #+#             */
/*   Updated: 2024/10/17 10:32:33 by nicolsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	count;
	int		nb_mots;

	count = 0;
	nb_mots = 0;
	while (*s)
	{
		if (*s != c && nb_mots == 0)
		{
			nb_mots = 1;
			count ++;
		}
		else if (*s == c)
			nb_mots = 0;
		s++;
	}
	return (count);
}

static char	*ft_alloc(char const *s, char c)
{
	size_t	lenght;
	char	*mot;

	lenght = 0;
	while (s[lenght] && s[lenght] != c)
		lenght++;
	mot = (char *)malloc(sizeof(char) * (lenght + 1));
	if (!mot)
		return (NULL);
	ft_strlcpy(mot, s, lenght + 1);
	return (mot);
}

static void	ft_free_split(char **resultat, size_t i)
{
	while (i > 0)
		free(resultat[--i]);
	free(resultat);
}

char	**ft_split(char const *s, char c)
{
	char	**resultat;
	size_t	i;
	size_t	mots_count ;

	i = 0;
	if (!s)
		return (NULL);
	mots_count = ft_count(s, c);
	resultat = (char **)malloc(sizeof(char *) * (mots_count + 1));
	if (!resultat)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			resultat[i] = ft_alloc(s, c);
			if (!resultat [i])
				return (ft_free_split(resultat, i), NULL);
			s += ft_strlen(resultat[i++]);
		}
		else
			s++;
	}
	resultat[i] = NULL;
	return (resultat);
}
