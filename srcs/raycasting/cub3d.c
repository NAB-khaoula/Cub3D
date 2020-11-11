/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:41:33 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/11 14:10:07 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"
#include "../../headers/libft.h"
#include <unistd.h>
#include <stdio.h>


void    sprite_1(t_sprite *sprite, t_struct *gnrl)
{
  int     i;

  i = -1;
  coord_sprite(sprite, gnrl);
  sprite->spriteorder = (int *)malloc(sizeof(int) * gnrl->map.num_sprites);
  sprite->spritedistance = (double *)malloc(sizeof(double) * gnrl->map.num_sprites);
  while (++i < gnrl->map.num_sprites)
  {
    *(sprite->spriteorder + i) = i;
    *(sprite->spritedistance + i) = ((gnrl->map.pos_x - *(sprite->x + i)) * (gnrl->map.pos_x - *(sprite->x + i))
    + (gnrl->map.pos_y - *(sprite->y + i)) * (gnrl->map.pos_y - *(sprite->y + i)));
  }
  sort_sprite(sprite, gnrl->map.num_sprites);
    i = -1;
    while (++i < gnrl->map.num_sprites)
    {
      sprite->spriteX = 0.5 + sprite->x[sprite->spriteorder[i]] - gnrl->map.pos_x;
      sprite->spriteY = 0.5 + sprite->y[sprite->spriteorder[i]] - gnrl->map.pos_y;
      sprite->invDet = 1.0 / (gnrl->map.plane_x * gnrl->map.dir_y - gnrl->map.dir_x * gnrl->map.plane_y);
      sprite->transformX = sprite->invDet * (gnrl->map.dir_y * sprite->spriteX - gnrl->map.dir_x * sprite->spriteY);
      sprite->transformY = sprite->invDet * (-gnrl->map.plane_y * sprite->spriteX + gnrl->map.plane_x * sprite->spriteY);
      sprite->spriteScreenX = (int)((gnrl->map.resol_w / 2) * (1 + sprite->transformX / sprite->transformY));
      sprite->spriteHeight = abs((int)(gnrl->map.resol_h / sprite->transformY));
      low_high_pixel(sprite, gnrl);                                                                                                                                                
      width_sprite(sprite, gnrl);
      draw_vert_stripes(sprite, gnrl);
    }
}

void  handle_keys(t_struct *gnrl)
{
  if (gnrl->key_up == 1)
		move_forward(gnrl);
	else if (gnrl->key_down == 1)
		move_backward(gnrl);
	else if (gnrl->key_right == 1)
		move_right(gnrl);
	else if (gnrl->key_left == 1)
		move_left(gnrl);
	else if (gnrl->key_r_rot == 1)
		rotate_right(gnrl);
	else if (gnrl->key_l_rot == 1)
		rotate_left(gnrl);
}

int	draw_world(t_struct *gnrl)
{
  t_sprite    sprite;
	gnrl->x = 0;
	mlx_clear_window(gnrl->ptr, gnrl->win);
  handle_keys(gnrl);
	init_image(gnrl, &sprite);
	while(gnrl->x < gnrl->map.resol_w)
	{
		init_var(gnrl);
		init_dist(gnrl);
		hit_the_wall(gnrl);
		projected_distance(gnrl);
		wall_distance(gnrl);
		draw_sky_flour(gnrl);
		init_texture(gnrl);
		texture(gnrl);
		gnrl->x++;
    sprite.z_buffer[gnrl->x] = gnrl->perpWallDist;
	}
  sprite_1(&sprite, gnrl);
	mlx_put_image_to_window(gnrl->ptr, gnrl->win, gnrl->img, 0, 0);
	return (0);
}

int press_key(int key, t_struct *gnrl)
{
	if (key == 53)
		exit(0);
	else if (key == 13)
		gnrl->key_up = 1;
	else if (key == 1)
		gnrl->key_down = 1;
	else if (key == 2)
		gnrl->key_right = 1;
	else if (key == 0)
		gnrl->key_left = 1;
	else if (key == 124)
		gnrl->key_l_rot = 1;
	else if (key == 123)
		gnrl->key_r_rot = 1;
	return (0);
}

int   exit_key()
{
  exit(0);
}

int key_release(int key, t_struct *gnrl)
{
  if (key == 13)
		gnrl->key_up = 0;
	else if (key == 1)
		gnrl->key_down = 0;
	else if (key == 2)
		gnrl->key_right = 0;
	else if (key == 0)
		gnrl->key_left = 0;
	else if (key == 124)
		gnrl->key_l_rot = 0;
	else if (key == 123)
		gnrl->key_r_rot = 0;
	return (0);
}

int main(int argc, char **argv)
{
  if(argc > 2)
    ft_putstr_fd("Oups, too many arguments",2);
  else
  {
    int i;
    char *str = ".cub";
	  t_struct	gnrl;
    
    i = -1;
    while(argc == 2 && ++i < 4)
    {
      if (*(*(argv + 1) + ft_strlen(*(argv + 1)) - i)
        != *(str + ft_strlen(str) - i) )
        ft_error("Error\n .cub extension needed");
    }
    if (*(argv + 1) == NULL)
      *(argv + 1) = "./map.cub";
    parsing(&gnrl, *(argv + 1));
    ft_init_map(&gnrl);
	  ft_init(&gnrl);
	  mlx_hook(gnrl.win,2, 0, press_key, &gnrl);
    mlx_hook(gnrl.win,3, 0, key_release, &gnrl);
    mlx_hook(gnrl.win,17, 0, exit_key, &gnrl);
	  mlx_loop_hook(gnrl.ptr, draw_world, &gnrl);
	  mlx_loop(gnrl.ptr);
  }
  return (0);
}

