#include <graphlib/structures>
#include "gl_test.hpp"

template <class SCALAR>
void TestConstructor () {
  GL_TEST_BEGIN(std::string("Constructor ")+typeid(SCALAR).name())
  gl::Node<SCALAR> n1;
  GL_ASSERT_EQUAL(n1.id(), 0)
  GL_ASSERT_EQUAL(n1.capacity(), SCALAR(1))
  GL_ASSERT(n1.label() == "", std::string(std::string("\"")+n1.label()+std::string("\" != ")))
  GL_ASSERT_THROW(n1.color() == gl::Color("white"))
  GL_ASSERT_EQUAL(n1.inDegree(), 0)
  GL_ASSERT_EQUAL(n1.outDegree(), 0)
  std::pair<float,float> position1 {0.,0.};
  GL_ASSERT_THROW(n1.position() == position1)
  gl::Node<SCALAR> n2 (4,SCALAR(8),gl::Color("aqua"),"New node",4.3,5.2);
  GL_ASSERT_EQUAL(n2.id(), 4)
  GL_ASSERT_EQUAL(n2.capacity(), SCALAR(8))
  GL_ASSERT(n2.label() == "New node", std::string(n2.label()+std::string(" != New node")))
  GL_ASSERT_THROW(n2.color() == gl::Color("aqua"))
  GL_ASSERT_EQUAL(n2.inDegree(), 0)
  GL_ASSERT_EQUAL(n2.outDegree(), 0)
  std::pair<float,float> position2 {4.3,5.2};
  GL_ASSERT_THROW(n2.position() == position2)
  GL_TEST_END()
}

template <class SCALAR>
void TestUpdate () {
  GL_TEST_BEGIN(std::string("Update ")+typeid(SCALAR).name())
  gl::Node<SCALAR> n2 (2,SCALAR(6),gl::Color("lime"),"bla bla");
  n2.id(4);
  n2.label("New node");
  n2.capacity(SCALAR(8));
  n2.color(gl::Color("aqua"));
  GL_ASSERT_EQUAL(n2.id(), 4)
  GL_ASSERT_EQUAL(n2.capacity(), SCALAR(8))
  GL_ASSERT(n2.label() == "New node", std::string(n2.label()+std::string(" != New node")))
  GL_ASSERT_THROW(n2.color() == gl::Color("aqua"))

  n2.inDegreeIncrement(5);
  n2.outDegreeIncrement(2);
  GL_ASSERT_EQUAL(n2.inDegree(), 5)
  GL_ASSERT_EQUAL(n2.outDegree(), 2)
  n2.inDegreeDecrement(2);
  n2.outDegreeDecrement(1);
  GL_ASSERT_EQUAL(n2.inDegree(), 3)
  GL_ASSERT_EQUAL(n2.outDegree(), 1)
  GL_TEST_CATCH_ERROR(n2.inDegreeDecrement(4);,std::runtime_error,"Node::inDegreeDecrement | Decrement results in negative inDegree")
  GL_TEST_CATCH_ERROR(n2.outDegreeDecrement(4);,std::runtime_error,"Node::outDegreeDecrement | Decrement results in negative outDegree")
  n2.position(std::move(std::make_pair(4.3,5.2)));
  std::pair<float,float> position2 {4.3,5.2};
  GL_ASSERT_THROW(n2.position() == position2)
  GL_TEST_END()
}

template <class SCALAR>
void TestEqualityOperator () {
  GL_TEST_BEGIN(std::string("Equality Operator ")+typeid(SCALAR).name())
  gl::Node<SCALAR> n1 (4,SCALAR(8),gl::Color("aqua"),"New node");
  gl::Node<SCALAR> n2 (4,SCALAR(8),gl::Color("aqua"),"New node");
  GL_ASSERT(n1 == n2, "Equality operator")
  GL_TEST_END()
}
template <class SCALAR>
void TestInequalityOperator () {
  GL_TEST_BEGIN(std::string("Inequality Operator ")+typeid(SCALAR).name())
  gl::Node<SCALAR> n1;
  gl::Node<SCALAR> n2 (4,SCALAR(8),gl::Color("aqua"),"New node");
  GL_ASSERT(n1 != n2, "Inequality operator")
  GL_TEST_END()
}
template <class SCALAR>
void TestCopy () {
  GL_TEST_BEGIN(std::string("Copy ")+typeid(SCALAR).name())
  gl::Node<SCALAR> n1 (4,SCALAR(8),gl::Color("aqua"),"New node");
  gl::Node<SCALAR> n2 (n1);
  gl::Node<SCALAR> n3 = n1;
  GL_ASSERT_THROW(n1 == n2)
  GL_ASSERT_THROW(n1 == n3)
  GL_TEST_END()
}
template <class SCALAR>
void TestMove () {
  GL_TEST_BEGIN(std::string("Move ")+typeid(SCALAR).name())
  gl::Node<SCALAR> n1 (4,SCALAR(8),gl::Color("aqua"),"New node");
  gl::Node<SCALAR> n1_copy (4,SCALAR(8),gl::Color("aqua"),"New node");
  gl::Node<SCALAR> n2 (4,SCALAR(8),gl::Color("aqua"),"New node");
  gl::Node<SCALAR> n2_copy (4,SCALAR(8),gl::Color("aqua"),"New node");
  gl::Node<SCALAR> n3 (std::move(n1));
  gl::Node<SCALAR> n4 = std::move(n2);
  GL_ASSERT_THROW(n3 == n1_copy)
  GL_ASSERT_THROW(n4 == n2_copy)
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
