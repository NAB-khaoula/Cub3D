/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:49:49 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/24 14:11:15 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"

void	position(t_struct *gnrl, int *i, int *j)
{
	if (gnrl->map.check_pos == 0)
	{
		gnrl->map.pos_x = (double)*i + 0.6;
		gnrl->map.pos_y = (double)*j + 0.6;
		if (*(*(gnrl->map.map + *i) + *j) == 'N')
		{
			gnrl->map.dir_x = -1;
			gnrl->map.dir_y = 0;
			gnrl->map.plane_x = 0;
			gnrl->map.plane_y = 0.66;
		}
		else if (*(*(gnrl->map.map + *i) + *j) == 'S')
		{
			gnrl->map.dir_x = 1;
			gnrl->map.dir_y = 0;
			gnrl->map.plane_x = 0;
			gnrl->map.plane_y = -0.66;
		}
		else
			continue_position(gnrl, i, j);
		gnrl->map.check_pos = 1;
	}
	else
		ft_error("Error\nDuplicated position");
}

void	check_space(t_struct *gnrl)
{
	int i;
	int j;

	i = 0;
	gnrl->map.num_sprites = 0;
	while (++i < gnrl->map.count - 1)
	{
		j = 0;
		while (*(*(gnrl->map.map + i) + j) == ' ')
			j++;
		if (*(*(gnrl->map.map + i) + j) != '1')
			free_error(gnrl->map.map, "Error\nInvalid map!");
		continue_space(gnrl, &i, &j);
	}
}

void	check_space_v(t_struct *gnrl)
{
	int i;
	int j;

	i = 0;
	while (++i < gnrl->map.max_len - 1)
	{
		j = 0;
		continue_vspace(gnrl, &i, &j);
	}
	ft_free(gnrl->map.map_rvs);
}

void	reverse_map(t_struct *gnrl)
{
	int i;
	int j;

	i = -1;
	gnrl->map.map_rvs = (char **)malloc(sizeof(char *) *
	(gnrl->map.max_len));
	while (++i < gnrl->map.max_len)
	{
		j = -1;
		*(gnrl->map.map_rvs + i) = (char *)malloc(sizeof(char) *
		(gnrl->map.count));
		while (++j < gnrl->map.count)
			*(*(gnrl->map.map_rvs + i) + j) = ' ';
		*(*(gnrl->map.map_rvs + i) + j) = '\0';
	}
	*(gnrl->map.map_rvs + i) = NULL;
	i = -1;
	while (++i < gnrl->map.max_len)
	{
		j = -1;
		while (++j < gnrl->map.count)
			if ((int)ft_strlen(*(gnrl->map.map + j)) > i)
				*(*(gnrl->map.map_rvs + i) + j) = *(*(gnrl->map.map + j) + i);
	}
}

void	pos_sprt(t_struct *gnrl, int *i, int *j)
{
	if (*(*(gnrl->map.map + (*i)) + (*j)) == '2')
		gnrl->map.num_sprites++;
	else if (*(*(gnrl->map.map + (*i)) + (*j)) == 'N'
	|| *(*(gnrl->map.map + (*i)) + (*j)) == 'S'
	|| *(*(gnrl->map.map + (*i)) + (*j)) == 'W'
	|| *(*(gnrl->map.map + (*i)) + (*j)) == 'E')
		position(gnrl, i, j);
	else
		free_error(gnrl->map.map, "Error\nInvalid map!");
}
