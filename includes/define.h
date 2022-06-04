/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:33:34 by ahayashi          #+#    #+#             */
/*   Updated: 2022/06/04 22:05:39 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <stdbool.h>
# include <stdio.h>
# include "math.h"
# include "vector3.h"
# include <float.h>

# define FOCUSIN 9
# define FOCUSCHANGEMASK (long)2097152L
# define DESTROYNOTIFY 17
# define STRUCTNOTIFYMASK (long)131072L

# define H 560
# define W 560
# define MAX_INPUT_LINE_LEN 1024
# define KEY_ESC 65307
# define COLOR_BLACK 0xFF000000

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
enum e_t_type
{
	T_T1,
	T_T2,
	T_NOT_CROSS,
};

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
	enum e_object	type;
	void			*ptr;
}	t_object;

typedef struct s_ambient_light {
	double	ratio;
	int		color;
}	t_ambient_light;

typedef struct s_camera {
	t_vec3	*point;
	t_vec3	*orientation_vec;
	double	fov;
}	t_camera;

typedef struct s_light {
	t_vec3	*point;
	double	ratio;
	int		color;
}	t_light;

typedef struct s_sphere {
	t_vec3	*center;
	double	diameter;
	int		color;
}	t_sphere;

typedef struct s_plane {
	t_vec3	*point;
	t_vec3	*normal_vec;
	int		color;
}	t_plane;

typedef struct s_cylinder {
	t_vec3	*point;
	t_vec3	*orientation_vec;
	double	radius;
	double	height;
	int		color;
}	t_cylinder;

/*
 * 雑にsphereを持たせているが本来はt_listに含まれている
 */
typedef struct s_scene {
	t_ambient_light	*ambient_light;
	t_camera		*camera;
	t_light			*light;
	t_list			*objects;
	t_cylinder		*cylinder;
}	t_scene;

/*
 * ray can represents 𝐬⃗ + t𝐝⃗
 */
typedef struct s_ray {
	t_vec3			*start_vec;
	t_vec3			*direction_vec;
}	t_ray;

#endif
