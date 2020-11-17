/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:20:13 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/16 11:28:38 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	*ft_memset(void *str, int n, size_t nb)
{
	unsigned int	i;
	char			*ch;
	unsigned char	c;

	i = 0;
	ch = str;
	c = n;
	while (i < nb)
	{
		ch[i] = c;
		i++;
	}
	return (str);
}
