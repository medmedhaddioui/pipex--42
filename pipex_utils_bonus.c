/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:20:46 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/06 22:10:41 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex_bonus.h"

int	file_open(const char *filename, int i)
{
	int	fd;

	if (i == 1)
	{
		if (access(filename, F_OK))
			ft_error("Error infile");
		fd = open(filename, O_RDONLY, 0644);
		return (fd);
	}
	else
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

char	*read_path(char **env, char *av)
{
	char	**arr;
	int		i;

	i = 0;
	if (av[0] == '/')
		return (NULL);
	if (access(av, F_OK) != -1)
		return (av);
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	arr = ft_split(env[i], ':');
	i = 0;
	arr[i] = ft_strchr(arr[i], '/');
	av = ft_strjoin("/", av);
	arr[i] = ft_strjoin(arr[i], av);
	while (arr[i] != NULL && access(arr[i], F_OK) == -1)
	{
		i++;
		arr[i] = ft_strjoin(arr[i], av);
	}
	return (arr[i]);
}
void close_pipes(data_b *o)
{
	int i;
	i = 0;
	while (i < o->pipes)
	{
		close(o->arr[i][0]);
		close(o->arr[i][1]);
		i++;
	}
}
int  **creat_pipes(data_b *o)
{
	int i;
	i = 0;
	int **arr;
	arr = malloc (o->pipes * sizeof(int *));
	if (!arr)
		return NULL;
	while (i < o->pipes)
    {
        arr[i] = malloc(2 * sizeof(int));
        if (!arr[i])
        {
            while (i > 0)
            {
                free(arr[i]);
				i--;
			}
            free(arr);
            return NULL;
        }
		if (pipe(arr[i]) < 0)
			perror("Error pipe");
		i++;
    }
	return arr;
}

void	ft_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}