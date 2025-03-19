/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:37:54 by sanbaek           #+#    #+#             */
/*   Updated: 2025/03/19 19:49:17 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_restaurant	*restaurant;
	t_philo			**philo;

	if (!validate_arg(argc, argv))
		return (1);
	restaurant = (t_restaurant *)ft_calloc(1, sizeof(t_restaurant));
	init_restaurant(restaurant, argc, argv);
	philo = (t_philo **)ft_calloc(restaurant->customer_index + 1, \
		sizeof(t_philo *));
	*philo = init_philo(restaurant, philo);
	table(*philo);
	clear_table(philo);
	return (0);
}

void	table(t_philo *philo)
{
	t_philo		*current;
	pthread_t	monitor;
	int			i;

	current = philo;
	pthread_create(&monitor, NULL, &monitoring, (void *)philo);
	i = 0;
	while (i <= philo->restaurant->customer_index)
	{
		pthread_create(&current->thread, NULL, &life, (void *)current);
		current = current->next;
		i++;
	}
	i = 0;
	while (i <= philo->restaurant->customer_index)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
		i++;
	}
	pthread_join(monitor, NULL);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->status_mutex);
		if (check_dead(get_interval(philo), philo->last_eat, philo->restaurant->starve_deadline))
		{
			
			pthread_mutex_lock((philo->restaurant->restaurant_mutex));
			philo->restaurant->restaurant_closed = 1;
			pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
			pthread_mutex_unlock(philo->status_mutex);
			
			pthread_mutex_lock(philo->printer);
			printf("%lld [%d] is ---------------------------- DEAD ---------------------------- \n", get_interval(philo), philo->index);
			pthread_mutex_unlock(philo->printer);
			return (NULL);
		}
		
		pthread_mutex_lock((philo->restaurant->restaurant_mutex));
		if (philo->restaurant->customer_index == philo->restaurant->full_man_index)
		{
			
			philo->restaurant->restaurant_closed = 1;
			pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
			pthread_mutex_unlock(philo->status_mutex);
			
			pthread_mutex_lock(philo->printer);
			printf("---------------------------- All philosophers are full ----------------------------\n");
			pthread_mutex_unlock(philo->printer);
			return (NULL);
		}
		pthread_mutex_unlock(philo->status_mutex);
		pthread_mutex_unlock((philo->restaurant->restaurant_mutex));
		philo = philo->next;
		usleep(10);
	}
}

void	clear_table(t_philo **philo)
{
	int	i;
	int	end;

	i = 0;
	end = philo[i]->restaurant->customer_index;
	pthread_mutex_destroy(philo[i]->waiter);
	pthread_mutex_destroy(philo[i]->printer);
	pthread_mutex_destroy(philo[i]->restaurant->restaurant_mutex);
	free(philo[i]->waiter);
	free(philo[i]->printer);
	free(philo[i]->restaurant->restaurant_mutex);
	free(philo[i]->restaurant);
	while (i <= end)
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
