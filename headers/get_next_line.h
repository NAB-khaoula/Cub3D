/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:14:29 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/18 13:13:58 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# define FD 10240
# define BUFFER_SIZE 24

size_t	ft_strlen2(const char *str);
char	*ft_strjoin2(char const *s1, char const *s2);
int		get_next_line(int fd, char **line);
char	*ft_strdup2(const char *src);
char	*ft_substr2(char const *s, unsigned int start, size_t len);
#endif
