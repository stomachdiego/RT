/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:41 by sdiego            #+#    #+#             */
/*   Updated: 2020/03/22 16:27:51 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <unistd.h>
# include <SDL2/SDL.h>
# include <math.h>
# include <stdio.h>

# define WIN_W 100
# define WIN_H 100
# define EPSILON 0.00001

typedef struct		s_matrix
{
	double			m[4][4];
}					t_matrix;

typedef struct		s_vec
{
	double			c[4];
}					t_vec;

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;

}					t_color;

typedef struct		s_pattern
{
	t_color			a;
	t_color			b;
	t_matrix		transform;
}					t_pattern;

typedef struct		s_material
{
	t_color			color;
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;
	double			reflective;
	int				pattern;
	t_color			(*pattern_at)(t_pattern p, void *obj, t_vec pos);
	t_pattern		p;

}					t_material;

typedef struct		s_t_h
{
	double			t1;
	double			t2;
	int				obj;
	int				count;

}					t_t_h;

typedef struct		s_t_o
{
	double			t;
	int				obj;
	int				count;

}					t_t_o;

typedef struct		s_camera
{
	int				hsize;
	int				vsize;
	double			fov;
	t_matrix		transform;
	double			half_width;
	double			half_height;
	double			pixel_size;
}					t_camera;

typedef struct		s_x
{
	int				count[20];
	t_t_h			t[20];
	int				max_obj;
}					t_x;

typedef struct		s_x_t
{
	t_t_o			t[40];
	int				max_obj;
}					t_x_t;

typedef struct		s_sp
{
	t_vec			c;
	double			r;
	//t_color			color;
	//int				obj;
	t_matrix		transform;
	t_material		m;
}					t_sp;

typedef struct		s_plane
{
	t_vec			c;
	t_matrix		transform;
	t_material		m;
}					t_plane;

typedef struct		s_i
{
	double			t;
	int				obj;
}					t_i;

typedef struct		s_comps
{
	double			t;
	int				obj;
	t_vec			point;
	t_vec			eyev;
	t_vec			normalv;
	t_vec			reflectv;
	int				inside;
	int				shadow;
	t_vec			over_point;
}					t_comps;

typedef struct		s_light
{
	t_color			intensity;
	t_vec			pos;
}					t_light;

typedef struct		s_ray
{
	t_vec			o;  //Origin
	t_vec			d;	//Direction
}					t_ray;

typedef struct s_world	t_world;
typedef struct s_shape	t_shape;

struct				s_shape
{
	void			*obj;
	int				(*loc_norm)(void *obj, t_vec world_point, t_vec *n);
	t_x_t			(*loc_intersect)(void *obj, t_ray r, t_x_t x, int obj_n);
	t_color			(*loc_shade)(t_world w, t_comps c, int remaining);
	t_material		*m;
};

struct				s_world
{
	t_light			light;
	t_sp			s[10];
	int				s_obj;
	t_plane			pl[10];
	int				pl_obj;
	int				max_obj;
	t_shape			obj_ar[10];
	int				ar_count;
};

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Event		e;
	SDL_Renderer	*ren;
	SDL_Texture		*text;
	int				*img;
	int				run;
}					t_sdl;

int					check_eps(double a, double b);
t_vec				add(t_vec a1, t_vec a2);
t_vec				set_v_p(double a, double b, double c, double d);
t_vec				sub(t_vec a1, t_vec a2);
t_vec				neg(t_vec a);
t_vec				mult(t_vec a, double b);
t_vec				divi(t_vec a, double b);
double				magnitude(t_vec a);
t_vec				normalize(t_vec v);
double				dot(t_vec a, t_vec b);
t_vec				cross(t_vec a, t_vec b);
t_color				color(double r, double g, double b);
t_color				add_col(t_color a1, t_color a2);
t_color				sub_col(t_color a1, t_color a2);
t_color				mult_col(t_color a, double b);
t_color				hadamard_prod(t_color a1, t_color a2);
int					identic_m_4(t_matrix a, t_matrix b);
t_matrix			matrix_mult(t_matrix a, t_matrix b);
t_vec				matrix_mult_v_p(t_matrix a, t_vec b);
t_matrix			matrix_identity(t_matrix a);
t_vec				matrix_identity_v_p(t_vec a);
t_matrix			matrix_transposing(t_matrix a);
double				matrix_determinant_2(t_matrix a);
t_matrix			matrix_submatrix(t_matrix m, int a, int b, int size);
double				matrix_minor(t_matrix m, int a, int b, int size);
double				matrix_cofactor(t_matrix m, int a, int b, int size);
double				matrix_determinant_3(t_matrix m);
double				matrix_determinant_4(t_matrix m);
int					matrix_inverse_test(t_matrix m);
t_matrix			matrix_inverse(t_matrix m);
t_matrix			matrix_nul(t_matrix m);
t_matrix			translation(double x, double y, double z);
t_matrix			scaling(double x, double y, double z);
t_matrix			rotation_x(double r);
t_matrix			rotation_y(double r);
t_matrix			rotation_z(double r);
t_matrix			shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);

t_ray				set_ray(t_vec or, t_vec di);
t_vec				position(t_ray r, double t);

t_sp				set_sphere(int obj);
t_x_t				intersect_sp(void *v_s, t_ray r, t_x_t x, int obj_n);
//t_x	intersect_sp(t_sp s, t_ray r);
//t_xs				intersect_sp(t_sp s, t_ray r);
t_matrix			set_transform(t_matrix s, t_matrix m);

t_ray				transform(t_ray r, t_matrix m);

t_matrix			identity_matrix(void);

void				raycast(t_sdl *sdl, t_ray r, int x, int y, t_world w);
//void	raycast(t_sdl *sdl);

//light

int					normal_at_sp(void *v_s, t_vec world_point, t_vec *n);
t_vec				reflect(t_vec in, t_vec normal);
t_light				point_light(t_color color, t_vec pos);
t_material			default_material(void);
t_color				lighting(t_material m, t_world w, t_comps c);
int					col_to_int(t_color c);
int					c(double r, double g, double b);

//world
void				default_world(t_world *w);
t_x_t	intersect_world(t_world w, t_ray r, t_x_t x);
void				bubblesort(t_t_o *num, int size);
t_i					intersection(double t, int obj);
t_comps				prepare_computations(t_i i, t_ray r, t_world w);
//shade
t_color				shade_hit_sp(t_world w, t_comps c, int remaining);
t_color				color_at(t_world w, t_ray r, int remaining);
int					hit(t_x_t x);

//view transform
t_matrix			view_transform(t_vec from, t_vec to, t_vec up);
t_matrix			default_view_transf(void);

//camera
t_camera			camera(double hsize, double vsize, double fov);
t_ray				ray_for_pixel(t_camera camera, int px, int py);
void				render(t_sdl *sdl, t_camera camera, t_world world);

//shadow
int					is_shadow(t_world w, t_vec	p);
//shape
t_vec				sp_normal_at(t_shape s, t_vec local_point);
void				push_obj(void *obj, int (*loc_norm)(void *, t_vec, t_vec*),
t_x_t (*loc_intersect)(void *, t_ray, t_x_t, int), t_color (*loc_shade)(t_world, t_comps, int), t_world *w, t_material *m);

//plane
int					normal_at_pl(void *v_s, t_vec world_point, t_vec *n);
t_plane				set_plane();
t_x_t				intersect_pl(void *v_s, t_ray r, t_x_t x, int obj_n);
t_color				shade_hit_pl(t_world w, t_comps c, int remaining);

//patterns
void   stripe_pattern_pl(t_color a, t_color b, t_plane *pl);
void   stripe_pattern_sp(t_color a, t_color b, t_sp *s);
t_color stripe_at(t_pattern p, t_vec point);
double  realmod(double x, double p);
t_color	stripe_at_sp(t_pattern p, void *obj, t_vec wolrd_point);
t_color	stripe_at_pl(t_pattern p, void *obj, t_vec wolrd_point);
//void    push_pat(t_color (*pattern_at)(t_pattern , void *, t_vec), t_world *w);
t_color gradient_at(t_pattern p, t_vec point);
t_color	gradient_at_pl(t_pattern p, void *obj, t_vec wolrd_point);
t_color	gradient_at_sp(t_pattern p, void *obj, t_vec wolrd_point);
void   gradient_pattern_sp(t_color a, t_color b, t_sp *s);
void   gradient_pattern_pl(t_color a, t_color b, t_plane *pl);
t_color	ring_at_sp(t_pattern p, void *obj, t_vec wolrd_point);
t_color ring_at(t_pattern p, t_vec point);
t_color	ring_at_pl(t_pattern p, void *obj, t_vec wolrd_point);
void   ring_pattern_sp(t_color a, t_color b, t_sp *s);
void   ring_pattern_pl(t_color a, t_color b, t_plane *pl);
t_color checker_at(t_pattern p, t_vec point);
t_color	checker_at_sp(t_pattern p, void *obj, t_vec wolrd_point);
t_color	checker_at_pl(t_pattern p, void *obj, t_vec wolrd_point);
void   checker_pattern_pl(t_color a, t_color b, t_plane *pl);
void   checker_pattern_sp(t_color a, t_color b, t_sp *s);

//reflect
t_color reflected_color(t_world w, t_comps c, int remaining);

#endif
