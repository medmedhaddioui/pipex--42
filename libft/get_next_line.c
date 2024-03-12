/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:27:19 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/12 15:30:58 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		buff = ft_strjoin_2(buff, str);
	}
	free(str);
	if (readed == 0 && (!buff || buff[0] == '\0'))
		return (free(buff), buff = NULL, NULL);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;
	int			len;
	char		*tmp;

	if (fd < 0)
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buff = read_file(fd, buff);
	if (!buff)
		return (NULL);
	len = count(buff);
	line = ft_substr(buff, 0, len + 1);
	tmp = buff;
	buff = ft_substr(buff, len + 1, ft_strlen(buff));
	free(tmp);
	return (line);
}
