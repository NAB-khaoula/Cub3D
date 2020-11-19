/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:55:07 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/18 12:25:08 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"
#include "../../headers/libft.h"

void			bmp_filling_flour(int x, t_struct *gnrl)
{
	gnrl->abv = x * gnrl->map.resol_w + gnrl->x;
	gnrl->image[(gnrl->abv) * 3 + 2] = (char)gnrl->map.flour_r;
	gnrl->image[(gnrl->abv) * 3 + 1] = (char)gnrl->map.flour_g;
	gnrl->image[(gnrl->abv) * 3 + 0] = (char)gnrl->map.flour_b;
}

void			bmp_filling_ceil(int x, t_struct *gnrl)
{
	gnrl->abv = (int)(x * gnrl->map.resol_w + gnrl->x);
	gnrl->image[(gnrl->abv) * 3 + 2] = (char)gnrl->map.ceil_r;
	gnrl->image[(gnrl->abv) * 3 + 1] = (char)gnrl->map.ceil_g;
	gnrl->image[(gnrl->abv) * 3 + 0] = (char)gnrl->map.ceil_b;
}

unsigned char	*fill_fileheader(t_struct *gnrl, unsigned char *bmpfileheader)
{
	bmpfileheader[0] = 'B';
	bmpfileheader[1] = 'M';
	bmpfileheader[2] = (unsigned char)(gnrl->filesize);
	bmpfileheader[3] = (unsigned char)(gnrl->filesize >> 8);
	bmpfileheader[4] = (unsigned char)(gnrl->filesize >> 16);
	bmpfileheader[5] = (unsigned char)(gnrl->filesize >> 24);
	bmpfileheader[10] = 54;
	return (bmpfileheader);
}

unsigned char	*fill_infoheader(t_struct *gnrl, unsigned char *bmpinfoheader)
{
	bmpinfoheader[0] = 40;
	bmpinfoheader[4] = (unsigned char)(gnrl->map.resol_w);
	bmpinfoheader[5] = (unsigned char)(gnrl->map.resol_w >> 8);
	bmpinfoheader[6] = (unsigned char)(gnrl->map.resol_w >> 16);
	bmpinfoheader[7] = (unsigned char)(gnrl->map.resol_w >> 24);
	bmpinfoheader[8] = (unsigned char)(gnrl->map.resol_h);
	bmpinfoheader[9] = (unsigned char)(gnrl->map.resol_h >> 8);
	bmpinfoheader[10] = (unsigned char)(gnrl->map.resol_h >> 16);
	bmpinfoheader[11] = (unsigned char)(gnrl->map.resol_h >> 24);
	bmpinfoheader[12] = 1;
	bmpinfoheader[14] = 24;
	return (bmpinfoheader);
}

void			bmp(t_struct *gnrl)
{
	int				fd;
	int				i;
	unsigned char	*bmpfileheader;
	unsigned char	*bmpinfoheader;
	unsigned char	*bmppad;

	i = -1;
	gnrl->filesize = 54 + 3 * gnrl->map.resol_w * gnrl->map.resol_h;
	bmpfileheader = (unsigned char *)malloc(14);
	bmpinfoheader = (unsigned char *)malloc(40);
	bmppad = (unsigned char *)malloc(3);
	ft_memset(bmpfileheader, 0, 14);
	ft_memset(bmpinfoheader, 0, 40);
	ft_memset(bmppad, 0, 3);
	bmpfileheader = fill_fileheader(gnrl, bmpfileheader);
	bmpinfoheader = fill_infoheader(gnrl, bmpinfoheader);
	fd = open("save.bmp", O_WRONLY | O_CREAT, 0777);
	write(fd, bmpfileheader, 14);
	write(fd, bmpinfoheader, 40);
	while (++i < gnrl->map.resol_h)
		fd_wrt(fd, gnrl, i, bmppad);
	gnrl->save = 2;
	close(fd);
	exit(0);
}
