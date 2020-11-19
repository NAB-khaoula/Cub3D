/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:42:31 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/18 10:54:37 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"

void	rotate_right(t_struct *gnrl)
{
	gnrl->olddirx = gnrl->map.dir_x;
	gnrl->map.dir_x = gnrl->map.dir_x * cos(gnrl->rotspeed)
	- gnrl->map.dir_y * sin(gnrl->rotspeed);
	gnrl->map.dir_y = gnrl->olddirx * sin(gnrl->rotspeed)
	+ gnrl->map.dir_y * cos(gnrl->rotspeed);
	gnrl->oldplanex = gnrl->map.plane_x;
	gnrl->map.plane_x = gnrl->map.plane_x * cos(gnrl->rotspeed)
	- gnrl->map.plane_y * sin(gnrl->rotspeed);
	gnrl->map.plane_y = gnrl->oldplanex * sin(gnrl->rotspeed)
	+ gnrl->map.plane_y * cos(gnrl->rotspeed);
}

void	move_forward(t_struct *gnrl)
{
	if (gnrl->worldmap[(int)(gnrl->map.pos_x + gnrl->map.dir_x
	* gnrl->movespeed)][(int)gnrl->map.pos_y] == 0)
		gnrl->map.pos_x += gnrl->map.dir_x * gnrl->movespeed;
	if (gnrl->worldmap[(int)gnrl->map.pos_x][(int)(gnrl->map.pos_y
	+ gnrl->map.dir_y * gnrl->movespeed)] == 0)
		gnrl->map.pos_y += gnrl->map.dir_y * gnrl->movespeed;
}

void	move_backward(t_struct *gnrl)
{
	if (gnrl->worldmap[(int)(gnrl->map.pos_x - gnrl->map.dir_x
	* gnrl->movespeed)][(int)gnrl->map.pos_y] == 0)
		gnrl->map.pos_x -= gnrl->map.dir_x * gnrl->movespeed;
	if (gnrl->worldmap[(int)gnrl->map.pos_x][(int)(gnrl->map.pos_y
	- gnrl->map.dir_y * gnrl->movespeed)] == 0)
		gnrl->map.pos_y -= gnrl->map.dir_y * gnrl->movespeed;
}

void	move_right(t_struct *gnrl)
{
	if (gnrl->worldmap[(int)(gnrl->map.pos_x + gnrl->map.plane_x
	* gnrl->movespeed)][(int)gnrl->map.pos_y] == 0)
		gnrl->map.pos_x += gnrl->map.plane_x * gnrl->movespeed;
	if (gnrl->worldmap[(int)gnrl->map.pos_x][(int)(gnrl->map.pos_y
	+ gnrl->map.plane_y * gnrl->movespeed)] == 0)
		gnrl->map.pos_y += gnrl->map.plane_y * gnrl->movespeed;
}

void	move_left(t_struct *gnrl)
{
	if (gnrl->worldmap[(int)(gnrl->map.pos_x + gnrl->map.plane_x
	* gnrl->movespeed)][(int)gnrl->map.pos_y] == 0)
		gnrl->map.pos_x -= gnrl->map.plane_x * gnrl->movespeed;
	if (gnrl->worldmap[(int)gnrl->map.pos_x][(int)(gnrl->map.pos_y
	+ gnrl->map.plane_y * gnrl->movespeed)] == 0)
		gnrl->map.pos_y -= gnrl->map.plane_y * gnrl->movespeed;
}
