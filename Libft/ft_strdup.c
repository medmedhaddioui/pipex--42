/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:44:30 by mel-hadd          #+#    #+#             */
/*   Updated: 2023/11/15 16:14:42 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*tab;

	len = ft_strlen(s);
	tab = (char *) malloc (len * sizeof(char) + 1);
	if (tab == NULL)
		return (NULL);
	ft_memcpy(tab, s, len);
	tab [len] = '\0';
	return (tab);
}
