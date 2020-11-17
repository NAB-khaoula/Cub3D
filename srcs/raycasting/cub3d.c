/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:41:33 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/17 10:29:42 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"
#include "../../headers/libft.h"
#include <unistd.h>
#include <stdio.h>


void    draw_sprite(t_struct *gnrl)
{
  int     i;

  i = -1;
  coord_sprite(gnrl);
  gnrl->sprite.spriteorder = (int *)malloc(sizeof(int) * gnrl->map.num_sprites);
  gnrl->sprite.spritedistance = (double *)malloc(sizeof(double) * gnrl->map.num_sprites);
  while (++i < gnrl->map.num_sprites)
  {
    *(gnrl->sprite.spriteorder + i) = i;
    *(gnrl->sprite.spritedistance + i) = ((gnrl->map.pos_x - *(gnrl->sprite.x + i)) * (gnrl->map.pos_x - *(gnrl->sprite.x + i))
    + (gnrl->map.pos_y - *(gnrl->sprite.y + i)) * (gnrl->map.pos_y - *(gnrl->sprite.y + i)));
  }
  sort_sprite(gnrl, gnrl->map.num_sprites);
    i = -1;
    while (++i < gnrl->map.num_sprites)
    {
      gnrl->sprite.spritex = 0.5 + gnrl->sprite.x[gnrl->sprite.spriteorder[i]] - gnrl->map.pos_x;
      gnrl->sprite.spritey = 0.5 + gnrl->sprite.y[gnrl->sprite.spriteorder[i]] - gnrl->map.pos_y;
      gnrl->sprite.invdet = 1.0 / (gnrl->map.plane_x * gnrl->map.dir_y - gnrl->map.dir_x * gnrl->map.plane_y);
      gnrl->sprite.transform_x = gnrl->sprite.invdet * (gnrl->map.dir_y * gnrl->sprite.spritex - gnrl->map.dir_x * gnrl->sprite.spritey);
      gnrl->sprite.transform_y = gnrl->sprite.invdet * (-gnrl->map.plane_y * gnrl->sprite.spritex + gnrl->map.plane_x * gnrl->sprite.spritey);
      gnrl->sprite.spritescreenx = (int)((gnrl->map.resol_w / 2) * (1 + gnrl->sprite.transform_x / gnrl->sprite.transform_y));
      gnrl->sprite.spriteheight = abs((int)(gnrl->map.resol_h / gnrl->sprite.transform_y));
      low_high_pixel(gnrl);                                                                                                                                     
      width_sprite(gnrl);
      draw_vert_stripes(gnrl);
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

void	flour_ceil_var(t_struct *gnrl)
{
	gnrl->flour = (gnrl->map.flour_r << 16) + (gnrl->map.flour_g << 8) + (gnrl->map.flour_b);
	gnrl->ceil = (gnrl->map.ceil_r << 16) + (gnrl->map.ceil_g << 8) + (gnrl->map.ceil_b);
}

void	bmp_filling_flour(int x, t_struct *gnrl)
{
	gnrl->abv = x * gnrl->map.resol_w + gnrl->x;
		gnrl->image[(gnrl->abv) * 3 + 2] = (char)gnrl->map.flour_r;
		gnrl->image[(gnrl->abv) * 3 + 1] = (char)gnrl->map.flour_g;
		gnrl->image[(gnrl->abv) * 3 + 0] = (char)gnrl->map.flour_b;
}

void	bmp_filling_ceil(int x, t_struct *gnrl)
{
	gnrl->abv = (int)(x * gnrl->map.resol_w + gnrl->x);
	gnrl->image[(gnrl->abv) * 3 + 2] = (char)gnrl->map.ceil_r;
	gnrl->image[(gnrl->abv) * 3 + 1] = (char)gnrl->map.ceil_g;
	gnrl->image[(gnrl->abv) * 3 + 0] = (char)gnrl->map.ceil_b;
}

void	bmp(t_struct *gnrl)
{
	int fd;
	int filesize = 54 + 3*gnrl->map.resol_w * gnrl->map.resol_h;
	
	unsigned char *bmpfileheader;
	unsigned char *bmpinfoheader;
	//[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char *bmppad;
	//[3] = {0,0,0};

	bmpfileheader = (unsigned char *)malloc(14);
	bmpinfoheader = (unsigned char *)malloc(40);
	bmppad = (unsigned char *)malloc(3);
	ft_memset(bmpfileheader, 0, 14);
	ft_memset(bmpinfoheader, 0, 40);
	ft_memset(bmppad, 0, 3);
	bmpfileheader[0] = 'B';
	bmpfileheader[1] = 'M';
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize>> 8);
	bmpfileheader[4] = (unsigned char)(filesize>>16);
	bmpfileheader[5] = (unsigned char)(filesize>>24);
	bmpfileheader[10] = 54;

	bmpinfoheader[0] = 40;
	bmpinfoheader[4] = (unsigned char)(gnrl->map.resol_w);
	bmpinfoheader[5] = (unsigned char)(gnrl->map.resol_w >> 8);
	bmpinfoheader[6] = (unsigned char)(gnrl->map.resol_w >> 16);
	bmpinfoheader[7] = (unsigned char)(gnrl->map.resol_w >> 24);
	bmpinfoheader[8] = (unsigned char)(gnrl->map.resol_h);
	bmpinfoheader[9] = (unsigned char)(gnrl->map.resol_h >> 8);
	bmpinfoheader[10] = (unsigned char)(gnrl->map.resol_h >> 16);
	bmpinfoheader[11] = (unsigned char)(gnrl->map.resol_h >> 24);
	bmpinfoheader[12] = 1;
	bmpinfoheader[14] = 24;

	fd = open("img.bmp", O_WRONLY | O_CREAT, 0777);
	write(fd, bmpfileheader,14);
	write(fd, bmpinfoheader,40);
	for(int i=0; i<gnrl->map.resol_h; i++)
	{
		write(fd, gnrl->image+(gnrl->map.resol_w*(gnrl->map.resol_h-i-1)*3),gnrl->map.resol_w * 3);
		write(fd, bmppad,(4-(gnrl->map.resol_w*3)%4)%4);
	}
	gnrl->save = 2;
	close(fd);
}

int	draw_world(t_struct *gnrl)
{
	gnrl->x = 0;
	mlx_clear_window(gnrl->ptr, gnrl->win);
  	handle_keys(gnrl);
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
    	gnrl->sprite.z_buffer[gnrl->x] = gnrl->perpwalldist;
	}
  	draw_sprite(gnrl);
	if(gnrl->save == 1)
		bmp(gnrl);
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
  if(argc > 3)
    ft_putstr_fd("Oups, too many arguments",2);
  else
  {
    int i;
    char *str = ".cub";
	  t_struct	gnrl;
    
    i = -1;
    while(argc >= 2 && ++i < 4)
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
	if(argc == 3 && !ft_strncmp(*(argv + 2), "--save", ft_strlen(*(argv + 2))))
		gnrl.save = 1;
	mlx_hook(gnrl.win,2, 0, press_key, &gnrl);
    mlx_hook(gnrl.win,3, 0, key_release, &gnrl);
    mlx_hook(gnrl.win,17, 0, exit_key, &gnrl);
	mlx_loop_hook(gnrl.ptr, draw_world, &gnrl);
	mlx_loop(gnrl.ptr);
	ft_free(gnrl.map.map);
  }
  return (0);
}

