/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pickups.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:09:27 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/02 17:44:09 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		del_spr(t_e *e, t_spr **s)
{
	*s = &(e->spr[e->spr_num - 1]);
	e->spr_num -= 1;
}

void		ft_pickup(t_e *e, t_spr *s)
{
	if (s->c == 'h' && sqrt(s->dist) < 0.3 && e->pl.hp < 100)
	{
		e->pl.hp += 10;
		del_spr(e, &s);
		dead_screen(e, 6, 0xff00);
	}
	if (s->c == 's' && sqrt(s->dist) < 0.3)
	{
		e->pl.ammo += 3;
		del_spr(e, &s);
		dead_screen(e, 6, 0xff);
	}
}
