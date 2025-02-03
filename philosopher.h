#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_condition
{
	int	philo_count;
	int	starteat_die_deadline;
	int	eating_duration;
	int	sleeping_duration;
	int	musteat_deadline;
}	t_condition;

typedef struct s_min_info
{
	int		minus_flag;
	int		length;
	int		n1;
	int		n2;
}	t_min_info;

int	ft_isspace(char c);
int	ft_atoi(char *str);
char	*ft_itoa(int n);
int	ft_strcmp(const char *s1, const char *s2);
int validate_argv(char **argv, int argc);








#endif