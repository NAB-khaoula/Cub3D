/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:41:22 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/18 10:55:18 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"

void	hit_the_wall(t_struct *gnrl)
{
	while (gnrl->hit == 0)
	{
		if (gnrl->side_dist_x < gnrl->side_dist_y)
		{
			gnrl->side_dist_x += gnrl->delta_dist_x;
			gnrl->map_x += gnrl->step_x;
			gnrl->side = 0;
		}
		else
		{
			gnrl->side_dist_y += gnrl->delta_dist_y;
			gnrl->map_y += gnrl->step_y;
			gnrl->side = 1;
		}
		if (gnrl->worldmap[gnrl->map_x][gnrl->map_y] == 1)
			gnrl->hit = 1;
	}
}

void	projected_distance(t_struct *gnrl)
{
	if (gnrl->side == 0)
		gnrl->perpwalldist = (gnrl->map_x - gnrl->map.pos_x
		+ (1 - gnrl->step_x) / 2) / gnrl->raydirx;
	else
		gnrl->perpwalldist = (gnrl->map_y - gnrl->map.pos_y
		+ (1 - gnrl->step_y) / 2) / gnrl->raydiry;
}

void	wall_distance(t_struct *gnrl)
{
	gnrl->line_height = (int)gnrl->map.resol_h / gnrl->perpwalldist;
	gnrl->drawstart = -gnrl->line_height / 2 + gnrl->map.resol_h / 2;
	if (gnrl->drawstart < 0)
		gnrl->drawstart = 0;
	gnrl->drawend = gnrl->line_height / 2 + gnrl->map.resol_h / 2;
	if (gnrl->drawend >= gnrl->map.resol_h)
		gnrl->drawend = gnrl->map.resol_h - 1;
}

void	draw_sky_flour(t_struct *gnrl)
{
	int x;

	x = 0;
	while (x < gnrl->map.resol_h)
	{
		if (x < gnrl->drawstart)
		{
			gnrl->data_sky[x * gnrl->map.resol_w + gnrl->x] = gnrl->ceil;
			bmp_filling_ceil(x, gnrl);
		}
		else if (x >= gnrl->drawend)
		{
			gnrl->data_sky[x * gnrl->map.resol_w + gnrl->x] = gnrl->flour;
			bmp_filling_flour(x, gnrl);
		}
		x++;
	}
}

void	rotate_left(t_struct *gnrl)
{
	gnrl->olddirx = gnrl->map.dir_x;
	gnrl->map.dir_x = gnrl->map.dir_x * cos(-gnrl->rotspeed)
	- gnrl->map.dir_y * sin(-gnrl->rotspeed);
	gnrl->map.dir_y = gnrl->olddirx * sin(-gnrl->rotspeed)
	+ gnrl->map.dir_y * cos(-gnrl->rotspeed);
	gnrl->oldplanex = gnrl->map.plane_x;
	gnrl->map.plane_x = gnrl->map.plane_x * cos(-gnrl->rotspeed)
	- gnrl->map.plane_y * sin(-gnrl->rotspeed);
	gnrl->map.plane_y = gnrl->oldplanex * sin(-gnrl->rotspeed)
	+ gnrl->map.plane_y * cos(-gnrl->rotspeed);
}
