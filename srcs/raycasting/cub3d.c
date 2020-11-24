/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:41:33 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/24 18:48:15 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"
#include "../../headers/libft.h"

void	draw_sprite(t_struct *gnrl)
{
	int	i;

	i = -1;
	coord_sprite(gnrl);
	gnrl->sprite.spriteorder = (int *)malloc(sizeof(int)
	* gnrl->map.num_sprites);
	gnrl->sprite.spritedistance = (double *)malloc(sizeof(double)
	* gnrl->map.num_sprites);
	while (++i < gnrl->map.num_sprites)
	{
		*(gnrl->sprite.spriteorder + i) = i;
		*(gnrl->sprite.spritedistance + i) = ((gnrl->map.pos_x -
		*(gnrl->sprite.x + i)) * (gnrl->map.pos_x - *(gnrl->sprite.x + i))
		+ (gnrl->map.pos_y - *(gnrl->sprite.y + i))
		* (gnrl->map.pos_y - *(gnrl->sprite.y + i)));
	}
	sort_sprite(gnrl, gnrl->map.num_sprites);
	i = -1;
	while (++i < gnrl->map.num_sprites)
		draw_sprite_bis(gnrl, i);
	free(gnrl->sprite.x);
	free(gnrl->sprite.y);
	free(gnrl->sprite.spriteorder);
	free(gnrl->sprite.spritedistance);
}

void	flour_ceil_var(t_struct *gnrl)
{
	gnrl->flour = (gnrl->map.flour_r << 16) +
	(gnrl->map.flour_g << 8) + (gnrl->map.flour_b);
	gnrl->ceil = (gnrl->map.ceil_r << 16) +
	(gnrl->map.ceil_g << 8) + (gnrl->map.ceil_b);
}

int		draw_world(t_struct *gnrl)
{
	gnrl->x = 0;
	mlx_clear_window(gnrl->ptr, gnrl->win);
	handle_keys(gnrl);
	while (gnrl->x < gnrl->map.resol_w)
	{
		init_var(gnrl);
		init_dist(gnrl);
		hit_the_wall(gnrl);
		projected_distance(gnrl);
		wall_distance(gnrl);
		draw_sky_flour(gnrl);
		init_texture(gnrl);
		texture(gnrl);
		gnrl->sprite.z_buffer[gnrl->x] = gnrl->perpwalldist;
		gnrl->x++;
	}
	draw_sprite(gnrl);
	if (gnrl->save == 1)
		bmp(gnrl);
	mlx_put_image_to_window(gnrl->ptr, gnrl->win, gnrl->img, 0, 0);
	return (0);
}

void	func_mlx(int argc, char **argv, t_struct *gnrl)
{
	parsing(gnrl, *(argv + 1));
	ft_init_map(gnrl);
	ft_init(gnrl);
	if (argc == 3 && !ft_strncmp(*(argv + 2),
	"--save", ft_strlen(*(argv + 2))))
		gnrl->save = 1;
	mlx_hook(gnrl->win, 2, 0, press_key, gnrl);
	mlx_hook(gnrl->win, 3, 0, key_release, gnrl);
	mlx_hook(gnrl->win, 17, 0, exit_key, gnrl);
	mlx_loop_hook(gnrl->ptr, draw_world, gnrl);
	mlx_loop(gnrl->ptr);
	ft_free(gnrl->map.map);
}

int		main(int argc, char **argv)
{
	int			i;
	char		*str;
	t_struct	gnrl;

	if (argc > 3)
		ft_error("Oups, too many arguments");
	else
	{
		str = ".cub";
		i = -1;
		while (argc >= 2 && ++i < 4)
			if (*(*(argv + 1) + ft_strlen(*(argv + 1)) - i)
			!= *(str + ft_strlen(str) - i))
				ft_error("Error\n .cub extension needed");
		func_mlx(argc, argv, &gnrl);
	}
	return (0);
}
