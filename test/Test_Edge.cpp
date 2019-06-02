#include <graphlib/structures>
#include "gl_test.hpp"

template <class SCALAR>
void TestConstructor () {
  GL_TEST_BEGIN(std::string("Constructor ")+typeid(SCALAR).name())
  gl::Edge<SCALAR> e1;
  GL_ASSERT_EQUAL(e1.source(), 0)
  GL_ASSERT_EQUAL(e1.dest(), 0)
  GL_ASSERT_EQUAL(e1.weight(), SCALAR(0))
  GL_ASSERT_THROW(e1.color() == gl::Color("black"))
  GL_ASSERT_THROW(!e1.exists())
  gl::Edge<SCALAR> e2 (5,7,SCALAR(3),gl::Color("aqua"), true);
  GL_ASSERT_EQUAL(e2.source(), 5)
  GL_ASSERT_EQUAL(e2.dest(), 7)
  GL_ASSERT_EQUAL(e2.weight(), SCALAR(3))
  GL_ASSERT_THROW(e2.color() == gl::Color("aqua"))
  GL_ASSERT_THROW(e2.exists())
  GL_TEST_END()
}

template <class SCALAR>
void TestUpdate () {
  GL_TEST_BEGIN(std::string("Update ")+typeid(SCALAR).name())
  gl::Edge<SCALAR> e2 (2,2,SCALAR(2),gl::Color("red"), false);
  e2.source(5);
  e2.dest(7);
  e2.weight(3);
  e2.color(gl::Color("aqua"));
  e2.exists(true);
  GL_ASSERT_EQUAL(e2.source(), 5)
  GL_ASSERT_EQUAL(e2.dest(), 7)
  GL_ASSERT_EQUAL(e2.weight(), SCALAR(3))
  GL_ASSERT_THROW(e2.color() == gl::Color("aqua"))
  GL_TEST_END()
}

template <class SCALAR>
void TestEqualityOperator () {
  GL_TEST_BEGIN(std::string("Equality Operator ")+typeid(SCALAR).name())
  gl::Edge<SCALAR> e1 (2,2,SCALAR(2),gl::Color("aqua"), true);
  gl::Edge<SCALAR> e2 (2,2,SCALAR(2),gl::Color("aqua"), true);
  GL_ASSERT(e1 == e2, "Equality operator")
  GL_TEST_END()
}
template <class SCALAR>
void TestInequalityOperator () {
  GL_TEST_BEGIN(std::string("Inequality Operator ")+typeid(SCALAR).name())
  gl::Edge<SCALAR> e1;
  gl::Edge<SCALAR> e2 (2,2,SCALAR(2),gl::Color("aqua"), true);
  GL_ASSERT(e1 != e2, "Inequality operator")
  GL_TEST_END()
}
template <class SCALAR>
void TestCopy () {
  GL_TEST_BEGIN(std::string("Copy ")+typeid(SCALAR).name())
  gl::Edge<SCALAR> e1 (5,7,SCALAR(3),gl::Color("aqua"), true);
  gl::Edge<SCALAR> e2 (e1);
  gl::Edge<SCALAR> e3 = e1;
  GL_ASSERT_THROW(e1 == e2)
  GL_ASSERT_THROW(e1 == e3)
  GL_TEST_END()
}
template <class SCALAR>
void TestMove () {
  GL_TEST_BEGIN(std::string("Move ")+typeid(SCALAR).name())
  gl::Edge<SCALAR> e1 (5,7,SCALAR(3),gl::Color("aqua"), true);
  gl::Edge<SCALAR> e1_copy (5,7,SCALAR(3),gl::Color("aqua"), true);
  gl::Edge<SCALAR> e2 (5,7,SCALAR(3),gl::Color("aqua"), true);
  gl::Edge<SCALAR> e2_copy (5,7,SCALAR(3),gl::Color("aqua"), true);
  gl::Edge<SCALAR> e3 (std::move(e1));
  gl::Edge<SCALAR> e4 = std::move(e2);
  GL_ASSERT_THROW(e3 == e1_copy)
  GL_ASSERT_THROW(e4 == e2_copy)
  GL_TEST_END()
}

template <class SCALAR>
void TestWrapper () {
  TestConstructor<SCALAR>();
  TestUpdate<SCALAR>();
  TestEqualityOperator<SCALAR>();
  TestInequalityOperator<SCALAR>();
  TestCopy<SCALAR>();
  TestMove<SCALAR>();
}


int main(int argc, char const *argv[])
{
  TestWrapper<int>();
  TestWrapper<float>();
  TestWrapper<double>();
  return 0;
}
