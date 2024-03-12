/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:27:29 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/12 15:31:13 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
