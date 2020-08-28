/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 16:01:23 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/27 06:00:56 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_trian	set_trian(t_vec p1, t_vec p2, t_vec p3)
{
	t_trian	t;

	t.p1 = p1;
	t.p2 = p2;
	t.p3 = p3;
	t.e1 = sub(p2, p1);
	t.e2 = sub(p3, p1);
	t.norm = normalize(cross(t.e2, t.e1));
	t.m = default_material();
	t.transform = identity_matrix();
	return (t);
}

int		normal_at_trian(void *v_s, t_vec world_point, t_vec *n)
{
	t_trian *s;
	t_vec   object_point;
	t_vec   object_normal;
	t_vec	world_normal;
	s = (t_trian*)v_s;
	if (matrix_inverse_test(s->transform) == 1)
	{
		object_point = matrix_mult_v_p(matrix_inverse(s->transform), world_point);
		object_normal = s->norm;
		world_normal = matrix_mult_v_p(matrix_transposing(matrix_inverse(s->transform)), object_normal);
		world_normal.c[3] = 0;
		*n = normalize(world_normal);
		return (1);
	}
	printf("error normal_at_trian\n");
	return(0);
}

t_x_t	intersect_trian(void *v_s, t_ray r, t_x_t x, int obj_n)
{
	t_ray	ray2;
	t_trian *s;
	t_vec	dir_cross_e2;
	double	det;
	double	f;
	t_vec	p1_to_origin;
	double	u;
	t_vec	origin_cross_e1;
	double	v;


	s = (t_trian*)v_s;

	if (matrix_inverse_test(s->transform) == 1)
	{
		ray2 = transform(r, matrix_inverse(s->transform));
		dir_cross_e2 = cross(ray2.d, s->e2);
		det = dot(s->e1, dir_cross_e2);
		if (fabs(det) < EPSILON)
        {
            return (x);
        }
		f = 1.0 / det;
		p1_to_origin = sub(ray2.o, s->p1);
		u = f * dot(p1_to_origin, dir_cross_e2);
		if (u < 0 || u > 1)
			return (x);
		origin_cross_e1 = cross(p1_to_origin, s->e1);
		v = f * dot(ray2.d, origin_cross_e1);
		if (v < 0 || (u + v) > 1)
			return (x);
        x.t[x.max_obj].t = f * dot(s->e2, origin_cross_e1);
		x.t[x.max_obj].obj = obj_n;
		x.t[x.max_obj].count = 2;
		x.max_obj = x.max_obj + 1;
        return (x);
	}
	printf("matrix_inverse_test error in intersect_trian\n");
	return(x);
}

t_color	shade_hit_trian(t_world w, t_comps c, int remaining)
{
	t_color surface;
	t_color	reflected;
	t_color refracted;
	t_trian	*s;
	double	reflectance;

	s = (t_trian*)w.obj_ar[c.obj].obj;
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

t_color	stripe_at_trian(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_trian	*s;

	s = (t_trian*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_trian error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_trian error\n");
	return(stripe_at(p, pattern_point));
}

t_color	gradient_at_trian(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_trian	*s;

	s = (t_trian*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_trian error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_trian error\n");
	return(gradient_at(p, pattern_point));
}

t_color	ring_at_trian(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_trian	*s;

	s = (t_trian*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_trian error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_trian error\n");
	return(ring_at(p, pattern_point));
}

t_color	checker_at_trian(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_trian	*s;

	s = (t_trian*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_trian error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_trian error\n");
	return(checker_at(p, pattern_point));
}
