/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:42:55 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/18 10:30:42 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"

void	init_texture(t_struct *gnrl)
{
	if (gnrl->side == 0)
		gnrl->wallx = gnrl->map.pos_y + gnrl->perpwalldist * gnrl->raydiry;
	else
		gnrl->wallx = gnrl->map.pos_x + gnrl->perpwalldist * gnrl->raydirx;
	gnrl->wallx -= floor((gnrl->wallx));
	gnrl->texx = (int)(gnrl->wallx * (double)gnrl->texwidth);
	if (gnrl->side == 0 && gnrl->raydirx > 0)
		gnrl->texx = gnrl->texwidth - gnrl->texx - 1;
	if (gnrl->side == 1 && gnrl->raydiry < 0)
		gnrl->texx = gnrl->texwidth - gnrl->texx - 1;
	gnrl->step = 1.0 * gnrl->texheight / gnrl->line_height;
	gnrl->texpos = (gnrl->drawstart - gnrl->map.resol_h
	/ 2 + gnrl->line_height / 2) * gnrl->step;
}

void	fill_img_tex(t_struct *gnrl)
{
	gnrl->texture[gnrl->map.resol_w * gnrl->drawstart
	+ gnrl->x] = gnrl->color;
	gnrl->image[(gnrl->map.resol_w * gnrl->drawstart
	+ gnrl->x) * 3 + 2] = gnrl->color >> 16;
	gnrl->image[(gnrl->map.resol_w * gnrl->drawstart
	+ gnrl->x) * 3 + 1] = gnrl->color >> 8;
	gnrl->image[(gnrl->map.resol_w * gnrl->drawstart
	+ gnrl->x) * 3 + 0] = gnrl->color;
}

void	fill_img_sprt(t_struct *gnrl, int j, int d)
{
	d = (j) * 256 - gnrl->map.resol_h * 128
	+ gnrl->sprite.spriteheight * 128;
	gnrl->texpos = ((d * gnrl->texheight)
	/ gnrl->sprite.spriteheight) / 256;
	gnrl->color = gnrl->sprite.spr_texture[gnrl->sprite.spr_w
	* (int)gnrl->texpos + gnrl->texx];
	if (gnrl->color != 9961608)
	{
		gnrl->texture[j * gnrl->map.resol_w
		+ gnrl->sprite.stripe] = gnrl->color;
		gnrl->image[(j * gnrl->map.resol_w + gnrl->sprite.stripe)
		* 3 + 2] = gnrl->color >> 16;
		gnrl->image[(j * gnrl->map.resol_w + gnrl->sprite.stripe)
		* 3 + 1] = gnrl->color >> 8;
		gnrl->image[(j * gnrl->map.resol_w
		+ gnrl->sprite.stripe) * 3 + 0] = gnrl->color;
	}
}

void	texture(t_struct *gnrl)
{
	while (gnrl->drawstart < gnrl->drawend)
	{
		gnrl->texy = (int)gnrl->texpos;
		gnrl->texpos += gnrl->step;
		if (gnrl->side == 0)
		{
			if (gnrl->map_x - gnrl->map.pos_x < 0)
				gnrl->color = gnrl->data[gnrl->texheight
				* gnrl->texy + gnrl->texx];
			else
				gnrl->color = gnrl->data_1[gnrl->texheight
				* gnrl->texy + gnrl->texx];
		}
		else
		{
			if (gnrl->map_y - gnrl->map.pos_y < 0)
				gnrl->color = gnrl->data_2[gnrl->texheight
				* gnrl->texy + gnrl->texx];
			else
				gnrl->color = gnrl->data_3[gnrl->texheight
				* gnrl->texy + gnrl->texx];
		}
		fill_img_tex(gnrl);
		gnrl->drawstart++;
	}
}
