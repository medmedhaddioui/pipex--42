/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:31:28 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/15 00:37:25 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

typedef struct m_data
{
	int		fdi;
	int		fdo;
	int		i;
	int		fds[2];
	pid_t	pid;
	pid_t	pid2;
	char	*path;
	char	**cmd;
	char	**cmd2;

}			t_data;

int			file_open(const char *filename, int i);
char		*read_path(char **env, char *cmd);
void		child(char **env, char **av, t_data *o);
void		child_2(char **env, char **av, t_data *o);
void		parent(char **env, char **av, t_data *o);
void		ft_error(char *s);
void		ft_free(char **arr);
char		*find_path(char **arr, char *av);
void		ft_exit(void);

#endif
