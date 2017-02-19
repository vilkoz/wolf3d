/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:01:10 by vrybalko          #+#    #+#             */
/*   Updated: 2017/02/19 17:27:59 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WOLF_H
# define _WOLF_H
# define RAD (0.0175433)
# define TEX_NUM 1

# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>

/*
** struct for key events
*/

typedef struct		s_k
{
	int				gopa;
	int				move_x;
	int				move_y;
	int				rot;
}					t_k;

typedef struct		s_p
{
	double			x;
	double			y;
}					t_p;

typedef struct		s_lin
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				d;
	int				d1;
	int				d2;
	int				error;
	int				error2;
	t_p				*p1;
	t_p				*p2;
}					t_lin;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_lst
{
	int				y;
	char			*line;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_pl
{
	t_p				pos;
	t_p				dir;
	t_p				plane;
	double			ms;
	double			rs;

}					t_pl;

typedef struct		s_pi
{
	int				x;
	int				y;
}					t_pi;

typedef struct		s_ray
{
	t_p				pos;
	t_p				dir;
	double			cam_x;
	t_p				sdist;
	t_p				ddist;
	t_pi			step;
	int				hit;
	int				side;
	double			wall_d;
	int				l_height;
	int				d_start;
	int				d_end;
	int				color;
	t_p				wall;
	t_pi			tex;
}					t_ray;

typedef struct		s_tex
{
	void			*img;
	char			*path;
	int				w;
	int				h;
}					t_tex;

typedef struct		s_e
{
	void			*mlx;
	void			*win;
	void			*img;
	int				height;
	int				width;
	t_k				k;
	t_lst			*lst;
	char			**map;
	int				map_w;
	int				map_h;
	t_pl			pl;
	double			time;
	int				fps;
	t_tex			*tex;
}					t_e;

t_e					*ft_mlx_init(t_lst *lst, int size_y, t_e *e);
void				ft_img_px_put(t_e *e, int x, int y, int rgb);
void				ft_mlx_events(t_e *e);
int					loop_hook(t_e *e);
void				keys_init(t_k *k);
int					key_press(int key, t_e *e);
int					key_release(int key, t_e *e);
int					mouse_hook(int key, int x, int y, t_e *e);
int					move_hook(int x, int y, t_e *e);
t_lin				line_init(t_p p1, t_p p2);
void				ft_draw_line(t_e *all, t_p p1, t_p p2, int rgb);
t_e					*ft_read_map(char *s);
t_p					init_point(double x, double y);
t_p					point_in(int x, int y);
void				ft_raycast(t_e *e);
void				ft_move(t_e *e);
void				ft_rotate(t_e *e);
void				ft_print_map(t_e *e);
t_e					*ft_load_tex(t_e *e);
int					ft_img_px_get(void *img, t_pi p, t_tex *tex);
char				s_map(t_e *e, int y, int x);

#endif
