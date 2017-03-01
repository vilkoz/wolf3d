/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img_px_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:59:57 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/01 23:59:18 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_img_px_put(t_e *e, int x, int y, int rgb)
{
	int				bpp;
	int				sl;
	int				en;
	char			*imag;
	unsigned int	tmp;

	imag = mlx_get_data_addr(e->img, &bpp, &sl, &en);
	tmp = (mlx_get_color_value(e->mlx, rgb));
	if (x > 0 && x < e->width && y > 0 && y < e->height)
		ft_memcpy((void *)((imag + y * e->width *
						(bpp / 8) + x * (bpp / 8))), (void *)&tmp, 4);
}

int		ft_img_px_get_s(void *img, t_pi p, t_spr *spr)
{
	int				bpp;
	int				sl;
	int				en;
	char			*imag;
	int				tmp;

	imag = mlx_get_data_addr(img, &bpp, &sl, &en);
	tmp = 0;
	if (p.x >= 0 && p.x < spr->w && p.y >= 0 && p.y < spr->h)
		ft_memcpy((void *)&tmp, (void *)((imag + p.y * spr->w *
						(bpp / 8) + p.x * (bpp / 8))), 4);
	return (tmp);
}

int		ft_img_px_get(void *img, t_pi p, t_tex *tex)
{
	int				bpp;
	int				sl;
	int				en;
	char			*imag;
	int				tmp;

	imag = mlx_get_data_addr(img, &bpp, &sl, &en);
	tmp = 0;
	if (p.x >= 0 && p.x < tex->w && p.y >= 0 && p.y < tex->h)
		ft_memcpy((void *)&tmp, (void *)((imag + p.y * tex->w *
						(bpp / 8) + p.x * (bpp / 8))), 4);
	return (tmp);
}

int		ft_img_px_get_gif(void *img, t_pi p, t_gif tex)
{
	int				bpp;
	int				sl;
	int				en;
	char			*imag;
	int				tmp;

	imag = mlx_get_data_addr(img, &bpp, &sl, &en);
	tmp = 0;
	if (p.x >= 0 && p.x < tex.w && p.y >= 0 && p.y < tex.h)
		ft_memcpy((void *)&tmp, (void *)((imag + p.y * tex.w *
						(bpp / 8) + p.x * (bpp / 8))), 4);
	return (tmp);
}
