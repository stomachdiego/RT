/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:32:12 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/27 05:59:40 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_color	color(double r, double g, double b)
{
	t_color c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	add_col(t_color a1, t_color a2)
{
	t_color	b;

	b.r = a1.r + a2.r;
	b.g = a1.g + a2.g;
	b.b = a1.b + a2.b;
	return (b);
}

t_color	sub_col(t_color a1, t_color a2)
{
	t_color	b;

	b.r = a1.r - a2.r;
	b.g = a1.g - a2.g;
	b.b = a1.b - a2.b;
	return (b);
}

t_color	mult_col(t_color a, double b)
{
	a.r = a.r * b;
	a.g = a.g * b;
	a.b = a.b * b;
	return (a);
}

t_color	hadamard_prod(t_color a1, t_color a2)
{
	t_color	b;

	b.r = a1.r * a2.r;
	b.g = a1.g * a2.g;
	b.b = a1.b * a2.b;
	return (b);
}

int	col_to_int(t_color c)
{
	double	r;
	double	g;
	double	b;

	c = mult_col(c, 255);
	r = c.r;
	g = c.g;
	b = c.b;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return (((int)r << 16) + ((int)g << 8) + (int)b);
}

int	c(double r, double g, double b)
{

	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return (((int)r << 16) + ((int)g << 8) + (int)b);
}
