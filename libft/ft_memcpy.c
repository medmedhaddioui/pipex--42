/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:18:10 by mel-hadd          #+#    #+#             */
/*   Updated: 2023/11/19 12:22:35 by mel-hadd         ###   ########.fr       */
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
