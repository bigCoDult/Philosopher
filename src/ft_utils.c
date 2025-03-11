/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:39:31 by sanbaek           #+#    #+#             */
/*   Updated: 2025/02/22 22:32:12 by sanbaek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_bzero(void *dest, size_t count)
{
	memset(dest, 0, count);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	if (num != 0 && (num * size) / num != size)
		return (NULL);
	ptr = malloc(num * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, num * size);
	return (ptr);
}
void	*ft_memmove(void *dest, const void *src, size_t count)
{
	unsigned char		*dest_tmp;
	const unsigned char	*src_tmp;

	dest_tmp = (unsigned char *)dest;
	src_tmp = (const unsigned char *)src;
	if (dest_tmp > src_tmp)
	{
		while (count--)
			*(dest_tmp + count) = *(src_tmp + count);
	}
	else
	{
		while (count--)
			*dest_tmp++ = *src_tmp++;
	}
	return (dest);
}

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

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

void control_sleep(void)
{
	usleep(500);
}