/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:17:32 by tpokalch          #+#    #+#             */
/*   Updated: 2019/03/09 20:07:05 by tpokalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	copy(t_global *d, t_global *s)
{
	d->c = s->c;
	d->w_p = s->w_p;
	d->m_p = s->m_p;
	d->img_ptr = s->img_ptr;
	d->data_ptr = s->data_ptr;
	d->zoom = s->zoom;
	d->precision = s->precision;
	d->sz_l = s->sz_l;
	d->bound = s->bound;
	d->core = s->core;
	d->color_mode = s->color_mode;
	d->center = s->center;
	d->fid = s->fid;
	d->fract = s->fract;
	d->m_pos.x = s->m_pos.x;
	d->m_pos.y = s->m_pos.y;
}

int		(*fractol_fun(char *s))(double, double, t_global)
{
	if (ft_strequ("mandelbrot", s))
		return (color_man);
	else if (ft_strequ("julia", s))
		return (color_jul);
	else if (ft_strequ("julia3", s))
		return (color_jul3);
	else if (ft_strequ("mandelbrot3", s))
		return (color_jul4);
	return (NULL);
}

void	write_manual(t_global g)
{
	mlx_string_put(g.m_p, g.w_p, 260, 0, 0xFFFFFF, "Hello!");
	mlx_string_put(g.m_p, g.w_p, 5, 60, 0xFFFFFF, "Use arrows to move.");
	mlx_string_put(g.m_p, g.w_p, 5, 80, 0xFFFFFF, "Press mouse to");
	mlx_string_put(g.m_p, g.w_p, 160, 80, 0xFFFFFF, "zoom into mouse");
	mlx_string_put(g.m_p, g.w_p, 335, 80, 0xFFFFFF, "position.");
	mlx_string_put(g.m_p, g.w_p, 5, 100, 0xFFFFFF, "Press it again to");
	mlx_string_put(g.m_p, g.w_p, 181, 100, 0xFFFFFF, "disable this mode.");
	mlx_string_put(g.m_p, g.w_p, 5, 120, 0xFFFFFF, "Press C to change color.");
	mlx_string_put(g.m_p, g.w_p, 5, 140, 0xFFFFFF, "Use P, L");
	mlx_string_put(g.m_p, g.w_p, 100, 140, 0xFFFFFF, "to control details.");
}

void	init(t_global *g)
{
	g->c.x = 0;
	g->c.y = 0;
	g->zoom = 100;
	g->precision = 64;
	g->bound = WIDTH * HEIGHT / 2;
	g->core = 0;
	g->zoom_mode = 0;
	g->color_mode = 0;
	g->m_pos.x = 0;
	g->m_pos.y = 0;
	g->center.x = 0;
	g->center.y = 0;
	g->m_p = mlx_init();
	g->w_p = mlx_new_window(g->m_p, WIDTH, HEIGHT, "window1");
	g->img_ptr = mlx_new_image(g->m_p, WIDTH, HEIGHT);
	g->data_ptr = (int *)mlx_get_data_addr(g->img_ptr, &g->bpp, &g->sz_l,
	&g->e);
}

int		main(int argc, char **argv)
{
	t_global	g;

	if (argc != 2 || !(g.fract = fractol_fun(*(argv + 1))))
	{
		ft_putstr("Usage : ./fractol <name>\n");
		ft_putstr("                  mandelbrot\n");
		ft_putstr("                  julia\n");
		ft_putstr("                  julia3\n");
		ft_putstr("                  mandelbrot3\n");
		return (0);
	}
	init(&g);
	write_manual(g);
	if ((mlx_hook(g.w_p, 2, 2, key_press, &g) == 0))
		return (0);
	mlx_hook(g.w_p, 6, 6, mouse_move, &g);
	mlx_hook(g.w_p, 4, 4, mouse_press, &g);
	mlx_loop(g.m_p);
	return (0);
}
