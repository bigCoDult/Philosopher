/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:49:44 by sanbaek           #+#    #+#             */
/*   Updated: 2025/03/20 22:45:24 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

int	print_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->status_mutex);
	philo->last_eat = get_interval(philo);
	philo->count_eat++;
	pthread_mutex_lock(philo->printer);
	if (is_closed(philo->restaurant, philo->printer, philo->status_mutex, NULL))
		return (0);
	printf("%lld %d is eating\n", philo->last_eat, philo->index);
	pthread_mutex_unlock(philo->printer);
	pthread_mutex_unlock(philo->status_mutex);
	return (1);
}

static void	done_eating(t_philo *philo)
{
	philo->fork = 0;
	philo->next->fork = 0;
	pthread_mutex_lock(philo->restaurant->restaurant_mutex);
	if (philo->count_eat == philo->restaurant->full_goal)
		philo->restaurant->full_man_index++;
	pthread_mutex_unlock(philo->restaurant->restaurant_mutex);
}

int	eating(t_philo *philo)
{
	controlled_sleep();
	if (is_closed(philo->restaurant, NULL, NULL, NULL))
		return (0);
	call_waiter(philo, philo->restaurant->customer_index);
	philo->fork = philo->index;
	philo->next->fork = philo->index;
	philo->action = EAT;
	pthread_mutex_lock(philo->printer);
	if (is_closed(philo->restaurant, philo->fork_mutex, \
		philo->next->fork_mutex, philo->printer))
		return (0);
	printf("%lld %d has taken a fork\n", get_interval(philo), philo->index);
	printf("%lld %d has taken a fork\n", get_interval(philo), philo->index);
	pthread_mutex_unlock(philo->printer);
	if (print_eating(philo) == 0)
		return (0);
	msleep(philo->restaurant->eating_duration);
	if (is_closed(philo->restaurant, \
		philo->fork_mutex, philo->next->fork_mutex, NULL))
		return (0);
	done_eating(philo);
	pthread_mutex_unlock(philo->fork_mutex);
	pthread_mutex_unlock(philo->next->fork_mutex);
	return (1);
}
