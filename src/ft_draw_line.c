/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:07:40 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/03 18:59:50 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_lin			line_init(t_p p1, t_p p2)
{
	t_lin	lin;

	lin.dx = fabs(p2.x - p1.x);
	lin.dy = fabs(p2.y - p1.y);
	lin.sx = p1.x < p2.x ? 1 : -1;
	lin.sy = p1.y < p2.y ? 1 : -1;
	lin.error = lin.dx - lin.dy;
	return (lin);
}

void			ft_draw_line(t_e *all, t_p p1, t_p p2, int rgb)
{
	t_lin	lin;
	int		x1;
	int		y1;

	x1 = p1.x;
	y1 = (p1.y > 0) ? p1.y : 0;
	p2.y = (p2.y > 0) ? p2.y : 0;
	p2.y = (p2.y < all->height) ? p2.y : all->height - 1;
	lin = line_init(p1, p2);
	ft_img_px_put(all, p2.x, p2.y, rgb);
	while (x1 != p2.x || y1 != p2.y)
	{
		ft_img_px_put(all, x1, y1, rgb);
		lin.error2 = lin.error * 2;
		if (lin.error2 > -lin.dy)
		{
			lin.error -= lin.dy;
			x1 += lin.sx;
		}
		if (lin.error2 < lin.dx)
		{
			lin.error += lin.dx;
			y1 += lin.sy;
		}
	}
}

t_pi			point_in(int x, int y)
{
	t_pi	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_p				point_in1(int x, int y)
{
	t_p		p;

	p.x = x;
	p.y = y;
	return (p);
}
