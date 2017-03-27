/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 17:03:08 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/27 13:51:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		sort_sprite(t_e *e)
{
	int		i;
	int		n;
	int		newn;
	t_spr	tmp;

	n = e->spr_num;
	newn = 1;
	while (newn != 0)
	{
		newn = 0;
		i = 0;
		while (++i <= n - 1)
		{
			if (e->spr[i].dist - e->spr[i - 1].dist > 0.1)
			{
				tmp = e->spr[i];
				e->spr[i] = e->spr[i - 1];
				e->spr[i - 1] = tmp;
				newn = 1;
			}
		}
	}
}

t_dspr		init_dspr(t_e *e, int i, t_dspr s)
{
	s.sprite.x = e->spr[i].pos.x - e->pl.pos.x;
	s.sprite.y = e->spr[i].pos.y - e->pl.pos.y;
	s.inv_det = 1. / (e->pl.plane.x * e->pl.dir.y - e->pl.plane.y *
			e->pl.dir.x);
	s.tran.x = s.inv_det * (e->pl.dir.y * s.sprite.x - e->pl.dir.x *
			s.sprite.y);
	s.tran.y = s.inv_det * (-e->pl.plane.y * s.sprite.x + e->pl.plane.x *
			s.sprite.y);
	s.spr_scr.x = (int)(e->width / 2) * (1 + s.tran.x / s.tran.y);
	s.s_h = abs((int)(e->height / (s.tran.y)));
	s.d_start.y = (-s.s_h / 2 + e->height / 2 < 0) ? 0 :
		-s.s_h / 2 + e->height / 2;
	s.d_end.y = (s.s_h / 2 + e->height / 2 > e->height) ? e->height - 1 :
		s.s_h / 2 + e->height / 2;
	if (e->spr[i].c == 'd')
		s.s_w = abs((int)((e->height / s.tran.y) * e->pl.dir.y));
	if (e->spr[i].c == 'D')
		s.s_w = abs((int)((e->height / s.tran.y) * e->pl.dir.x));
	if (e->spr[i].c != 'd' && e->spr[i].c != 'D')
		s.s_w = abs((int)(e->height / (s.tran.y)));
	s.d_start.x = (-s.s_w / 2 + s.spr_scr.x < 0) ? 0 : -s.s_w / 2 + s.spr_scr.x;
	s.d_end.x = (s.s_w / 2 + s.spr_scr.x > e->width) ? e->width - 1 : s.s_w / 2
		+ s.spr_scr.x;
	s.i = i;
	return (s);
}

void		put_spr_stripe(t_e *e, t_pi tex, t_pi p, t_dspr s)
{
	int		d;
	int		clr;

	if (e->spr[s.i].c == 'd' || e->spr[s.i].c == 'D')
		s.s_h = calc_d_height(e, s.i, p.x, &s);
	p.y = s.d_start.y - 1;
	while (++p.y < s.d_end.y)
	{
		d = p.y * 2 - e->height + s.s_h;
		tex.y = (d * e->spr[s.i].h / s.s_h) / 2;
		clr = ft_img_px_get_s(e->spr[s.i].img, tex, &e->spr[s.i]);
		if ((clr & 0xFFFFFF) != 0)
			ft_img_px_put(e, p.x, p.y, add_shade_spr(clr, e->spr[s.i].dist));
	}
}

/*
** x - stripe
*/

void		put_spr_tex(t_e *e, int i, t_dspr s)
{
	t_pi	tex;
	int		x;

#pragma omp parallel private(x, tex)
#pragma omp for schedule(dynamic)
	for (x = s.d_start.x; x < s.d_end.x; x++)
	{
		tex.x = (int)((x - (-s.s_w / 2 + s.spr_scr.x)) *
				e->spr[i].w / s.s_w);
		if (s.tran.y > 0 && x > 0 && x < e->width &&
				s.tran.y < e->z[x])
			put_spr_stripe(e, tex, point_in(x, 0), s);
	}
}

void		put_sprite(t_e *e)
{
	int		i;
	t_dspr	s;

	i = -1;
	while (++i < e->spr_num)
	{
		(e->spr[i].c == 'Z') ? ft_play_gif(e, &e->spr[i]) : 23;
		e->spr[i].dist = (e->pl.pos.x - e->spr[i].pos.x) *
			(e->pl.pos.x - e->spr[i].pos.x) + (e->pl.pos.y - e->spr[i].pos.y) *
			(e->pl.pos.y - e->spr[i].pos.y);
	}
	sort_sprite(e);
	i = -1;
	while (++i < e->spr_num)
	{
		s = init_dspr(e, i, s);
		put_spr_tex(e, i, s);
	}
}
