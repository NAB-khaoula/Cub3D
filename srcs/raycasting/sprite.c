/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:53:25 by knabouss          #+#    #+#             */
/*   Updated: 2020/11/11 10:09:01 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/raycasting.h"
#include "../../headers/libft.h"

void  sort_sprite(t_sprite  *sprite, int num_sprites)
{
  int     i;
  int     j;
  int     p;
  double  max;

  i = -1;
  while (++i < num_sprites)
  {
    max = sprite->spritedistance[i];
    j = 0;
    while (j < num_sprites)
    {
      if (max <= sprite->spritedistance[j])
      {
        max = sprite->spritedistance[j];
        p = j;
      }
      j++;
    }
    sprite->spritedistance[p] = 0;
    sprite->spriteorder[i] = p;
  }
}

void  coord_sprite(t_sprite *sprite, t_struct *gnrl)
{
  int i;
  int j;
  int k;

  i = -1;
  sprite->x = (int *)malloc(sizeof(int) * gnrl->map.num_sprites);
  sprite->y = (int *)malloc(sizeof(int) * gnrl->map.num_sprites);
  while (++i < gnrl->map.count)
  {
    j = -1;
    while (++j < ft_strlen(*(gnrl->map.map + i)))
    {
      if (gnrl->worldmap[i][j] == 2)
      {
        sprite->x[k] = i;
        sprite->y[k] = j;
        k++;
      }
    }
  }
}

void    low_high_pixel(t_sprite *sprite, t_struct *gnrl)
{
    sprite->drawStartY = -sprite->spriteHeight / 2 + gnrl->map.resol_h / 2;
    if(sprite->drawStartY < 0)
      sprite->drawStartY = 0;
    sprite->drawEndY = sprite->spriteHeight / 2 + gnrl->map.resol_h / 2;
    if(sprite->drawEndY >= gnrl->map.resol_h)
      sprite->drawEndY = gnrl->map.resol_h - 1;
}

void    width_sprite(t_sprite *sprite, t_struct *gnrl)
{
  sprite->spriteWidth = abs( (int) (gnrl->map.resol_h / sprite->transformY));
  sprite->drawStartX = -sprite->spriteWidth / 2 + sprite->spriteScreenX;
  if(sprite->drawStartX < 0)
    sprite->drawStartX = 0;
  sprite->drawEndX = sprite->spriteWidth / 2 + sprite->spriteScreenX;
  if(sprite->drawEndX >= gnrl->map.resol_w)
    sprite->drawEndX = gnrl->map.resol_w - 1;
}

void    draw_vert_stripes(t_sprite  *sprite, t_struct *gnrl)
{
  int     d;
  int     j;
  sprite->stripe = sprite->drawStartX - 1;
      while (++sprite->stripe < sprite->drawEndX)
      {
        gnrl->texX = (int)(256 * (sprite->stripe - (-sprite->spriteWidth / 2 + sprite->spriteScreenX)) * sprite->spr_w / sprite->spriteWidth) / 256;
        if(sprite->transformY > 0 && sprite->stripe > 0 && sprite->stripe < gnrl->map.resol_w && sprite->transformY < sprite->z_buffer[sprite->stripe])
        {
          j = sprite->drawStartY - 1;
        while (++j < sprite->drawEndY)
        {
          d = (j) * 256 - gnrl->map.resol_h * 128 + sprite->spriteHeight * 128;
          gnrl->texPos = ((d * gnrl->texheight) / sprite->spriteHeight) / 256;
          gnrl->color = sprite->spr_texture[sprite->spr_w * (int)gnrl->texPos + gnrl->texX];
          if(gnrl->color != 9961608)
            gnrl->texture[j * gnrl->map.resol_w + sprite->stripe] = gnrl->color;
        }
        }
      }
}
