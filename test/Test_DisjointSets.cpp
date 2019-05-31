#include <graphlib/gl>
#include "gl_test.hpp"

void TestEmptyConstructor () 
{
  GL_TEST_BEGIN("Empty constructor")
  gl::DisjointSets d;
  GL_TEST_END()
}

void TestElementConstructor () 
{
  GL_TEST_BEGIN("Element constructor")
  gl::DisjointSets d(3);
  GL_ASSERT_EQUAL_DESC(d.find(0), 0, "Parent of 0 should be 0")
  GL_ASSERT_EQUAL_DESC(d.find(1), 1, "Parent of 1 should be 1")
  GL_ASSERT_EQUAL_DESC(d.find(2), 2, "Parent of 2 should be 2")
  GL_TEST_CATCH_ERROR(d.find(3);,std::runtime_error,"DisjointSets::find || Element 3 is larger than the max: 2")
  GL_TEST_END()
}

void TestFindAndMerge () 
{
  GL_TEST_BEGIN("Find and merge")
  gl::DisjointSets d(10);
  GL_ASSERT_EQUAL_DESC(d.find(0), 0, "Parent of 0 should be 0")
  GL_ASSERT_EQUAL_DESC(d.find(1), 1, "Parent of 1 should be 1")
  GL_ASSERT_EQUAL_DESC(d.find(2), 2, "Parent of 2 should be 2")
  GL_ASSERT_EQUAL_DESC(d.find(3), 3, "Parent of 3 should be 3")
  GL_ASSERT_EQUAL_DESC(d.find(4), 4, "Parent of 4 should be 4")
  GL_ASSERT_EQUAL_DESC(d.find(5), 5, "Parent of 5 should be 5")

  d.merge(2,5); // equal rank, second element will be root
  GL_ASSERT_EQUAL_DESC(d.find(0), 0, "Parent of 0 should be 0")
  GL_ASSERT_EQUAL_DESC(d.find(1), 1, "Parent of 1 should be 1")
  GL_ASSERT_EQUAL_DESC(d.find(2), 5, "Parent of 2 should be 5")
  GL_ASSERT_EQUAL_DESC(d.find(3), 3, "Parent of 3 should be 3")
  GL_ASSERT_EQUAL_DESC(d.find(4), 4, "Parent of 4 should be 4")
  GL_ASSERT_EQUAL_DESC(d.find(5), 5, "Parent of 5 should be 5")

  d.merge(5,3); // 5 has larger rank than 3, thus set containing 3 will be subset of set 5
  GL_ASSERT_EQUAL_DESC(d.find(0), 0, "Parent of 0 should be 0")
  GL_ASSERT_EQUAL_DESC(d.find(1), 1, "Parent of 1 should be 1")
  GL_ASSERT_EQUAL_DESC(d.find(2), 5, "Parent of 2 should be 5")
  GL_ASSERT_EQUAL_DESC(d.find(3), 5, "Parent of 3 should be 5")
  GL_ASSERT_EQUAL_DESC(d.find(4), 4, "Parent of 4 should be 4")
  GL_ASSERT_EQUAL_DESC(d.find(5), 5, "Parent of 5 should be 5")
  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  TestEmptyConstructor();
  TestElementConstructor();
  TestFindAndMerge();
  return 0;
}
