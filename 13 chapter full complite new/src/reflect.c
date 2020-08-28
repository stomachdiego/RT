/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 16:24:47 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/27 10:23:34 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_vec	reflect(t_vec in, t_vec normal)
{
	t_vec a;
	t_vec b;

	b = mult(normal, (2 * dot(in, normal)));
	a = sub(in, b);
	return(a);
}

t_color reflected_color(t_world w, t_comps c, int remaining)
{
    t_ray reflect_ray;
    t_color col;
    if (remaining <= 0)
    {
        return (color(0,0,0));
    }
    if (w.obj_ar[c.obj].m->reflective > 0 && w.obj_ar[c.obj].m->reflective <= 1)
    {
        reflect_ray = set_ray(c.over_point, c.reflectv);
        col = color_at(&w, reflect_ray, remaining - 1);
        return (mult_col(col, w.obj_ar[c.obj].m->reflective));
    }
    else
    {
        return (color(0,0,0));
    }
}

t_color	refracted_color(t_world w, t_comps c, int remaining)
{
	double	n_ratio;
	double	cos_i;
	double	sin2_t;
	double	cos_t;
	t_vec	direction;
	t_ray	refract_ray;
	t_color	col;

	if (remaining < 1)
	{
		return (color(0,0,0));
	}
	if (w.obj_ar[c.obj].m->transparency == 0)
	{
		return (color(0,0,0));
	}
	//проверка на полное внутренне отражение
	n_ratio = c.n1 / c.n2;
	cos_i = dot(c.eyev, c.normalv);
//	printf("cos_i = %f\n", cos_i);
	sin2_t = (n_ratio * n_ratio) * (1.0 - (cos_i * cos_i));
	//printf("sin2_t = %f\n", sin2_t);
	if (sin2_t > 1.0)
	{
		return (color(0,0,0));
	}
	cos_t = sqrt(1.0 - sin2_t);
//	printf("cos_t = %f\n", cos_t);
	direction = sub(mult(c.normalv, (n_ratio * cos_i - cos_t)), mult(c.eyev, n_ratio));
	refract_ray = set_ray(c.under_point, direction);
	col = mult_col(color_at(&w, refract_ray, remaining - 1), w.obj_ar[c.obj].m->transparency);
	return (col);
}
