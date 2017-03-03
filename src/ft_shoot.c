/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shoot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:19:31 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/03 18:18:25 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		draw_gun(t_e *e, t_gif g, t_pi shift, int zoom)
{
	int		i;
	int		j;
	int		color;

	shift = point_in(shift.x - (g.w * zoom) / 2, shift.y - g.h * zoom);
	i = shift.y - 1;
	while (++i < g.h * zoom + shift.y)
	{
		j = shift.x - 1;
		while (++j < g.w * zoom + shift.x)
		{
			color = ft_img_px_get_gif(g.img,
					point_in((j - shift.x) / zoom, (i - shift.y) / zoom), g);
			if (color != 0)
				ft_img_px_put(e, j, i, color);
		}
	}
}

void		put_gun(t_e *e)
{
	if (e->bob_param.x == 1 && e->bob_param.y == 1)
		e->bob += 30 * e->pl.ms;
	else if (e->bob_param.x == 1 && e->bob_param.y == -1)
		e->bob -= 30 * e->pl.ms;
	else if (e->bob_param.x == 0)
		e->bob = 0;
	if (e->bob < -30 && e->bob_param.y == -1)
		e->bob_param.y = 1;
	else if (e->bob > -5 - 10 * e->pl.ms && e->bob_param.y == 1)
		e->bob_param.y = -1;
	if (e->is_shot > 0 && e->is_shot < GIF_GUN_NUM)
	{
		draw_gun(e, e->gun_gif[e->is_shot],
				point_in(e->width / 2, e->height - e->bob), 3);
		e->is_shot += 1;
	}
	else
	{
		e->is_shot = 0;
		draw_gun(e, e->gun_gif[e->is_shot],
				point_in(e->width / 2, e->height - e->bob), 3);
	}
}

void		check_shot(t_e *e, t_spr *s)
{
	double	ang1;
	double	ang2;

	ang1 = atan2(e->pl.dir.y, e->pl.dir.x) / RAD;
	ang2 = atan2(s->pos.y - e->pl.pos.y, s->pos.x - e->pl.pos.x) / RAD;
	if (fabs(ang2 - ang1) < 30 / s->dist)
	{
		s->c = 'Z';
		e->pl.points += 100;
	}
}

void		ft_play_gif(t_e *e, t_spr *s)
{
	if ((s->spr_swp += 1) >= 2 && s->spr_swp < GIF_NUM + 2)
	{
		s->img = e->z_death[s->spr_swp - 2].img;
		s->w = e->z_death[s->spr_swp - 2].w;
		s->h = e->z_death[s->spr_swp - 2].h;
	}
}

void		ft_shoot(t_e *e)
{
	int		i;

	i = -1;
	if (e->pl.ammo > 0)
	{
		e->is_shot = 1;
		e->pl.ammo -= 1;
		while (++i < e->spr_num)
		{
			if (e->spr[i].c == 'z')
				check_shot(e, &(e->spr[i]));
		}
	}
}
