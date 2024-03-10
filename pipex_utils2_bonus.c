
#include "pipex_bonus.h"
#include <string.h>
void	ft_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
int ft_strcmp(char *s1, char *s2)
{
	if(s1)
		s1[ft_strlen(s1) - 1] = '\0';
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
void here_doc (char **av, data_b *o)
{
	(void ) o;

	char *str;
	str  = get_next_line(0);
	while (ft_strcmp(str, av[2]) != 0)
	{
		str = get_next_line(0);
	}

}