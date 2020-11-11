/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:32:49 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/07 14:17:35 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"
#include "../../headers/get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*d;
	int		i;

	i = 0;
	d = (char *)malloc((len + 1) * sizeof(char));
	if (d == NULL || s == NULL)
		return (NULL);
	while (i < (int)len && s[start] && start < ft_strlen(s))
	{
		d[i] = s[start];
		start++;
		i++;
	}
	d[i] = '\0';
	return ((char *)d);
}
