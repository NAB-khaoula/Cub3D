/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:42:24 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/24 13:35:28 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"
#include "../../headers/libft.h"

void	init_map_bis(t_struct *gnrl, int i, int j)
{
	if (*(*(gnrl->map.map + i) + j) == '0' || *(*(gnrl->map.map + i) + j) == 'N'
	|| *(*(gnrl->map.map + i) + j) == 'S' || *(*(gnrl->map.map + i) + j) == 'W'
	|| *(*(gnrl->map.map + i) + j) == 'E')
		*(*(gnrl->worldmap + i) + j) = 0;
	else if (*(*(gnrl->map.map + i) + j) == '2')
		*(*(gnrl->worldmap + i) + j) = 2;
}

void	ft_init_map(t_struct *gnrl)
{
	int	i;
	int j;

	i = -1;
	gnrl->worldmap = (int **)malloc(sizeof(int *) * (gnrl->map.count));
	while (++i < gnrl->map.count)
	{
		*(gnrl->worldmap + i) = (int *)malloc(sizeof(int)
		* (gnrl->map.max_len));
		j = -1;
		while (++j < gnrl->map.max_len)
			*(*(gnrl->worldmap + i) + j) = 1;
	}
	i = -1;
	while (++i < gnrl->map.count)
	{
		j = -1;
		while (++j < (int)ft_strlen(*(gnrl->map.map + i)))
			init_map_bis(gnrl, i, j);
	}
}

void	ft_init(t_struct *gnrl)
{
	gnrl->filesize = 54 + 3 * gnrl->map.resol_w * gnrl->map.resol_h;
	gnrl->movespeed = 0.1;
	gnrl->rotspeed = 0.1;
	gnrl->ptr = mlx_init();
	gnrl->win = mlx_new_window(gnrl->ptr,
	gnrl->map.resol_w, gnrl->map.resol_h, "Cub3D");
	gnrl->img = mlx_new_image(gnrl->ptr,
	gnrl->map.resol_w, gnrl->map.resol_h);
	gnrl->xpm_file_img = mlx_xpm_file_to_image(gnrl->ptr,
	gnrl->map.north, &gnrl->tw, &gnrl->th);
	gnrl->xpm_file_img_1 = mlx_xpm_file_to_image(gnrl->ptr,
	gnrl->map.south, &gnrl->tw, &gnrl->th);
	gnrl->xpm_file_img_2 = mlx_xpm_file_to_image(gnrl->ptr,
	gnrl->map.west, &gnrl->tw, &gnrl->th);
	gnrl->xpm_file_img_3 = mlx_xpm_file_to_image(gnrl->ptr,
	gnrl->map.east, &gnrl->tw, &gnrl->th);
	free(gnrl->map.north);
	free(gnrl->map.south);
	free(gnrl->map.west);
	free(gnrl->map.east);
	init_bis(gnrl);
}

void	init_var(t_struct *gnrl)
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
		gnrl->side_dist_x = (gnrl->map.pos_x
		- gnrl->map_x) * gnrl->delta_dist_x;
	}
	else
	{
		gnrl->step_x = 1;
		gnrl->side_dist_x = (gnrl->map_x + 1.0
		- gnrl->map.pos_x) * gnrl->delta_dist_x;
	}
	if (gnrl->raydiry < 0)
	{
		gnrl->step_y = -1;
		gnrl->side_dist_y = (gnrl->map.pos_y
		- gnrl->map_y) * gnrl->delta_dist_y;
	}
	else
	{
		gnrl->step_y = 1;
		gnrl->side_dist_y = (gnrl->map_y + 1.0
		- gnrl->map.pos_y) * gnrl->delta_dist_y;
	}
}
