/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:34:00 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/18 12:20:03 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"

void	init_bis(t_struct *gnrl)
{
	gnrl->sprite.spr_img = mlx_xpm_file_to_image(gnrl->ptr,
	gnrl->map.sprite, &gnrl->sprite.spr_w, &gnrl->sprite.spr_h);
	gnrl->texture = (int *)mlx_get_data_addr(gnrl->img,
	&gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->data_sky = (int *)mlx_get_data_addr(gnrl->img,
	&gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->data = (int *)mlx_get_data_addr(gnrl->xpm_file_img,
	&gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->data_1 = (int *)mlx_get_data_addr(gnrl->xpm_file_img_1,
	&gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->data_2 = (int *)mlx_get_data_addr(gnrl->xpm_file_img_2,
	&gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->data_3 = (int *)mlx_get_data_addr(gnrl->xpm_file_img_3,
	&gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->sprite.spr_texture = (int *)mlx_get_data_addr(gnrl->sprite.spr_img,
	&gnrl->sprite.spr_bbp, &gnrl->sprite.spr_s_l, &gnrl->sprite.spr_end);
	gnrl->texwidth = gnrl->tw;
	gnrl->texheight = gnrl->th;
	gnrl->save = 0;
	flour_ceil_var(gnrl);
	gnrl->image = (char *)malloc(gnrl->map.resol_h * gnrl->map.resol_w * 3);
}

void	draw_sprite_bis(t_struct *gnrl, int i)
{
	gnrl->sprite.spritex = 0.5 + gnrl->sprite.x[gnrl->sprite.spriteorder[i]]
	- gnrl->map.pos_x;
	gnrl->sprite.spritey = 0.5 + gnrl->sprite.y[gnrl->sprite.spriteorder[i]]
	- gnrl->map.pos_y;
	gnrl->sprite.invdet = 1.0 / (gnrl->map.plane_x * gnrl->map.dir_y
	- gnrl->map.dir_x * gnrl->map.plane_y);
	gnrl->sprite.transform_x = gnrl->sprite.invdet * (gnrl->map.dir_y
	* gnrl->sprite.spritex - gnrl->map.dir_x * gnrl->sprite.spritey);
	gnrl->sprite.transform_y = gnrl->sprite.invdet * (-gnrl->map.plane_y
	* gnrl->sprite.spritex + gnrl->map.plane_x * gnrl->sprite.spritey);
	gnrl->sprite.spritescreenx = (int)((gnrl->map.resol_w / 2) *
	(1 + gnrl->sprite.transform_x / gnrl->sprite.transform_y));
	gnrl->sprite.spriteheight = abs((int)(gnrl->map.resol_h /
	gnrl->sprite.transform_y));
	low_high_pixel(gnrl);
	width_sprite(gnrl);
	draw_vert_stripes(gnrl);
}

void	fd_wrt(int fd, t_struct *gnrl, int i, unsigned char *bmppad)
{
	write(fd, gnrl->image + (gnrl->map.resol_w *
	(gnrl->map.resol_h - i - 1) * 3), gnrl->map.resol_w * 3);
	write(fd, bmppad, (4 - (gnrl->map.resol_w * 3) % 4) % 4);
}
