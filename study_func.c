#include "philosopher.h"

void *call_back1(void *arg)
{
	int *number;
	number = (int *)arg;
	printf("\n");
	int i;
	i = 0;
	while(i < 5)
	{
		pthread_mutex_lock(&mutex);
		printf("1number : %d\n", *number);
		--(*number);
		pthread_mutex_unlock(&mutex);
		i++;
		usleep(10000);
	}
	return NULL;
}

void *call_back2(void *arg)
{
	int *number;
	number = (int *)arg;
	printf("\n");
	int i;
	i = 0;
	while(i < 5)
	{
		pthread_mutex_lock(&mutex);
		printf("3number : %d\n", *number);
		--(*number);
		pthread_mutex_unlock(&mutex);
		i++;
		usleep(10000);
	}
	return NULL;
}

void *call_back3(void *arg)
{
	int *number;
	number = (int *)arg;
	printf("\n");
	int i;
	i = 0;
	while(i < 5)
	{
		pthread_mutex_lock(&mutex);
		printf("2number : %d\n", *number);
		++(*number);
		pthread_mutex_unlock(&mutex);
		i++;
		usleep(10000);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_mutex_t mutex;
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	int result;
	int number;
	
	number = 0;
	
	result = pthread_mutex_init(&mutex, NULL);
	usleep(100000);
	result = pthread_create(&thread1, NULL, call_back1, &number);
	result = pthread_create(&thread2, NULL, call_back2, &number);
	result = pthread_create(&thread3, NULL, call_back3, &number);
	usleep(100000);
	// pthread_join(thread1, NULL);
	// pthread_join(thread2, NULL);
	// pthread_join(thread3, NULL);
	result = pthread_mutex_destroy(&mutex);
	return 0;
}

// int main(void)
// {
// 	int n =5;
// 	t_philo *philo;
// 	philo = (t_philo *)malloc(sizeof(t_philo) * n);
// }