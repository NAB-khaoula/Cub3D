/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:49:01 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/17 13:47:18 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"
#include "../../headers/get_next_line.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				sgn;
	long int		nb;

	i = 0;
	sgn = 1;
	nb = 0;
	while (str[i] == '\n' || str[i] == '\r' || str[i] == '\t' || str[i] == '\f'
			|| str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sgn = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	nb = sgn * nb;
	return ((int)nb);
}
