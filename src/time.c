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
	// printf("start_time : %lld\n", philo->condition->start_time);
	// printf("now : %lld\n", now);
	// exit(0);
	return (now - philo->condition->start_time);
}

int check_dead(long long now, long long last_eat, long long deadline)
{
	long long starving;

	starving = now - last_eat;
	if (deadline < starving)
		return (1);
	return (0);
}
