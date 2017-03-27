/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img_px_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:59:57 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/27 14:24:02 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_img_px_put(t_e *e, int x, int y, int rgb)
{
	unsigned int	tmp;

	tmp = (mlx_get_color_value(e->mlx, rgb));
	if (x > 0 && x < e->width && y > 0 && y < e->height)
	{
		*(((e->imag + y * e->width * (e->bpp / 8) + x * (e->bpp / 8))) + 2) =
			(char)((tmp & 0x00ff0000) >> 16);
		*(((e->imag + y * e->width * (e->bpp / 8) + x * (e->bpp / 8))) + 1) =
			(char)((tmp & 0x0000ff00) >> 8);
		*(((e->imag + y * e->width * (e->bpp / 8) + x * (e->bpp / 8))) + 0) =
			(char)((tmp & 0x000000ff) >> 0);
	}
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
