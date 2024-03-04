/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:07:55 by mel-hadd          #+#    #+#             */
/*   Updated: 2023/11/18 18:24:28 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
