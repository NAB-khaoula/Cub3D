/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 11:08:25 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/07 14:17:17 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"
#include "../../headers/get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	char	ch;
	int		i;

	ch = c;
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return ((char *)&str[i]);
	else
		return (NULL);
}
