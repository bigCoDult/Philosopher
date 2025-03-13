#include "philosopher.h"

void	init_restaurant(t_restaurant *restaurant, int argc, char **argv)
{
	restaurant->customer_count = ft_atoi(argv[1]);
	restaurant->starve_deadline = ft_atoi(argv[2]);
	restaurant->eating_duration = ft_atoi(argv[3]);
	restaurant->sleeping_duration = ft_atoi(argv[4]);
	if (argc == 6)
		restaurant->eat_goal = ft_atoi(argv[5]);
	restaurant->open_time = get_now();
	restaurant->restaurant_closed = 0;
	return ;
}

t_philo *init_philo(t_restaurant *restaurant, t_philo **philo)
{
	int i;
	int k;
	
	i = 0;
	k = 0;
	pthread_mutex_t *waiter;
	pthread_mutex_t *printer;
	waiter = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	printer = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(waiter, NULL);
	pthread_mutex_init(printer, NULL);
	while (k < restaurant->customer_count)
		philo[k++] = (t_philo *)ft_calloc(1, sizeof(t_philo));
	while (i < restaurant->customer_count)
	{
		philo[i]->restaurant = restaurant;
		philo[i]->waiter = waiter;
		philo[i]->printer = printer;
		
		
		philo[i]->head = i;
		philo[i]->fork_mutex = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
		philo[i]->status_mutex = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i]->fork_mutex, NULL);
		pthread_mutex_init(philo[i]->status_mutex, NULL);
		
		if (i == restaurant->customer_count - 1)
			philo[i]->next = philo[0];
		else
			philo[i]->next = philo[i + 1];
		i++;
	}
	return (*philo);
}
