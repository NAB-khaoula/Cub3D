/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:53:25 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/17 10:20:19 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"
#include "../../headers/libft.h"

void  sort_sprite(t_struct *gnrl, int num_sprites)
{
  int     i;
  int     j;
  int     p;
  double  max;

  i = -1;
  while (++i < num_sprites)
  {
    max = gnrl->sprite.spritedistance[i];
    j = 0;
    while (j < num_sprites)
    {
      if (max <= gnrl->sprite.spritedistance[j])
      {
        max = gnrl->sprite.spritedistance[j];
        p = j;
      }
      j++;
    }
    gnrl->sprite.spritedistance[p] = 0;
    gnrl->sprite.spriteorder[i] = p;
  }
}

void  coord_sprite(t_struct *gnrl)
{
  int i;
  int j;
  int k;

  i = -1;
  k = 0;
  gnrl->sprite.x = (int *)malloc(sizeof(int) * gnrl->map.num_sprites);
  gnrl->sprite.y = (int *)malloc(sizeof(int) * gnrl->map.num_sprites);
  while (++i < gnrl->map.count)
  {
    j = -1;
    while (++j < (int)ft_strlen(*(gnrl->map.map + i)))
    {
      if (gnrl->worldmap[i][j] == 2)
      {
        gnrl->sprite.x[k] = i;
        gnrl->sprite.y[k] = j;
        k++;
      }
    }
  }
}

void    low_high_pixel(t_struct *gnrl)
{
    gnrl->sprite.drawstarty = -gnrl->sprite.spriteheight / 2 + gnrl->map.resol_h / 2;
    if(gnrl->sprite.drawstarty < 0)
      gnrl->sprite.drawstarty = 0;
    gnrl->sprite.drawendy = gnrl->sprite.spriteheight / 2 + gnrl->map.resol_h / 2;
    if(gnrl->sprite.drawendy >= gnrl->map.resol_h)
      gnrl->sprite.drawendy = gnrl->map.resol_h - 1;
}

void    width_sprite(t_struct *gnrl)
{
  gnrl->sprite.spritewidth = abs( (int) (gnrl->map.resol_h / gnrl->sprite.transform_y));
  gnrl->sprite.drawstartx = -gnrl->sprite.spritewidth / 2 + gnrl->sprite.spritescreenx;
  if(gnrl->sprite.drawstartx < 0)
    gnrl->sprite.drawstartx = 0;
  gnrl->sprite.drawendx = gnrl->sprite.spritewidth / 2 + gnrl->sprite.spritescreenx;
  if(gnrl->sprite.drawendx >= gnrl->map.resol_w)
    gnrl->sprite.drawendx = gnrl->map.resol_w - 1;
}

void    draw_vert_stripes(t_struct *gnrl)
{
  int     d;
  int     j;
  gnrl->sprite.stripe = gnrl->sprite.drawstartx - 1;
      while (++gnrl->sprite.stripe < gnrl->sprite.drawendx)
      {
        gnrl->texx = (int)(256 * (gnrl->sprite.stripe - (-gnrl->sprite.spritewidth / 2 + gnrl->sprite.spritescreenx)) * gnrl->sprite.spr_w / gnrl->sprite.spritewidth) / 256;
        if(gnrl->sprite.transform_y > 0 && gnrl->sprite.stripe > 0 && gnrl->sprite.stripe < gnrl->map.resol_w && gnrl->sprite.transform_y < gnrl->sprite.z_buffer[gnrl->sprite.stripe])
        {
          j = gnrl->sprite.drawstarty - 1;
        while (++j < gnrl->sprite.drawendy)
        {
          d = (j) * 256 - gnrl->map.resol_h * 128 + gnrl->sprite.spriteheight * 128;
          gnrl->texpos = ((d * gnrl->texheight) / gnrl->sprite.spriteheight) / 256;
          gnrl->color = gnrl->sprite.spr_texture[gnrl->sprite.spr_w * (int)gnrl->texpos + gnrl->texx];
          if(gnrl->color != 9961608)
          {
            gnrl->texture[j * gnrl->map.resol_w + gnrl->sprite.stripe] = gnrl->color;
            gnrl->image[(j * gnrl->map.resol_w + gnrl->sprite.stripe) * 3 + 2] = gnrl->color >> 16;
            gnrl->image[(j * gnrl->map.resol_w + gnrl->sprite.stripe) * 3 + 1] = gnrl->color >> 8;
            gnrl->image[(j * gnrl->map.resol_w + gnrl->sprite.stripe) * 3 + 0] = gnrl->color;
          }
        }
        }
      }
}
