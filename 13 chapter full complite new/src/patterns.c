/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 14:28:16 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/27 06:00:15 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void   stripe_pattern_pl(t_color a, t_color b, t_plane *pl)
{
    pl->m.p.a = a;
    pl->m.p.b = b;
    pl->m.p.transform = identity_matrix();
    pl->m.pattern = 1;
    pl->m.pattern_at = &stripe_at_pl;
}

void   stripe_pattern_cyl(t_color a, t_color b, t_cyl *cyl)
{
    cyl->m.p.a = a;
    cyl->m.p.b = b;
    cyl->m.p.transform = identity_matrix();
    cyl->m.pattern = 1;
    cyl->m.pattern_at = &stripe_at_cyl;
}

void   stripe_pattern_trian(t_color a, t_color b, t_trian *trian)
{
    trian->m.p.a = a;
    trian->m.p.b = b;
    trian->m.p.transform = identity_matrix();
    trian->m.pattern = 1;
    trian->m.pattern_at = &stripe_at_trian;
}

void   stripe_pattern_cone(t_color a, t_color b, t_cone *cone)
{
    cone->m.p.a = a;
    cone->m.p.b = b;
    cone->m.p.transform = identity_matrix();
    cone->m.pattern = 1;
    cone->m.pattern_at = &stripe_at_cone;
}

void   stripe_pattern_cube(t_color a, t_color b, t_cube *cb)
{
    cb->m.p.a = a;
    cb->m.p.b = b;
    cb->m.p.transform = identity_matrix();
    cb->m.pattern = 1;
    cb->m.pattern_at = &stripe_at_cube;
}

void   stripe_pattern_sp(t_color a, t_color b, t_sp *s)
{
    s->m.p.a = a;
    s->m.p.b = b;
    s->m.p.transform = identity_matrix();
    s->m.pattern = 1;
    s->m.pattern_at = &stripe_at_sp;
}

void   gradient_pattern_pl(t_color a, t_color b, t_plane *pl)
{
    pl->m.p.a = a;
    pl->m.p.b = b;
    pl->m.p.transform = identity_matrix();
    pl->m.pattern = 1;
    pl->m.pattern_at = &gradient_at_pl;
}

void   gradient_pattern_cyl(t_color a, t_color b, t_cyl *cyl)
{
    cyl->m.p.a = a;
    cyl->m.p.b = b;
    cyl->m.p.transform = identity_matrix();
    cyl->m.pattern = 1;
    cyl->m.pattern_at = &gradient_at_cyl;
}

void   gradient_pattern_trian(t_color a, t_color b, t_trian *trian)
{
    trian->m.p.a = a;
    trian->m.p.b = b;
    trian->m.p.transform = identity_matrix();
    trian->m.pattern = 1;
    trian->m.pattern_at = &gradient_at_trian;
}

void   gradient_pattern_cone(t_color a, t_color b, t_cone *cone)
{
    cone->m.p.a = a;
    cone->m.p.b = b;
    cone->m.p.transform = identity_matrix();
    cone->m.pattern = 1;
    cone->m.pattern_at = &gradient_at_cone;
}

void   gradient_pattern_cube(t_color a, t_color b, t_cube *cb)
{
    cb->m.p.a = a;
    cb->m.p.b = b;
    cb->m.p.transform = identity_matrix();
    cb->m.pattern = 1;
    cb->m.pattern_at = &gradient_at_cube;
}

void   gradient_pattern_sp(t_color a, t_color b, t_sp *s)
{
    s->m.p.a = a;
    s->m.p.b = b;
    s->m.p.transform = identity_matrix();
    s->m.pattern = 1;
    s->m.pattern_at = &gradient_at_sp;
}

void   ring_pattern_pl(t_color a, t_color b, t_plane *pl)
{
    pl->m.p.a = a;
    pl->m.p.b = b;
    pl->m.p.transform = identity_matrix();
    pl->m.pattern = 1;
    pl->m.pattern_at = &ring_at_pl;
}

void   ring_pattern_cyl(t_color a, t_color b, t_cyl *cyl)
{
    cyl->m.p.a = a;
    cyl->m.p.b = b;
    cyl->m.p.transform = identity_matrix();
    cyl->m.pattern = 1;
    cyl->m.pattern_at = &ring_at_cyl;
}

