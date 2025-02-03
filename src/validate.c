#include "philosopher.h"

int validate_argv(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if ( (ft_strcmp(ft_itoa(ft_atoi(argv[1])), argv[1]) != 0) \
		|| (ft_strcmp(ft_itoa(ft_atoi(argv[2])), argv[2]) != 0) \
		|| (ft_strcmp(ft_itoa(ft_atoi(argv[3])), argv[3]) != 0) \
		|| (ft_strcmp(ft_itoa(ft_atoi(argv[4])), argv[4]) != 0) )
	{
		printf("Error: improper argv\n");
		return (0);
	}
	if (argc == 6 && ft_strcmp(ft_itoa(ft_atoi(argv[5])), argv[5]) != 0)
	{
		printf("Error: improper argv\n");
		return (0);
	}
	if (ft_atoi(argv[1]) > 300)
	{
		printf("Error: Too many philosophers\n");
		return (0);
	}
	return (1);
}
