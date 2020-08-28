/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 14:05:29 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/27 05:59:47 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_cone	set_cone()
{
	t_cone	c;

	c.c = set_v_p(0, 0, 0, 1);
	c.r = 1;
	c.min = -INFINITY;
	c.max = INFINITY;
	c.closed = 0;
	c.transform = identity_matrix();
	c.m = default_material();
	return (c);
}

t_x_t	intersect_cone(void *v_s, t_ray r, t_x_t x, int obj_n)
{
	t_ray	ray2;
	t_cone	*s;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	temp;
	double	t1;
	double	t0;
	double	y0;
	double	y1;

	s = (t_cone*)v_s;

	if (matrix_inverse_test(s->transform) == 1)
	{
		ray2 = transform(r, matrix_inverse(s->transform));

		a = (ray2.d.c[0] * ray2.d.c[0]) - (ray2.d.c[1] * ray2.d.c[1]) + (ray2.d.c[2] * ray2.d.c[2]);
		b = (2 * ray2.o.c[0] * ray2.d.c[0]) - (2 * ray2.o.c[1] * ray2.d.c[1]) + (2 * ray2.o.c[2] * ray2.d.c[2]);
		if (fabs(a) <= EPSILON && fabs(b) <= EPSILON)
		{
			x = intersect_caps_cone(s, ray2, x, obj_n);
			return (x);
		}
		c = (ray2.o.c[0] * ray2.o.c[0]) - (ray2.o.c[1] * ray2.o.c[1]) + (ray2.o.c[2] * ray2.o.c[2]);
		if (fabs(a) <= EPSILON && fabs(b) > EPSILON)
		{
			x.t[x.max_obj].t = -c / (2 * b);
			x.t[x.max_obj].obj = obj_n;
			x.t[x.max_obj].count = 2;
			x.max_obj = x.max_obj + 1;
			x = intersect_caps_cone(s, ray2, x, obj_n);
			return (x);
		}
		disc = (b * b) - (4 * a * c);
		if (disc < 0)
			return (x);
		else
		{
			t0 = ((-b - sqrt(disc)) / (2 * a));
			t1 = ((-b + sqrt(disc)) / (2 * a));
			if (t0 > t1)
			{
				temp = t0;
				t0 = t1;
				t1 = temp;
			}
			y0 = ray2.o.c[1] + t0 * ray2.d.c[1];
			if (s->min < y0 && y0 < s->max)
			{
				x.t[x.max_obj].t = t0;
				x.t[x.max_obj].obj = obj_n;
				x.t[x.max_obj].count = 2;
				x.max_obj = x.max_obj + 1;
			}
			y1 = ray2.o.c[1] + t1 * ray2.d.c[1];
			if (s->min < y1 && y1 < s->max)
			{
				x.t[x.max_obj].t = t1;
				x.t[x.max_obj].obj = obj_n;
				x.t[x.max_obj].count = 2;
				x.max_obj = x.max_obj + 1;
			}
		}
		x = intersect_caps_cone(s, ray2, x, obj_n);
		return (x);
	}
	printf("matrix_inverse_test error in intersect_cone\n");
	return(x);
}

int	check_cap_cone(t_ray r, double t, double y)
{
	double	x;
	double	z;

	x = r.o.c[0] + t * r.d.c[0];
	z = r.o.c[2] + t * r.d.c[2];
	if ((x * x) + (z * z) <= fabs(y))
		return (1);
	return (0);
}

t_x_t	intersect_caps_cone(t_cone *cone, t_ray r, t_x_t x, int obj_n)
{
	double	t;

	if (cone->closed == 0 || fabs(r.d.c[1]) <= EPSILON)
		return (x);
	t = (cone->min - r.o.c[1]) / r.d.c[1];
	if (check_cap_cone(r, t, cone->min) == 1) //проверка нижней крышки
	{
		x.t[x.max_obj].t = t;
		x.t[x.max_obj].obj = obj_n;
		x.t[x.max_obj].count = 2;
		x.max_obj = x.max_obj + 1;
	}
	t = (cone->max - r.o.c[1]) / r.d.c[1];
	if (check_cap_cone(r, t, cone->max) == 1) // проверка верхней крышки
	{
		x.t[x.max_obj].t = t;
		x.t[x.max_obj].obj = obj_n;
		x.t[x.max_obj].count = 2;
		x.max_obj = x.max_obj + 1;
	}
	return (x);
}

int		normal_at_cone(void *v_s, t_vec world_point, t_vec *n)
{
	t_cone	*s;
	t_vec	object_point;
	t_vec   object_normal;
	t_vec	world_normal;
	double	dist;
	double y;

	s = (t_cone*)v_s;
	if (matrix_inverse_test(s->transform) == 1)
	{
		object_point = matrix_mult_v_p(matrix_inverse(s->transform), world_point);
		dist = (object_point.c[0] * object_point.c[0]) + (object_point.c[2] * object_point.c[2]);
		if (dist < 1 && object_point.c[1] >= s->max - EPSILON)
		{
			object_normal = set_v_p(0, 1, 0, 0);
		}
		else if (dist < 1 && object_point.c[1] <= s->min + EPSILON)
		{
			object_normal = set_v_p(0, -1, 0, 0);
		}
		else
		{
			y = sqrt((object_point.c[0] * object_point.c[0]) + (object_point.c[2] * object_point.c[2]));
			if (object_point.c[1] > 0)
				y = -y;
			object_normal = set_v_p(object_point.c[0], y, object_point.c[2], 0);
		}
		world_normal = matrix_mult_v_p(matrix_transposing(matrix_inverse(s->transform)), object_normal);
		world_normal.c[3] = 0;
		*n = normalize(world_normal);
		return (1);
	}
	printf("error normal_at_cyl\n");
	return(0);
}

t_color	shade_hit_cone(t_world w, t_comps c, int remaining)
{
	t_color surface;
	t_color	reflected;
	t_color refracted;
	t_cone	*s;
	double	reflectance;

	s = (t_cone*)w.obj_ar[c.obj].obj;
	c.shadow = is_shadow(w, c.over_point);
	surface = lighting(s->m, w, c);
	reflected = reflected_color(w, c, remaining);
	refracted = refracted_color(w, c, remaining);

	if (s->m.reflective > 0 && s->m.transparency > 0)
	{
		reflectance = schlick(c);
		return (add_col(surface, add_col(mult_col(reflected, reflectance), mult_col(refracted, (1.0 - reflectance)))));
	}
	else
	{
		return (add_col(refracted, add_col(surface, reflected)));
	}
}

t_color	stripe_at_cone(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_cone	*s;

	s = (t_cone*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_cone error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_cone error\n");
	return(stripe_at(p, pattern_point));
}

t_color	gradient_at_cone(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_cone	*s;

	s = (t_cone*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_cone error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_cone error\n");
	return(gradient_at(p, pattern_point));
}

t_color	ring_at_cone(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_cone	*s;

	s = (t_cone*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_cone error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_cone error\n");
	return(ring_at(p, pattern_point));
}

t_color	checker_at_cone(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_cone	*s;

	s = (t_cone*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_cone error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_cone error\n");
	return(checker_at(p, pattern_point));
}

