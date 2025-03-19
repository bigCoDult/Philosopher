/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:45:05 by sanbaek           #+#    #+#             */
/*   Updated: 2025/03/19 18:52:25 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_restaurant(t_restaurant *restaurant, int argc, char **argv)
{
	restaurant->customer_index = ft_atoi(argv[1]) - 1;
	restaurant->starve_deadline = ft_atoi(argv[2]);
	restaurant->eating_duration = ft_atoi(argv[3]);
	restaurant->sleeping_duration = ft_atoi(argv[4]);
	if (argc == 6)
		restaurant->eat_goal = ft_atoi(argv[5]);
	restaurant->open_time = get_now();
	restaurant->restaurant_mutex = \
		(pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(restaurant->restaurant_mutex, NULL);
	restaurant->restaurant_closed = 0;
	return ;
}

static void	init_one(t_philo **philo, int customer_index, int i)
{
	philo[i]->index = i;
	philo[i]->fork_mutex = \
		(pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	philo[i]->status_mutex = \
		(pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(philo[i]->fork_mutex, NULL);
	pthread_mutex_init(philo[i]->status_mutex, NULL);
	if (i != customer_index)
		philo[i]->next = philo[i + 1];
	else
		philo[i]->next = philo[0];
}

t_philo	*init_philo(t_restaurant *restaurant, t_philo **philo)
{
	int				i;
	int				k;
	pthread_mutex_t	*waiter;
	pthread_mutex_t	*printer;

	i = 0;
	k = 0;
	waiter = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	printer = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(waiter, NULL);
	pthread_mutex_init(printer, NULL);
	while (k <= restaurant->customer_index)
		philo[k++] = (t_philo *)ft_calloc(1, sizeof(t_philo));
	while (i <= restaurant->customer_index)
	{
		philo[i]->restaurant = restaurant;
		philo[i]->waiter = waiter;
		philo[i]->printer = printer;
		init_one(philo, restaurant->customer_index, i);
		i++;
	}
	return (*philo);
}
