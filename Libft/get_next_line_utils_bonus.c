/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:18:17 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/02/28 20:46:15 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst;

	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	i = 0;
	dst = (unsigned char *)dest;
	while (i < n)
	{
		*dst = *(unsigned char *)src;
		i++;
		dst++;
		src++;
	}
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*tab;

	len = ft_strlen(s);
	tab = (char *)malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	ft_memcpy(tab, s, len);
	tab[len] = '\0';
	return (tab);
}

char	*ft_strjoin_2(char *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	int		total_len;
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	total_len = len_s1 + len_s2;
	new_str = (char *)malloc((total_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, len_s1);
	ft_memcpy(new_str + len_s1, s2, len_s2);
	new_str[total_len] = '\0';
	free(s1);
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		ptr = ft_strdup("");
		return (ptr);
	}
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (len && s[start + i] != '\0')
	{
		ptr[i] = (char)s[start + i];
		len--;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
