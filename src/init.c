#include "philosopher.h"

void	init_condition(t_condition *condition, int argc, char **argv)
{
	condition->start_time = get_now();
	condition->philo_count = ft_atoi(argv[1]);
	condition->starteat_die_deadline = 1000 * ft_atoi(argv[2]);
	condition->eating_duration = 1000 * ft_atoi(argv[3]);
	condition->sleeping_duration = 1000 * ft_atoi(argv[4]);
	if (argc == 6)
		condition->musteat_deadline = ft_atoi(argv[5]);
	return ;
}

t_philo *init_philo(t_condition *condition, t_philo **philo)
{
	int i;
	int k;
	long long start;
	
	i = 0;
	k = 0;
	start = get_now();
	pthread_mutex_t *waiter;
	pthread_mutex_t *printer;
	waiter = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	printer = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(waiter, NULL);
	pthread_mutex_init(printer, NULL);
	while (i < condition->philo_count)
	{
		while (k < condition->philo_count)
			philo[k++] = (t_philo *)ft_calloc(1, sizeof(t_philo));
		philo[i]->condition = condition;
		philo[i]->waiter = waiter;
		philo[i]->printer = printer;
		
		philo[i]->head = i;
		philo[i]->last_eat = start;
		
		philo[i]->fork_mutex = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
		philo[i]->status_mutex = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i]->fork_mutex, NULL);
		pthread_mutex_init(philo[i]->status_mutex, NULL);
		
		if (i == condition->philo_count - 1)
			philo[i]->next = philo[0];
		else
			philo[i]->next = philo[i + 1];
		i++;
	}
	return (*philo);
}
