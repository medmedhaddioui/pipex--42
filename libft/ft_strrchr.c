/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:34:07 by mel-hadd          #+#    #+#             */
/*   Updated: 2023/11/13 17:25:04 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen (s);
	while (i > 0 && *(s + i) != (char) c)
		i--;
	if (*(s + i) == (char) c)
		return ((char *)(s + i));
	return (NULL);
}
