#include "philo.h"

void	slowing_odds(int at)
{
	if (at % 2 == 1 && g_s.stt == 1)
		usleep(1);
	g_s.phil[at].is_eat = 0;
	g_s.stt = 1;
}

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
	if ((g_s.forks && !g_s.prm[4]) || (g_s.forks && g_s.phil[at].jst_eat
			< g_s.prm[4] && g_s.prm[4]))
	{
		if (g_s.phil[at].fork == 1 && g_s.forks > 0)
		{
			g_s.phil[at].fork++;
			g_s.forks--;
			g_s.phil[at].is_eat = 1;
		}
		if (g_s.phil[at].fork == 2 && g_s.forks > 1)
		{
			g_s.phil[at].fork += 2;
			g_s.forks -= 2;
			g_s.phil[at].is_eat = 1;
		}
	}
	pv = pv + 0;
	t = gettime();
	pthread_mutex_unlock(&g_s.lock);
	return (t);
}

void	ft_sleep(unsigned long long	t, int at, int pv)
{
	g_s.phil[at].fork = 0;
	g_s.forks += 2;
	pv += 0;
	say(t, at, " is sleeping\n");
}
