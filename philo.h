#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_phil
{
	int					is_eat;
	int					pos;
	int					fork;
	unsigned long long	lst_eat;
	unsigned long long	jst_eat;
	unsigned long long	num_eat;
	pthread_t			thread;
	pthread_mutex_t		mutex;
}	t_phil;

typedef struct s_str
{
	t_phil				*phil;
	pthread_mutex_t		*fork;
	pthread_mutex_t		mutx;
	pthread_mutex_t		lock;
	size_t				prm[5];
	int					ret;
	int					stt;
	unsigned long long	forks;
}	t_str;

t_str	g_s;

unsigned long long	lockfork(int at, int pv);
unsigned long long	gettime(void);
void				ft_sleep(unsigned long long	t, int at, int pv);
void				say(unsigned long long t, int i, char *txt);
void				put_time(unsigned long long n);
void				*thread_q(void *ag);
void				aboba(int at);
int					ft_strlen(char *str);
int					ft_atoi(const char *str);
int					str_error(int status, char *message);
int					ft_set_prms(int ac, char **av);
int					pre_main(int ac, char **av);
int					ft_free(int i);
int					main2(void);

#endif