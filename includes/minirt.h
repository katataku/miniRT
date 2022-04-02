/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:29:44 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/02 17:32:43 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "xlibft.h"

typedef struct	s_image {
	void	*mlx_img;
	char	*data_addr;
	int		bits_per_pixel;
	int		bytes_per_line;
	int		endian;
	int		width;
	int		height;
}	t_image;

#endif
