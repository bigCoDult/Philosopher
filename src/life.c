/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:37:56 by sanbaek           #+#    #+#             */
/*   Updated: 2025/03/19 19:32:40 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_closed(t_restaurant *restaurant, pthread_mutex_t	*one, pthread_mutex_t *two, pthread_mutex_t *three)
{
	pthread_mutex_lock(restaurant->restaurant_mutex);
	if (restaurant->restaurant_closed)
	{
		pthread_mutex_unlock(restaurant->restaurant_mutex);
		if (one != NULL)
			pthread_mutex_unlock(one);
		if (two != NULL)
			pthread_mutex_unlock(two);
		if (three != NULL)
			pthread_mutex_unlock(three);
		return (1);
	}
	pthread_mutex_unlock(restaurant->restaurant_mutex);
	return (0);
}

static void	call_waiter(t_philo *philo, int customer_index)
{
	pthread_mutex_lock(philo->fork_mutex);
	pthread_mutex_unlock(philo->fork_mutex);
	pthread_mutex_lock(philo->next->fork_mutex);
	pthread_mutex_unlock(philo->next->fork_mutex);
	pthread_mutex_lock(philo->waiter);
	if (philo->index == customer_index)
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


















static int	eating(t_philo *philo)
{
	controlled_sleep();
	if (is_closed(philo->restaurant, NULL, NULL, NULL))
		return (0);
	call_waiter(philo, philo->restaurant->customer_index);

	philo->fork = philo->index;
	philo->next->fork = philo->index;





	
	pthread_mutex_lock(philo->printer);
		if (is_closed(philo->restaurant, philo->fork_mutex, philo->next->fork_mutex, philo->printer))
			return (0);
		printf("%lld [%d] has taken a fork\n", get_interval(philo), philo->index);
		printf("%lld [%d] has taken a fork\n", get_interval(philo), philo->index);
	pthread_mutex_unlock(philo->printer);
	
	philo->action = EAT;
	pthread_mutex_lock(philo->status_mutex);
		philo->last_eat = get_interval(philo);
		philo->count_eat++;
		
		
		pthread_mutex_lock(philo->restaurant->restaurant_mutex);
			if (philo->count_eat == philo->restaurant->full_goal)
				philo->restaurant->full_man_index++;
		pthread_mutex_unlock(philo->restaurant->restaurant_mutex);
		
		pthread_mutex_lock(philo->printer);
			if (is_closed(philo->restaurant, philo->printer, philo->status_mutex, NULL))
				return (0);
			printf("%lld [%d] is eating\n", philo->last_eat, philo->index);
		pthread_mutex_unlock(philo->printer);
	pthread_mutex_unlock(philo->status_mutex);
	msleep(philo->restaurant->eating_duration);
	if (is_closed(philo->restaurant, philo->fork_mutex, philo->next->fork_mutex, NULL))
		return (0);
	philo->fork = 0;
	philo->next->fork = 0;
	pthread_mutex_unlock(philo->fork_mutex);
	pthread_mutex_unlock(philo->next->fork_mutex);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	controlled_sleep();
	philo->action = SLEEP;
	pthread_mutex_lock(philo->printer);
	if (is_closed(philo->restaurant, philo->printer, NULL, NULL))
		return (0);
	printf("%lld [%d] is sleeping\n", get_interval(philo), philo->index);
	pthread_mutex_unlock(philo->printer);
	msleep(philo->restaurant->sleeping_duration);
	if (is_closed(philo->restaurant, NULL, NULL, NULL))
		return (0);
	return (1);
}

static int	thinking(t_philo *philo)
{
	controlled_sleep();
	if (is_closed(philo->restaurant, NULL, NULL, NULL))
		return (0);
	if (philo->action == THINK)
		return (1);
	philo->action = THINK;
	pthread_mutex_lock(philo->printer);
	if (is_closed(philo->restaurant, philo->printer, NULL, NULL))
		return (0);
	printf("%lld [%d] is thinking\n", get_interval(philo), philo->index);
	pthread_mutex_unlock(philo->printer);
	return (1);
}

void	*life(void *arg)
{
	t_philo	*philo_himself;

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
