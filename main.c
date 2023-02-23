#include "philo.h"

void	*thread_q(void *ag)
{
	unsigned long long	t;
	int					at;
	int					pv;

	at = *(int *)ag;
	if (at % 2 == 1 && g_s.stt == 1)
		usleep(1);
	g_s.stt = 1;
	pv = at - 1;
	if (at == 0)
		pv = g_s.prm[0] - 1;
	t = lockfork(at, pv);
	g_s.phil[at].lst_eat = t;
	say(t, at, " is eating\n");
	g_s.phil[at].jst_eat++;
	usleep(g_s.prm[2] * 1000);
	t = gettime();
	ft_sleep(t, at, pv);
	usleep((g_s.prm[3] - (t - g_s.phil[at].lst_eat - g_s.prm[2])) * 1000);
	t = gettime();
	say(t, at, " is thinking\n");
	if (g_s.stt == 1)
		thread_q(ag);
	return (NULL);
}

int	ft_set_prms(int ac, char **av)
{
	int	i;

	i = 0;
	if (!av[1] || !av[2] || !av[3] || !av[4])
		return (0);
	while (i < 4)
	{
		g_s.prm[i] = ft_atoi(av[i + 1]);
		i++;
	}
	if (g_s.prm[0] <= 0 || g_s.prm[1] <= 0 || g_s.prm[2] <= 0
		|| g_s.prm[3] <= 0)
		return (0);
	if (ac == 6)
	{
		if (!ft_atoi(av[5]))
			return (0);
		else
			g_s.prm[4] = ft_atoi(av[5]);
	}
	if (g_s.prm[4])
		return (2);
	return (1);
}

int	pre_main(int ac, char **av)
{
	unsigned long long	t;
	size_t				i;

	g_s.ret = ft_set_prms(ac, av);
	if (!g_s.ret)
		return (ft_free(0));
	pthread_mutex_init(&g_s.mutx, NULL);
	pthread_mutex_init(&g_s.lock, NULL);
	g_s.phil = malloc(sizeof(t_phil) * g_s.prm[0]);
	if (!g_s.phil)
		return (ft_free(0));
	t = gettime();
	i = -1;
	while (++i < g_s.prm[0])
	{
		g_s.phil[i].pos = i;
		g_s.phil[i].lst_eat = t;
		g_s.phil[i].num_eat = 0;
		pthread_mutex_init(&g_s.phil[i].mutex, NULL);
	}
	return (1);
}

int	main2(void)
{
	unsigned long long	t;
	size_t				i;
	int					et;

	i = 0;
	t = gettime();
	et = 1;
	while (i < g_s.prm[0])
	{
		if (g_s.prm[4] && et == 1 && g_s.phil[i].jst_eat < g_s.prm[4])
			et = 0;
		if (g_s.phil[i].lst_eat + g_s.prm[1] < t)
		{
			say(t, i, " died\n");
			return (ft_free(1));
		}
		i++;
	}
	pthread_mutex_lock(&g_s.mutx);
	if (g_s.prm[4] && et == 1)
		return (ft_free(1));
	pthread_mutex_unlock(&g_s.mutx);
	return (1);
}

int	main(int ac, char **av)
{
	size_t	i;

	if (!(ac == 5 || ac == 6) || !pre_main(ac, av))
		return (str_error(0, "Error: arguments"));
	i = 0;
	while (i < g_s.prm[0])
	{
		pthread_create(&g_s.phil[i].thread, NULL, thread_q,
			(void *)&g_s.phil[i].pos);
		i++;
	}
	while (1)
		if (!main2())
			break ;
	pthread_mutex_destroy(&g_s.lock);
	pthread_mutex_destroy(&g_s.mutx);
	return (0);
}
