/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flour.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:36:21 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/09 11:55:24 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"

void    check_file(t_struct    *gnrl)
{
    if (open(gnrl->map.path, O_RDONLY) == -1 && *gnrl->map.path == '.')
        ft_error("Error\n FILE NOT EXISTING!");
}

void	check_digit_f(char	*tab)
{
    while(*tab == ' ')
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
    if (*(*gnrl->map.tab + ft_strlen(*gnrl->map.tab) - 1) == ',' || !(*(gnrl->map.tab + 2)) || !(*(gnrl->map.tab + 1)))
        ft_error("Error\n the argument must follow this format R,G,B!");
    else if (gnrl->map.check_f == 1)
	    ft_error("Error\n duplicated line, focus mate!");
}

void    check_flour_bis(t_struct   *gnrl)
{
    check_digit_f(*gnrl->map.tab);
    check_digit_f(*(gnrl->map.tab + 1));
    check_digit_f(*(gnrl->map.tab + 2));
    gnrl->map.flour_r = ft_atoi(*gnrl->map.tab);
    gnrl->map.flour_g = ft_atoi(*(gnrl->map.tab + 1));
    gnrl->map.flour_b = ft_atoi(*(gnrl->map.tab + 2));
    if (gnrl->map.flour_r > 255 || gnrl->map.flour_r < 0 || gnrl->map.flour_g > 255
    || gnrl->map.flour_g < 0 || gnrl->map.flour_b > 255 || gnrl->map.flour_b < 0)
	    ft_error("Error\n color R,G,B range is [0,255]");
    gnrl->map.check_f = 1;
}

void    check_flour(t_struct   *gnrl)
{
    int i;

    i = -1;
    if (*(gnrl->map.line + 1) == ' ')
    {
        gnrl->map.line = ft_strtrim(gnrl->map.line + 1 , " ");
        while(*(gnrl->map.line + ++i))
            if((*(gnrl->map.line + i) == ',' &&  *(gnrl->map.line + i + 1) == ',') 
            || (*(gnrl->map.line + i) == ',' &&  *(gnrl->map.line + i + 1) == '\0') || *gnrl->map.line == ',')
                ft_error("Error\nargument must follow this format R,G,B!");
        gnrl->map.tab = ft_split(gnrl->map.line, ',');
        if (*gnrl->map.tab && *(gnrl->map.tab + 1) && *(gnrl->map.tab + 2) && !(*(gnrl->map.tab + 3)) && gnrl->map.check_f == 0)
            check_flour_bis(gnrl);
        else
            error_flour(gnrl);
    }
    else
        ft_error("Error\n! element 'F' is not followed by space.");
}
