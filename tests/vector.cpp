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

bool	isEqual(t_vector3 *v, float x, float y, float z)
{
	return (v->x == x && v->y == y && v->z == z);
}

TEST_F(VectorTest, vector) {
	t_vector3 *actual = vector3(0.0, 1.0, 9.0);
	ASSERT_TRUE(isEqual(actual, 0.0, 1.0, 9.0));
	free(actual);
}

TEST_F(VectorTest, add) {
	t_vector3 *v1 = vector3(0.0, 1.0, 9.0);
	t_vector3 *v2 = vector3(2.2, 6.0, 1.0);
	t_vector3 *actual = add(v1, v2);
	print(actual);
	ASSERT_TRUE(isEqual(actual, 2.2, 7.0, 10.0));
	free(actual);
}
