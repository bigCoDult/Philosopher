/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:37:56 by sanbaek           #+#    #+#             */
/*   Updated: 2025/03/20 22:48:36 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_closed(t_restaurant *restaurant, \
	pthread_mutex_t	*one, pthread_mutex_t *two, pthread_mutex_t *three)
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

static int	sleeping(t_philo *philo)
{
	controlled_sleep();
	philo->action = SLEEP;
	pthread_mutex_lock(philo->printer);
	if (is_closed(philo->restaurant, philo->printer, NULL, NULL))
		return (0);
	printf("%lld %d is sleeping\n", get_interval(philo), philo->index);
	pthread_mutex_unlock(philo->printer);
	msleep(philo->restaurant->sleeping_duration);
	return (1);
}

static int	thinking(t_philo *philo)
{
	controlled_sleep();
	if (philo->action == THINK)
		return (1);
	philo->action = THINK;
	pthread_mutex_lock(philo->printer);
	if (is_closed(philo->restaurant, philo->printer, NULL, NULL))
		return (0);
	printf("%lld %d is thinking\n", get_interval(philo), philo->index);
	pthread_mutex_unlock(philo->printer);
	return (1);
}

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->restaurant->customer_index == 0)
		return (0);
	while (1)
	{
		if (!thinking(philo))
			return (NULL);
		if (!eating(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
	}
	return (NULL);
}
