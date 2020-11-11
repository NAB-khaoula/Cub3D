/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 10:42:31 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/11 12:29:17 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../headers/raycasting.h"

void rotate_left(t_struct *gnrl)
{
		gnrl->oldDirX = gnrl->map.dir_x;
    	gnrl->map.dir_x = gnrl->map.dir_x * cos(-rotSpeed) - gnrl->map.dir_y * sin(-rotSpeed);
    	gnrl->map.dir_y = gnrl->oldDirX * sin(-rotSpeed) + gnrl->map.dir_y * cos(-rotSpeed);
    	gnrl->oldPlaneX = gnrl->map.plane_x; 
    	gnrl->map.plane_x = gnrl->map.plane_x * cos(-rotSpeed) - gnrl->map.plane_y * sin(-rotSpeed);
    	gnrl->map.plane_y = gnrl->oldPlaneX * sin(-rotSpeed) + gnrl->map.plane_y * cos(-rotSpeed);
}

void rotate_right(t_struct *gnrl)
{
	gnrl->oldDirX = gnrl->map.dir_x;
    gnrl->map.dir_x = gnrl->map.dir_x * cos(rotSpeed) - gnrl->map.dir_y * sin(rotSpeed);
    gnrl->map.dir_y = gnrl->oldDirX * sin(rotSpeed) + gnrl->map.dir_y * cos(rotSpeed);
    gnrl->oldPlaneX = gnrl->map.plane_x;
    gnrl->map.plane_x = gnrl->map.plane_x * cos(rotSpeed) - gnrl->map.plane_y * sin(rotSpeed);
    gnrl->map.plane_y = gnrl->oldPlaneX * sin(rotSpeed) + gnrl->map.plane_y * cos(rotSpeed);
}

void	move_forward(t_struct *gnrl)
{
		if(gnrl->worldmap[(int)(gnrl->map.pos_x + gnrl->map.dir_x * moveSpeed)][(int)gnrl->map.pos_y] == 0) 
			gnrl->map.pos_x += gnrl->map.dir_x * moveSpeed;
		if(gnrl->worldmap[(int)gnrl->map.pos_x][(int)(gnrl->map.pos_y + gnrl->map.dir_y * moveSpeed)] == 0) 
			gnrl->map.pos_y += gnrl->map.dir_y * moveSpeed;
}

void	move_backward(t_struct *gnrl)
{
	if(gnrl->worldmap[(int)(gnrl->map.pos_x - gnrl->map.dir_x * moveSpeed)][(int)gnrl->map.pos_y] == 0) 
		gnrl->map.pos_x -= gnrl->map.dir_x * moveSpeed;
	if(gnrl->worldmap[(int)gnrl->map.pos_x][(int)(gnrl->map.pos_y - gnrl->map.dir_y * moveSpeed)] == 0)
		gnrl->map.pos_y -= gnrl->map.dir_y * moveSpeed;
}
void	move_right(t_struct *gnrl)
{
	if(gnrl->worldmap[(int)(gnrl->map.pos_x + gnrl->map.plane_x * moveSpeed)][(int)gnrl->map.pos_y] == 0) 
		gnrl->map.pos_x += gnrl->map.plane_x * moveSpeed;
	if(gnrl->worldmap[(int)gnrl->map.pos_x][(int)(gnrl->map.pos_y + gnrl->map.plane_y * moveSpeed)] == 0) 
		gnrl->map.pos_y += gnrl->map.plane_y * moveSpeed;
}

void	move_left(t_struct *gnrl)
{
	if(gnrl->worldmap[(int)(gnrl->map.pos_x + gnrl->map.plane_x * moveSpeed)][(int)gnrl->map.pos_y] == 0) 
		gnrl->map.pos_x -= gnrl->map.plane_x * moveSpeed;
	if(gnrl->worldmap[(int)gnrl->map.pos_x][(int)(gnrl->map.pos_y + gnrl->map.plane_y * moveSpeed)] == 0) 
		gnrl->map.pos_y -= gnrl->map.plane_y * moveSpeed;
}
