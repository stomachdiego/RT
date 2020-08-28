/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:49:00 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/27 06:00:51 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_matrix	translation(double x, double y, double z)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = 1;
	m.m[1][1] = 1;
	m.m[2][2] = 1;
	m.m[3][3] = 1;
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return (m);
}

t_matrix	scaling(double x, double y, double z)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	m.m[3][3] = 1;
	return (m);
}

t_matrix	rotation_x(double r)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = 1;
	m.m[1][1] = cos(r);
	m.m[1][2] = -1 * sin(r);
	m.m[2][1] = sin(r);
	m.m[2][2] = cos(r);
	m.m[3][3] = 1;
	return (m);
}

t_matrix	rotation_y(double r)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = cos(r);
	m.m[0][2] = sin(r);
	m.m[1][1] = 1;
	m.m[2][0] = -1 * sin(r);
	m.m[2][2] = cos(r);
	m.m[3][3] = 1;
	return (m);
}

t_matrix	rotation_z(double r)
{
	t_matrix	m;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = cos(r);
	m.m[0][1] = -1 * sin(r);
	m.m[1][0] = sin(r);
	m.m[1][1] = cos(r);
	m.m[2][2] = 1;
	m.m[3][3] = 1;
	return (m);
}

t_matrix	shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y)
{
	t_matrix	m;
	/*int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.m[i][j] = 0;
			j++;
		}
		i++;
	}
	m.m[0][0] = 1;
	m.m[1][1] = 1;
	m.m[2][2] = 1;
	m.m[3][3] = 1;*/
	m = identity_matrix();
	m.m[0][1] = x_y;
	m.m[0][2] = x_z;
	m.m[1][0] = y_x;
	m.m[1][2] = y_z;
	m.m[2][0] = z_x;
	m.m[2][1] = z_y;
	return (m);
}

t_ray	transform(t_ray r, t_matrix m)
{
	t_ray r2;

	r2.o = matrix_mult_v_p(m, r.o);
	r2.d = matrix_mult_v_p(m, r.d);
	return(r2);
}

t_matrix	set_transform(t_matrix s, t_matrix m)
{
	s = matrix_mult(m, s);
	return (s);
}

t_matrix	view_transform(t_vec from, t_vec to, t_vec up)
{
	t_vec		forward;
	t_vec		upn;
	t_vec		left;
	t_vec		true_up;
	t_matrix	orientation;

	forward = normalize(sub(to, from));
	upn = normalize(up);
	left = cross(forward, upn);
	true_up = cross(left, forward);
	orientation = matrix_nul(orientation);
	orientation.m[0][0] = left.c[0];
	orientation.m[0][1] = left.c[1];
	orientation.m[0][2] = left.c[2];
	orientation.m[1][0] = true_up.c[0];
	orientation.m[1][1] = true_up.c[1];
	orientation.m[1][2] = true_up.c[2];
	orientation.m[2][0] = -forward.c[0];
	orientation.m[2][1] = -forward.c[1];
	orientation.m[2][2] = -forward.c[2];
	orientation.m[3][3] = 1;
	return (matrix_mult(orientation,
	translation(-from.c[0], -from.c[1], -from.c[2])));
}

t_matrix	default_view_transf(void)
{
	t_vec	from = set_v_p(0,0,0,1);
	t_vec	to = set_v_p(0,0,-1,1);
	t_vec	up = set_v_p(0,1,0,0);

	t_matrix	t = view_transform(from, to, up);
	return (t);
}

