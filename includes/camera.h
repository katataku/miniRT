/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:18:53 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/31 14:18:54 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "xlibft.h"
# include "define.h"
# include "utils.h"

t_vec3	*calc_camera_ray(t_scene *scene);
t_vec3	*to_screen_vec(t_scene *scene, double x, double y);

#endif
