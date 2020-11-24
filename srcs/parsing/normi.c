/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:47:33 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/24 13:08:13 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include "../../headers/raycasting.h"

void	check_flour_norm(t_struct *gnrl, char *tmp)
{
	int i;

	i = -1;
	tmp = gnrl->map.line;
	gnrl->map.line = ft_strtrim(gnrl->map.line + 1, " ");
	free(tmp);
	while (*(gnrl->map.line + ++i))
		if ((*(gnrl->map.line + i) == ','
		&& *(gnrl->map.line + i + 1) == ',')
		|| (*(gnrl->map.line + i) == ','
		&& *(gnrl->map.line + i + 1) == '\0')
		|| *gnrl->map.line == ',')
			ft_error("Error\nargument must follow this format R,G,B!");
	if (!(gnrl->map.tab = ft_split(gnrl->map.line, ',')))
		free(gnrl->map.tab);
	if (*gnrl->map.tab && *(gnrl->map.tab + 1) && *(gnrl->map.tab + 2)
	&& !(*(gnrl->map.tab + 3)) && gnrl->map.check_f == 0)
		check_flour_bis(gnrl);
	else
		error_flour(gnrl);
}

void	check_ceil_norm(t_struct *gnrl, char *tmp)
{
	int i;

	i = -1;
	tmp = gnrl->map.line;
	gnrl->map.line = ft_strtrim(gnrl->map.line + 1, " ");
	free(tmp);
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
		error_ceil(gnrl);
}
