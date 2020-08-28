/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:31:01 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/27 10:22:33 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_light	point_light(t_color color, t_vec pos)
{
	t_light l;

	l.intensity = color;
	l.pos = pos;
	return (l);
}

t_material	default_material(void)
{
	t_material	m;
	t_color		c = {1,1,1};

	m.color = c;
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	m.reflective = 0;
	m.pattern = 0;
	m.refractive_index = 1;
	m.transparency = 0;
	m.shadow = 1;
	return (m);
}

/*t_color	lighting(t_material m, t_light l, t_vec pos, t_vec eye, t_vec norm_v, int shadow)
{
	t_color	effective_color;
	t_vec	light_v;
	t_color ambient;
	double	light_dot_normal;
	t_color	diffuse;
	t_color specular;
	t_vec	reflect_v;
	double	reflect_dot_eye;
	double	factor;

	if (m.pattern == 1)
		m.color = stripe_at(m.p, pos);

	effective_color = hadamard_prod(m.color, l.intensity);
	light_v = normalize(sub(l.pos, pos));
	ambient = mult_col(effective_color, m.ambient);
	light_dot_normal = dot(light_v, norm_v);
	if (shadow == 0)
	{
		if (light_dot_normal < 0)
		{
			diffuse = color(0,0,0);
			specular = color(0,0,0);
		}
		else
		{
			diffuse = mult_col(mult_col(effective_color, m.diffuse), light_dot_normal);

			reflect_v = reflect(neg(light_v), norm_v);
			reflect_dot_eye = dot(reflect_v, eye);
			if (reflect_dot_eye <= 0)
				specular = color(0,0,0);
			else
			{
				factor = powf(reflect_dot_eye, m.shininess);
				specular = mult_col(mult_col(l.intensity, m.specular), factor);
			}
		}
		return (add_col(add_col(ambient, diffuse), specular));
	}
	else
		return(ambient);
}*/

int	is_shadow(t_world w, t_vec	p)
{
	t_vec	v;
	t_vec	direction;
	double	distance;
	t_ray	r;
	t_x_t	x;
	int		hit_obj;

	v = sub(w.light.pos, p);
	distance = magnitude(v);
	direction = normalize(v);
	r = set_ray(p, direction);
	x = intersect_world(&w, r, x);
	hit_obj = hit(x);
	if (hit_obj != -1 && x.t[hit_obj].t < distance)
	{
		if (w.obj_ar[x.t[hit_obj].obj].m->shadow != 0)
			return (1);
		return (0);
	}
	else
	{
		return (0);
	}
}

t_color	lighting(t_material m, t_world w, t_comps c)
{
	t_color	effective_color;
	t_vec	light_v;
	t_color ambient;
	double	light_dot_normal;
	t_color	diffuse;
	t_color specular;
	t_vec	reflect_v;
	double	reflect_dot_eye;
	double	factor;

	if (m.pattern == 1)
	{
		m.color = (*m.pattern_at)(m.p, w.obj_ar[c.obj].obj, c.over_point);
	}
	effective_color = hadamard_prod(m.color, w.light.intensity);
	light_v = normalize(sub(w.light.pos, c.over_point));
	ambient = mult_col(effective_color, m.ambient);
	light_dot_normal = dot(light_v, c.normalv);
	if (c.shadow == 0)
	{
		if (light_dot_normal < 0)
		{
			diffuse = color(0,0,0);
			specular = color(0,0,0);
		}
		else
		{
			diffuse = mult_col(mult_col(effective_color, m.diffuse), light_dot_normal);

			reflect_v = reflect(neg(light_v), c.normalv);
			reflect_dot_eye = dot(reflect_v, c.eyev);
			if (reflect_dot_eye <= 0)
				specular = color(0,0,0);
			else
			{
				factor = powf(reflect_dot_eye, m.shininess);
				specular = mult_col(mult_col(w.light.intensity, m.specular), factor);
			}
		}
		return (add_col(add_col(ambient, diffuse), specular));
	}
	else
		return(ambient);
}
