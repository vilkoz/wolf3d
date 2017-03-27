/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:01:10 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/27 13:21:12 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WOLF_H
# define _WOLF_H
# define RAD (0.0175433)
# define TEX_NUM 8
# define GIF_NUM 7
# define GIF_GUN_NUM 5
# define SIGN(x) ((x < 0) ? -1 : 1)

/*
** Keys
*/

# ifdef linux
#  define XK_LATIN1
#  define XK_MISCELLANY
#  define XK_TECHNICAL
#  include <X11/keysymdef.h>
#  define K_ESC XK_Escape
#  define K_W XK_w
#  define K_S XK_s
#  define K_A XK_a
#  define K_D XK_d
#  define K_LA XK_Left
#  define K_RA XK_Right
#  define K_E XK_e
#  define K_M XK_m
#  define K_T XK_t
#  define K_Q XK_q
#  define K_SP XK_space
# else
#  define K_ESC 53
#  define K_W 13
#  define K_S 1
#  define K_A 0
#  define K_D 2
#  define K_LA 123
#  define K_E 14
#  define K_M 46
#  define K_T 17
#  define K_Q 12
#  define K_RA 124
#  define K_SP 49
# endif

# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <sys/time.h>

typedef struct timeval s_t;

/*
** struct for key events
*/

typedef struct		s_k
{
	int				gopa;
	int				move_x;
	int				move_y;
	int				rot;
	int				map;
	int				tex;
	int				menu;
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

typedef struct		s_lsp
{
	t_p				pos;
	char			c;
	struct s_lsp	*next;
}					t_lsp;

typedef struct		s_pl
{
	t_p				pos;
	t_p				dir;
	t_p				plane;
	double			ms;
	double			rs;
	int				hp;
	int				ammo;
	int				points;
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

typedef struct		s_spr
{
	void			*img;
	void			*img2;
	char			*path;
	double			dist;
	int				w;
	int				h;
	char			c;
	int				op;
	int				spr_swp;
	t_p				pos;
	t_p				old_pos;
}					t_spr;

typedef struct		s_dspr
{
	double			inv_det;
	t_p				sprite;
	t_p				tran;
	t_pi			spr_scr;
	t_pi			d_start;
	t_pi			d_end;
	int				s_h;
	int				s_w;
	int				i;
}					t_dspr;

typedef struct		s_chk_chr
{
	int				is_solid;
	char			c;
}					t_chk_chr;

typedef struct		s_gif
{
	void			*img;
	char			*path;
	int				w;
	int				h;
}					t_gif;

typedef struct		s_e
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*imag;
	int				bpp;
	int				en;
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
	t_spr			*spr;
	int				tex_max;
	double			z[1500];
	t_lsp			*lsp;
	int				spr_num;
	t_pi			txt_shift;
	t_pi			m;
	t_gif			*z_death;
	t_gif			*gun_gif;
	void			*gun;
	int				is_shot;
	char			*map_path;
	t_pi			bob_param;
	int				bob;
}					t_e;

t_e					*ft_mlx_init(t_lst *lst, int size_y, t_e *e, char *s);
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
t_pi				point_in(int x, int y);
void				ft_raycast(t_e *e);
void				ft_move(t_e *e);
void				ft_rotate(t_e *e);
void				ft_print_map(t_e *e);
t_e					*ft_load_tex(t_e *e);
int					ft_img_px_get(void *img, t_pi p, t_tex *tex);
char				s_map(t_e *e, int y, int x);
void				free_map(char **map);
int					ft_img_px_get_s(void *img, t_pi p, t_spr *spr);
void				tex_put_floor(t_e *e, t_ray ray, t_p map, int i);
void				tex_put(t_e *e, t_ray ray, t_p map, int i);
void				choose_color(t_e *e, t_ray ray, t_p map, int i);
int					add_shade(t_e *e, t_ray ray, int color);
int					add_shade_f(int color, int y);
int					add_shade_spr(int color, double y);
void				count_sprite_dist(t_e *e);
void				sort_sprite(t_e *e);
void				put_sprite(t_e *e);
void				put_spr_tex(t_e	*e, int i, t_dspr s);
t_dspr				init_dspr(t_e *e, int i, t_dspr s);
void				ft_open_door(t_e *e);
int					calc_d_height(t_e *e, int i, int x, t_dspr *s);
void				ft_move_enemies(t_e *e);
void				ft_put_info(t_e *e);
void				choose_menu(t_e *e);

/*
** ft_game_mode_hooks.c
*/

void				game_key_press(int	key, t_e *e);
void				game_key_release(int key, t_e *e);
void				game_move_hook(t_e *e, int x, int y);
void				game_loop_hook(t_e *e);
void				game_mouse_hook(t_e *e, int key);
void				dead_screen(t_e *e, int hit, int c);
t_p					point_in1(int x, int y);
void				ft_play_gif(t_e *e, t_spr *s);
void				ft_shoot(t_e *e);
void				ft_load_gif(t_e *e);
void				put_gun(t_e *e);
int					ft_img_px_get_gif(void *img, t_pi p, t_gif tex);
void				ft_pickup(t_e *e, t_spr *s);
void				calc_speed(t_e *e);
void				win_menu_mouse_hook(int key, int x, int y, t_e *e);
void				pause_key_hook(int key, t_e *e);
void				pause_mouse_hook(int key, int x, int y, t_e *e);
void				free_map(char **map);
t_lsp				*lsp_new(t_p pos, char c);
t_lsp				*lsp_add(t_lsp *new, t_lsp *old);
t_chk_chr			init_chk(int is_solid, char c);
void				check_char(t_e *e, int y, t_lst *tmp, t_chk_chr s);
int					calc_kill_rate(t_e *e);
char				*ft_rs(char *s1, char *s2);
void				ft_putstry(t_e *e, char *str);

#endif
