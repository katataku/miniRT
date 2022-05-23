#include <gtest/gtest.h>

extern "C" {
#include "vector3.h"
}

class VectorTest : public ::testing::Test {
protected:
	static void SetUpTestCase() {
	}
	static void TearDownTestCase() {
	}

	virtual void SetUp() {}
	virtual void TearDown() {
	}
};

bool	isEqual(t_vec3 *v, double x, double y, double z)
{
	return (v->x == x && v->y == y && v->z == z);
}

TEST_F(VectorTest, vector) {
	t_vec3 *actual = vector3(0.0, 1.0, 9.0);
	ASSERT_TRUE(isEqual(actual, 0.0, 1.0, 9.0));
	free(actual);
}

TEST_F(VectorTest, add) {
	t_vec3 *v1 = vector3(0.0, 1.0, 9.0);
	t_vec3 *v2 = vector3(2.2, 6.0, 1.0);
	t_vec3 *actual = vec3_add(v1, v2);
	ASSERT_TRUE(isEqual(actual, 2.2, 7.0, 10.0));
	free(v1);
	free(v2);
	free(actual);
}

TEST_F(VectorTest, sub) {
	t_vec3 *v1 = vector3(0.0, 1.0, 9.0);
	t_vec3 *v2 = vector3(2.2, 6.0, 1.0);
	t_vec3 *actual = vec3_sub(v1, v2);
	ASSERT_TRUE(isEqual(actual, -2.2, -5.0, 8.0));
	free(v1);
	free(v2);
	free(actual);
}

TEST_F(VectorTest, multiply) {
	t_vec3 *v1 = vector3(0.0, 1.0, 9.0);
	t_vec3 *actual = vec3_multiply(v1, 2.2);
	ASSERT_TRUE(isEqual(actual, 0.0, 2.2, 19.8));
	free(v1);
	free(actual);
}

TEST_F(VectorTest, inner_product) {
	t_vec3 *v1 = vector3(0.0, 1.0, 9.0);
	t_vec3 *v2 = vector3(2.2, 6.0, 1.0);
	double actual = vec3_inner_product(v1, v2);
	ASSERT_DOUBLE_EQ(15.0, actual);
	free(v1);
	free(v2);
}

TEST_F(VectorTest, inner_product_is_zero) {
	t_vec3 *v1 = vector3(-3.0, 1.2, 3.3);
	t_vec3 *v2 = vector3(2.3, 3.0, 1.0);
	double actual = vec3_inner_product(v1, v2);
	ASSERT_DOUBLE_EQ(0.0, actual);
	free(v1);
	free(v2);
}

TEST_F(VectorTest, norm) {
	t_vec3 *v1 = vector3(1.0, 3.0, 6.0);
	double actual = vec3_norm(v1);
	ASSERT_DOUBLE_EQ(sqrt(46), actual);
	free(v1);
}

TEST_F(VectorTest, cos_of_angles) {
	t_vec3 *v1 = vector3(1.0, 3.0, 6.0);
	t_vec3 *v2 = vector3(-2.2, 1.2, -3.4);
	double actual = cos_of_angles(v1, v2);
	ASSERT_DOUBLE_EQ(-19 / sqrt(46) / sqrt(17.84), actual);
	free(v1);
	free(v2);
}

TEST_F(VectorTest, cos_of_angles_with_same_orientation) {
	t_vec3 *v1 = vector3(1.0, 3.0, 6.0);
	t_vec3 *v2 = vector3(1.0, 3.0, 6.0);
	double actual = cos_of_angles(v1, v2);
	ASSERT_DOUBLE_EQ(1.0, actual);
	free(v1);
	free(v2);
}

TEST_F(VectorTest, outer_product) {
	t_vec3 *v1 = vector3(1.0, 2.0, 3.0);
	t_vec3 *v2 = vector3(4.0, 5.0, 6.0);
	t_vec3 *actual = vec3_outer_product(v1, v2);
	ASSERT_DOUBLE_EQ(-3, actual->x);
	ASSERT_DOUBLE_EQ(6, actual->y);
	ASSERT_DOUBLE_EQ(-3, actual->z);
	free(v1);
	free(v2);
}
