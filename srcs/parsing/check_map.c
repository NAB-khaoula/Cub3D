/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:46:25 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/24 18:48:35 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"
#include "../../headers/get_next_line.h"

void	check_borders_v(t_struct *gnrl)
{
	int		i;

	i = -1;
	while (*(*gnrl->map.map_rvs + ++i))
		if (*(*gnrl->map.map_rvs + i) != ' '
		&& *(*gnrl->map.map_rvs + i) != '1')
			ft_error("Error\nInvalid map!");
	i = -1;
	while (*(*(gnrl->map.map_rvs + gnrl->map.max_len - 1) + ++i))
		if (*(*(gnrl->map.map_rvs + gnrl->map.max_len - 1) + i) != '1'
		&& *(*(gnrl->map.map_rvs + gnrl->map.max_len - 1) + i) != ' ')
			ft_error("Error\nInvalid map!");
}

void	check_borders(t_struct *gnrl)
{
	int		i;

	i = -1;
	gnrl->map.count = 0;
	gnrl->map.max_len = ft_strlen(*gnrl->map.map);
	while (*(gnrl->map.map + ++i))
	{
		if (gnrl->map.max_len < (int)ft_strlen(*(gnrl->map.map + i)))
			gnrl->map.max_len = ft_strlen(*(gnrl->map.map + i));
		gnrl->map.count++;
	}
	i = -1;
	while (*(*gnrl->map.map + ++i))
		if (*(*gnrl->map.map + i) != ' ' && *(*gnrl->map.map + i) != '1')
			free_error(gnrl->map.map, "Error\nInvalid map!");
	i = -1;
	if (ft_strncmp(ft_strtrim(*(gnrl->map.map + gnrl->map.count - 1),
	" "), "", 1) == 0)
		free_error(gnrl->map.map, "Error\nInvalid map!");
	while (*(*(gnrl->map.map + gnrl->map.count - 1) + ++i))
		if (*(*(gnrl->map.map + gnrl->map.count - 1) + i) != '1'
		&& *(*(gnrl->map.map + gnrl->map.count - 1) + i) != ' ')
			free_error(gnrl->map.map, "Error\nInvalid map!");
}

void	valid_map(t_struct *gnrl)
{
	check_borders(gnrl);
	check_space(gnrl);
	reverse_map(gnrl);
	check_borders_v(gnrl);
	check_space_v(gnrl);
}

void	read_map(t_struct *gnrl, int fd)
{
	int		r;
	int		cmp;
	char	*tmp;

	free(gnrl->map.line);
	r = 1;
	while (r == 1)
	{
		r = get_next_line(fd, &gnrl->map.line);
		if (ft_strncmp(gnrl->map.line, "",
		ft_strlen(gnrl->map.line)) != 0 && cmp == 0)
			free_line(gnrl->map.fst_line, "Error\nInvalid map");
		tmp = gnrl->map.fst_line;
		gnrl->map.fst_line = ft_strjoin(gnrl->map.fst_line, "\v");
		free(tmp);
		tmp = gnrl->map.fst_line;
		gnrl->map.fst_line = ft_strjoin(gnrl->map.fst_line, gnrl->map.line);
		free(tmp);
		cmp = ft_strncmp(gnrl->map.line, "", ft_strlen(gnrl->map.line));
		if (r == 1 || ft_strncmp(gnrl->map.line, "",
		ft_strlen(gnrl->map.line)) != 0)
			free(gnrl->map.line);
	}
	gnrl->map.map = ft_split(gnrl->map.fst_line, '\v');
	free(gnrl->map.fst_line);
}

void	check_map(t_struct *gnrl, int fd)
{
	char	*tmp;

	gnrl->map.fst_line = ft_strdup(gnrl->map.line);
	tmp = gnrl->map.line;
	gnrl->map.line = ft_strtrim(gnrl->map.line, " ");
	if (*gnrl->map.line == '1')
	{
		if (gnrl->map.check_r == 0 || gnrl->map.check_n == 0
		|| gnrl->map.check_s == 0 || gnrl->map.check_sp == 0
		|| gnrl->map.check_w == 0 || gnrl->map.check_e == 0
		|| gnrl->map.check_f == 0 || gnrl->map.check_c == 0)
			ft_error("Error\nInvalid file!");
		else
		{
			read_map(gnrl, fd);
			valid_map(gnrl);
		}
		gnrl->map.check_m = 1;
		free(tmp);
		close(fd);
	}
	else if (*gnrl->map.line == '0')
		ft_error("Error\nInvalid map, a border needed!!");
	else
		ft_error("Error\nImposter line");
}
