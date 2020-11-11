/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:16:47 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/07 14:17:21 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"
#include "../../headers/get_next_line.h"

static char		*ft_join(char *str, char const *s1, char const *s2)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (s1[j])
	{
		str[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str = ft_join(str, s1, s2);
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}
