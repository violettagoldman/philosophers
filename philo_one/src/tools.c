/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 12:45:54 by vgoldman          #+#    #+#             */
/*   Updated: 2020/09/26 15:49:49 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	length(int n)
{
	int i;

	i = 0;
	if (n == -2147483648)
		return (12);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		nb;

	nb = n;
	i = length(nb) + 1;
	if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (nb == -2147483648)
		return (ft_memcpy(res, "-2147483648", i));
	res[i--] = '\0';
	if (nb == 0)
		return (ft_memcpy(res, "0", 2));
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		res[i--] = '0' + (nb % 10);
		nb /= 10;
	}
	return (res);
}

int			ft_atoi(const char *str)
{
	int		sign;
	int		res;

	sign = 1;
	res = 0;
	while (*str == '\t' || *str == '\n' || *str == '\f' || *str == '\r' ||
		*str == ' ' || *str == '\v')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * sign);
}

int			ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}
