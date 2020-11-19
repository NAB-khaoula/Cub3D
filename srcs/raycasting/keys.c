/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:56:54 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/18 11:57:43 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"
#include "../../headers/libft.h"

void	handle_keys(t_struct *gnrl)
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

int		press_key(int key, t_struct *gnrl)
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

int		exit_key(void)
{
	exit(0);
}

int		key_release(int key, t_struct *gnrl)
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
