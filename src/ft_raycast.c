/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:29:35 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/21 21:23:29 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_vline(t_e *e, t_p p1, t_p p2, int rgb)
{
	int			i;

	i = (p1.y > 0) ? p1.y : 0;
	p2.y = (p2.y > e->height) ? e->height - 1 : p2.y;
	while (i < p2.y)
	{
		ft_img_px_put(e, p1.x, i, rgb);
		i++;
	}
}

static void	cast_a_ray(t_e *e, t_ray *ray, t_p *map)
{
	while (ray->hit == 0)
	{
		if (ray->sdist.x < ray->sdist.y)
		{
			ray->sdist.x += ray->ddist.x;
			map->x += ray->step.x;
			ray->side = (ray->step.x < 0) ? 0 : 2;
		}
		else
		{
			ray->sdist.y += ray->ddist.y;
			map->y += ray->step.y;
			ray->side = (ray->step.y < 0) ? 1 : 3;
		}
		if (s_map(e, (int)map->y, (int)map->x) > '0' &&
				(s_map(e, (int)map->y, (int)map->x) != 'a'))
			ray->hit = 1;
	}
}

static void	ray_init(t_e *e, t_ray *ray, t_p *map, int i)
{
	ray->hit = 0;
	ray->cam_x = 2 * i / (double)e->width - 1;
	ray->pos = init_point(e->pl.pos.x, e->pl.pos.y);
	ray->dir.x = e->pl.dir.x + e->pl.plane.x * ray->cam_x;
	ray->dir.y = e->pl.dir.y + e->pl.plane.y * ray->cam_x;
	*map = init_point((int)(ray->pos.x), (int)(ray->pos.y));
	ray->ddist.x = sqrt(1 + ray->dir.y * ray->dir.y
			/ (ray->dir.x * ray->dir.x));
	ray->ddist.y = sqrt(1 + ray->dir.x * ray->dir.x
			/ (ray->dir.y * ray->dir.y));
	ray->step.x = (ray->dir.x < 0) ? -1 : 1;
	if (ray->dir.x < 0)
		ray->sdist.x = (ray->pos.x - map->x) * ray->ddist.x;
	else
		ray->sdist.x = (map->x + 1. - ray->pos.x) * ray->ddist.x;
	ray->step.y = (ray->dir.y < 0) ? -1 : 1;
	if (ray->dir.y < 0)
		ray->sdist.y = (ray->pos.y - map->y) * ray->ddist.y;
	else
		ray->sdist.y = (map->y + 1. - ray->pos.y) * ray->ddist.y;
}

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

int			add_shade_f(int color, int  y)
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

void		choose_color(t_e *e, t_ray ray, t_p map, int i)
{
	if (s_map(e, (int)map.y, (int)map.x) >= '0')
	{
		if (ray.side == 0)
			ray.color = 0x00ff00;
		if (ray.side == 1)
			ray.color = 0xffff00;
		if (ray.side == 2)
			ray.color = 0x0000ff;
		if (ray.side == 3)
			ray.color = 0x00ffff;
	}
	ft_vline(e, point_in(i, 0), point_in(i, ray.d_start),
			0x33);
	ft_vline(e, point_in(i, ray.d_start), point_in(i, ray.d_end),
			add_shade(e, ray, ray.color));
	ft_vline(e, point_in(i, ray.d_end), point_in(i, e->height - 1),
			0x777777);
}

void		count_sprite_dist(t_e *e)
{
	int		i;

	i = -1;
	while (++i < SPRITE_NUM)
	{
		e->spr[i].dist = (e->pl.pos.x - e->spr[i].pos.x) *
			(e->pl.pos.x - e->spr[i].pos.x) + (e->pl.pos.y - e->spr[i].pos.y) *
			(e->pl.pos.y - e->spr[i].pos.y);
	}
}

void		sort_sprite(t_e *e)
{
	int		i;
	int		n;
	int		newn;
	t_spr	tmp;

	count_sprite_dist(e);
	i = 0;
	n = SPRITE_NUM;
	while (n != 0)
	{
		newn = 0;
		while (++i < n - 1)
		{
			if (e->spr[i].dist < e->spr[i - 1].dist)
			{
				tmp = e->spr[i];
				e->spr[i] = e->spr[i + 1];
				e->spr[i + 1] = tmp;
				newn = i;
			}
		}
		n = newn;
	}
}

t_dspr		init_spr(t_e *e, int i, t_dspr s)
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
	s.d_end.y = (-s.s_h / 2 + e->height / 2 > e->height) ? e->height - 1 :
		-s.s_h / 2 + e->height / 2;
	s.s_w = abs((int)(e->height / (s.tran.y)));
	s.d_start.x = (-s.s_w / 2 + s.spr_scr.x < 0) ? 0 : -s.s_w / 2 + s.spr_scr.x;
	s.d_end.x = (s.s_w / 2 + s.spr_scr.x > e->width) ? e->width - 1 : s.s_w / 2
		+ s.spr_scr.x;
	return (s);
}