void   ring_pattern_trian(t_color a, t_color b, t_trian *trian)
{
    trian->m.p.a = a;
    trian->m.p.b = b;
    trian->m.p.transform = identity_matrix();
    trian->m.pattern = 1;
    trian->m.pattern_at = &ring_at_trian;
}

void   ring_pattern_cone(t_color a, t_color b, t_cone *cone)
{
    cone->m.p.a = a;
    cone->m.p.b = b;
    cone->m.p.transform = identity_matrix();
    cone->m.pattern = 1;
    cone->m.pattern_at = &ring_at_cone;
}

void   ring_pattern_cube(t_color a, t_color b, t_cube *cb)
{
    cb->m.p.a = a;
    cb->m.p.b = b;
    cb->m.p.transform = identity_matrix();
    cb->m.pattern = 1;
    cb->m.pattern_at = &ring_at_cube;
}

void   ring_pattern_sp(t_color a, t_color b, t_sp *s)
{
    s->m.p.a = a;
    s->m.p.b = b;
    s->m.p.transform = identity_matrix();
    s->m.pattern = 1;
    s->m.pattern_at = &ring_at_sp;
}

void   checker_pattern_pl(t_color a, t_color b, t_plane *pl)
{
    pl->m.p.a = a;
    pl->m.p.b = b;
    pl->m.p.transform = identity_matrix();
    pl->m.pattern = 1;
    pl->m.pattern_at = &checker_at_pl;
}

void   checker_pattern_cyl(t_color a, t_color b, t_cyl *cyl)
{
    cyl->m.p.a = a;
    cyl->m.p.b = b;
    cyl->m.p.transform = identity_matrix();
    cyl->m.pattern = 1;
    cyl->m.pattern_at = &checker_at_cyl;
}

void   checker_pattern_trian(t_color a, t_color b, t_trian *trian)
{
    trian->m.p.a = a;
    trian->m.p.b = b;
    trian->m.p.transform = identity_matrix();
    trian->m.pattern = 1;
    trian->m.pattern_at = &checker_at_trian;
}

void   checker_pattern_cone(t_color a, t_color b, t_cone *cone)
{
    cone->m.p.a = a;
    cone->m.p.b = b;
    cone->m.p.transform = identity_matrix();
    cone->m.pattern = 1;
    cone->m.pattern_at = &checker_at_cone;
}

void   checker_pattern_cube(t_color a, t_color b, t_cube *cb)
{
    cb->m.p.a = a;
    cb->m.p.b = b;
    cb->m.p.transform = identity_matrix();
    cb->m.pattern = 1;
    cb->m.pattern_at = &checker_at_cube;
}

void   checker_pattern_sp(t_color a, t_color b, t_sp *s)
{
    s->m.p.a = a;
    s->m.p.b = b;
    s->m.p.transform = identity_matrix();
    s->m.pattern = 1;
    s->m.pattern_at = &checker_at_sp;
}

double  realmod(double x, double p)
{
    if (x < 0)
        return (fmod((fmod(x, p) + p), p));
    else
        return (fmod(x, p));
}

t_color stripe_at(t_pattern p, t_vec point)
{
    if (realmod(floor(point.c[0]), 2) == 0)
        return (p.a);
    else
        return (p.b);
}
/* //testpattern
t_color stripe_at(t_pattern p, t_vec point)
{
    if (realmod(floor(point.c[0]), 2) == 0)
        return (color(point.c[0], point.c[1], point.c[2]));
    else
        return (color(point.c[0], point.c[1], point.c[2]));
}*/

t_color gradient_at(t_pattern p, t_vec point)
{
    t_color distance;
    double  fraction;

    distance = sub_col(p.b, p.a);
    fraction = point.c[0] - floor(point.c[0]);
    return (add_col(p.a, mult_col(distance, fraction)));
}

t_color ring_at(t_pattern p, t_vec point)
{
    if (realmod(floor(sqrt((point.c[0] * point.c[0]) + (point.c[2] * point.c[2]))), 2) == 0)
        return (p.a);
    else
        return (p.b);
}

t_color checker_at(t_pattern p, t_vec point)
{
    if ((realmod(floor(point.c[0]) + floor(point.c[1]) + floor(point.c[2]), 2)) == 0)
        return (p.a);
    else
        return (p.b);
}
