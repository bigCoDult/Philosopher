/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:37:54 by sanbaek           #+#    #+#             */
/*   Updated: 2025/03/19 20:42:00 by sanbaek          ###   ########.fr       */
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
