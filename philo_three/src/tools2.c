/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <vgoldman@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 16:56:16 by vgoldman          #+#    #+#             */
/*   Updated: 2020/10/10 17:02:50 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*prefix(char *id)
{
	char	*result;
	int		len;

	len = ft_strlen(id);
	if (!(result = (char *)malloc((len + 2) * sizeof(char))))
		err("Malloc error");
	result[0] = '/';
	len = -1;
	while (id[++len])
		result[len + 1] = id[len];
	result[len + 1] = '\0';
	free(id);
	return (result);
}
