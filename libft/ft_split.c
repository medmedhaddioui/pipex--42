/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:19:14 by mel-hadd          #+#    #+#             */
/*   Updated: 2023/11/18 18:27:23 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free_memory(char **s, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (1);
}

static int	ft_word(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	*ft_alloc_dup_word(char *s, char c)
{
	int		i;
	char	*word;
	int		len;

	len = 0;
	i = 0;
	while (s[len] != c && s[len])
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**tab;

	if (!s)
		return (NULL);
	count = 0;
	tab = malloc((ft_word((char *)s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else if (*s != c)
		{
			tab[count] = ft_alloc_dup_word((char *)s, c);
			if (!tab[count] && ft_free_memory(tab, count))
				return (NULL);
			count++;
			while (*s != c && *s)
				s++;
		}
	}
	tab[count] = 0;
	return (tab);
}
