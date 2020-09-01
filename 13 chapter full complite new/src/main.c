/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2020/09/01 05:21:19 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int		quit(t_sdl *sdl)
{
	if (sdl->text != NULL)
		SDL_DestroyTexture(sdl->text);
	sdl->text = NULL;
	if (sdl->img != NULL)
		free(sdl->img);
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();

	return(0);
}

int	clear_img(t_sdl *sdl)
{
	if (SDL_SetRenderDrawColor(sdl->ren, 0x00, 0x00, 0x00, 0x00) == -1)
	{
		printf("error");
		return (1);
	}
	if (SDL_RenderClear(sdl->ren) == -1)
	{
		printf("error");
		return (1);
	}
	return (0);
}

int		init(t_sdl *sdl)
{
	int i;

	i = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (sdl->win == NULL)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_SOFTWARE);
	if (sdl->ren == NULL)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->text = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (sdl->text == NULL)
	{
		printf("%s\n", SDL_GetError());
		i = 1;
	}
	sdl->img = malloc(WIN_W * WIN_H * sizeof(int));
	if (sdl->img == NULL)
	{
		write(1, "Can't create texture\n", 21);
		return (1);
	}
	return(i);
}

int		hit(t_x_t x)
{
	int	i;
	int check;
	int	a;
	int	b;

	i = 0;
	check = 0;
	b = 0;
	while (i < x.max_obj)
	{
		if (x.t[i].count > 0 && x.t[i].t >= 0)
		{
			b = 1;
			if (check == 0)
			{
				a = i;
				check++;
			}
			if (x.t[i].t < x.t[a].t)
			{
				a = i;
			}
		}
		i++;
	}
	if (b == 1)
		return (a);
	else
		return (-1); // значит нет пересечений
}

void	alg(t_sdl *sdl, t_world w)
{
	int	x;
	int	y;
	double world_y;
	double	world_x;
	double wall_size = 7;
	double wall_z = 10;
	t_vec ray_org = set_v_p(0,0,-5,1);

	y = 0;
	double pixel_size = wall_size / WIN_H;
	double half = wall_size / 2;
	while (y < WIN_H)
	{
		world_y = half - pixel_size * y;
		x = 0;
		while (x < WIN_W)
		{
			world_x = -half + pixel_size * x;
			t_vec pos = set_v_p(world_x, world_y, wall_z, 1);
			t_ray r = set_ray(ray_org, normalize(sub(pos, ray_org)));
			//raycast(sdl, r, x, y, w);
			x++;
		}
		y++;
	}
}

