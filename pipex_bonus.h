/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:21:19 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/07 21:25:51 by mel-hadd         ###   ########.fr       */
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
	int argc;
	int pipes;
	int index_cmd;
	int i;
	int x;
	int		fdi;
	int		fdo;
	pid_t	pid;
	pid_t pid2;
	char	*path;
	char	**cmd;
	char	**cmd2;
	char **cmd3;
	int **arr;
}			data_b;

void ft_error(char *s);
char		*read_path(char **env, char *av);
int	file_open(const char *filename, int i);
void child_first(char **env, char **av, data_b *o);
void child_middle(char **env, char **av, data_b *o);
void child_last(char **env, char **av, data_b *o);
void parent(char **env ,char **av , data_b *o);
int  **creat_pipes(data_b *o);
void close_pipes(data_b *o);

#endif
