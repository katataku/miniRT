/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:33:34 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/24 16:31:32 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <stdbool.h>
# include <stdio.h>
# include "math.h"
# include "vector3.h"
# include <float.h>

# define H 1001
# define W 1001
# define MAX_INPUT_LINE_LEN 1024
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17 // Exit program key code
# define KEY_ESC 65307

typedef struct s_image {
	void	*mlx_img;
	char	*data_addr;
	int		bits_per_pixel;
	int		bytes_per_line;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_window_info {
	void		*mlx;
	void		*win;
	t_image		*img;
}	t_window_info;

/****************************************************************
 * 複数個出現するオブジェクトのみenumとして定義する。
 * ******/
enum e_object
{
	T_NOTUSE,
	T_SPHERE,
	T_PLANE,
	T_CYLINDER,
};

/****************************************************************
 * 線形リストで、t_objectを持つことで複数オブジェクトのオブジェクト一覧を保持する
 * オブジェクトの種類によって型が違うのでidentifierで区別してからptrをキャストする。
 * ******/
typedef struct s_object {
	enum e_object	identifier;
	void			*ptr;
}	t_object;

typedef struct s_ambient_lightning {
	double		ratio;
	int			color;
}	t_ambient_lightning;

typedef struct s_camera {
	t_vec3		*point;
	t_vec3		*orientation_vector;
	double		fov;
}	t_camera;

typedef struct s_light {
	t_vec3		*point;
	double		ratio;
	int			color;
}	t_light;

typedef struct s_sphere {
	t_vec3		*center;
	double		diameter;
	int			color;
}	t_sphere;

typedef struct s_plane {
	t_vec3		*point;
	t_vec3		*orientation_vector;
	int			color;
}	t_plane;

typedef struct s_cylinder {
	t_vec3		*coordinates;
	t_vec3		*orientation_vector;
	double		cylinder_diameter;
	double		cylinder_height;
	int			color;
}	t_cylinder;

/*
 * 雑にsphereを持たせているが本来はt_listに含まれている
 */
typedef struct s_scene {
	t_ambient_lightning	*ambient_lightning;
	t_camera			*camera;
	t_light				*light;
	t_list				*objects;
	t_object			*object;
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
}	t_scene;

/*
 * ray can represents 𝐬⃗ + t𝐝⃗
 */
typedef struct s_ray {
	t_vec3	*start_vector;
	t_vec3	*direction_vector;
}	t_ray;

#endif
