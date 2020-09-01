/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:41 by sdiego            #+#    #+#             */
/*   Updated: 2020/09/01 07:41:50 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <unistd.h>
# include <SDL.h>
# include <math.h>
# include <stdio.h>

# define WIN_W 400
# define WIN_H 400
# define EPSILON 0.00001

typedef struct		s_arr
{
	int				size;
	int				arr[120];
//	double			t[40];
}					t_arr;

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
	double			transparency;
	double			refractive_index;
	int				shadow;
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
/*
typedef struct		s_x
{
	int				count[40];
	t_t_h			t[40];
	int				max_obj;
}					t_x;
*/
typedef struct		s_x_t
{
	t_t_o			t[120];
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

typedef struct		s_cyl
{
	t_vec			c;
	double			r;
	double			min;
	double			max;
	int				closed;
	t_matrix		transform;
	t_material		m;
}					t_cyl;

typedef struct		s_cone
{
	t_vec			c;
	double			r;
	double			min;
	double			max;
	int				closed;
	t_matrix		transform;
	t_material		m;
}					t_cone;

typedef struct		s_plane
{
	t_vec			c;
	t_matrix		transform;
	t_material		m;
}					t_plane;

typedef struct		s_cube
{
	t_vec			c;
	t_matrix		transform;
	t_material		m;
}					t_cube;

typedef struct		s_trian
{
	t_vec			p1;
	t_vec			p2;
	t_vec			p3;
	t_vec			e1;
	t_vec			e2;
	t_vec			norm;
	t_material		m;
	t_matrix		transform;
}					t_trian;

typedef struct		s_i
{
	double			t;
	int				obj;
//	int				hit;
}					t_i;

//refraction
typedef struct		s_xs
{
	t_i				i[120];
	int				max_obj;
}					t_xs;
//

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
	t_vec			under_point;
	double			n1;
	double			n2;
}					t_comps;

typedef struct		s_t_minmax
{
	double			min;
	double			max;
}					t_t_minmax;

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
	t_plane			pl[10];
	t_cube			cub[20];
	t_cyl			cyl[10];
	t_cone			cone[10];
	t_trian			trian[10];
	int				trian_obj;
	int				s_obj;
	int				cone_obj;
	int				cyl_obj;
	int				cub_obj;
	int				pl_obj;
	int				max_obj;
	t_shape			obj_ar[30];
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

t_sp				set_sphere();
t_x_t				intersect_sp(void *v_s, t_ray r, t_x_t x, int obj_n);

t_matrix			set_transform(t_matrix s, t_matrix m);

t_ray				transform(t_ray r, t_matrix m);

t_matrix			identity_matrix(void);

void				raycast(t_sdl *sdl, t_ray r, int x, int y, t_world w);


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
t_x_t				intersect_world(t_world *w, t_ray r);
void				bubblesort(t_t_o *num, int size);
t_i					intersection(double t, int obj);
t_comps	prepare_computations(t_i i, t_ray r, t_world *w, t_xs xs);



//shade
t_color				shade_hit_sp(t_world w, t_comps c, int remaining);
t_color				color_at(t_world *w, t_ray r, int remaining);
int					hit(t_x_t x);

//view transform
t_matrix			view_transform(t_vec from, t_vec to, t_vec up);
t_matrix			default_view_transf(void);

//camera
t_camera			camera(double hsize, double vsize, double fov);
t_ray				ray_for_pixel(t_camera *camera, int px, int py);
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

//refract
t_sp	glass_sp(t_sp s);
t_color	refracted_color(t_world w, t_comps c, int remaining);

//Fresnel effect
double	schlick(t_comps c);

