#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_condition
{
	int	philo_count;
	int	starteat_die_deadline;
	int	eating_duration;
	int	sleeping_duration;
	int	musteat_deadline;
	long long start_time;
}	t_condition;

typedef enum s_status
{
	EAT,
	THINK,
	SLEEP
}	t_status;

typedef struct s_philo
{
	int	head;
	long long time_lasteat;
	int alive;
	pthread_t thread;
	pthread_mutex_t	*fork;
	t_condition *condition;
	t_philo *next;
	t_philo *prev;
}	t_philo;

typedef struct s_min_info
{
	int		minus_flag;
	int		length;
	int		n1;
	int		n2;
}	t_min_info;

int validate_argv(int argc,char **argv);
void	*ft_calloc(size_t num, size_t size);
int	ft_atoi(char *str);
void	init_condition(t_condition *condition, char **argv, int argc);
long long convert_timeval_msec(struct timeval *timeval);









#endif