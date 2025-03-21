/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:38:00 by sanbaek           #+#    #+#             */
/*   Updated: 2025/03/21 16:29:43 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	get_now(void)
{
	long long		now;
	struct timeval	time;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (now);
}

long long	get_interval(t_philo *philo)
{
	long long	now;

	now = get_now();
	return (now - philo->restaurant->open_time);
}

int	check_dead(long long now, long long last_eat, long long deadline)
{
	long long	starving;

	starving = now - last_eat;
	if (deadline < starving)
		return (1);
	return (0);
}

void	msleep(long long time, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < time)
	{
		if (is_onedead(philo) || is_allfull(philo))
			return ;
		usleep(1000);
		i++;
	}
}

void	controlled_sleep(void)
{
	usleep(700);
}
