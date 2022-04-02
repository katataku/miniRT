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

	t_vector3 *actual;

	virtual void SetUp() {}
	virtual void TearDown() {
	}
};

bool	isEqual(t_vector3 *v, double x, double y, double z)
{
	return (v->x == x && v->y == y && v->z == z);
}

TEST_F(VectorTest, vector) {
	actual = vector3(0.0, 1.0, 9.0);
	ASSERT_TRUE(isEqual(actual, 0.0, 1.0, 9.0));
}
