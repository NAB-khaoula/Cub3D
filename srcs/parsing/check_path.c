/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:41:53 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/13 14:32:12 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"

void    check_east(t_struct    *gnrl)
{
    if (*gnrl->map.line == 'E' && *(gnrl->map.line + 1) == 'A' && *(gnrl->map.line + 2) == ' ' && gnrl->map.check_e == 0)
    {
        gnrl->map.check_e = 1;
        gnrl->map.east = (char *)malloc(sizeof(char) * ft_strlen(gnrl->map.path));
		gnrl->map.east = ft_strdup(gnrl->map.path);
    }
    else if (gnrl->map.check_e == 1)
        ft_error("Error\nCheck duplicated lines, focus mate!");
    else if (*gnrl->map.line == 'E' && (*(gnrl->map.line + 1) != 'A' || *(gnrl->map.line + 2) != ' '))
        ft_error("Error\n Texture format invalid");
}


void    check_west(t_struct    *gnrl)
{
    if (*gnrl->map.line == 'W' && *(gnrl->map.line + 1) == 'E' && *(gnrl->map.line + 2) == ' ' && gnrl->map.check_w == 0)
    {
        gnrl->map.check_w = 1;
		gnrl->map.west = ft_strdup(gnrl->map.path);
    }
    else if (gnrl->map.check_w == 1)
        ft_error("Error\nCheck duplicated lines, focus mate!");
    else if (*gnrl->map.line == 'W' && (*(gnrl->map.line + 1) != 'E' || *(gnrl->map.line + 2) != ' '))
        ft_error("Error\n Texture format invalid");
}

void    check_south_sprite(t_struct   *gnrl)
{
    if (*gnrl->map.line == 'S' && *(gnrl->map.line + 1) == 'O' && *(gnrl->map.line + 2) == ' ' && gnrl->map.check_s == 0)
    {
        gnrl->map.check_s = 1;
		gnrl->map.south = ft_strdup(gnrl->map.path);
    }
    else if (*gnrl->map.line == 'S' && *(gnrl->map.line + 1) == ' ' && gnrl->map.check_sp == 0)
    {
        gnrl->map.check_sp = 1;
	    gnrl->map.sprite = ft_strdup(gnrl->map.path);
    }
    else if (gnrl->map.check_s == 1 || gnrl->map.check_sp == 1)
        ft_error("Error\nCheck duplicated lines, focus mate!");
    else if (*gnrl->map.line == 'S' && (*(gnrl->map.line + 1) != 'O' || *(gnrl->map.line + 2) != ' '))
        ft_error("Error\n Texture format invalid");
}

void    check_north(t_struct   *gnrl)
{
    if (*gnrl->map.line == 'N' && *(gnrl->map.line + 1) == 'O' && *(gnrl->map.line + 2) == ' ' && gnrl->map.check_n == 0)
    {
        gnrl->map.check_n = 1;
		gnrl->map.north = ft_strdup(gnrl->map.path);
    }
    else if (gnrl->map.check_n == 1)
        ft_error("Error\nCheck duplicated lines, focus mate!");
    else if (*gnrl->map.line == 'N' && (*(gnrl->map.line + 1) != 'O' || *(gnrl->map.line + 2) != ' '))
        ft_error("Error\n Texture format invalid");
}

void    check_path(t_struct    *gnrl)
{
    gnrl->map.path = ft_strtrim(gnrl->map.line + 2 , " ");
    check_file(gnrl);
    if (*gnrl->map.line == 'N')
        check_north(gnrl);
    else if (*gnrl->map.line == 'S')
        check_south_sprite(gnrl);
    else if (*gnrl->map.line == 'W')
        check_west(gnrl);
    else if (*gnrl->map.line == 'E')
        check_east(gnrl);
    free(gnrl->map.path);
}
