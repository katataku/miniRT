/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:29:44 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/16 15:24:45 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "xlibft.h"
# include "define.h"


# define H 1001
# define W 1001

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
	double		lighting_ratio;
	int			color;
}	t_ambient_lightning;

typedef struct s_camera {
	t_vec3		*view_point;
	t_vec3		*orientation_vector;
	double		fov;
}	t_camera;

typedef struct s_light {
	t_vec3		*light_point;
	double		brightness_ratio;
	t_vec3		*orientation_vector;
	int			color;
}	t_light;

typedef struct s_sphere {
	t_vec3		*sphere_center;
	double		diameter;
	int			color;
}	t_sphere;

typedef struct s_plane {
	t_vec3		*coordinates;
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

#endif
