/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img_px_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:59:57 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/17 14:04:20 by vrybalko         ###   ########.fr       */
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
