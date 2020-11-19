/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:19:33 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/18 09:06:18 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/get_next_line.h"

size_t		ft_strlen2(const char *str)
{
	size_t i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char		*ft_strjoin2(char const *s1, char const *s2)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (ft_strdup2(s2));
	if (s2 == NULL)
		return (ft_strdup2(s1));
	tmp = malloc((ft_strlen2(s1) + ft_strlen2(s2) + 1) * sizeof(char));
	if (tmp == NULL)
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tmp[i + j] = s2[j];
		j++;
	}
	tmp[i + j] = '\0';
	return (tmp);
}

char		*ft_strdup2(const char *src)
{
	char	*dest;
	size_t	i;
	size_t	index;

	i = ft_strlen2(src);
	dest = (char *)malloc((i + 1) * sizeof(char));
	index = 0;
	if (dest == NULL)
		return (NULL);
	while (index < i)
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char		*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char	*d;
	int		i;

	i = 0;
	d = (char *)malloc((len + 1) * sizeof(char));
	if (d == NULL || s == NULL)
		return (NULL);
	while (i < (int)len && s[start] && start < ft_strlen2(s))
	{
		d[i] = s[start];
		start++;
		i++;
	}
	d[i] = '\0';
	return ((char *)d);
}
