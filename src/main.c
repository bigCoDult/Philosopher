#include "philosopher.h"

void	init_condition(t_condition *condition, char **argv, int argc)
{
	condition->philo_count = ft_atoi(argv[1]);
	condition->starteat_die_deadline = ft_atoi(argv[2]);
	condition->eating_duration = ft_atoi(argv[3]);
	condition->sleeping_duration = ft_atoi(argv[4]);
	if (argc == 6)
		condition->musteat_deadline = ft_atoi(argv[5]);
	return ;
}


int main(int argc, char **argv)
{
	t_condition *condition;

	if (!validate_arg(argc, argv))
		return (1);
	init_condition(condition, argc, argv);

	return (0);
}