/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:47:41 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/07 14:17:01 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"
#include "../../headers/get_next_line.h"

int		ft_isdigit(int ch)
{
	if (ch >= 48 && ch <= 57)
		return (1);
	return (0);
}
