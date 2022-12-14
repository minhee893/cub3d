/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_render_source.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhale <chanhale@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:11:54 by chanhale          #+#    #+#             */
/*   Updated: 2022/08/13 11:57:56 by chanhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/cub3d.h"

void	init_t_render_source(t_render_source *source)
{
	source->distance = 0;
	source->object = NULL;
	source->object_pos = 0;
	source->render_screen_pos = 0;
}
