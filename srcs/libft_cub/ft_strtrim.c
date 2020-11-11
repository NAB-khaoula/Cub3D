/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:27:11 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/07 14:17:31 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"
#include "../../headers/get_next_line.h"

char	*ft_strtrim(char const *s, char const *set)
{
	size_t		len;
	char		*str;

	if (s == NULL)
		return (NULL);
	while (*s && ft_strchr(set, *s))
		s++;
	len = ft_strlen(s);
	while (len && ft_strchr(set, s[len]))
		len--;
	str = ft_substr(s, 0, len + 1);
	if (str == NULL)
		return (NULL);
	return (str);
}
