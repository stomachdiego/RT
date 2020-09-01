/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:09:18 by sdiego            #+#    #+#             */
/*   Updated: 2020/09/01 05:16:20 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	default_world(t_world *w)
{
	w->ar_count = 0;
	w->light = point_light(color(1,1,1), set_v_p(-10,10,-10,1));
	w->s[0] = set_sphere(0);
	w->s[0].m.color = color(0.8, 1.0, 0.6);
	w->s[0].m.diffuse = 0.7;
	w->s[0].m.specular = 0.2;
//
	//w->s[0].m.ambient = 1;
//
	w->s[1] = set_sphere(1);

	w->s[1].transform = scaling(0.5, 0.5, 0.5);
	w->max_obj = 2;
	int i = 0;
	while (i < w->max_obj)
	{
		push_obj((void*)(&w->s[i]), &normal_at_sp, &intersect_sp, &shade_hit_sp, w, &w->s[i].m);
		i++;
	}

/*
	w->pl[2] = set_plane();
	w->pl[2].m.reflective = 0.5;
	w->pl[2].transform = translation(0, -1, 0);
	push_obj((void*)(&w->pl[2]), &normal_at_pl, &intersect_pl, &shade_hit_pl, w, &w->pl[2].m);
	w->max_obj = 3;
*/
}

t_x_t	set_nul(t_x_t x, int size)
{
	int i = 0;

	while (i < size + size)
	{
		x.t[i].count = 0;
		x.t[i].t = 0;
		x.t[i].obj = 0;
		i++;
	}
	return (x);
}

t_x_t	sortminus(t_x_t x)
{
	int i;
	int j;
	t_x_t newx;

	i = 0;
	j = 0;
	while (i < x.max_obj)
	{
		while (x.t[i].t < 0)
		{
			i++;
		}
		newx.t[j] =x.t[i];
		j++;
		i++;
	}
	newx.max_obj = j;
	return (newx);
}

t_x_t	intersect_world(t_world *w, t_ray r, t_x_t x)
{
	//t_x_t	x_t;
	int		i;
	int		hit_obj;

	i = 0;
	x.max_obj = 0;
	x = set_nul(x, w->ar_count);
	while (i < w->ar_count)
	{
		x = (*w->obj_ar[i].loc_intersect)(w->obj_ar[i].obj, r, x, i);
		//x = intersect_sp(w.s[i], r, x);
		i++;
	}
	bubblesort(x.t, x.max_obj);
	//под вопросом
	//x = sortminus(x);
	//
	return (x);
}

/*t_x_t	t_to_h(t_x x, t_x_t x_t)
{
	int i;
	int	j;

	i = 0;
	while (i < x.max_obj)
	{
		x_t.t[i].t = x.t[i].t1;
		x_t.t[i].count = x.t[i].count;
		x_t.t[i].obj = x.t[i].obj;
		i++;
	}
	j = i;
	i = 0;
	while (j < x.max_obj + x.max_obj)
	{
		x_t.t[j].t = x.t[i].t2;
		x_t.t[j].count = x.t[i].count;
		x_t.t[j].obj = x.t[i].obj;
		i++;
		j++;
	}
	x_t.max_obj = x.max_obj + x.max_obj;
	return (x_t);
}*/

void	bubblesort(t_t_o *num, int size)
{
	int		i;
	int		j;
	t_t_o	min;
	t_t_o	max;

	i = 0;
	while (i < size - 1)
	{
		j = (size - 1);
		while (j > i)
		{
			min = num[j - 1].t < num[j].t ? num[j - 1] : num[j];
			max = num[j - 1].t < num[j].t ? num[j] : num[j - 1];
			num[j - 1] = min;
			num[j] = max;
			j--;
		}
		i++;
	}
}

t_i	intersection(double t, int obj)
{
	t_i	i;

	i.t = t;
	i.obj = obj;
	return(i);
}

t_arr	removenull(t_arr arr)
{
	t_arr res;
	res.size = 0;
	int aa = 0;
	int bb = 0;
	while (aa < arr.size)
	{
		if (arr.arr[aa] != -1)
		{
			res.arr[bb] = arr.arr[aa];
			++bb;
			res.size = bb;
		}
		aa++;
	}
	return (res);
}

