/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flour.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:36:21 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/24 11:50:38 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"

void	check_file(t_struct *gnrl)
{
	if (open(gnrl->map.path, O_RDONLY) == -1)
		ft_error("Error\n FILE NOT EXISTING!");
}

void	check_digit_f(char *tab)
{
	while (*tab == ' ')
		tab++;
	while (*tab != 0)
	{
		if (!ft_isdigit(*tab) && *tab != ' ')
			ft_error("Error\n It must be a number and POSITIVE!");
		else if (*tab == ' ')
			ft_error("Error\n Too many arguments!");
		tab++;
	}
}

void	error_flour(t_struct *gnrl)
{
	if (*(gnrl->map.line + 1) != ' ')
		write(2, "Error\n element 'F' is incorrect.", 33);
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

void	check_flour_bis(t_struct *gnrl)
{
	check_digit_f(*gnrl->map.tab);
	check_digit_f(*(gnrl->map.tab + 1));
	check_digit_f(*(gnrl->map.tab + 2));
	gnrl->map.flour_r = ft_atoi(*gnrl->map.tab);
	gnrl->map.flour_g = ft_atoi(*(gnrl->map.tab + 1));
	gnrl->map.flour_b = ft_atoi(*(gnrl->map.tab + 2));
	if (gnrl->map.flour_r > 255 || gnrl->map.flour_r < 0
	|| gnrl->map.flour_g > 255 || gnrl->map.flour_g < 0
	|| gnrl->map.flour_b > 255 || gnrl->map.flour_b < 0)
		error_flour(gnrl);
	gnrl->map.check_f = 1;
	ft_free(gnrl->map.tab);
}

void	check_flour(t_struct *gnrl)
{
	char	*tmp;

	tmp = NULL;
	if (*(gnrl->map.line + 1) == ' ')
		check_flour_norm(gnrl, tmp);
	else
		ft_error("Error\n! element 'F' is not followed by space.");
	free(gnrl->map.line);
}
