/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_resol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:29:41 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/18 14:52:39 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"
#include "../../headers/libft.h"

void	ft_error(char *s)
{
	ft_putstr_fd(s, 2);
	exit(0);
}

void	check_digit_r(t_struct *gnrl, char *tab)
{
	gnrl->map.check_r = 1;
	while (*tab != 0)
	{
		if (!ft_isdigit(*tab))
			ft_error("Error\n It must be a positive 'number'!");
		tab++;
	}
}

void	error_resolution(t_struct *gnrl)
{
	if (*(gnrl->map.line + 1) != ' ')
		ft_error("Error\n element 'R' is not followed by space.");
	else if (*(gnrl->map.tab + 1) == NULL || *(gnrl->map.tab + 2)
	== NULL)
		ft_error("Error\n Too few information, more efforts please!");
	else if (*(gnrl->map.tab + 2) != NULL && *(gnrl->map.tab + 3)
	!= NULL)
		ft_error("Error\n Too many information, make your mind first!");
	else if (gnrl->map.check_r == 1)
		ft_error("Error\n duplicated line, focus mate!");
}

void	check_resolution(t_struct *gnrl)
{
	gnrl->map.tab = ft_split(gnrl->map.line, ' ');
	if (**gnrl->map.tab == 'R' && *(*gnrl->map.tab + 1) == '\0')
	{
		if (*(gnrl->map.tab + 1) != NULL && *(gnrl->map.tab + 2) != NULL
		&& *(gnrl->map.tab + 3) == NULL && gnrl->map.check_r == 0)
		{
			check_digit_r(gnrl, *(gnrl->map.tab + 1));
			check_digit_r(gnrl, *(gnrl->map.tab + 2));
			gnrl->map.resol_w = ft_atoi(*(gnrl->map.tab + 1));
			gnrl->map.resol_h = ft_atoi(*(gnrl->map.tab + 2));
			if (gnrl->map.resol_h == 0 || gnrl->map.resol_w == 0)
				ft_error("Error\nResolution must be a struct positive number!");
			if (gnrl->map.resol_h >= 1620 || gnrl->map.resol_w >= 2880
			|| gnrl->map.resol_h < 0 || gnrl->map.resol_w < 0)
			{
				gnrl->map.resol_h = 1620;
				gnrl->map.resol_w = 2880;
			}
			ft_free(gnrl->map.tab);
		}
		else
			free_r_error(gnrl->map.tab, gnrl);
	}
	else
		free_r_error(gnrl->map.tab, gnrl);
}

void	continue_check_vspace(t_struct *gnrl, int *i, int *j)
{
	if (*(*(gnrl->map.map_rvs + *i) + (*j - 1)) != '1')
		free_error(gnrl->map.map_rvs, "Error\nInvalid map!");
	else
	{
		while (*(*(gnrl->map.map_rvs + *i) + *j) == ' ')
			(*j)++;
		if (*(*(gnrl->map.map_rvs + *i) + *j) != '1'
		&& *(*(gnrl->map.map_rvs + *i) + *j))
			free_error(gnrl->map.map_rvs, "Error\nInvalid map!");
	}
}
