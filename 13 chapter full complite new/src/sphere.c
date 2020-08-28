/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:54:30 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/27 06:00:44 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_sp	set_sphere()
{
	t_sp	s;

	s.c = set_v_p(0, 0, 0, 1);
	s.r = 1;
	//s.color = color;
	//s.obj = obj;
	s.transform = identity_matrix();
	s.m = default_material();
	return (s);
}

t_sp	glass_sp(t_sp s)
{
	s.m.transparency = 1;
	s.m.refractive_index = 1.5;
	return (s);
}

t_x_t	intersect_sp(void *v_s, t_ray r, t_x_t x, int obj_n)
{
	double	a;
	double	b;
	double	c;
	t_vec	sp_to_ray;
	double	disc;
	t_ray	ray2;
	t_sp	*s;
	t_t_o	temp;

	s = (t_sp*)v_s;

	if (matrix_inverse_test(s->transform) == 1)
	{
		ray2 = transform(r, matrix_inverse(s->transform));

		sp_to_ray = sub(ray2.o, s->c);

		a = dot(ray2.d, ray2.d);
		b = 2 * dot(ray2.d, sp_to_ray);
		c = dot(sp_to_ray, sp_to_ray) - 1;

		disc = (b * b) - 4 * a * c;

		if (disc < 0)
		{
			//x.max_obj = x.max_obj + 2;
			return (x);
		}
		else
		{
			x.t[x.max_obj].t = ((-b - sqrt(disc)) / (2 * a));
			x.t[x.max_obj].obj = obj_n;
			x.t[x.max_obj].count = 2;
			x.max_obj = x.max_obj + 1;
			x.t[x.max_obj].t = ((-b + sqrt(disc)) / (2 * a));
			x.t[x.max_obj].obj = obj_n;
			x.t[x.max_obj].count = 2;
			x.max_obj = x.max_obj + 1;
			/*if (x.t[x.max_obj - 1].t > x.t[x.max_obj].t)
			{
				temp = x.t[x.max_obj - 1];
				x.t[x.max_obj - 1] = x.t[x.max_obj];
				x.t[x.max_obj] = temp;
			}*/
			//x.max_obj = x.max_obj + 1;
			return (x);
		}
	}
	printf("matrix_inverse_test error in intersect_sp\n");
	//x.max_obj = x.max_obj + 2;
	return(x);
}

int		normal_at_sp(void *v_s, t_vec world_point, t_vec *n)
{
	t_sp	*s;
	t_vec object_point;
	t_vec object_normal;
	t_vec	world_normal;
	s = (t_sp*)v_s;
	if (matrix_inverse_test(s->transform) == 1)
	{
		object_point = matrix_mult_v_p(matrix_inverse(s->transform), world_point);
		object_normal = sub(object_point, set_v_p(0, 0, 0, 1));
		world_normal = matrix_mult_v_p(matrix_transposing(matrix_inverse(s->transform)), object_normal);
		world_normal.c[3] = 0;
		*n = normalize(world_normal);
		return (1);
	}
	printf("error normal_at_sp\n");
	return(0);
}

t_color	shade_hit_sp(t_world w, t_comps c, int remaining)
{
	t_color surface;
	t_color	reflected;
	t_color refracted;
	t_sp	*s;
	double	reflectance;

	s = (t_sp*)w.obj_ar[c.obj].obj;
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

t_color	stripe_at_sp(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_sp	*s;

	s = (t_sp*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_sp error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_sp error\n");
	return(stripe_at(p, pattern_point));
}

t_color	gradient_at_sp(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_sp	*s;

	s = (t_sp*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_sp error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_sp error\n");
	return(gradient_at(p, pattern_point));
}

t_color	ring_at_sp(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_sp	*s;

	s = (t_sp*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_sp error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_sp error\n");
	return(ring_at(p, pattern_point));
}

t_color	checker_at_sp(t_pattern p, void *obj, t_vec wolrd_point)
{
	t_vec	obj_point;
	t_vec	pattern_point;
	t_sp	*s;

	s = (t_sp*)obj;
	if (matrix_inverse_test(s->transform) == 1)
		obj_point = matrix_mult_v_p(matrix_inverse(s->transform), wolrd_point);
	else
		printf("matrix s stripe_at_sp error\n");
	if (matrix_inverse_test(p.transform) == 1)
		pattern_point = matrix_mult_v_p(matrix_inverse(p.transform), obj_point);
	else
		printf("matrix p stripe_at_sp error\n");
	return(checker_at(p, pattern_point));
}
