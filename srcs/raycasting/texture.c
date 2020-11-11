/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:42:55 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/09 12:50:53 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"

void    init_texture(t_struct *gnrl)
{
	if (gnrl->side == 0)
		gnrl->wallX = gnrl->map.pos_y + gnrl->perpWallDist * gnrl->raydirY;
	else
		gnrl->wallX = gnrl->map.pos_x + gnrl->perpWallDist * gnrl->raydirX;
	gnrl->wallX -= floor ((gnrl->wallX));
	//x coordinate on the texture
    gnrl->texX = (int)(gnrl->wallX * (double)gnrl->texwidth);
    if(gnrl->side == 0 && gnrl->raydirX > 0)
		gnrl->texX = gnrl->texwidth - gnrl->texX - 1;
	if(gnrl->side == 1 && gnrl->raydirY < 0)
		gnrl->texX = gnrl->texwidth - gnrl->texX - 1;
	// How much to increase the texture coordinate per screen pixel
    gnrl->step = 1.0 * gnrl->texheight / gnrl->line_height;
	// Starting texture coordinate
	gnrl->texPos = (gnrl->drawStart - gnrl->map.resol_h / 2 + gnrl->line_height / 2) * gnrl->step;
}

void    texture(t_struct *gnrl)
{
    while(gnrl->drawStart < gnrl->drawEnd)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)gnrl->texPos;
        gnrl->texPos += gnrl->step;
		if (gnrl->side == 0)
		{
			if(gnrl->map_x - gnrl->map.pos_x < 0)
        		gnrl->color = gnrl->data[gnrl->texheight * texY + gnrl->texX];
			else
				gnrl->color = gnrl->data_1[gnrl->texheight * texY + gnrl->texX];
		}
		else
		{
			if(gnrl->map_y - gnrl->map.pos_y < 0)
        		gnrl->color = gnrl->data_2[gnrl->texheight * texY + gnrl->texX];
			else
				gnrl->color = gnrl->data_3[gnrl->texheight * texY + gnrl->texX];
		}
		gnrl->texture[gnrl->map.resol_w * gnrl->drawStart + gnrl->x] = gnrl->color;
		gnrl->drawStart++;
      }
}