t_comps comps_n_calculate(t_world *w, t_i i, t_xs xs, t_comps c)
{
	t_arr containers;
	containers.size = 0;
	int aa = 0;
	while (aa < xs.max_obj)
	{
		t_i curr_i = xs.i[aa];
		if (curr_i.t == i.t && curr_i.obj == i.obj)
		{
			if (containers.size == 0)
			{
				c.n1 = 1.0;
			}
			else
			{
				c.n1 = w->obj_ar[containers.arr[containers.size - 1]].m->refractive_index;
			}
		}
		int	flag = -1;
		int bb = 0;
		while (bb < containers.size)
		{
			if (containers.arr[bb] == curr_i.obj)
			{
				flag = bb;
			}
			bb++;
		}
		if (flag > -1)
		{
			containers.arr[flag] = -1;
			containers = removenull(containers);
		}
		else
		{
			containers.arr[containers.size] = curr_i.obj;
			containers.size = containers.size + 1;
		}
		if (curr_i.t == i.t && curr_i.obj == i.obj)
		{
			if (containers.size == 0)
			{
				c.n2 = 1.0;
			}
			else
			{
				c.n2 = w->obj_ar[containers.arr[containers.size - 1]].m->refractive_index;
			}
			aa = xs.max_obj;
		}
		aa++;
	}
	return (c);
}

t_comps	prepare_computations(t_i i, t_ray r, t_world *w, t_xs xs)
{
	t_comps	c;
	t_vec	normal;

	c.t = i.t;
	c.obj = i.obj;
	c.point = position(r, c.t);
	c.eyev = neg(r.d);
	if ((*w->obj_ar[c.obj].loc_norm)(w->obj_ar[c.obj].obj, c.point, &normal) == 0)
		printf("normal error");
	else
		c.normalv = normal;
	if (dot(c.normalv, c.eyev) < 0)
	{
		c.inside = 1;
		c.normalv = neg(c.normalv);
	}
	else
	{
		c.inside = 0;
	}
	c.over_point = add(c.point, mult(c.normalv, EPSILON));
	c.reflectv = reflect(r.d, c.normalv);
	c.under_point = sub(c.point, mult(c.normalv, EPSILON));

	c = comps_n_calculate(w, i, xs, c);

	//printf("n1 comps = %f\n", c.n1);
	//printf("n2 comps = %f\n\n", c.n2);
	return(c);
}

/*t_color	shade_hit(t_world w, t_comps c)
{
	c.shadow = is_shadow(w, c.over_point);
	t_sp *s;
	s = (t_sp*)w.obj_ar[c.obj].obj;
	return (lighting(s->m, w.light, c.point, c.eyev, c.normalv, c.shadow));
}*/

t_xs	intersections(t_x_t x, t_xs xs) // для прозрачный обьектов список  всех пересечений
{
	int i;

	i = 0;
	while (i < x.max_obj)
	{
		xs.i[i].t = x.t[i].t;
		xs.i[i].obj = x.t[i].obj;
		i++;
	}
	xs.max_obj = x.max_obj;
	return (xs);
}

t_color	color_at(t_world *w, t_ray r, int remaining)
{
	t_x_t	x;
	int hit_obj;
	t_color col;
	t_comps comps;
	t_i i;
	t_xs xs;

	hit_obj = 0;
	x = intersect_world(w, r, x);
	hit_obj = hit(x);
	//printf("hit = %i\n", hit_obj);
	//printf("count = %i\n", x.t[hit_obj].count);
	if (hit_obj != -1)
	{
		i = intersection(x.t[hit_obj].t, x.t[hit_obj].obj);
		xs = intersections(x, xs);
		comps = prepare_computations(i, r, w, xs);
		col = (*w->obj_ar[comps.obj].loc_shade)(*w, comps, remaining);
		//col = shade_hit(w, comps);
	}
	else
	{
		col = color(0,0,0);
	}
	return(col);
}
