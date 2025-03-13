#include "philosopher.h"

static void call_waiter(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_mutex);
	pthread_mutex_unlock(philo->fork_mutex);
	pthread_mutex_lock(philo->next->fork_mutex);
	pthread_mutex_unlock(philo->next->fork_mutex);
	
	pthread_mutex_lock(philo->waiter);
		if (philo->head == philo->restaurant->customer_count - 1)
		{
			pthread_mutex_lock(philo->next->fork_mutex);
			pthread_mutex_lock(philo->fork_mutex);
		}
		else
		{
			pthread_mutex_lock(philo->fork_mutex);
			pthread_mutex_lock(philo->next->fork_mutex);
		}
	pthread_mutex_unlock(philo->waiter);
}

static int eating(t_philo *philo)
{
	controlled_sleep();
	if (is_closed(philo->restaurant))
		return (0);

	call_waiter(philo);

	pthread_mutex_lock(philo->status_mutex);
	philo->fork = philo->head;
	philo->next->fork = philo->head;
	
	pthread_mutex_lock((philo->restaurant->restaurant_mutex));
	if (philo->restaurant->restaurant_closed)
	{
		pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
		pthread_mutex_unlock(philo->status_mutex);
		pthread_mutex_unlock(philo->fork_mutex);
		pthread_mutex_unlock(philo->next->fork_mutex);
		return (0);
	}
	pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
	pthread_mutex_unlock(philo->status_mutex);
	
	pthread_mutex_lock(philo->printer);
		printf("%lld [%d] has taken a fork\n", get_interval(philo), philo->head);
		printf("%lld [%d] has taken a fork\n", get_interval(philo), philo->head);
	pthread_mutex_unlock(philo->printer);
	
	pthread_mutex_lock(philo->status_mutex);
	philo->action = EAT;
	philo->last_action = get_interval(philo);
	philo->last_eat = philo->last_action;
	philo->count_eat++;
	pthread_mutex_unlock(philo->status_mutex);
	
	pthread_mutex_lock(philo->printer);
	printf("%lld [%d] is eating\n", philo->last_action, philo->head);
	pthread_mutex_unlock(philo->printer);
	
	
	
	msleep(philo->restaurant->eating_duration);
	
	pthread_mutex_lock(philo->status_mutex);
	
	pthread_mutex_lock((philo->restaurant->restaurant_mutex));
	if (philo->restaurant->restaurant_closed)
	{
		pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
		pthread_mutex_unlock(philo->status_mutex);
		pthread_mutex_unlock(philo->fork_mutex);
		pthread_mutex_unlock(philo->next->fork_mutex);
		return (0);
	}
	pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
	pthread_mutex_unlock(philo->status_mutex);
	philo->fork = 0;
	philo->next->fork = 0;
	pthread_mutex_unlock(philo->fork_mutex);
	pthread_mutex_unlock(philo->next->fork_mutex);
	return (1);
}

static int sleeping(t_philo *philo)
{
	controlled_sleep();
	
	pthread_mutex_lock(philo->status_mutex);
	pthread_mutex_lock((philo->restaurant->restaurant_mutex));
	
	if (philo->restaurant->restaurant_closed)
	{
		pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
		pthread_mutex_unlock(philo->status_mutex);
		return (0);
	}
	pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
	pthread_mutex_unlock(philo->status_mutex);

	
	pthread_mutex_lock(philo->status_mutex);
	philo->action = SLEEP;
	philo->last_action = get_interval(philo);
	pthread_mutex_unlock(philo->status_mutex);
	
	pthread_mutex_lock(philo->printer);
	printf("%lld [%d] is sleeping\n", philo->last_action, philo->head);
	pthread_mutex_unlock(philo->printer);
	
	msleep(philo->restaurant->sleeping_duration);
	
	pthread_mutex_lock(philo->status_mutex);
	pthread_mutex_lock((philo->restaurant->restaurant_mutex));
	
	if (philo->restaurant->restaurant_closed)
	{
		pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
		pthread_mutex_unlock(philo->status_mutex);
		return (0);
	}
	pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
	pthread_mutex_unlock(philo->status_mutex);
	return (1);
}

static int thinking(t_philo *philo)
{
	controlled_sleep();

	pthread_mutex_lock(philo->status_mutex);
	pthread_mutex_lock((philo->restaurant->restaurant_mutex));
	if (philo->restaurant->restaurant_closed)
	{
		pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
		pthread_mutex_unlock(philo->status_mutex);
		return (0);
	}
	pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
	pthread_mutex_unlock(philo->status_mutex);

	pthread_mutex_lock(philo->status_mutex);
	if (philo->action == THINK)
	{
		pthread_mutex_unlock(philo->status_mutex);
		return (1);
	};
	philo->action = THINK;
	philo->last_action = get_interval(philo);
	pthread_mutex_lock(philo->printer);
	printf("%lld [%d] is thinking\n", philo->last_action, philo->head);
	pthread_mutex_unlock(philo->printer);
	
	
	pthread_mutex_unlock(philo->status_mutex);
	return (1);
}

void *life(void *arg)
{
	t_philo *philo_himself;
	philo_himself = (t_philo *)arg;
	while (1)
	{
		if (!thinking(philo_himself))
			return (NULL);
		if (!eating(philo_himself))
			return (NULL);
		if (!sleeping(philo_himself))
			return (NULL);
	}
	return (NULL);
}

