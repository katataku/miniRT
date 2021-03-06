#include <gtest/gtest.h>

extern "C" {
#include "io.h"
}

class IoTest : public ::testing::Test {
protected:
	static void SetUpTestCase() {
	}
	static void TearDownTestCase() {
	}
	virtual void SetUp() {}
	virtual void TearDown() {
	}
};

static bool	vector_eq(t_vec3 *a, t_vec3 *b)
{
	return (a->x == b->x) && (a->y == b->y) && (a->z == b->z);
}

TEST_F(IoTest, ambient_light) {
	t_scene	*scene;

	scene = (t_scene *)ft_xcalloc(1, sizeof(t_scene));
	read_ambient(scene, ft_xsplit("A 0.2 0,100,200", ' '));
	ASSERT_EQ(scene->ambient_light->ratio, 0.2);
	ASSERT_EQ(scene->ambient_light->color, make_color_from_trgb(255, 0, 100, 200));
	free(scene->ambient_light);
	free(scene);
}

TEST_F(IoTest, camera) {
	t_scene	*scene;

	scene = (t_scene *)ft_xcalloc(1, sizeof(t_scene));
	read_camera(scene, ft_xsplit("C -50,0,20 0,1,1 70", ' '));
	ASSERT_TRUE(vector_eq(scene->camera->point, vector3(-50, 0, 20)));
	ASSERT_TRUE(vector_eq(scene->camera->orientation_vec,vec3_normalize(vector3(0, 1, 1))));
	ASSERT_EQ(scene->camera->fov, 70);
	free(scene->camera);
	free(scene);
}


TEST_F(IoTest, light) {
	t_scene	*scene;

	scene = (t_scene *)ft_xcalloc(1, sizeof(t_scene));
	read_light(scene, ft_xsplit("L -40,0,30 0.7 0,100,200", ' '));
	ASSERT_TRUE(vector_eq(scene->light->point, vector3(-40, 0, 30)));
	ASSERT_EQ(scene->light->ratio, 0.7);
	ASSERT_EQ(scene->light->color, make_color_from_trgb(255, 0, 100, 200));
	free(scene->light);
	free(scene);
}

TEST_F(IoTest, sphere) {
	t_object *object;
	t_sphere *sphere;

	object = read_sphere(ft_xsplit("sp 0,10,20 20 0,100,200", ' '));
	sphere = (t_sphere *)object->ptr;
	ASSERT_EQ(object->type, T_SPHERE);
	ASSERT_TRUE(vector_eq(sphere->center, vector3(0, 10, 20)));
	ASSERT_EQ(sphere->diameter, 20);
	ASSERT_EQ(sphere->color, make_color_from_trgb(255, 0, 100, 200));
	free(object);
}

TEST_F(IoTest, plane) {
	t_object *object;
	t_plane	*plane;

	object = read_plane(ft_xsplit("pl 0,1,2 0,1.0,1.0 0,100,200", ' '));
	plane = (t_plane *)object->ptr;
	ASSERT_EQ(object->type, T_PLANE);
	ASSERT_TRUE(vector_eq(plane->point, vector3(0, 1, 2)));
	ASSERT_TRUE(vector_eq(plane->normal_vec, vec3_normalize(vector3(0, 1.0, 1.0))));
	ASSERT_EQ(plane->color, make_color_from_trgb(255, 0, 100, 200));
	free(object->ptr);
	free(object);
}

TEST_F(IoTest, cylinder) {
	t_object *object;
	t_cylinder	*cylinder;

	object = read_cylinder(ft_xsplit("cy 0.0,1.0,2 0,1,1.0 14.2 21.42 0,100,200", ' '));
	cylinder = (t_cylinder *)object->ptr;
	ASSERT_TRUE(vector_eq(cylinder->point, vector3(0, 1, 2)));
	ASSERT_TRUE(vector_eq(cylinder->orientation_vec,vec3_normalize(vector3(0, 1, 1))));
	ASSERT_EQ(cylinder->radius, 7.1);
	ASSERT_EQ(cylinder->height, 21.42);
	ASSERT_EQ(cylinder->color, make_color_from_trgb(255, 0, 100, 200));
	free(cylinder);
	free(object);
}
