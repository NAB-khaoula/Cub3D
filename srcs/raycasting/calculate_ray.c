/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:41:22 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/10 10:58:53 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../headers/raycasting.h"

void	 hit_the_wall(t_struct *gnrl)
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

void	projected_distance(t_struct	*gnrl)
{
	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	if (gnrl->side == 0)
		gnrl->perpWallDist = (gnrl->map_x - gnrl->map.pos_x + (1 - gnrl->step_x) / 2) / gnrl->raydirX;
	else
		gnrl->perpWallDist = (gnrl->map_y - gnrl->map.pos_y + (1 - gnrl->step_y) / 2) / gnrl->raydirY;
}

void	wall_distance(t_struct *gnrl)
{
	//Calculate height of line to draw on screen
	gnrl->line_height = (int)gnrl->map.resol_h / gnrl->perpWallDist;
	//calculate lowest and highest pixel to fill in current stripe
	gnrl->drawStart = -gnrl->line_height / 2 + gnrl->map.resol_h / 2;
	if(gnrl->drawStart < 0)
		gnrl->drawStart = 0;
	gnrl->drawEnd = gnrl->line_height / 2 + gnrl->map.resol_h / 2;
	if(gnrl->drawEnd >= gnrl->map.resol_h)
		gnrl->drawEnd = gnrl->map.resol_h - 1;
}

void    draw_sky_flour(t_struct *gnrl)
{
	int x = 0;
	while(x < gnrl->map.resol_h)
	{
		if (x < gnrl->drawStart)
			gnrl->data_sky[x * gnrl->map.resol_w + gnrl->x] = 10092543;
		else if (x >= gnrl->drawEnd)
			gnrl->data_sky[x * gnrl->map.resol_w + gnrl->x] = 8737555;
		x++;
	}
}
