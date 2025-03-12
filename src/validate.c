#include "philosopher.h"

static int cmp_atoitoa(char *origin)
{
	int n;
	char *str;

	n = ft_atoi(origin);
	if (n < 0)
		return (0);
	str = ft_itoa(n);
	if (ft_strcmp(str, origin) == 0)
	{
		free(str);
		return (0);
	}
	else
	{
		free(str);
		return (-1);
	}
}

int validate_arg(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	if ( (cmp_atoitoa(argv[1]) != 0) || (cmp_atoitoa(argv[2]) != 0) \
		|| (cmp_atoitoa(argv[3]) != 0) || (cmp_atoitoa(argv[4]) != 0) )
	{
		printf("Error1: improper argv\n");
		return (0);
	}
	if (argc == 6 && cmp_atoitoa(argv[5]) != 0)
	{
		printf("Error2: improper argv\n");
		return (0);
	}
	if (ft_atoi(argv[1]) > 300)
	{
		printf("Error3: Too many philosophers\n");
		return (0);
	}
	return (1);
}
