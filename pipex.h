/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:31:28 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/01 20:39:21 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/wait.h>


typedef struct data_s
{
	int		fdi;
	int		fdo;
	int		i;
	int		fds[2];
	pid_t	pid;
	pid_t pid2;
	char	*path;
	char	**cmd;
	char	**cmd2;

}			data_t;

void		ft_error(void);
char		*read_path(char **env, char *av);
void child (char **env, char **av, int fd_1);
void child_2(char **env, char **av, int fd_0);

#endif
