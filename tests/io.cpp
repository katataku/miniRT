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

TEST_F(IoTest, ambient_lightning) {
	t_scene	*scene;

	scene = (t_scene *)ft_xcalloc(1, sizeof(t_scene));
	read_ambient(scene, ft_xsplit("A 0.2 0,100,200", ' '));
	ASSERT_EQ(scene->ambient_lightning->lighting_ratio, 0.2);
	ASSERT_EQ(scene->ambient_lightning->color, make_color_from_trgb(255, 0, 100, 200));
	free(scene->ambient_lightning);
	free(scene);
}

TEST_F(IoTest, camera) {
	t_scene	*scene;

	scene = (t_scene *)ft_xcalloc(1, sizeof(t_scene));
	read_camera(scene, ft_xsplit("C -50,0,20 0,1,2 70", ' '));
	ASSERT_TRUE(vector_eq(scene->camera->view_point, vector3(-50, 0, 20)));
	ASSERT_TRUE(vector_eq(scene->camera->orientation_vector, vector3(0, 1, 2)));
	ASSERT_EQ(scene->camera->fov, 70);
	free(scene->camera);
	free(scene);
}


TEST_F(IoTest, light) {
	t_scene	*scene;

	scene = (t_scene *)ft_xcalloc(1, sizeof(t_scene));
	read_light(scene, ft_xsplit("L -40,0,30 0.7 0,100,200", ' '));
	ASSERT_TRUE(vector_eq(scene->light->light_point, vector3(-40, 0, 30)));
	ASSERT_EQ(scene->light->brightness_ratio, 0.7);
	ASSERT_EQ(scene->light->color, make_color_from_trgb(255, 0, 100, 200));
	free(scene->light);
	free(scene);
}

TEST_F(IoTest, sphere) {
	t_scene	*scene;

	scene = (t_scene *)ft_xcalloc(1, sizeof(t_scene));
	read_sphere(scene, ft_xsplit("sp 0,10,20 20 0,100,200", ' '));
	ASSERT_TRUE(vector_eq(scene->sphere->sphere_center, vector3(0, 10, 20)));
	ASSERT_EQ(scene->sphere->diameter, 20);
	ASSERT_EQ(scene->sphere->color, make_color_from_trgb(255, 0, 100, 200));
	free(scene->sphere);
	free(scene);
}

TEST_F(IoTest, plane) {
	t_scene	*scene;

	scene = (t_scene *)ft_xcalloc(1, sizeof(t_scene));
	read_plane(scene, ft_xsplit("pl 0,1,2 0,10.0,20.0 0,100,200", ' '));
	ASSERT_TRUE(vector_eq(scene->plane->coordinates, vector3(0, 1, 2)));
	ASSERT_TRUE(vector_eq(scene->plane->orientation_vector, vector3(0, 10, 20)));
	ASSERT_EQ(scene->plane->color, make_color_from_trgb(255, 0, 100, 200));
	free(scene->plane);
	free(scene);
}

TEST_F(IoTest, cylinder) {
	t_scene	*scene;

	scene = (t_scene *)ft_xcalloc(1, sizeof(t_scene));
	read_cylinder(scene, ft_xsplit("cy 0.0,1.0,2 0,10,20.0 14.2 21.42 0,100,200", ' '));
	ASSERT_TRUE(vector_eq(scene->cylinder->coordinates, vector3(0, 1, 2)));
	ASSERT_TRUE(vector_eq(scene->cylinder->orientation_vector, vector3(0, 10, 20)));
	ASSERT_EQ(scene->cylinder->cylinder_diameter, 14.2);
	ASSERT_EQ(scene->cylinder->cylinder_height, 21.42);
	ASSERT_EQ(scene->cylinder->color, make_color_from_trgb(255, 0, 100, 200));
	free(scene->cylinder);
	free(scene);
}
