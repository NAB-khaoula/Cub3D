/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ceil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:39:51 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/24 12:03:16 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"

void	error_ceil(t_struct *gnrl)
{
	if (*(gnrl->map.line + 1) != ' ')
		write(2, "Error\n element 'C' is incorrect.", 33);
	else
	{
		if (*(*gnrl->map.tab + ft_strlen(*gnrl->map.tab) - 1) == ','
		|| !(*(gnrl->map.tab + 2)) || !(*(gnrl->map.tab + 1)))
			write(2, "Error\n the argument must follow this format R,G,B!", 68);
		else if (gnrl->map.ceil_r > 255 || gnrl->map.ceil_r < 0
		|| gnrl->map.ceil_g > 255 || gnrl->map.ceil_g < 0
		|| gnrl->map.ceil_b > 255 || gnrl->map.ceil_b < 0)
			write(2, "Error\n color R,G,B range is [0,255]", 36);
		else if (gnrl->map.check_c == 1)
			write(2, "Error\n duplicated line, focus mate!", 36);
		ft_free(gnrl->map.tab);
	}
	exit(0);
}

void	check_ceil_bis(t_struct *gnrl)
{
	check_digit_f(*gnrl->map.tab);
	check_digit_f(*(gnrl->map.tab + 1));
	check_digit_f(*(gnrl->map.tab + 2));
	gnrl->map.ceil_r = ft_atoi(*gnrl->map.tab);
	gnrl->map.ceil_g = ft_atoi(*(gnrl->map.tab + 1));
	gnrl->map.ceil_b = ft_atoi(*(gnrl->map.tab + 2));
	if (gnrl->map.ceil_r > 255 || gnrl->map.ceil_r < 0
	|| gnrl->map.ceil_g > 255 || gnrl->map.ceil_g < 0
	|| gnrl->map.ceil_b > 255 || gnrl->map.ceil_b < 0)
		error_ceil(gnrl);
	gnrl->map.check_c = 1;
	ft_free(gnrl->map.tab);
}

void	check_ceil(t_struct *gnrl)
{
	char	*tmp;

	tmp = NULL;
	if (*(gnrl->map.line + 1) == ' ')
		check_ceil_norm(gnrl, tmp);
	else
		ft_error("Error\n! element 'F' is not followed by space.");
	free(gnrl->map.line);
}

void	continue_vspace(t_struct *gnrl, int *i, int *j)
{
	while (gnrl->map.map_rvs[(*i)][(*j)] == ' ')
		(*j)++;
	if (gnrl->map.map_rvs[(*i)][(*j)] != '1'
	&& gnrl->map.map_rvs[(*i)][(*j)])
		free_error(gnrl->map.map_rvs, "Error\nInvalid map!");
	while (++(*j) < gnrl->map.count)
	{
		if (gnrl->map.map_rvs[(*i)][(*j)] == 0
		|| gnrl->map.map_rvs[(*i)][(*j)] == 1)
			continue;
		else if (gnrl->map.map_rvs[(*i)][(*j)] == ' ')
		{
			if (gnrl->map.map_rvs[(*i)][(*j) - 1] != '1')
				free_error(gnrl->map.map_rvs, "Error\nInvalid map!");
			else
			{
				while (gnrl->map.map_rvs[(*i)][(*j)] == ' ')
					(*j)++;
				if (gnrl->map.map_rvs[(*i)][(*j)] != '1'
				&& gnrl->map.map_rvs[(*i)][(*j)])
					free_error(gnrl->map.map_rvs, "Error\nInvalid map!");
			}
		}
	}
}

void	continue_space(t_struct *gnrl, int *i, int *j)
{
	while (++(*j) < (int)ft_strlen(*(gnrl->map.map + *i)))
	{
		if (*(*(gnrl->map.map + (*i)) + (*j)) == '0'
		|| *(*(gnrl->map.map + (*i)) + (*j)) == '1')
			continue;
		else if (*(*(gnrl->map.map + (*i)) + (*j)) == ' ')
		{
			if (*(*(gnrl->map.map + (*i)) + ((*j) - 1)) != '1')
				free_error(gnrl->map.map, "Error\nInvalid map!");
			else
			{
				while ((*j) < (int)ft_strlen(*(gnrl->map.map + (*i)))
				&& *(*(gnrl->map.map + (*i)) + (*j)) == ' ')
					(*j)++;
				if (*(*(gnrl->map.map + (*i)) + (*j)) != ' '
				&& *(*(gnrl->map.map + (*i)) + (*j)) != '1'
				&& (*(*(gnrl->map.map + (*i)) + (*j))))
					free_error(gnrl->map.map, "Error\nInvalid map!");
			}
		}
		else
			pos_sprt(gnrl, i, j);
	}
}
