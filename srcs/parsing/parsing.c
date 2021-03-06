/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 09:00:13 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/24 14:44:22 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"
#include "../../headers/get_next_line.h"

void	init_checker(t_struct *gnrl)
{
	gnrl->map.check_r = 0;
	gnrl->map.check_n = 0;
	gnrl->map.check_s = 0;
	gnrl->map.check_w = 0;
	gnrl->map.check_e = 0;
	gnrl->map.check_sp = 0;
	gnrl->map.check_f = 0;
	gnrl->map.check_c = 0;
	gnrl->map.check_m = 0;
	gnrl->map.check_pos = 0;
}

void	parsing_check(t_struct *gnrl, int fd)
{
	if (*gnrl->map.line == 'R')
		check_resolution(gnrl);
	else if (*gnrl->map.line == 'F')
		check_flour(gnrl);
	else if (*gnrl->map.line == 'C')
		check_ceil(gnrl);
	else if (*gnrl->map.line == 'N' || *gnrl->map.line == 'S'
	|| *gnrl->map.line == 'W' || *gnrl->map.line == 'E')
		check_path(gnrl);
	else if (*gnrl->map.line == ' ' || *gnrl->map.line == '1')
		check_map(gnrl, fd);
	else if (*gnrl->map.line != '\0')
	{
		ft_error("Error\nImposter line!");
		free(gnrl->map.line);
	}
	else if (gnrl->map.line)
		free(gnrl->map.line);
}

void	parsing(t_struct *gnrl, char *argv)
{
	int	fd;
	int	r;

	init_checker(gnrl);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_error("Error\nArgument not valid!");
	while ((r = get_next_line(fd, &gnrl->map.line)) == 1)
		parsing_check(gnrl, fd);
	if (r == 0)
		free(gnrl->map.line);
	if (gnrl->map.check_m == 0)
		ft_error("Error\nMap needed!");
	if (gnrl->map.check_pos == 0)
		ft_error("Error\nNo position found");
	close(fd);
}
