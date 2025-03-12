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
	int i;
	i = 0;
	while (i++ < philo->condition->philo_count)
	{
		pthread_create(&current->thread, NULL, &life, (void *)current);
		current = current->next;
	}
	i = 0;
	while (i++ < philo->condition->philo_count)
	{
		pthread_join(current->thread, (void *)current);
		current = current->next;
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


