
#include "pipex_bonus.h"
#include <string.h>
void	ft_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
int ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] == '\n' && s2[i] == '\0')
		return 0;
	return (s1[i] - s2[i]);
}
void here_doc (char **env, char **av, data_b *o)
{
	char *s;
	if  (pipe(o->fds) < 0)
		ft_error("error pipe");
	s = get_next_line(0);
	while (ft_strcmp(s, av[2]) != 0)
	{
		str = get_next_line(0);
	}
	free(str);
}
void ft_free(char **arr)
{
	int i;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}