#include "philosopher.h"

int main(int argc, char **argv)
{
	t_condition	*condition;
	t_philo		**philo;

	if (!validate_arg(argc, argv))
		return (1);
	condition = (t_condition *)ft_calloc(1, sizeof(t_condition));
	init_condition(condition, argc, argv);
	philo = (t_philo **)ft_calloc(condition->philo_count, sizeof(t_philo *));
	*philo = init_philo(condition, philo);
	table(*philo);
	clear_table(philo);
	return (0);
}

void table(t_philo *philo)
{
	t_philo *current;
	current = philo;
	pthread_t monitor;
	int i;
	
	pthread_create(&monitor, NULL, &monitoring, (void *)philo);
	i = 0;
	while (i++ < philo->condition->philo_count)
	{
		pthread_create(&current->thread, NULL, &life, (void *)current);
		// pthread_join(current->thread, NULL);
		current = current->next;
	}
	pthread_join(monitor, NULL);
}

void *monitoring(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->status_mutex);
		if (check_dead(get_interval(philo), philo->last_eat, philo->condition->starteat_die_deadline))
		{
			pthread_mutex_lock(philo->printer);
			printf("%lld [%d] is DEAD\n", get_interval(philo), philo->head);
			pthread_mutex_unlock(philo->printer);
			philo->action = DEAD;
			pthread_mutex_unlock(philo->status_mutex);
			return (NULL);
		}
		else
			pthread_mutex_unlock(philo->status_mutex);
		philo = philo->next;
		usleep(10);
	}
}

void clear_table(t_philo **philo)
{
	int i;
	int end;
	i = 0;
	end = philo[i]->condition->philo_count;
	pthread_mutex_destroy(philo[i]->waiter);
	pthread_mutex_destroy(philo[i]->printer);
	free(philo[i]->condition);
	free(philo[i]->waiter);
	free(philo[i]->printer);
	while (i < end)
	{
		pthread_mutex_destroy(philo[i]->fork_mutex);
		pthread_mutex_destroy(philo[i]->status_mutex);
		free(philo[i]->fork_mutex);
		free(philo[i]->status_mutex);
		free(philo[i]);
		i++;
	}
	free(philo);
}


