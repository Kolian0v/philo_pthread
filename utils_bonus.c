#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res);
}

unsigned long long	gettime(void)
{
	struct timeval		tme;
	unsigned long long	tii;

	gettimeofday(&tme, NULL);
	tii = (tme.tv_usec / 1000) + (tme.tv_sec * 1000);
	return (tii);
}

int	ft_free(int i)
{
	if (g_s.phil && i == 1)
		free(g_s.phil);
	return (0);
}

int	str_error(int status, char *message)
{
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	return (status);
}
