/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medmed <medmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:19:34 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/02 16:17:36 by medmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	found_newline(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	count(char *buff)
{
	int	i;

	i = 0;
	while (buff && (buff[i] != '\0' && buff[i] != '\n'))
		i++;
	return (i);
}

char	*read_file(int fd, char *buff)
{
	char	*str;
	int		readed;

	str = NULL;
	readed = 1;
	while (!found_newline(str) && readed != 0)
	{
		if (str)
			free(str);
		str = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!str)
			return (NULL);
		readed = read(fd, str, BUFFER_SIZE);
		if (readed < 0)
			return (free(str), free(buff), buff = NULL, NULL);
		str[readed] = '\0';
		buff = ft_strjoin(buff, str);
	}
	free(str);
	if (readed == 0 && (!buff || buff[0] == '\0'))
		return (free(buff), buff = NULL, NULL);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff[1024];
	char		*line;
	int			len;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buff[fd] = read_file(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	len = count(buff[fd]);
	line = ft_substr(buff[fd], 0, len + 1);
	tmp = buff[fd];
	buff[fd] = ft_substr(buff[fd], len + 1, ft_strlen(buff[fd]));
	free(tmp);
	return (line);
}
