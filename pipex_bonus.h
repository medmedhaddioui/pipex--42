/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:21:19 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/05 13:59:54 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/wait.h>

#define STDIN 0
#define STDOUT 1
#define INFILE 1
#define OUTFILE 0

typedef struct data_s
{
	int len;
	int i;
	int fds[2];
	int		fdi;
	int		fdo;
	pid_t	pid;
	pid_t pid2;
	char	*path;
	char	**cmd;
	char	**cmd2;

}			data_b;

void ft_error(char *s);
char		*read_path(char **env, char *av);
void	child(char **env, char **av, data_b *o);
int	file_open(const char *filename, int i);
// void	child_2(char **env, char **av, data_b *o);
// void parent(char **env ,char **av , data_b *o);
#endif
