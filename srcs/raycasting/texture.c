/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:42:55 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/12 14:35:18 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"

void    init_texture(t_struct *gnrl)
{
	if (gnrl->side == 0)
		gnrl->wallx = gnrl->map.pos_y + gnrl->perpwalldist * gnrl->raydiry;
	else
		gnrl->wallx = gnrl->map.pos_x + gnrl->perpwalldist * gnrl->raydirx;
	gnrl->wallx -= floor ((gnrl->wallx));
	//x coordinate on the texture
    gnrl->texx = (int)(gnrl->wallx * (double)gnrl->texwidth);
    if(gnrl->side == 0 && gnrl->raydirx > 0)
		gnrl->texx = gnrl->texwidth - gnrl->texx - 1;
	if(gnrl->side == 1 && gnrl->raydiry < 0)
		gnrl->texx = gnrl->texwidth - gnrl->texx - 1;
	// How much to increase the texture coordinate per screen pixel
    gnrl->step = 1.0 * gnrl->texheight / gnrl->line_height;
	// Starting texture coordinate
	gnrl->texpos = (gnrl->drawstart - gnrl->map.resol_h / 2 + gnrl->line_height / 2) * gnrl->step;
}

void    texture(t_struct *gnrl)
{
    while(gnrl->drawstart < gnrl->drawend)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)gnrl->texpos;
        gnrl->texpos += gnrl->step;
		if (gnrl->side == 0)
		{
			if(gnrl->map_x - gnrl->map.pos_x < 0)
        		gnrl->color = gnrl->data[gnrl->texheight * texY + gnrl->texx];
			else
				gnrl->color = gnrl->data_1[gnrl->texheight * texY + gnrl->texx];
		}
		else
		{
			if(gnrl->map_y - gnrl->map.pos_y < 0)
        		gnrl->color = gnrl->data_2[gnrl->texheight * texY + gnrl->texx];
			else
				gnrl->color = gnrl->data_3[gnrl->texheight * texY + gnrl->texx];
		}
		gnrl->texture[gnrl->map.resol_w * gnrl->drawstart + gnrl->x] = gnrl->color;
		gnrl->drawstart++;
      }
}

