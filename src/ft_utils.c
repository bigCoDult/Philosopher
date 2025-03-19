/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanbaek <sanbaek@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:39:31 by sanbaek           #+#    #+#             */
/*   Updated: 2025/03/19 18:43:23 by sanbaek          ###   ########.fr       */
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
