#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_min_info
{
	int		minus_flag;
	int		length;
	int		n1;
	int		n2;
}	t_min_info;

typedef struct s_study
{
	int		number;
	pthread_mutex_t *mutex;
	int time;
}	t_study;



typedef struct s_restaurant
{
	int	customer_count;
	int	starve_deadline;
	int	eating_duration;
	int	sleeping_duration;
	int	eat_goal;
	long long open_time;
	int restaurant_closed;
	pthread_mutex_t *restaurant_mutex;
}	t_restaurant;

typedef enum s_status
{
	ENTER,
	THINK,
	EAT,
	SLEEP
}	t_status;

typedef struct s_philo
{
	t_restaurant *restaurant;
	pthread_mutex_t	*waiter;
	pthread_mutex_t *printer;
	int	head;
	pthread_t thread;
	int action;
	long long last_eat;
	long long last_action;
	int fork;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*status_mutex;
	int count_eat;
	struct s_philo *next;
}	t_philo;



int		ft_atoi(char *str);
char	*ft_itoa(int n);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t num, size_t size);

int		validate_arg(int argc,char **argv);

void	init_restaurant(t_restaurant *restaurant, int argc, char **argv);
t_philo *init_philo(t_restaurant *restaurant, t_philo **philo);

long long get_now(void);
long long get_interval(t_philo *philo);
int check_dead(long long now, long long last_eat, long long deadline);
void msleep(long long time);
void controlled_sleep(void);

void		clear_table(t_philo **philo);
void table(t_philo *philo);

void *life(void *arg);
void *monitoring(void *arg);








#endif