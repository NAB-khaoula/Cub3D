/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:42:24 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/17 10:11:31 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"
#include "../../headers/libft.h"

void	ft_init_map(t_struct *gnrl)
{
	int	i;
	int j;

	i = -1;
	gnrl->worldmap = (int **)malloc(sizeof(int *) * (gnrl->map.count));
	while (++i < gnrl->map.count)
	{
		*(gnrl->worldmap + i) = (int *)malloc(sizeof(int) * (gnrl->map.max_len));
		j = -1;
		while (++j < gnrl->map.max_len)
			*(*(gnrl->worldmap + i) + j) = 1;
	}
	i = -1;
	while (++i < gnrl->map.count)
	{
		j = -1;
		while (++j < (int)ft_strlen(*(gnrl->map.map + i)))
		{
			if (*(*(gnrl->map.map + i) + j) == '0' || *(*(gnrl->map.map + i) + j) == 'N'
			|| *(*(gnrl->map.map + i) + j) == 'S' || *(*(gnrl->map.map + i) + j) == 'W'
			|| *(*(gnrl->map.map + i) + j) == 'E')
				*(*(gnrl->worldmap + i) + j) = 0;
			else if (*(*(gnrl->map.map + i) + j) == '2')
				*(*(gnrl->worldmap + i) + j) = 2;
		}
	}
}

void	ft_init(t_struct *gnrl)
{
	gnrl->ptr = mlx_init();
	gnrl->win = mlx_new_window(gnrl->ptr, gnrl->map.resol_w, gnrl->map.resol_h, "Cub3D");
	gnrl->img = mlx_new_image(gnrl->ptr, gnrl->map.resol_w, gnrl->map.resol_h);
	gnrl->xpm_file_img = mlx_xpm_file_to_image(gnrl->ptr, gnrl->map.north, &gnrl->tw, &gnrl->th);
	gnrl->xpm_file_img_1 = mlx_xpm_file_to_image(gnrl->ptr, gnrl->map.south, &gnrl->tw, &gnrl->th);
	gnrl->xpm_file_img_2 = mlx_xpm_file_to_image(gnrl->ptr, gnrl->map.west, &gnrl->tw, &gnrl->th);
	gnrl->xpm_file_img_3 = mlx_xpm_file_to_image(gnrl->ptr, gnrl->map.east, &gnrl->tw, &gnrl->th);
	gnrl->sprite.spr_img = mlx_xpm_file_to_image(gnrl->ptr, gnrl->map.sprite, &gnrl->sprite.spr_w, &gnrl->sprite.spr_h);
	gnrl->texture = (int *)mlx_get_data_addr(gnrl->img, &gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->data_sky = (int *)mlx_get_data_addr(gnrl->img, &gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->data = (int *)mlx_get_data_addr(gnrl->xpm_file_img, &gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->data_1 = (int *)mlx_get_data_addr(gnrl->xpm_file_img_1, &gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->data_2 = (int *)mlx_get_data_addr(gnrl->xpm_file_img_2, &gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->data_3 = (int *)mlx_get_data_addr(gnrl->xpm_file_img_3, &gnrl->bits_per_pixel, &gnrl->size_line, &gnrl->endian);
	gnrl->sprite.spr_texture = (int *)mlx_get_data_addr(gnrl->sprite.spr_img, &gnrl->sprite.spr_bbp, &gnrl->sprite.spr_s_l, &gnrl->sprite.spr_end);
	gnrl->texwidth = gnrl->tw;
	gnrl->texheight = gnrl->th;
	gnrl->save = 0;
	flour_ceil_var(gnrl);
	gnrl->image = (char *)malloc(gnrl->map.resol_h * gnrl->map.resol_w * 3);
}

void    init_var(t_struct *gnrl)
{
	gnrl->camerax = 2 * gnrl->x / (double)gnrl->map.resol_w - 1;
	gnrl->raydirx = gnrl->map.dir_x + gnrl->map.plane_x * gnrl->camerax;
	gnrl->raydiry = gnrl->map.dir_y + gnrl->map.plane_y * gnrl->camerax;
	gnrl->map_x = (int)gnrl->map.pos_x;
	gnrl->map_y = (int)gnrl->map.pos_y;
	gnrl->delta_dist_x = fabs(1 / gnrl->raydirx);
	gnrl->delta_dist_y = fabs(1 / gnrl->raydiry);
	gnrl->hit = 0;
}

void	init_dist(t_struct *gnrl)
{
	if (gnrl->raydirx < 0)
  	{
   		gnrl->step_x = -1;
		gnrl->side_dist_x = (gnrl->map.pos_x - gnrl->map_x) * gnrl->delta_dist_x;
  	}
  	else
  	{
		gnrl->step_x = 1;
		gnrl->side_dist_x = (gnrl->map_x + 1.0 - gnrl->map.pos_x) * gnrl->delta_dist_x;
  	}
  	if (gnrl->raydiry < 0)
  	{
		gnrl->step_y = -1;
		gnrl->side_dist_y = (gnrl->map.pos_y - gnrl->map_y) * gnrl->delta_dist_y;
  	}
  	else
  	{
		gnrl->step_y = 1;
		gnrl->side_dist_y = (gnrl->map_y + 1.0 - gnrl->map.pos_y) * gnrl->delta_dist_y;
  	}
}
