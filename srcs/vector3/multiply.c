#include "vector3.h"

t_vec3	*vec3_multiply(t_vec3 *v, double scalar)
{
	t_vec3	*rtv;

	rtv = (t_vec3 *)ft_xcalloc(1, sizeof(t_vec3));
	rtv->x = v->x * scalar;
	rtv->y = v->y * scalar;
	rtv->z = v->z * scalar;
	return (rtv);
}
