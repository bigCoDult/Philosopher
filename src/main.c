#include "philosopher.h"

int main(int argc, char **argv)
{
	t_condition *condition;
	t_philo *philo;
	
	if (!validate_arg(argc, argv))
	return (1);
	init_condition(condition, argc, argv);
	philo = (t_philo *)ft_calloc(condition->philo_count, sizeof(t_philo));
	philo = init_philo(condition, philo);
	while(1)
		table(philo);
	// free_table();
	return (0);
}

void table(t_philo *philo)
{
	t_philo *current;
	current = philo->next;
	while (current != philo)
	{
		pthread_create(&current->thread, NULL, &life, (void *)current);
		current = current->next;
	}
}







void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(philo->next->fork);
	printf("%d philo : eating\n", get_interval(philo));
	usleep(philo->condition->eating_duration);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
}


void life(void *arg)
{
	t_philo *philo_himself;
	philo_himself = (t_philo *)arg;
	long long now;
	while (1)
	{
		
		if (check_dead(philo_himself))
			break;
		
		eat(philo_himself);
		
		if (check_dead(philo_himself))
			break;
		
		sleep(philo_himself);
		think(philo_himself);
	}
}

