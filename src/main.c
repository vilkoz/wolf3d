/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:17:44 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/03 14:36:46 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			main(int argc, char **argv)
{
	t_e		*e;

	if (argc != 2)
	{
		ft_putstr("usage ./wolf3D <map_file>\n");
		return (1);
	}
	if ((e = ft_read_map(argv[1])) == NULL || e->map == NULL)
	{
		if (e != NULL)
			ft_putstr("map error\n");
		return (1);
	}
	ft_print_array(e->map);
	ft_mlx_events(e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
