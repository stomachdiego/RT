/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:19:19 by aannara           #+#    #+#             */
/*   Updated: 2020/08/27 06:01:07 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_vec	add(t_vec a1, t_vec a2)
{
	t_vec	b;

	b.c[0] = a1.c[0] + a2.c[0];
	b.c[1] = a1.c[1] + a2.c[1];
	b.c[2] = a1.c[2] + a2.c[2];
	b.c[3] = a1.c[3] + a2.c[3];
	return (b);
}

t_vec	sub(t_vec a1, t_vec a2)
{
	t_vec	b;

	b.c[0] = a1.c[0] - a2.c[0];
	b.c[1] = a1.c[1] - a2.c[1];
	b.c[2] = a1.c[2] - a2.c[2];
	b.c[3] = a1.c[3] - a2.c[3];
	return (b);
}

t_vec	neg(t_vec a)
{
	a.c[0] = -a.c[0];
	a.c[1] = -a.c[1];
	a.c[2] = -a.c[2];
	a.c[3] = -a.c[3];
	return (a);
}

t_vec	mult(t_vec a, double b)
{
	a.c[0] = a.c[0] * b;
	a.c[1] = a.c[1] * b;
	a.c[2] = a.c[2] * b;
	a.c[3] = a.c[3] * b;
	return (a);
}

t_vec	divi(t_vec a, double b)
{
	a.c[0] = a.c[0] / b;
	a.c[1] = a.c[1] / b;
	a.c[2] = a.c[2] / b;
	a.c[3] = a.c[3] / b;
	return (a);
}

double	magnitude(t_vec a)
{
	return (sqrt(a.c[0] * a.c[0] + a.c[1] * a.c[1] + a.c[2] * a.c[2] + a.c[3] * a.c[3]));
}

t_vec	normalize(t_vec v)
{
	double mg = magnitude(v);
	v.c[0] = v.c[0] / mg;
	v.c[1] = v.c[1] / mg;
	v.c[2] = v.c[2] / mg;
	v.c[3] = v.c[3] / mg;
	return (v);
}

double	dot(t_vec a, t_vec b)
{
	return (a.c[0] * b.c[0] + a.c[1] * b.c[1] + a.c[2] * b.c[2] + a.c[3] * b.c[3]);
}

t_vec	cross(t_vec a, t_vec b)
{
	return(set_v_p(a.c[1] * b.c[2] - a.c[2] * b.c[1], a.c[2] * b.c[0] - a.c[0] * b.c[2], a.c[0] * b.c[1] - a.c[1] * b.c[0], 0));
}
