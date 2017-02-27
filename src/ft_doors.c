/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 10:58:56 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/27 11:00:29 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** beta - angle between player and ray angles
*/

static double		calc_beta(t_e *e, int x)
{
	double	dist_ang;

	dist_ang = ((double)x / (double)e->width) * 66 - 66 / 2;
	dist_ang *= RAD;
	return (dist_ang);
}

int					calc_d_height(t_e *e, int i, int x, t_dspr *s)
{
	int		cam_x;
	t_p 	plane_dot;
	t_p		spr_dot;
	double	stdist;
	int		height;

	cam_x = 2 * x / (double)e->width - 1;
	plane_dot.x = e->pl.pos.x + e->pl.plane.x * cam_x;
	plane_dot.y = e->pl.pos.y + e->pl.plane.y * cam_x;
	if (e->spr[i].c == 'd')
		spr_dot.x = e->spr[i].pos.x + SIGN(e->pl.dir.y) *
			((double)((x - s->d_start.x) - s->s_w / 2) / (double)s->s_w);
	else if (e->spr[i].c == 'D')
		spr_dot.y = e->spr[i].pos.y - SIGN(e->pl.dir.x) *
			((double)((x - s->d_start.x) - s->s_w / 2) / (double)s->s_w);
	(e->spr[i].c == 'd') ? spr_dot.y = e->spr[i].pos.y : 23;
	(e->spr[i].c == 'D') ? spr_dot.x = e->spr[i].pos.x : 23;
	stdist = sqrt((plane_dot.x - spr_dot.x) * (plane_dot.x - spr_dot.x) +
			(plane_dot.y - spr_dot.y) * (plane_dot.y - spr_dot.y));
	stdist *= cos(calc_beta(e, x));
	height = (stdist > 0.3) ? (int)(e->height / stdist) : e->height;
	s->d_start.y = -height / 2 + e->height / 2;
	s->d_end.y = height / 2 + e->height / 2;
	return (height);
}
