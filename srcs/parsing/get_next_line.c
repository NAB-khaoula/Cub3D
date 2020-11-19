/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:16:29 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/17 14:14:00 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/get_next_line.h"

static char		*ft_search(const char *str, int c)
{
	char		ch;
	int			i;

	ch = c;
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return ((char *)&str[i]);
	else
		return (NULL);
}

int				ft_gnl(char **stat, char **line)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = *stat;
	while ((*stat)[i] != '\n' && (*stat)[i] != '\0')
		i++;
	if ((*stat)[i] == '\0')
	{
		*line = ft_substr2(*stat, 0, i);
		free(tmp);
		return (0);
	}
	*line = ft_substr2(*stat, 0, i);
	*stat = ft_strdup2(*stat + i + 1);
	free(tmp);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	int			r;
	static char *stat;
	char		*buff;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD)
		return (-1);
	if (!(buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((r = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r] = '\0';
		tmp = stat;
		stat = ft_strjoin2(stat, buff);
		free(tmp);
		if (ft_search(stat, '\n'))
			break ;
	}
	free(buff);
	*line = "\0";
	if (r < 0)
		return (-1);
	if (r == 0 && (ft_strlen2(stat)) == 0)
		return (0);
	return (ft_gnl(&stat, line));
}
