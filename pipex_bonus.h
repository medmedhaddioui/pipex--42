/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medmed <medmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:21:19 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/11 22:08:44 by medmed           ###   ########.fr       */
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
	int		fds[2];
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
void first_child(char **env, char **av, data_b *o);
void n_child(char **env, char **av, data_b *o);
void last_child(char **env, char **av, data_b *o);
void parent(char **env ,char **av , data_b *o);
int  **creat_pipes(data_b *o);
void close_pipes(data_b *o);
char *find_path (char **arr, char *av);
void here_doc (char **env, char **av, data_b *o);
int ft_strcmp(char *s1, char *s2);
void ft_free(char **arr);

#endif
