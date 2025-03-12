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
	// while(1)
	// 	table(*philo);
	t_philo *current;
	current = *philo;
	while (1)
	{
		pthread_mutex_lock(current->status_mutex);
		printf("%lld philo[%d] : %d\n", current->last_action, current->head, current->action);
		pthread_mutex_unlock(current->status_mutex);
		if (current->head == condition->philo_count - 1)
			break;
		current = current->next;
	}
	clear_table(philo);
	return (0);
}

void clear_table(t_philo **philo)
{
	int i;
	int end;
	i = 0;
	end = philo[i]->condition->philo_count;
	pthread_mutex_destroy(philo[i]->waiter);
	free(philo[i]->condition);
	free(philo[i]->waiter);
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

void table(t_philo *philo)
{
	t_philo *current;
	current = philo->next;
	// pthread_t *monitor_thread;
	while (current != philo)
	{
		pthread_create(&current->thread, NULL, &life, (void *)current);
		current = current->next;
	}
	// pthread_create(monitor_thread, NULL, &monitor, (void *)philo);
	// pthread_join(monitor, NULL);
}

// void *monitor(void *arg)
// {
// 	t_philo *philo;
// 	philo = (t_philo *)arg;
// 	t_philo *current;
// 	current = philo;
// 	while (1)
// 	{
// 		printf()
// 		printf("%d philo "philo->did
// 		pthread_mutex_lock(philo->status_mutex);
// 		philo->status = DEAD;
// 		pthread_mutex_unlock(philo->status_mutex);
// 	}
// 	return (NULL);
// }





void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->waiter);
	pthread_mutex_lock(philo->fork_mutex);
	pthread_mutex_lock(philo->next->fork_mutex);
	pthread_mutex_unlock(philo->waiter);
	philo->fork = philo->head;
	philo->next->fork = philo->next->head;
	
	pthread_mutex_lock(philo->status_mutex);
	philo->action = EAT;
	philo->last_eat = get_now();
	philo->last_action = philo->last_eat;
	philo->count_eat++;
	pthread_mutex_unlock(philo->status_mutex);
	
	
	usleep(philo->condition->eating_duration);
	philo->fork = 0;
	philo->next->fork = 0;
	pthread_mutex_unlock(philo->fork_mutex);
	pthread_mutex_unlock(philo->next->fork_mutex);
}

void sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->status_mutex);
	philo->last_action = get_now();
	philo->action = SLEEP;
	pthread_mutex_unlock(philo->status_mutex);
	usleep(philo->condition->sleeping_duration);
}

void think(t_philo *philo)
{
	pthread_mutex_lock(philo->status_mutex);
	philo->last_action = get_now();
	philo->action = THINK;
	pthread_mutex_unlock(philo->status_mutex);
}

void *life(void *arg)
{
	t_philo *philo_himself;
	philo_himself = (t_philo *)arg;
	while (1)
	{
		eat(philo_himself);
		sleeping(philo_himself);
		think(philo_himself);
	}
}

