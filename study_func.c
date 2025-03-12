#include "philosopher.h"

void *call_back1(void *arg)
{
	t_study *study;
	study = (t_study *)arg;
	int i;
	i = 0;
	pthread_mutex_lock(study->mutex);
	printf("\n");
	while(i < 5)
	{
		printf("1number : %d\n", study->number);
		--(study->number);
		i++;
		// usleep(10000);
	}
	pthread_mutex_unlock(study->mutex);
	return (NULL);
}
void *call_back2(void *arg)
{
	t_study *study;
	study = (t_study *)arg;
	int i;
	i = 0;
	pthread_mutex_lock(study->mutex);
	printf("\n");
	while(i < 5)
	{
		printf("2number : %d\n", study->number);
		++(study->number);
		i++;
		// usleep(10000);
	}
	pthread_mutex_unlock(study->mutex);
	return (NULL);
}
void *call_back3(void *arg)
{
	t_study *study;
	study = (t_study *)arg;
	int i;
	i = 0;
	pthread_mutex_lock(study->mutex);
	printf("\n");
	while(i < 5)
	{
		printf("3number : %d\n", study->number);
		--(study->number);
		i++;
		// usleep(10000);
	}
	pthread_mutex_unlock(study->mutex);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_study *study;
	study = (t_study *)malloc(sizeof(t_study));
	study->number = 0;
	study->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(study->mutex, NULL);
	
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	int result;
	
	result = pthread_create(&thread1, NULL, call_back1, (void *)study);
	result = pthread_create(&thread2, NULL, call_back2, (void *)study);
	result = pthread_create(&thread3, NULL, call_back3, (void *)study);
	usleep(100000);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	result = pthread_mutex_destroy(study->mutex);
	return 0;
}