int		main(int argc, char **argv)
{
	t_sdl		sdl;
	t_world		w;

	if (init(&sdl) != 0)
		quit(&sdl);

	sdl.run = 0;
/*
//WORLD
	//floor
	w.s[0] = set_sphere(0);
	w.s[0].transform = scaling(10,0.01,10);
	w.s[0].m.color = color(1, 0.9, 0.9);
	w.s[0].m.specular = 0;
	//left_wall
	w.s[1] = set_sphere(1);
	w.s[1].transform = matrix_mult(translation(0,0,5), rotation_y(-M_PI / 4));
	w.s[1].transform = matrix_mult(w.s[1].transform, rotation_x(M_PI / 2));
	w.s[1].transform = matrix_mult(w.s[1].transform, scaling(10, 0.01, 10));
	w.s[1].m.color = color(1, 0.9, 0.9);
	w.s[1].m.specular = 0;
	//right_wall
	w.s[2] = set_sphere(2);
	w.s[2].transform = matrix_mult(translation(0,0,5), rotation_y(M_PI / 4));
	w.s[2].transform = matrix_mult(w.s[2].transform, rotation_x(M_PI / 2));
	w.s[2].transform = matrix_mult(w.s[2].transform, scaling(10, 0.01, 10));
	w.s[2].m.color = color(1, 0.9, 0.9);
	w.s[2].m.specular = 0;*/

	//floor
/*	w.pl[0] = set_plane(0);
	w.pl[0].m.color = color(1, 0, 0);
	w.pl[0].m.specular = 0;
	w.pl[0].m.reflective = 0.2;
	//checker_pattern_pl(color(1,1,1), color(0,0,0), &w.pl[0]);
	//w.pl[0].m.p.transform = set_transform(w.pl[0].m.p.transform, translation(0, 0, 0));
	//stripe_pattern_pl(color(1,1,1), color(0,0,0), &w.pl[0]);
	//gradient_pattern_pl(color(1,1,1), color(0,0,0), &w.pl[0]);
	//ring_pattern_pl(color(1,1,1), color(0,0,0), &w.pl[0]);
	//w.pl[0].m.p.transform = set_transform(w.pl[0].m.p.transform, scaling(0.2, 0.2, 0.2));
	//w.pl[0].m.p.transform = set_transform(w.pl[0].m.p.transform, rotation_y(M_PI / 2));

	//задняя стена
	/*w.pl[1] = set_plane(1);
	w.pl[1].transform = matrix_mult(w.pl[1].transform, translation(0, 0, 4));
	w.pl[1].transform = matrix_mult(w.pl[1].transform, rotation_x(M_PI / 2));
	w.pl[1].m.color = color(1, 0.5, 0.5);
	w.pl[1].m.specular = 0;
	//stripe_pattern_pl(color(1,1,1), color(1,0.5,0.5), &w.pl[1]);
	//w.pl[1].m.p.transform = set_transform(w.pl[1].m.p.transform, scaling(0.2, 0.2, 0.2));
	//w.pl[1].m.p.transform = set_transform(w.pl[1].m.p.transform, rotation_y(M_PI / 2));
	//checker_pattern_pl(color(1,1,1), color(1,0.5,0.5), &w.pl[1]);
	//потолок
	w.pl[2] = set_plane(2);
	//w.pl[2].transform = matrix_mult(w.pl[2].transform, rotation_x(M_PI / 2));
	w.pl[2].transform = matrix_mult(w.pl[2].transform, translation(0, 3, 0));
	w.pl[2].m.color = color(0.9, 0.5, 0.9);
	//w.pl[2].m.reflective = 0.1;
	//checker_pattern_pl(color(1,1,1), color(0,0,0), &w.pl[2]);
	//ring_pattern_pl(color(1,1,1), color(1,0,0), &w.pl[2]);
	w.pl[2].m.specular = 0;*/
/*	//middle
	w.s[0] = set_sphere(3);
	w.s[0].transform = translation(-0.5, 1, 0.5);
	w.s[0].m.color = color(0.1, 1, 0.5);
	w.s[0].m.specular = 0.3;
	w.s[0].m.diffuse = 0.7;
	w.s[0].m.reflective = 0.7;
	//gradient_pattern_sp(color(1,1,1), color(0.1,1,0.5), &w.s[0]);
	//w.s[0].m.p.transform = set_transform(w.s[0].m.p.transform, translation(-0.5,0,0));
	//w.s[0].m.p.transform = set_transform(w.s[0].m.p.transform, scaling(2, 1, 1));

	//w.s[0].m.p.transform = set_transform(w.s[0].m.p.transform, translation(-0.5,0,0));
	//w.s[0].m.pattern = 1;
	//w.s[0].m.p = stripe_pattern(color(1,1,1), color(0,0,0));
	//right
	w.s[1] = set_sphere(4);
	w.s[1].transform = matrix_mult(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
	w.s[1].m.color = color(0.5, 1, 0.1);
	w.s[1].m.specular = 0.3;
	w.s[1].m.diffuse = 0.1;
	w.s[1].m.transparency = 0.9;
	w.s[1].m.refractive_index = 1.5;
	//checker_pattern_sp(color(1,1,1), color(0.5,1,0.1), &w.s[1]);
	//left
	w.s[2] = set_sphere(5);
	w.s[2].transform = matrix_mult(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
	w.s[2].m.color = color(1, 0.8, 0.1);
	//w.s[2].m.specular = 0.3;
	w.s[2].m.specular = 1;
	w.s[2].m.shininess = 300;
	w.s[2].m.diffuse = 0.7;
//	ring_pattern_sp(color(1,1,1), color(0,0,0), &w.s[2]);
//	w.s[2].m.p.transform = set_transform(w.s[2].m.p.transform, scaling(0.2, 1, 0.2));
*/
/*	w.cyl[0] = set_cylinder();
	w.cyl[0].closed = 1;
	w.cyl[0].max = 1;
	w.cyl[0].min = 0;
	w.cyl[0].m.color = color (1, 1 ,1);
	w.cyl[0].transform = matrix_mult(w.cyl[0].transform, translation(-2, 1, 0));
	//w.cyl[0].transform = matrix_mult(w.cyl[0].transform, rotation_y (3.14 / 4));
	//w.cyl[0].transform = matrix_mult(w.cyl[0].transform, rotation_x (-3.14 / 4));


	w.cyl[1] = set_cylinder();
	w.cyl[1].m.color = color (0.5, 0.5, 1);
	w.cyl[1].transform = matrix_mult(w.cyl[1].transform, translation(1.5, 0, 0));
	//light
	w.light = point_light(color(1, 1, 1), set_v_p(-10, 2, -10, 1));
	w.s_obj = 0;
	w.pl_obj = 1;
	w.cyl_obj = 2;
	w.max_obj = 6;
	w.ar_count = 0;
	int i = 0;
	while (i < w.pl_obj)
	{
		push_obj((void*)(&w.pl[i]), &normal_at_pl, &intersect_pl, &shade_hit_pl, &w, &w.pl[i].m);
		i++;
	}
	i = 0;
	while (i < w.s_obj)
	{
		push_obj((void*)(&w.s[i]), &normal_at_sp, &intersect_sp, &shade_hit_sp, &w, &w.s[i].m);
		i++;
	}
	i = 0;
	while (i < w.cyl_obj)
	{
		push_obj((void*)(&w.cyl[i]), &normal_at_cyl, &intersect_cyl, &shade_hit_cyl, &w, &w.cyl[i].m);
		i++;
	}
//WORLD

	//camera
	t_camera c = camera(WIN_W, WIN_H, M_PI / 3);
	c.transform = view_transform(set_v_p(0, 1.5, -5, 1), set_v_p(0, 1, 0, 1), set_v_p(0, 1, 0, 0));

	render(&sdl, c, w);

*/





/*
w.cub[0] = set_cube();
t_vec p;
p = set_v_p(1, 0.5, -0.8, 1);

t_vec n;

if (normal_at_cube((void*)&w.cub[0], p, &n) == 1)
{
	printf("# 1\n");
	printf("0 = %f\n", n.c[0]);
	printf("1 = %f\n", n.c[1]);
	printf("2 = %f\n\n", n.c[2]);
}

p = set_v_p(-1, -0.2, 0.9, 1);
if (normal_at_cube((void*)&w.cub[0], p, &n) == 1)
{
	printf("# 2\n");
	printf("0 = %f\n", n.c[0]);
	printf("1 = %f\n", n.c[1]);
	printf("2 = %f\n\n", n.c[2]);
}

p = set_v_p(-0.4, 1, -0.1, 1);
if (normal_at_cube((void*)&w.cub[0], p, &n) == 1)
{
	printf("# 3\n");
	printf("0 = %f\n", n.c[0]);
	printf("1 = %f\n", n.c[1]);
	printf("2 = %f\n\n", n.c[2]);
}

p = set_v_p(0.3, -1, -0.7, 1);
if (normal_at_cube((void*)&w.cub[0], p, &n) == 1)
{
	printf("# 4\n");
	printf("0 = %f\n", n.c[0]);
	printf("1 = %f\n", n.c[1]);
	printf("2 = %f\n\n", n.c[2]);
}

p = set_v_p(-0.6, 0.3, 1, 1);
if (normal_at_cube((void*)&w.cub[0], p, &n) == 1)
{
	printf("# 5\n");
	printf("0 = %f\n", n.c[0]);
	printf("1 = %f\n", n.c[1]);
	printf("2 = %f\n\n", n.c[2]);
}

p = set_v_p(0.4, 0.4, -1, 1);
if (normal_at_cube((void*)&w.cub[0], p, &n) == 1)
{
	printf("# 6\n");
	printf("0 = %f\n", n.c[0]);
	printf("1 = %f\n", n.c[1]);
	printf("2 = %f\n\n", n.c[2]);
}

p = set_v_p(1, 1, 1, 1);
if (normal_at_cube((void*)&w.cub[0], p, &n) == 1)
{
	printf("# 7\n");
	printf("0 = %f\n", n.c[0]);
	printf("1 = %f\n", n.c[1]);
	printf("2 = %f\n\n", n.c[2]);
}

p = set_v_p(-1, -1, -1, 1);
if (normal_at_cube((void*)&w.cub[0], p, &n) == 1)
{
	printf("# 8\n");
	printf("0 = %f\n", n.c[0]);
	printf("1 = %f\n", n.c[1]);
	printf("2 = %f\n\n", n.c[2]);
}
*/

/*
	w.cub[0] = set_cube();
	t_ray r = set_ray(set_v_p(-2, 0, 0, 1), set_v_p(0.2673, 0.5345, 0.8018, 0));
	t_x_t xs;
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#1 +x\n");
	printf("xs max obj %i\n\n", xs.max_obj);

	r = set_ray(set_v_p(0, -2, 0, 1), set_v_p(0.8018, 0.2673, 0.5345, 0));
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#2 -x\n");
	printf("xs max obj %i\n\n", xs.max_obj);

	r = set_ray(set_v_p(0, 0, -2, 1), set_v_p(0.5345, 0.8018, 0.2673, 0));
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#3 +y\n");
	printf("xs max obj %i\n\n", xs.max_obj);

	r = set_ray(set_v_p(2, 0, 2, 1), set_v_p(0, 0, -1, 0));
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#4 -y\n");
	printf("xs max obj %i\n\n", xs.max_obj);

	r = set_ray(set_v_p(0, 2, 2, 1), set_v_p(0, -1, 0, 0));
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#5 +z\n");
	printf("xs max obj %i\n\n", xs.max_obj);

	r = set_ray(set_v_p(2, 2, 0, 1), set_v_p(-1, 0, 0, 0));
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#6 -z\n");
	printf("xs max obj %i\n\n", xs.max_obj);
*/


/*
	w.cub[0] = set_cube();
	t_ray r = set_ray(set_v_p(5, 0.5, 0, 1), set_v_p(-1, 0, 0, 0));
	t_x_t xs;
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#1 +x\n");
	printf("0 = count = %i\n", xs.t[0].count);
	printf("0 = t = %f\n", xs.t[0].t);
	printf("1 = count = %i\n", xs.t[1].count);
	printf("1 = t = %f\n\n", xs.t[1].t);

	r = set_ray(set_v_p(-5, 0.5, 0, 1), set_v_p(1, 0, 0, 0));
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#2 -x\n");
	printf("0 = count = %i\n", xs.t[0].count);
	printf("0 = t = %f\n", xs.t[0].t);
	printf("1 = count = %i\n", xs.t[1].count);
	printf("1 = t = %f\n\n", xs.t[1].t);

	r = set_ray(set_v_p(0.5, 5, 0, 1), set_v_p(0, -1, 0, 0));
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#3 +y\n");
	printf("0 = count = %i\n", xs.t[0].count);
	printf("0 = t = %f\n", xs.t[0].t);
	printf("1 = count = %i\n", xs.t[1].count);
	printf("1 = t = %f\n\n", xs.t[1].t);

	r = set_ray(set_v_p(0.5, -5, 0, 1), set_v_p(0, 1, 0, 0));
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#4 -y\n");
	printf("0 = count = %i\n", xs.t[0].count);
	printf("0 = t = %f\n", xs.t[0].t);
	printf("1 = count = %i\n", xs.t[1].count);
	printf("1 = t = %f\n\n", xs.t[1].t);

	r = set_ray(set_v_p(0.5, 0, 5, 1), set_v_p(0, 0, -1, 0));
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#5 +z\n");
	printf("0 = count = %i\n", xs.t[0].count);
	printf("0 = t = %f\n", xs.t[0].t);
	printf("1 = count = %i\n", xs.t[1].count);
	printf("1 = t = %f\n\n", xs.t[1].t);

	r = set_ray(set_v_p(0.5, 0, -5, 1), set_v_p(0, 0, 1, 0));
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#6 -z\n");
	printf("0 = count = %i\n", xs.t[0].count);
	printf("0 = t = %f\n", xs.t[0].t);
	printf("1 = count = %i\n", xs.t[1].count);
	printf("1 = t = %f\n\n", xs.t[1].t);

	r = set_ray(set_v_p(0, 0.5, 0, 1), set_v_p(0, 0, 1, 0));
	xs.max_obj = 0;
	xs = intersect_cube((void*)&w.cub[0], r, xs, 0);
	printf("#7 inside\n");
	printf("0 = count = %i\n", xs.t[0].count);
	printf("0 = t = %f\n", xs.t[0].t);
	printf("1 = count = %i\n", xs.t[1].count);
	printf("1 = t = %f\n\n", xs.t[1].t);





/*	t_vec p;
	p = set_v_p(1,0,1,1);
	t_matrix a = rotation_x(M_PI/2);
	t_matrix b = scaling(5,5,5);
	t_matrix d = translation(10,5,7);
	t_vec p2;
	t_vec p3;
	t_vec p4;

	p2 = matrix_mult_v_p(a, p);
	p3 = matrix_mult_v_p(b, p2);
	p4 = matrix_mult_v_p(d, p3);

	printf("1 = %f\n", p4.c[0]);
	printf("2 = %f\n", p4.c[1]);
	printf("3 = %f\n", p4.c[2]);*/



/*
w.cyl[0] = set_cylinder();
w.cyl[0].min = 1;
w.cyl[0].max = 2;
w.cyl[0].closed = 1;
t_vec p;
t_vec n;
t_vec d;
t_x_t xs;
t_ray r;

p = set_v_p(0, 3, 0, 1);
d = normalize(set_v_p(0, -1, 0, 0));
r = set_ray(p, d);
xs.max_obj = 0;
xs = intersect_cyl((void*)&w.cyl[0], r, xs, 0);
printf(" # 1\n");
printf("count %i\n", xs.max_obj);

p = set_v_p(0, 3, -2, 1);
d = normalize(set_v_p(0, -1, 2, 0));
r = set_ray(p, d);
xs.max_obj = 0;
xs = intersect_cyl((void*)&w.cyl[0], r, xs, 0);
printf(" # 2\n");
printf("count %i\n", xs.max_obj);

p = set_v_p(0, 4, -2, 1);
d = normalize(set_v_p(0, -1, 1, 0));
r = set_ray(p, d);
xs.max_obj = 0;
xs = intersect_cyl((void*)&w.cyl[0], r, xs, 0);
printf(" # 3\n");
printf("count %i\n", xs.max_obj);

p = set_v_p(0, 0, -2, 1);
d = normalize(set_v_p(0, 1, 2, 0));
r = set_ray(p, d);
xs.max_obj = 0;
xs = intersect_cyl((void*)&w.cyl[0], r, xs, 0);
printf(" # 4\n");
printf("count %i\n", xs.max_obj);

p = set_v_p(0, -1, -2, 1);
d = normalize(set_v_p(0, 1, 1, 0));
r = set_ray(p, d);
xs.max_obj = 0;
xs = intersect_cyl((void*)&w.cyl[0], r, xs, 0);
printf(" # 5\n");
printf("count %i\n", xs.max_obj);
*/
/*
w.cyl[0] = set_cylinder();
w.cyl[0].min = 1;
w.cyl[0].max = 2;
w.cyl[0].closed = 1;
t_vec p;
t_vec n;
t_vec d;
t_x_t xs;
t_ray r;

p = set_v_p(0, 1, 0, 1);
if (normal_at_cyl((void*)&w.cyl[0], p, &n) == 1)
printf("#1\n");
printf("0 = %f\n", n.c[0]);
printf("1 = %f\n", n.c[1]);
printf("2 = %f\n", n.c[2]);

p = set_v_p(0.5, 1, 0, 1);
if (normal_at_cyl((void*)&w.cyl[0], p, &n) == 1)
printf("#2\n");
printf("0 = %f\n", n.c[0]);
printf("1 = %f\n", n.c[1]);
printf("2 = %f\n", n.c[2]);

p = set_v_p(0, 1, 0.5, 1);
if (normal_at_cyl((void*)&w.cyl[0], p, &n) == 1)
printf("#3\n");
printf("0 = %f\n", n.c[0]);
printf("1 = %f\n", n.c[1]);
printf("2 = %f\n", n.c[2]);

p = set_v_p(0, 2, 0, 1);
if (normal_at_cyl((void*)&w.cyl[0], p, &n) == 1)
printf("#4\n");
printf("0 = %f\n", n.c[0]);
printf("1 = %f\n", n.c[1]);
printf("2 = %f\n", n.c[2]);

p = set_v_p(0.5, 2, 0, 1);
if (normal_at_cyl((void*)&w.cyl[0], p, &n) == 1)
printf("#5\n");
printf("0 = %f\n", n.c[0]);
printf("1 = %f\n", n.c[1]);
printf("2 = %f\n", n.c[2]);

p = set_v_p(0, 2, 0.5, 1);
if (normal_at_cyl((void*)&w.cyl[0], p, &n) == 1)
printf("#6\n");
printf("0 = %f\n", n.c[0]);
printf("1 = %f\n", n.c[1]);
printf("2 = %f\n", n.c[2]);
*/


/*
w.cone[0] = set_cone();
t_vec d;
t_ray r;
t_x_t xs;
t_vec o;
d = normalize(set_v_p(0, 0, 1, 0));
o = set_v_p(0, 0, -5, 1);
r = set_ray(o, d);
xs = intersect_cone((void*)&w.cone[0], r, xs, 0);
printf("#1\n");
printf("count %i\n", xs.max_obj);
printf("0 %f\n", xs.t[0].t);
printf("1 = %f\n\n", xs.t[1].t);

xs.max_obj = 0;
d = normalize(set_v_p(1, 1, 1, 0));
o = set_v_p(0, 0, -5, 1);
r = set_ray(o, d);
xs = intersect_cone((void*)&w.cone[0], r, xs, 0);
printf("#2\n");
printf("count %i\n", xs.max_obj);
printf("0 %f\n", xs.t[0].t);
printf("1 = %f\n\n", xs.t[1].t);

xs.max_obj = 0;
d = normalize(set_v_p(-0.5, -1, 1, 0));
o = set_v_p(1, 1, -5, 1);
r = set_ray(o, d);
xs = intersect_cone((void*)&w.cone[0], r, xs, 0);
printf("#3\n");
printf("count %i\n", xs.max_obj);
printf("0 %f\n", xs.t[0].t);
printf("1 = %f\n", xs.t[1].t);

xs.max_obj = 0;
d = normalize(set_v_p(0, 1, 1, 0));
o = set_v_p(0, 0, -1, 1);
r = set_ray(o, d);
xs = intersect_cone((void*)&w.cone[0], r, xs, 0);
printf("#4\n");
printf("count %i\n", xs.max_obj);
printf("0 %f\n", xs.t[0].t);
*/
/*
w.cone[0] = set_cone();
t_vec n;
t_vec p;
p = set_v_p(0,0,0,1);
if (normal_at_cone((void*)&w.cone[0], p, &n) == 1)
{
	printf("#1\n");
	printf("0 = %f\n", n.c[0]);
	printf("1 = %f\n", n.c[1]);
	printf("2 = %f\n\n", n.c[2]);
}

p = set_v_p(1,1,1,1);
if (normal_at_cone((void*)&w.cone[0], p, &n) == 1)
{
	printf("#2\n");
	printf("0 = %f\n", n.c[0]);
	printf("1 = %f\n", n.c[1]);
	printf("2 = %f\n\n", n.c[2]);
}

p = set_v_p(-1,-1,0,1);
if (normal_at_cone((void*)&w.cone[0], p, &n) == 1)
{
	printf("#3\n");
	printf("0 = %f\n", n.c[0]);
	printf("1 = %f\n", n.c[1]);
	printf("2 = %f\n\n", n.c[2]);
}
*/



/*

	w.pl[0] = set_plane(0);
	w.pl[0].m.color = color(1, 0.5, 0.5);
	w.pl[0].m.specular = 0;
	w.pl[0].m.reflective = 0.2;

	w.cone[0] = set_cone();
	w.cone[0].m.color = color(0, 1, 0);
	w.cone[0].transform = matrix_mult(w.cone[0].transform, scaling(0.2, 1, 0.2));
	ring_pattern_cone(color(0,1,0), color(1,0,1), &w.cone[0]);
	w.cone[0].m.p.transform = matrix_mult(w.cone[0].m.p.transform, scaling(0.3, 0.3, 0.3));

	w.cone[1] = set_cone();
	w.cone[1].m.color = color(0, 1, 1);
	w.cone[1].closed = 1;
	w.cone[1].max = 0;
	w.cone[1].min = -1;
	w.cone[1].transform = matrix_mult(w.cone[1].transform, translation(-2, 1, 0));
	gradient_pattern_cone(color(1,1,0), color(0,1,1), &w.cone[1]);
	w.cone[1].m.p.transform = matrix_mult(w.cone[1].m.p.transform, scaling(0.5, 0.5, 0.5));
	//w.cone[1].transform = matrix_mult(w.cone[1].transform, rotation_x(-3.14 / 4));

	w.cone[2] = set_cone();
	w.cone[2].m.color = color(1, 1, 0);
	w.cone[2].closed = 1;
	w.cone[2].max = 1;
	w.cone[2].min = -1;
	w.cone[2].transform = matrix_mult(w.cone[2].transform, translation(2, 1, 0));
	stripe_pattern_cone(color(0,0,0), color(1,1,1), &w.cone[2]);
	w.cone[2].m.p.transform = matrix_mult(w.cone[2].m.p.transform, scaling(0.3, 0.3, 0.3));
	//w.cone[2].transform = matrix_mult(w.cone[2].transform, rotation_x(-3.14 / 4));


	//light
	w.light = point_light(color(1, 1, 1), set_v_p(-10, 2, -10, 1));
	w.pl_obj = 1;
	w.cone_obj = 3;
	w.max_obj = 3;
	w.ar_count = 0;
	int i = 0;
	while (i < w.pl_obj)
	{
		push_obj((void*)(&w.pl[i]), &normal_at_pl, &intersect_pl, &shade_hit_pl, &w, &w.pl[i].m);
		i++;
	}
	i = 0;
	while (i < w.cone_obj)
	{
		push_obj((void*)(&w.cone[i]), &normal_at_cone, &intersect_cone, &shade_hit_cone, &w, &w.cone[i].m);
		i++;
	}
//WORLD

	//camera
	t_camera c = camera(WIN_W, WIN_H, M_PI / 3);
	c.transform = view_transform(set_v_p(0, 1.5, -5, 1), set_v_p(0, 1, 0, 1), set_v_p(0, 1, 0, 0));

	render(&sdl, c, w);

*/

/*
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
t_vec p1 = set_v_p(0, 1, 0, 1);
t_vec p2 = set_v_p(-1, 0, 0, 1);
t_vec p3 = set_v_p(1, 0, 0, 1);
w.trian[0] = set_trian(p1, p2, p3);
w.trian[0].m.color = color (1, 0.75, 0.5);
w.trian[0].transform = matrix_mult(w.trian[0].transform, translation(0, 1.5, 0));
//w.trian[0].transform = matrix_mult(w.trian[0].transform, rotation_x(3.14 / 2));
w.trian[0].transform = matrix_mult(w.trian[0].transform, scaling(1.5, 1.5, 1.5));
w.trian_obj = 1;
w.light = point_light(color(1, 1, 1), set_v_p(-10, 2, -10, 1));
w.ar_count = 0;
int i = 0;
	while (i < w.trian_obj)
	{
		push_obj((void*)(&w.trian[i]), &normal_at_trian, &intersect_trian, &shade_hit_trian, &w, &w.trian[i].m);
		i++;
	}
//camera
	t_camera c = camera(WIN_W, WIN_H, M_PI / 3);
	c.transform = view_transform(set_v_p(0, 1.5, -5, 1), set_v_p(0, 1, 0, 1), set_v_p(0, 1, 0, 0));

	//render(&sdl, c, w);
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

//CH 11//
//
	//floor
	w.pl[0] = set_plane();
	w.pl[0].m.specular = 0;
	w.pl[0].m.reflective = 0.4;
	w.pl[0].transform = matrix_mult(w.pl[0].transform, rotation_y(0.31415));
	checker_pattern_pl(color(0.35, 0.35, 0.35), color(0.65,0.65,0.65), &w.pl[0]);

	//ceiling
	w.pl[1] = set_plane();
	w.pl[1].transform = matrix_mult(w.pl[1].transform, translation(0,5,0));
	w.pl[1].m.color = color(0.8, 0.8, 0.8);
	w.pl[1].m.specular = 0;
	w.pl[1].m.ambient = 0.3;

	// west wall
	w.pl[2] = set_plane();
	w.pl[2].transform = matrix_mult(w.pl[2].transform, translation(-5, 0, 0));
	w.pl[2].transform = matrix_mult(w.pl[2].transform, rotation_z(1.5708));
	w.pl[2].transform = matrix_mult(w.pl[2].transform, rotation_y(1.5708));
	//material def
	stripe_pattern_pl(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[2]);
	w.pl[2].m.p.transform = matrix_mult(w.pl[2].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[2].m.p.transform = matrix_mult(w.pl[2].m.p.transform, rotation_y(1.5708));
	w.pl[2].m.ambient = 0;
	w.pl[2].m.diffuse = 0.4;
	w.pl[2].m.specular = 0;
	w.pl[2].m.reflective = 0.3;

	//east wall
	w.pl[3] = set_plane();
	w.pl[3].transform = matrix_mult(w.pl[3].transform, translation(5, 0, 0));
	w.pl[3].transform = matrix_mult(w.pl[3].transform, rotation_z(1.5708));
	w.pl[3].transform = matrix_mult(w.pl[3].transform, rotation_y(1.5708));
	//material def
	stripe_pattern_pl(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[3]);
	w.pl[3].m.p.transform = matrix_mult(w.pl[3].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[3].m.p.transform = matrix_mult(w.pl[3].m.p.transform, rotation_y(1.5708));
	w.pl[3].m.ambient = 0;
	w.pl[3].m.diffuse = 0.4;
	w.pl[3].m.specular = 0;
	w.pl[3].m.reflective = 0.3;

	//north wall
	w.pl[4] = set_plane();
	w.pl[4].transform = matrix_mult(w.pl[4].transform, translation(0, 0, 5));
	w.pl[4].transform = matrix_mult(w.pl[4].transform, rotation_x(1.5708));
	//material def
	stripe_pattern_pl(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[4]);
	w.pl[4].m.p.transform = matrix_mult(w.pl[4].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[4].m.p.transform = matrix_mult(w.pl[4].m.p.transform, rotation_y(1.5708));
	w.pl[4].m.ambient = 0;
	w.pl[4].m.diffuse = 0.4;
	w.pl[4].m.specular = 0;
	w.pl[4].m.reflective = 0.3;

	//south wall
	w.pl[5] = set_plane();
	w.pl[5].transform = matrix_mult(w.pl[5].transform, translation(0, 0, -5));
	w.pl[5].transform = matrix_mult(w.pl[5].transform, rotation_x(1.5708));
	//material def
	stripe_pattern_pl(color(0.45,0.45,0.45), color(0.55,0.55,0.55), &w.pl[5]);
	w.pl[5].m.p.transform = matrix_mult(w.pl[5].m.p.transform, scaling(0.25, 0.25, 0.25));
	w.pl[5].m.p.transform = matrix_mult(w.pl[5].m.p.transform, rotation_y(1.5708));
	w.pl[5].m.ambient = 0;
	w.pl[5].m.diffuse = 0.4;
	w.pl[5].m.specular = 0;
	w.pl[5].m.reflective = 0.3;


	//background ball
	w.s[0] = set_sphere();
	w.s[0].transform = matrix_mult(w.s[0].transform, translation(4.6, 0.4, 1));
	w.s[0].transform = matrix_mult(w.s[0].transform, scaling(0.4, 0.4, 0.4));
	w.s[0].m.color = (color(0.8, 0.5, 0.3));
	w.s[0].m.shininess = 50;


	//background ball
	w.s[1] = set_sphere();
	w.s[1].transform = matrix_mult(w.s[1].transform, translation(4.7, 0.3, 0.4));
	w.s[1].transform = matrix_mult(w.s[1].transform, scaling(0.3,0.3,0.3));

	w.s[1].m.color = (color(0.9, 0.4, 0.5));
	w.s[1].m.shininess = 50;


	//background ball
	w.s[2] = set_sphere();
	w.s[2].transform = matrix_mult(w.s[2].transform, translation(-1, 0.5, 4.5));
	w.s[2].transform = matrix_mult(w.s[2].transform, scaling(0.5, 0.5, 0.5));
	w.s[2].m.color = (color(0.4, 0.9, 0.6));
	w.s[2].m.shininess = 50;


	//background ball
	w.s[3] = set_sphere();
	w.s[3].transform =  matrix_mult(w.s[3].transform, translation(-1.7, 0.3, 4.7));
	w.s[3].transform = matrix_mult(w.s[3].transform, scaling(0.3 ,0.3, 0.3));

	w.s[3].m.color = (color(0.4, 0.6, 0.9));
	w.s[3].m.shininess = 50;

	//foreground balls

	//red
	w.s[4] = set_sphere();
	w.s[4].transform =  matrix_mult(w.s[4].transform, translation(-0.6, 1, 0.6));
	w.s[4].m.color = (color(1, 0.3, 0.2));
	w.s[4].m.specular = 0.4;
	w.s[4].m.shininess = 5;

	//blue glass
	w.s[5] = set_sphere();
	w.s[5].transform =  matrix_mult(w.s[5].transform, translation(0.6, 0.7, -0.6));
	w.s[5].transform = matrix_mult(w.s[5].transform, scaling(0.7,0.7,0.7));

	w.s[5].m.color = (color(0, 0, 0.2));
	w.s[5].m.ambient = 0;
	w.s[5].m.diffuse = 0.4;
	w.s[5].m.specular = 0.9;
	w.s[5].m.shininess = 300;
	w.s[5].m.reflective = 0.9;
	w.s[5].m.transparency = 0.9;
	w.s[5].m.refractive_index = 1.5;

	//green glass
	w.s[6] = set_sphere();
	w.s[6].transform =  matrix_mult(w.s[6].transform, translation(-0.7, 0.5, -0.8));
	w.s[6].transform = matrix_mult(w.s[6].transform, scaling(0.5,0.5,0.5));

	w.s[6].m.color = (color(0, 0.2, 0));
	w.s[6].m.ambient = 0;
	w.s[6].m.diffuse = 0.4;
	w.s[6].m.specular = 0.9;
	w.s[6].m.shininess = 300;
	w.s[6].m.reflective = 0.9;
	w.s[6].m.transparency = 0.9;
	w.s[6].m.refractive_index = 1.5;

	//light
	w.light = point_light(color(1, 1, 1), set_v_p(-4.9, 4.9, -1, 1));

	w.s_obj = 7;
	w.pl_obj = 6;
	w.max_obj = 13;
	w.ar_count = 0;
	int i = 0;
	while (i < w.pl_obj)
	{
		push_obj((void*)(&w.pl[i]), &normal_at_pl, &intersect_pl, &shade_hit_pl, &w, &w.pl[i].m);
		i++;
	}
	i = 0;
	while (i < w.s_obj)
	{
		push_obj((void*)(&w.s[i]), &normal_at_sp, &intersect_sp, &shade_hit_sp, &w, &w.s[i].m);
		i++;
	}

	t_camera c = camera(WIN_W, WIN_H, 1.152);
	c.transform = view_transform(set_v_p(-2.6, 1.5, -3.9, 1), set_v_p(-0.6, 1, -0.8, 1), set_v_p(0, 1, 0, 0));










	/*
	SDL_UpdateTexture(sdl.text, NULL, sdl.img, WIN_W * (sizeof(int)));
	SDL_RenderClear(sdl.ren);
	SDL_RenderCopy(sdl.ren, sdl.text, NULL, NULL);
	SDL_RenderPresent(sdl.ren);
	*/
	int progress = 0;
	while (sdl.run == 0)
	{
		while (SDL_PollEvent(&sdl.e) != 0)
		{
			if (sdl.e.type == SDL_QUIT)
				sdl.run = 1;
			/*if (sdl.e.type == SDL_KEYDOWN)
				key_press(&m);
			if (sdl.e.type == SDL_MOUSEMOTION)
				mouse_move(&m);*/
			/*if (clear_img(&sdl) != 0)
				sdl.run = 1;
			if (raycast(&sdl) != 0)
				sdl.run = 1;
			if (draw(&sdl) != 0)
				sdl.run = 1;
			SDL_RenderPresent(sdl.ren);*/
		}
		if (progress == 0)
		{
			render(&sdl, c, w);
			progress++;
		}
	}
	quit(&sdl);
	return(0);
}
