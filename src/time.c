#include "philosopher.h"

long long get_now(void)
{
	struct timeval time;
	long long now;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec / 1000;
	return now;
}

long long get_interval(t_philo *philo)
{
	long long now;

	now = get_now();
	return (now - philo->condition->start_time);
}

int check_dead(t_philo *philo)
{
	long long now;
	long long starving;
	now = get_interval(philo);
	starving = now - philo->lasteat;
	if (philo->condition->musteat_deadline < starving)
		return (1);
	return (0);
}
