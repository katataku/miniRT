#include <gtest/gtest.h>

extern "C" {
#include "utils.h"
}

class UtilsTest : public ::testing::Test {
protected:
	static void SetUpTestCase() {
	}
	static void TearDownTestCase() {
	}
	virtual void SetUp() {}
	virtual void TearDown() {
	}
};

TEST_F(UtilsTest, atod) {
	ASSERT_DOUBLE_EQ(1.5, ft_atod("1.5"));
	ASSERT_DOUBLE_EQ(1.0, ft_atod("1.0"));
	ASSERT_DOUBLE_EQ(0.5, ft_atod("0.5"));
	ASSERT_DOUBLE_EQ(0.0, ft_atod("0.0"));
	ASSERT_DOUBLE_EQ(-1.5, ft_atod("-1.5"));
	ASSERT_DOUBLE_EQ(-1.05, ft_atod("-1.05"));
	ASSERT_DOUBLE_EQ(-1.005, ft_atod("-1.005"));
	ASSERT_DOUBLE_EQ(-0.9, ft_atod("-0.9"));
}
