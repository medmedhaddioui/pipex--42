/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:03:27 by mel-hadd          #+#    #+#             */
/*   Updated: 2023/11/16 19:17:13 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	len = 0;
	while (len < dstsize - 1 && src[len] != '\0')
	{
		dst[len] = src[len];
		len++;
	}
	if (len < dstsize)
		dst[len] = '\0';
	len = ft_strlen(src);
	return (len);
}
