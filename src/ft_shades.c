/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shades.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 17:01:26 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/23 17:05:12 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			add_shade(t_e *e, t_ray ray, int color)
{
	t_rgb	c;

	c.r = (color & 0xff0000) >> 16;
	c.g = (color & 0x00ff00) >> 8;
	c.b = (color & 0x0000ff);
	c.r *= (1 - fabs(e->height * 1. / ray.l_height - 1) / 5.);
	c.g *= (1 - fabs(e->height * 1. / ray.l_height - 1) / 5.);
	c.b *= (1 - fabs(e->height * 1. / ray.l_height - 1) / 5.);
	c.r = (c.r < 0) ? 0 : c.r;
	c.g = (c.g < 0) ? 0 : c.g;
	c.b = (c.b < 0) ? 0 : c.b;
	return ((c.r << 16) + (c.g << 8) + c.b);
}

int			add_shade_f(int color, int y)
{
	t_rgb	c;

	c.r = (color & 0xff0000) >> 16;
	c.g = (color & 0x00ff00) >> 8;
	c.b = (color & 0x0000ff);
	c.r *= (1 - (800. / abs(y)) / 2.);
	c.g *= (1 - (800. / abs(y)) / 2.);
	c.b *= (1 - (800. / abs(y)) / 2.);
	c.r = (c.r < 0) ? 0 : c.r;
	c.g = (c.g < 0) ? 0 : c.g;
	c.b = (c.b < 0) ? 0 : c.b;
	return ((c.r << 16) + (c.g << 8) + c.b);
}

int			add_shade_spr(int color, double y)
{
	t_rgb	c;

	c.r = (color & 0xff0000) >> 16;
	c.g = (color & 0x00ff00) >> 8;
	c.b = (color & 0x0000ff);
	c.r *= (1 - y / 30.);
	c.g *= (1 - y / 30.);
	c.b *= (1 - y / 30.);
	c.r = (c.r < 0) ? 0 : c.r;
	c.g = (c.g < 0) ? 0 : c.g;
	c.b = (c.b < 0) ? 0 : c.b;
	return ((c.r << 16) + (c.g << 8) + c.b);
}
