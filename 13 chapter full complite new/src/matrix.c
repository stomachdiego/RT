/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:50:33 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/27 06:00:10 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int	identic_m_4(t_matrix a, t_matrix b)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (check_eps(a.m[i][j], b.m[i][j]) == 0)
				return (0);
			j++;
		}

		i++;
	}
	return (1);
}

t_matrix	matrix_mult(t_matrix a, t_matrix b)
{
	t_matrix m;
	int r;
	int c;

	r = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			m.m[r][c] = a.m[r][0] * b.m[0][c] + a.m[r][1] * b.m[1][c] + a.m[r][2] * b.m[2][c] + a.m[r][3] * b.m[3][c];
			c++;
		}
		r++;
	}
	return (m);
}

t_vec	matrix_mult_v_p(t_matrix a, t_vec b)
{
	t_vec m;
	int r;
	int c;

	r = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			m.c[r] = a.m[r][0] * b.c[0] + a.m[r][1] * b.c[1] + a.m[r][2] * b.c[2] + a.m[r][3] * b.c[3];
			c++;
		}
		r++;
	}
	return (m);
}

t_matrix	matrix_identity(t_matrix a)
{
	t_matrix m;
	t_matrix b;
	int r;
	int c;

	r = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			b.m[r][c] = 0;
			c++;
		}
		r++;
	}
	b.m[0][0] = 1;
	b.m[1][1] = 1;
	b.m[2][2] = 1;
	b.m[3][3] = 1;
	r = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			m.m[r][c] = a.m[r][0] * b.m[0][c] + a.m[r][1] * b.m[1][c] + a.m[r][2] * b.m[2][c] + a.m[r][3] * b.m[3][c];
			c++;
		}
		r++;
	}
	return (m);
}

t_vec	matrix_identity_v_p(t_vec a)
{
	t_vec m;
	t_matrix b;
	int r;
	int c;

	r = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			b.m[r][c] = 0;
			c++;
		}
		r++;
	}
	b.m[0][0] = 1;
	b.m[1][1] = 1;
	b.m[2][2] = 1;
	b.m[3][3] = 1;
	r = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			m.c[r] = a.c[r] * b.m[0][c] + a.c[r] * b.m[1][c] + a.c[r] * b.m[2][c] + a.c[r] * b.m[3][c];
			c++;
		}
		r++;
	}
	return (m);
}

t_matrix	matrix_transposing(t_matrix a)
{
	t_matrix b;
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			b.m[j][i] = a.m[i][j];
			j++;
		}
		i++;
	}
	return (b);
}

double	matrix_determinant_2(t_matrix m)
{
	double	a;
	double	b;
	double	c;
	double	d;

	a = m.m[0][0];
	b = m.m[0][1];
	c = m.m[1][0];
	d = m.m[1][1];
	return((a * d) - (b * c));
}

t_matrix	matrix_submatrix(t_matrix m, int a, int b, int size)
{
	t_matrix	v;
	int			i;
	int			j;
	int			r;
	int			c;

	i = 0;
	r = 0;
	while (i < size)
	{
		j = 0;
		c = 0;
		if (i != a)
		{
			while (j < size)
			{
				if (j != b)
				{
					v.m[r][c] = m.m[i][j];
					c++;
				}
				j++;
			}
			r++;
		}
		i++;
	}
	return (v);
}

double	matrix_minor(t_matrix m, int a, int b, int size)
{
	double w;

	m = matrix_submatrix(m, a, b, size);
	if (size == 4)
		w = matrix_determinant_3(m);
	else
		w = matrix_determinant_2(m);
	return (w);
}

double	matrix_cofactor(t_matrix m, int a, int b, int size)
{
	int i;
	int j;
	int c;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			c = i + j;
			if (c == 1 || c == 3 || c == 5 || c == 7)
				m.m[i][j] = -m.m[i][j];
			j++;
		}
		i++;
	}
	return (matrix_minor(m, a, b, size));
}

double	matrix_determinant_3(t_matrix m)
{
	double	a;
	double	b;
	double	c;
	double	res;

	a = m.m[0][0];
	b = m.m[0][1];
	c = m.m[0][2];

	res = (a * matrix_cofactor(m, 0, 0, 3)) + (b * matrix_cofactor(m, 0, 1, 3)) + (c * matrix_cofactor(m, 0, 2, 3));
	return(res);
}

double	matrix_determinant_4(t_matrix m)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	res;

	a = m.m[0][0];
	b = m.m[0][1];
	c = m.m[0][2];
	d = m.m[0][3];

	res = (a * matrix_cofactor(m, 0, 0, 4)) + (b * matrix_cofactor(m, 0, 1, 4)) + (c * matrix_cofactor(m, 0, 2, 4)) + (d * matrix_cofactor(m, 0, 3, 4));
	return(res);
}

int	matrix_inverse_test(t_matrix m)
{
	if (matrix_determinant_4(m) == 0)
		return(0);
	return (1);
}

t_matrix	matrix_inverse(t_matrix m)
{
	int r;
	int c;
	double cof;
	t_matrix m2;

	r = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			cof = matrix_cofactor(m, r, c, 4);
			m2.m[c][r] = cof / matrix_determinant_4(m);
			c++;
		}
		r++;
	}
	return (m2);
}

t_matrix	identity_matrix(void)
{
	t_matrix b;
	int r;
	int c;

	r = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			b.m[r][c] = 0;
			c++;
		}
		r++;
	}
	b.m[0][0] = 1;
	b.m[1][1] = 1;
	b.m[2][2] = 1;
	b.m[3][3] = 1;
	return (b);
}

t_matrix	matrix_nul(t_matrix m)
{
	int r;
	int c;

	r = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			m.m[r][c] = 0;
			c++;
		}
		r++;
	}
	return (m);
}