//cube
t_cube	set_cube();
t_x_t	intersect_cube(void *v_s, t_ray r, t_x_t x, int obj_n);
double	min(double x, double y, double z);
double	max(double x, double y, double z);
t_t_minmax	check_axis(double origin, double direction, t_t_minmax t);
int		normal_at_cube(void *v_s, t_vec world_point, t_vec *n);
t_color	shade_hit_cube(t_world w, t_comps c, int remaining);
t_color	stripe_at_cube(t_pattern p, void *obj, t_vec wolrd_point);
t_color	gradient_at_cube(t_pattern p, void *obj, t_vec wolrd_point);
t_color	ring_at_cube(t_pattern p, void *obj, t_vec wolrd_point);
t_color	checker_at_cube(t_pattern p, void *obj, t_vec wolrd_point);
void   stripe_pattern_cube(t_color a, t_color b, t_cube *cb);
void   gradient_pattern_cube(t_color a, t_color b, t_cube *cb);
void   ring_pattern_cube(t_color a, t_color b, t_cube *cb);
void   checker_pattern_cube(t_color a, t_color b, t_cube *cb);

//cylinder
t_cyl	set_cylinder();
t_x_t	intersect_cyl(void *v_s, t_ray r, t_x_t x, int obj_n);
int		normal_at_cyl(void *v_s, t_vec world_point, t_vec *n);
t_x_t	intersect_caps(t_cyl *cyl, t_ray r, t_x_t x, int obj_n);
void   stripe_pattern_cyl(t_color a, t_color b, t_cyl *cyl);
void   gradient_pattern_cyl(t_color a, t_color b, t_cyl *cyl);
void   ring_pattern_cyl(t_color a, t_color b, t_cyl *cyl);
void   checker_pattern_cyl(t_color a, t_color b, t_cyl *cyl);
t_color	checker_at_cyl(t_pattern p, void *obj, t_vec wolrd_point);
t_color	ring_at_cyl(t_pattern p, void *obj, t_vec wolrd_point);
t_color	gradient_at_cyl(t_pattern p, void *obj, t_vec wolrd_point);
t_color	stripe_at_cyl(t_pattern p, void *obj, t_vec wolrd_point);
t_color	shade_hit_cyl(t_world w, t_comps c, int remaining);

//cone
t_cone	set_cone();
t_x_t	intersect_cone(void *v_s, t_ray r, t_x_t x, int obj_n);
t_x_t	intersect_caps_cone(t_cone *cone, t_ray r, t_x_t x, int obj_n);
int	check_cap_cone(t_ray r, double t, double y);
int		normal_at_cone(void *v_s, t_vec world_point, t_vec *n);
t_color	shade_hit_cone(t_world w, t_comps c, int remaining);
t_color	stripe_at_cone(t_pattern p, void *obj, t_vec wolrd_point);
t_color	gradient_at_cone(t_pattern p, void *obj, t_vec wolrd_point);
t_color	ring_at_cone(t_pattern p, void *obj, t_vec wolrd_point);
t_color	checker_at_cone(t_pattern p, void *obj, t_vec wolrd_point);
void   stripe_pattern_cone(t_color a, t_color b, t_cone *cone);
void   gradient_pattern_cone(t_color a, t_color b, t_cone *cone);
void   ring_pattern_cone(t_color a, t_color b, t_cone *cone);
void   checker_pattern_cone(t_color a, t_color b, t_cone *cone);

//triangle
t_trian	set_trian(t_vec p1, t_vec p2, t_vec p3);
int		normal_at_trian(void *v_s, t_vec world_point, t_vec *n);
t_x_t	intersect_trian(void *v_s, t_ray r, t_x_t x, int obj_n);
t_color	shade_hit_trian(t_world w, t_comps c, int remaining);
t_color	stripe_at_trian(t_pattern p, void *obj, t_vec wolrd_point);
t_color	gradient_at_trian(t_pattern p, void *obj, t_vec wolrd_point);
t_color	ring_at_trian(t_pattern p, void *obj, t_vec wolrd_point);
t_color	checker_at_trian(t_pattern p, void *obj, t_vec wolrd_point);
void   stripe_pattern_trian(t_color a, t_color b, t_trian *trian);
void   gradient_pattern_trian(t_color a, t_color b, t_trian *trian);
void   ring_pattern_trian(t_color a, t_color b, t_trian *trian);
void   checker_pattern_trian(t_color a, t_color b, t_trian *trian);



#endif
