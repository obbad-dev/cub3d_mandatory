/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:25:25 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:25:26 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

long	ft_atoi(char *nb, int *flag)
{
	long	n;
	int		i;
	long	sign;

	n = 0;
	i = 0;
	sign = 1;
	if (!nb)
		return (-1);
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == 32)
		i++;
	if (nb[i] == '-' || nb[i] == '+')
	{
		if (nb[i] == '-')
			sign = -sign;
		i++;
	}
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		n = n * 10 + (nb[i] - 48);
		i++;
	}
	if (!(nb[i] >= '0' && nb[i] <= '9') && nb[i])
		*flag = 0;
	return (n * sign);
}
