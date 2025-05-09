/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_atoitoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:43:36 by sanbaek           #+#    #+#             */
/*   Updated: 2025/03/19 18:43:53 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(char *str)
{
	long long	rest;
	int			sign;
	int			length;

	rest = 0;
	sign = 1;
	length = 0;
	while (str[length] && ft_isspace(str[length]))
		length++;
	if (str[length] == '-')
	{
		sign = sign * -1;
		length++;
	}
	else if (str[length] == '+')
		length++;
	while (str[length] && (str[length] >= '0' && str[length] <= '9'))
	{
		rest = rest * 10 + str[length] - '0';
		length++;
	}
	return (sign * (int)(rest));
}

static char	*ft_get_bigmin_str(void)
{
	char	*str;

	str = (char *)ft_calloc(11 + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memmove(str, "-2147483648", 11);
	return (str);
}

static void	ft_set_min_info(t_min_info *min_info, int n)
{
	if (n < 0)
	{
		min_info->minus_flag = 1;
		min_info->length = 2;
		min_info->n1 = -n;
		min_info->n2 = -n;
	}
	else
	{
		min_info->minus_flag = 0;
		min_info->length = 1;
		min_info->n1 = n;
		min_info->n2 = n;
	}
	while (min_info->n1 > 9)
	{
		min_info->n1 /= 10;
		min_info->length++;
	}
	return ;
}

char	*ft_itoa(int n)
{
	t_min_info	min_info;
	char		*str;

	if (n == -2147483648)
		return (ft_get_bigmin_str());
	min_info.minus_flag = 0;
	min_info.length = 0;
	min_info.n1 = 0;
	min_info.n2 = 0;
	ft_set_min_info(&min_info, n);
	str = (char *)ft_calloc(min_info.length + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	if (min_info.minus_flag == 1)
		str[0] = '-';
	while (min_info.length-- > min_info.minus_flag)
	{
		str[min_info.length] = (char)((min_info.n2 % 10) + '0');
		min_info.n2 /= 10;
	}
	return (str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
