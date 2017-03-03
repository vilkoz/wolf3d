/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemies.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 17:15:57 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/03 18:57:12 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		dodge(t_e *e, t_spr *s)
{
	if (s_map(e, (int)(s->pos.y + 0.5 * e->pl.dir.x),
				(int)(s->pos.x - 0.5 * e->pl.dir.y)) < '0')
	{
		s->pos.y += 0.5 * e->pl.dir.x;
		s->pos.x -= 0.5 * e->pl.dir.y;
	}
	else if (s_map(e, (int)(s->pos.y - 0.5 * e->pl.dir.x),
				(int)(s->pos.x + 0.5 * e->pl.dir.y)) < '0')
	{
		s->pos.y -= 0.5 * e->pl.dir.x;
		s->pos.x += 0.5 * e->pl.dir.y;
	}
}

static void		move_enemy(t_e *e, t_spr *s)
{
	t_p			delta;
	t_p			bak;
	void		*tmp;

	if (s->dist < 25 && sqrt(s->dist) > 0.5)
	{
		delta.x = s->pos.x - e->pl.pos.x;
		delta.y = s->pos.y - e->pl.pos.y;
		bak = s->pos;
		s->pos.x -= delta.x * e->pl.ms / 10;
		s->pos.y -= delta.y * e->pl.ms / 10;
		if (s_map(e, (int)(s->pos.y), (int)(s->pos.x)) >= '0')
		{
			s->pos = bak;
			dodge(e, s);
		}
		if (s->spr_swp % 4 == 0)
		{
			tmp = s->img;
			s->img = s->img2;
			s->img2 = tmp;
			s->spr_swp = 0;
		}
		s->spr_swp++;
	}
}

static void		deal_damage(t_e *e, t_spr *s)
{
	time_t	t;
	t_p		bak;

	srand(time(&t));
	if (sqrt(s->dist) < 0.7 && e->pl.hp > 0)
	{
		e->pl.hp -= 5;
		bak = e->pl.pos;
		e->pl.pos.x -= (s->pos.x - e->pl.pos.x) / 2;
		e->pl.pos.y -= (s->pos.y - e->pl.pos.y) / 2;
		if (s_map(e, (int)e->pl.pos.y, (int)e->pl.pos.x) >= '0')
			e->pl.pos = bak;
		dead_screen(e, 6, 0xff0000);
	}
}

void			ft_move_enemies(t_e *e)
{
	int		i;

	i = -1;
	while (++i < e->spr_num)
	{
		if (e->spr[i].c == 'z')
		{
			move_enemy(e, &(e->spr[i]));
			deal_damage(e, &(e->spr[i]));
		}
		ft_pickup(e, &e->spr[i]);
	}
}
