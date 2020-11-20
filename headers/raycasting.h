/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:18:29 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/20 12:10:26 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef	struct	s_sprite
{
	int			*x;
	int			*y;
	double		z_buffer[3000];
	int			spr_w;
	int			spr_h;
	int			spr_s_l;
	int			spr_end;
	int			spr_bbp;
	int			*spr_texture;
	void		*spr_img;
	int			*spriteorder;
	double		*spritedistance;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transform_x;
	double		transform_y;
	int			spritescreenx;
	int			spriteheight;
	int			drawstarty;
	int			drawendy;
	int			spritewidth;
	int			drawstartx;
	int			drawendx;
	int			stripe;
}				t_sprite;

typedef struct	s_map
{
	char		*line;
	char		**tab;
	long long	resol_w;
	long long	resol_h;
	int			check_r;
	int			check_n;
	int			check_s;
	int			check_w;
	int			check_e;
	int			check_sp;
	int			check_f;
	int			check_c;
	int			check_m;
	int			check_pos;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*path;
	char		*sprite;
	long long	flour_r;
	long long	flour_g;
	long long	flour_b;
	long long	ceil_r;
	long long	ceil_g;
	long long	ceil_b;
	char		*fst_line;
	char		**map;
	char		**map_rvs;
	int			count;
	int			max_len;
	int			num_sprites;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_map;

typedef	struct	s_struct
{
	float		movespeed;
	float		rotspeed;
	int			**worldmap;
	void		*xpm_file_img;
	void		*xpm_file_img_1;
	void		*xpm_file_img_2;
	void		*xpm_file_img_3;
	int			texwidth;
	int			texheight;
	void		*ptr;
	void		*win;
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			x;
	int			map_x;
	int			map_y;
	double		side_dist_y;
	double		side_dist_x;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perpwalldist;
	int			line_height;
	int			drawstart;
	int			drawend;
	int			color;
	double		olddirx;
	double		oldplanex;
	void		*img;
	int			*data;
	int			*data_1;
	int			*data_2;
	int			*data_3;
	int			*data_sky;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			texnum;
	double		wallx;
	int			texx;
	int			th;
	int			tw;
	int			*texture;
	double		step;
	int			texy;
	double		texpos;
	int			key;
	int			key_up;
	int			key_down;
	int			key_l_rot;
	int			key_r_rot;
	int			key_left;
	int			key_right;
	long int	flour;
	long int	ceil;
	int			save;
	char		*image;
	int			abv;
	int			filesize;
	t_map		map;
	t_sprite	sprite;
}				t_struct;

void			ft_init(t_struct *gnrl);
int				press_key(int key, t_struct *gnrl);
void			draw_sky(t_struct *gnrl);
void			draw_flour(t_struct *gnrl);
int				draw_world(t_struct *gnrl);
void			rotate_left(t_struct *gnrl);
void			rotate_right(t_struct *gnrl);
void			move_forward(t_struct *gnrl);
void			move_backward(t_struct *gnrl);
void			move_right(t_struct *gnrl);
void			move_left(t_struct *gnrl);
void			handle_keys(t_struct *gnrl);
void			init_var(t_struct *gnrl);
void			init_dist(t_struct *gnrl);
void			hit_the_wall(t_struct *gnrl);
void			projected_distance(t_struct	*gnrl);
void			wall_distance(t_struct *gnrl);
void			draw_sky_flour(t_struct *gnrl);
void			init_texture(t_struct *gnrl);
void			texture(t_struct *gnrl);
void			sort_sprite(t_struct *gnrl, int num_sprites);
void			check_resolution(t_struct	*gnrl);
void			check_digit_r(t_struct	*gnrl, char	*tab);
void			ft_error(char *s);
void			error_resolution(t_struct *gnrl);
void			check_flour(t_struct	*gnrl);
void			check_digit_f(char	*tab);
void			error_flour(t_struct	*gnrl);
void			error_ceil(t_struct	*gnrl);
void			check_ceil(t_struct	*gnrl);
void			check_file(t_struct	*gnrl);
void			check_north(t_struct	*gnrl);
void			check_south_sprite(t_struct	*gnrl);
void			check_west(t_struct	*gnrl);
void			check_east(t_struct	*gnrl);
void			init_checker(t_struct	*gnrl);
void			check_map(t_struct	*gnrl, int	fd);
void			valid_map(t_struct	*gnrl);
void			check_borders(t_struct	*gnrl);
void			check_borders_v(t_struct	*gnrl);
void			position(t_struct	*gnrl, int	*i, int	*j);
void			check_space(t_struct	*gnrl);
void			check_space_v(t_struct	*gnrl);
void			reverse_map(t_struct	*gnrl);
void			check_path(t_struct	*gnrl);
void			check_ceil_bis(t_struct	*gnrl);
void			read_map(t_struct	*gnrl, int	fd);
void			parsing(t_struct	*gnrl, char *argv);
void			check_flour_bis(t_struct	*gnrl);
void			sort_sprite(t_struct	*gnrl, int num_sprites);
void			coord_sprite(t_struct *gnrl);
void			low_high_pixel(t_struct *gnrl);
void			width_sprite(t_struct *gnrl);
void			draw_vert_stripes(t_struct *gnrl);
void			draw_sprite(t_struct *gnrl);
void			ft_init_map(t_struct *gnrl);
void			flour_ceil_var(t_struct *gnrl);
void			ft_free(char **str);
void			bmp(t_struct *gnrl);
void			bmp_filling_ceil(int x, t_struct *gnrl);
void			bmp_filling_flour(int x, t_struct *gnrl);
void			free_error(char **str, char *err);
void			free_line(char *str, char *err);
void			parsing_check(t_struct	*gnrl, int fd);
void			free_r_error(char **str, t_struct *gnrl);
void			continue_position(t_struct *gnrl, int *i, int *j);
void			continue_vspace(t_struct *gnrl, int *i, int *j);
void			continue_space(t_struct *gnrl, int *i, int *j);
void			fill_img_tex(t_struct *gnrl);
void			fill_img_sprt(t_struct *gnrl, int j, int d);
void			init_map_bis(t_struct *gnrl, int i, int j);
void			init_bis(t_struct *gnrl);
void			draw_sprite_bis(t_struct *gnrl, int i);
int				exit_key(void);
int				key_release(int key, t_struct *gnrl);
void			func_mlx(int argc, char **argv, t_struct *gnrl);
unsigned char	*fill_fileheader(t_struct *gnrl, unsigned char	*bmpfileheader);
unsigned char	*fill_infoheader(t_struct *gnrl, unsigned char	*bmpinfoheader);
void			fd_wrt(int fd, t_struct *gnrl, int i, unsigned char *bmppad);
void			pos_sprt(t_struct *gnrl, int *i, int *j);
#endif
