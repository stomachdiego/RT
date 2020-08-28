/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:08:48 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/28 13:36:03 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

t_camera    camera(double  hsize, double vsize, double fov)
{
    t_camera    c;
    double       half_view;
    double       aspect;

    c.hsize = hsize;
    c.vsize = vsize;
    c.fov = fov;
    c.transform = identity_matrix();
    half_view = tanf(c.fov / 2);
    aspect = hsize / vsize;
    if (aspect >= 1)
    {
        c.half_width = half_view;
        c.half_height = half_view / aspect;
    }
    else
    {
        c.half_width = half_view * aspect;
        c.half_height = half_view;
    }
    c.pixel_size = (c.half_width * 2) / c.hsize;
    return (c);
}

t_ray   ray_for_pixel(t_camera *camera, int px, int py)
{
    double   xoffset;
    double   yoffset;
    double   world_x;
    double   wolrd_y;
    t_vec   pixel;
    t_vec   origin;
    t_vec   direction;

    xoffset = (px + 0.5) * camera->pixel_size;
    yoffset = (py + 0.5) * camera->pixel_size;
    world_x = camera->half_width - xoffset;
    wolrd_y = camera->half_height - yoffset;

    if (matrix_inverse_test(camera->transform) == 1)
    {
        pixel = matrix_mult_v_p(matrix_inverse(camera->transform), set_v_p(world_x, wolrd_y, -1 , 1));
        origin = matrix_mult_v_p(matrix_inverse(camera->transform), set_v_p(0, 0, 0, 1));
        direction = normalize(sub(pixel, origin));
    }
    else
        printf("error ray_for_pixel\n");
    return (set_ray(origin, direction));
}

#include <pthread.h>
#define THREADS 20

typedef struct		s_treads
{
	t_sdl            *sdl;
    t_camera       *camera;
    t_world         *world;
    int				start;
	int				finish;
}					t_treads;

void    draw(t_treads *treads)
{
    int     x;
    int     y;
    t_ray   r;
    t_color col;
    int remaining = 5;

    y = treads->start;
    while (y < treads->finish)
    {
        x = 0;
        while (x < treads->camera->hsize)
        {
            r = ray_for_pixel(treads->camera, x, y);
            col = color_at(treads->world, r, remaining);
            treads->sdl->img[y * treads->camera->hsize + x] = col_to_int(col);
            x++;
        }

        SDL_UpdateTexture(treads->sdl->text, NULL, treads->sdl->img, WIN_W * (sizeof(int)));
	    SDL_RenderClear(treads->sdl->ren);
	    SDL_RenderCopy(treads->sdl->ren, treads->sdl->text, NULL, NULL);
	    SDL_RenderPresent(treads->sdl->ren);

        y++;
    }
}

void    render(t_sdl *sdl, t_camera camera, t_world world)
{
    int remaining = 5; // повторений рекурсии в отражении
    pthread_t	threads[THREADS];
	t_treads    htreads[THREADS];
	int i = 0;

    while (i < THREADS)
	{
		htreads[i].camera = &camera;
        htreads[i].sdl = sdl;
        htreads[i].world = &world;
		htreads[i].start = i * (camera.hsize / THREADS);
		htreads[i].finish = (i + 1) * (camera.hsize / THREADS);
		if (pthread_create(&threads[i], NULL, (void *)draw, (void *)&htreads[i]))
        {
            printf("error threads\n");
            exit(1);
        }
		i++;
	}
	while (i > 0)
    {
		if (pthread_join(threads[--i], NULL))
		{
            printf("error threads\n");
            exit(1);
        }
        /*
        SDL_UpdateTexture(sdl->text, NULL, sdl->img, WIN_W * (sizeof(int)));
	    SDL_RenderClear(sdl->ren);
	    SDL_RenderCopy(sdl->ren, sdl->text, NULL, NULL);
	    SDL_RenderPresent(sdl->ren);
        */
    }
    /*
    SDL_UpdateTexture(sdl->text, NULL, sdl->img, WIN_W * (sizeof(int)));
	SDL_RenderClear(sdl->ren);
	SDL_RenderCopy(sdl->ren, sdl->text, NULL, NULL);
	SDL_RenderPresent(sdl->ren);
    */
}

/*
void    render(t_sdl *sdl, t_camera camera, t_world world)
{
    int     x;
    int     y;
    t_ray   r;
    t_color col;

    int remaining = 5; // повторений рекурсии в отражении

    y = 0;
    while (y < camera.vsize)
    {
        x = 0;
        while (x < camera.hsize)
        {
            r = ray_for_pixel(camera, x, y);
            col = color_at(world, r, remaining);
            sdl->img[y * camera.hsize + x] = col_to_int(col);
            x++;
        }

		SDL_UpdateTexture(sdl->text, NULL, sdl->img, WIN_W * (sizeof(int)));
		SDL_RenderClear(sdl->ren);
		SDL_RenderCopy(sdl->ren, sdl->text, NULL, NULL);
		SDL_RenderPresent(sdl->ren);

        y++;
    }
}
*/