void		put_spr_tex(t_e *e, int	i, t_dspr s)
{
	int		stripe;
	t_pi	tex;
	int		y;
	int		d;

	stripe = s.d_start.x - 1;
	while(++stripe < s.d_end.x)
	{
		tex.x = (int)(256 * (stripe - (-s.s_w / 2 + s.spr_scr.x)) * e->spr[i].w / s.s_w) / 256;
		if (s.tran.y > 0 && stripe > 0 && stripe < e->width && s.tran.y < e->z[stripe])
		{
			y = s.d_start.y - 1;
			while (++y < s.d_end.y)
			{
				d = y * 256 - e->height * 128 + s.s_h * 128;
				tex.y = (d * e->spr[i].h / s.s_h) / 256;
				ft_img_px_put(e, stripe, y, ft_img_px_get_s(e->spr[i].img, tex, &e->spr[i]));
			}
		}
	}
}

void		put_sprite(t_e *e)
{
	int		i;
	t_dspr  s;

	sort_sprite(e);
	i = -1;
	while (++i < SPRITE_NUM)
	{
		s = init_spr(e, i, s);
		put_spr_tex(e, i, s);
	}
}

void		tex_put_floor(t_e *e, t_ray ray, t_p map, int i)
{
	t_p		floor;
	t_p		cur_floor;
	t_pi	floor_tex;
	double	cur_d;
	int		y;
	double	weight;

	if ((ray.side == 0 || ray.side == 2) && ray.dir.x > 0)
	{
		floor.x = map.x;
		floor.y = map.y + ray.wall.x;
	}
	else if ((ray.side == 0 || ray.side == 2) && ray.dir.x < 0)
	{
		floor.x = map.x + 1.0;
		floor.y = map.y + ray.wall.x;
	}
	else if ((ray.side == 1 || ray.side == 3) && ray.dir.y > 0)
	{
		floor.x = map.x + ray.wall.x;
		floor.y = map.y;
	}
	else if ((ray.side == 1 || ray.side == 3) && ray.dir.y < 0)
	{
		floor.x = map.x + ray.wall.x;
		floor.y = map.y + 1.0;
	}
	y = ray.d_end;
	while (++y < e->height)
	{
		cur_d = e->height / (2.0 * y - e->height);
		weight = cur_d / ray.wall_d;
		cur_floor.x = weight * floor.x + (1. - weight) * e->pl.pos.x;
		cur_floor.y = weight * floor.y + (1. - weight) * e->pl.pos.y;
		floor_tex.x = (int)(cur_floor.x * e->tex[2].w) % e->tex[2].w;
		floor_tex.y = (int)(cur_floor.y * e->tex[2].h) % e->tex[2].h;
		ft_img_px_put(e, i, y, add_shade_f(ft_img_px_get(e->tex[2].img,
						floor_tex, &e->tex[2]), y));
		ft_img_px_put(e, i, e->height - y, add_shade_f(ft_img_px_get(
						e->tex[3].img, floor_tex, &e->tex[3]), y));
	}
}

void		tex_put(t_e *e, t_ray ray, t_p map, int i)
{
	int		tex;
	int		y;
	int		d;
	int		color;

	if ((tex = s_map(e, (int)map.y, (int)map.x) - 48 - 1) >= TEX_NUM)
	{
		choose_color(e, ray, map, i);
		return ;
	}
	ray.wall.x = (ray.side == 0 || ray.side == 2) ? ray.pos.y + ray.wall_d *
		ray.dir.y : ray.pos.x + ray.wall_d * ray.dir.x;
	ray.wall.x -= floor(ray.wall.x);
	ray.tex.x = (int)(ray.wall.x * (double)e->tex[tex].w);
	y = ray.d_start - 1;
	while (++y < ray.d_end)
	{
		d = y * 256 - e->height * 128 + ray.l_height * 128;
		ray.tex.y = ((d * e->tex[tex].h) / ray.l_height ) / 256;
		color = ft_img_px_get(e->tex[tex].img, ray.tex, &e->tex[tex]);
		ft_img_px_put(e, i, y, add_shade(e, ray, color));
	}
	tex_put_floor(e, ray, map, i);
}

void		ft_raycast(t_e *e)
{
	int			i;
	t_ray		ray;
	t_p			map;

	i = -1;
	while (++i < e->width)
	{
		ray_init(e, &ray, &map, i);
		cast_a_ray(e, &ray, &map);
		if (ray.side == 0 || ray.side == 2)
			ray.wall_d = (map.x - ray.pos.x + (1 - ray.step.x) / 2) / ray.dir.x;
		else
			ray.wall_d = (map.y - ray.pos.y + (1 - ray.step.y) / 2) / ray.dir.y;
		if (ray.wall_d > 0.3)
			ray.l_height = (int)(e->height / ray.wall_d);
		else
			ray.l_height = e->height;
		ray.d_start = -ray.l_height / 2 + e->height / 2;
		ray.d_end = ray.l_height / 2 + e->height / 2;
		e->z[i] = ray.wall_d;
		(e->k.tex) ? choose_color(e, ray, map, i) : tex_put(e, ray, map, i);
	}
	put_sprite(e);
}
