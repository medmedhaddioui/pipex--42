/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:21:47 by mel-hadd          #+#    #+#             */
/*   Updated: 2023/11/19 12:27:55 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		start;
	int		end;
	char	*tab;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	j--;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > i && ft_strchr(set, s1[j]))
		j--;
	start = i;
	end = j;
	tab = (char *)malloc((end - start) * sizeof(char) + 2);
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
		tab[i++] = s1[start++];
	tab[i] = '\0';
	return (tab);
}
