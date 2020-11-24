/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:01:52 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/24 09:57:36 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"

void	ft_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	str = NULL;
}

void	free_error(char **str, char *err)
{
	ft_free(str);
	ft_error(err);
}

void	free_r_error(char **str, t_struct *gnrl)
{
	ft_free(str);
	error_resolution(gnrl);
}

void	free_line(char *str, char *err)
{
	free(str);
	ft_error(err);
}

void	continue_position(t_struct *gnrl, int *i, int *j)
{
	if (*(*(gnrl->map.map + *i) + *j) == 'W')
	{
		gnrl->map.dir_x = 0;
		gnrl->map.dir_y = -1;
		gnrl->map.plane_x = -0.66;
		gnrl->map.plane_y = 0;
	}
	else if (*(*(gnrl->map.map + *i) + *j) == 'E')
	{
		gnrl->map.dir_x = 0;
		gnrl->map.dir_y = 1;
		gnrl->map.plane_x = 0.66;
		gnrl->map.plane_y = 0;
	}
}
