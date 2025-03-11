#include "philosopher.h"

void	init_condition(t_condition *condition, char **argv, int argc)
{
	condition->philo_count = ft_atoi(argv[1]);
	condition->starteat_die_deadline = ft_atoi(argv[2]);
	condition->eating_duration = ft_atoi(argv[3]);
	condition->sleeping_duration = ft_atoi(argv[4]);
	if (argc == 6)
		condition->musteat_deadline = ft_atoi(argv[5]);
	return ;
}

t_philo *init_philo(t_condition *condition)
{
	int i;
	t_philo *philo;
	long long start;
	
	i = 0;
	start = get_now();
	while (i < condition->philo_count)
	{
		philo[i].head = i;
		philo[i].time_lasteat = start;
		philo[i].alive = 1;
		philo[i].condition = condition;
		philo[i].fork = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].fork, NULL);
		if (i == 0)
			philo[i].prev = &philo[condition->philo_count - 1];
		else
			philo[i].prev = &philo[i - 1];
		if (i == condition->philo_count - 1)
			philo[i].next = &philo[0];
		else
			philo[i].next = &philo[i + 1];
		i++;
	}
	return (philo);
}
