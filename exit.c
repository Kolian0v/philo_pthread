#include "philo.h"

void	put_time(unsigned long long n)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	else
	{
		put_time(n / 10);
		put_time(n % 10);
	}
}

void	say(unsigned long long t, int i, char *txt)
{
	pthread_mutex_lock(&g_s.mutx);
	put_time(t);
	write(1, " ", 1);
	put_time(i + 1);
	write(1, txt, ft_strlen(txt));
	pthread_mutex_unlock(&g_s.mutx);
}

unsigned long long	lockfork(int at, int pv)
{
	unsigned long long	t;

	pthread_mutex_lock(&g_s.lock);
	pthread_mutex_lock(&g_s.phil[pv].mutex);
	t = gettime();
	say(t, at, " has taken a fork\n");
	pthread_mutex_lock(&g_s.phil[at].mutex);
	t = gettime();
	say(t, at, " has taken a fork\n");
	pthread_mutex_unlock(&g_s.lock);
	return (t);
}

void	ft_sleep(unsigned long long	t, int at, int pv)
{
	pthread_mutex_unlock(&g_s.phil[pv].mutex);
	pthread_mutex_unlock(&g_s.phil[at].mutex);
	say(t, at, " is sleeping\n");
}
