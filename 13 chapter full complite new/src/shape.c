/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:55:38 by sdiego            #+#    #+#             */
/*   Updated: 2020/08/27 06:00:40 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void    push_pat(t_color (*pattern_at)(t_pattern, void *, t_vec), t_world *w)
{
    w->pl[0].m.pattern_at = pattern_at;
}

void    push_obj(void *obj, int (*loc_norm)(void *, t_vec, t_vec*),
t_x_t (*loc_intersect)(void *, t_ray, t_x_t, int), t_color (*loc_shade)(t_world, t_comps, int), t_world *w, t_material *m)
{
    w->obj_ar[w->ar_count].obj = obj;
    w->obj_ar[w->ar_count].loc_norm = loc_norm;
    w->obj_ar[w->ar_count].loc_intersect = loc_intersect;
    w->obj_ar[w->ar_count].loc_shade = loc_shade;
    w->obj_ar[w->ar_count].m = m;
    w->ar_count++;
}











