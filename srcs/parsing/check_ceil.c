/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ceil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:39:51 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/18 14:20:35 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"

void	error_ceil(t_struct *gnrl)
{
	if (*(gnrl->map.line + 1) != ' ')
		write(2, "Error\n element 'C' is not followed by space.", 45);
	else if (*(*gnrl->map.tab + ft_strlen(*gnrl->map.tab) - 1) == ','
	|| !(*(gnrl->map.tab + 2)) || !(*(gnrl->map.tab + 1)))
		write(2, "Error\n the argument must follow this format R,G,B!", 68);
	else if (gnrl->map.ceil_r > 255 || gnrl->map.ceil_r < 0
	|| gnrl->map.ceil_g > 255 || gnrl->map.ceil_g < 0
	|| gnrl->map.ceil_b > 255 || gnrl->map.ceil_b < 0)
		write(2, "Error\n color R,G,B range is [0,255]", 36);
	else if (gnrl->map.check_c == 1)
		write(2, "Error\n duplicated line, focus mate!", 36);
	ft_free(gnrl->map.tab);
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
	int i;

	i = -1;
	if (*(gnrl->map.line + 1) == ' ')
	{
		gnrl->map.line = ft_strtrim(gnrl->map.line + 1, " ");
		while (*(gnrl->map.line + ++i))
			if ((*(gnrl->map.line + i) == ','
			&& *(gnrl->map.line + i + 1) == ',')
			|| (*(gnrl->map.line + i) == ','
			&& *(gnrl->map.line + i + 1) == '\0')
			|| *gnrl->map.line == ',')
				ft_error("Error\nargument must follow this format R,G,B!");
		gnrl->map.tab = ft_split(gnrl->map.line, ',');
		if (*gnrl->map.tab && *(gnrl->map.tab + 1) && *(gnrl->map.tab + 2)
		&& !(*(gnrl->map.tab + 3)) && gnrl->map.check_c == 0)
			check_ceil_bis(gnrl);
		else
		{
			ft_free(gnrl->map.tab);
			error_ceil(gnrl);
		}
	}
	else
		error_ceil(gnrl);
}

void	continue_check_space(t_struct *gnrl, int *i, int *j)
{
	if (*(*(gnrl->map.map + *i) + *j) == ' ')
	{
		if (*(*(gnrl->map.map + *i) + (*j - 1)) != '1')
			free_error(gnrl->map.map, "Error\nInvalid map!");
		else
		{
			while (*j < (int)ft_strlen(*(gnrl->map.map + *i) + *j)
			&& *(*(gnrl->map.map + *i) + *j) == ' ')
				j++;
			if (*(*(gnrl->map.map + *i) + *j) != ' '
			&& *(*(gnrl->map.map + *i) + *j) != '1'
			&& !(*(*(gnrl->map.map + *i) + *j)))
				free_error(gnrl->map.map, "Error\nInvalid map!");
		}
	}
	else if (*(*(gnrl->map.map + *i) + *j) == '2')
		gnrl->map.num_sprites++;
	else if (*(*(gnrl->map.map + *i) + *j) == 'N'
	|| *(*(gnrl->map.map + *i) + *j) == 'S'
	|| *(*(gnrl->map.map + *i) + *j) == 'W'
	|| *(*(gnrl->map.map + *i) + *j) == 'E')
		position(gnrl, i, j);
	else
		free_error(gnrl->map.map, "Error\nInvalid map!");
}
