/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:21:19 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/12 15:36:08 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define STDIN 0
# define STDOUT 1
# define INFILE 1
# define OUTFILE 0

typedef struct b_data
{
	int		len;
	int		argc;
	int		pipes;
	int		index_cmd;
	int		fds[2];
	int		i;
	int		x;
	int		fdi;
	int		fdo;
	pid_t	pid;
	pid_t	pid2;
	char	*path;
	char	**cmd;
	char	**cmd2;
	char	**cmd3;
	int		**arr;
	char	*s;

}			t_data;

void		ft_error(char *s);
char		*read_path(char **env, char *av);
int			file_open(const char *filename, int i);
void		first_child(char **env, char **av, t_data *o);
void		n_child(char **env, char **av, t_data *o);
void		last_child(char **env, char **av, t_data *o);
void		parent(char **env, char **av, t_data *o);
int			**creat_pipes(t_data *o);
void		close_pipes(t_data *o);
char		*find_path(char **arr, char *av);
void		here_doc(char **env, char **av, t_data *o);
int			ft_strcmp(char *s1, char *s2);
void		ft_free(char **arr);

#endif
