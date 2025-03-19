/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:43:45 by sanbaek           #+#    #+#             */
/*   Updated: 2025/03/19 20:43:52 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_allfull(t_philo *philo)
{
	pthread_mutex_lock((philo->restaurant->restaurant_mutex));
	if (philo->restaurant->customer_index == philo->restaurant->full_man_index)
	{
		philo->restaurant->restaurant_closed = 1;
		pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
		pthread_mutex_unlock(philo->status_mutex);
		pthread_mutex_lock(philo->printer);
		printf("All philosophers are full\n");
		pthread_mutex_unlock(philo->printer);
		return (1);
	}
	else
		return (0);
}

static int	is_onedead(t_philo *philo)
{
	pthread_mutex_lock(philo->status_mutex);
	if (check_dead(get_interval(philo), \
		philo->last_eat, philo->restaurant->starve_deadline))
	{
		pthread_mutex_lock((philo->restaurant->restaurant_mutex));
		philo->restaurant->restaurant_closed = 1;
		pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
		pthread_mutex_unlock(philo->status_mutex);
		pthread_mutex_lock(philo->printer);
		printf("%lld [%d] is \
			---------------------------- \
			DEAD \
			---------------------------- \
			\n", get_interval(philo), philo->index);
		pthread_mutex_unlock(philo->printer);
		return (1);
	}
	else
		return (0);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_onedead(philo))
			return (NULL);
		if (is_allfull(philo))
			return (NULL);
		pthread_mutex_unlock(philo->status_mutex);
		pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
		philo = philo->next;
		usleep(10);
	}
}
