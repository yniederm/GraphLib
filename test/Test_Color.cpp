#include <graphlib/gl>
#include "gl_test.hpp"

#include <vector>

void TestEmptyConstructor ()
{
  GL_TEST_BEGIN("Empty Constructor")
  gl::Color c;
  GL_ASSERT_EQUAL_DESC(c.r(),0,"R=0")
  GL_ASSERT_EQUAL_DESC(c.g(),0,"G=0")
  GL_ASSERT_EQUAL_DESC(c.b(),0,"B=0")
  GL_ASSERT_EQUAL_DESC(c.a(),100,"A=100")
  GL_TEST_END()
}

void TestRGBConstructor ()
{
  GL_TEST_BEGIN("RBG Constructor")
  gl::Color c (25,56,123);
  GL_ASSERT_EQUAL_DESC(c.r(),25,"R=25")
  GL_ASSERT_EQUAL_DESC(c.g(),56,"G=56")
  GL_ASSERT_EQUAL_DESC(c.b(),123,"B=123")
  GL_ASSERT_EQUAL_DESC(c.a(),100,"A=100")
  GL_TEST_END()
}

void TestRGBAConstructor ()
{
  GL_TEST_BEGIN("RGBA Constructor")
  gl::Color c (25,56,123,12);
  GL_ASSERT_EQUAL_DESC(c.r(),25,"R=25")
  GL_ASSERT_EQUAL_DESC(c.g(),56,"G=56")
  GL_ASSERT_EQUAL_DESC(c.b(),123,"B=123")
  GL_ASSERT_EQUAL_DESC(c.a(),12,"A=12")
  GL_TEST_END()
}

void TestRGBAConstructorForcedIntoRangeFromAbove ()
{
  GL_TEST_BEGIN("RGBA Constructor forced into range from above")
  gl::Color c (257,300,789,124);
  GL_ASSERT_EQUAL_DESC(c.r(),255,"R=255")
  GL_ASSERT_EQUAL_DESC(c.g(),255,"G=255")
  GL_ASSERT_EQUAL_DESC(c.b(),255,"B=255")
  GL_ASSERT_EQUAL_DESC(c.a(),100,"A=100")
  GL_TEST_END()
}
void TestRGBAConstructorForcedIntoRangeFromBelow ()
{
  GL_TEST_BEGIN("RGBA Constructor forced into range from below")
  gl::Color c (-3,-7,-5,-10);
  GL_ASSERT_EQUAL_DESC(c.r(),0,"R=0")
  GL_ASSERT_EQUAL_DESC(c.g(),0,"G=0")
  GL_ASSERT_EQUAL_DESC(c.b(),0,"B=0")
  GL_ASSERT_EQUAL_DESC(c.a(),0,"A=0")
  GL_TEST_END()
}

void TestDoubleRGBConstructor ()
{
  GL_TEST_BEGIN("Double RBG Constructor")
  gl::Color c (0.1, 0.3, 0.5);
  GL_ASSERT_EQUAL_DESC(c.r(),25,"R=25")
  GL_ASSERT_EQUAL_DESC(c.g(),76,"G=76")
  GL_ASSERT_EQUAL_DESC(c.b(),127,"B=127")
  GL_ASSERT_EQUAL_DESC(c.a(),100,"A=100")
  GL_TEST_END()
}

void TestDoubleRGBAConstructor ()
{
  GL_TEST_BEGIN("Double RBGA Constructor")
  gl::Color c (0.1, 0.3, 0.5, 0.6123);
  GL_ASSERT_EQUAL_DESC(c.r(),25,"R=25")
  GL_ASSERT_EQUAL_DESC(c.g(),76,"G=76")
  GL_ASSERT_EQUAL_DESC(c.b(),127,"B=127")
  GL_ASSERT_EQUAL_DESC(c.a(),61,"A=61")
  GL_TEST_END()
}

void TestHexConstructorRandom ()
{
  GL_TEST_BEGIN("Hex Constructor")
  gl::Color c (0xF23456);
  GL_ASSERT_EQUAL_DESC(c.r(),242,"R=242")
  GL_ASSERT_EQUAL_DESC(c.g(),52,"G=52")
  GL_ASSERT_EQUAL_DESC(c.b(),86,"B=86")
  GL_ASSERT_EQUAL_DESC(c.a(),100,"A=100")
  GL_TEST_END()
}

void TestHexConstructorBlack ()
{
  GL_TEST_BEGIN("Hex Constructor Black")
  gl::Color c (0xFFFFFF);
  GL_ASSERT_EQUAL_DESC(c.r(),255,"R=255")
  GL_ASSERT_EQUAL_DESC(c.g(),255,"G=255")
  GL_ASSERT_EQUAL_DESC(c.b(),255,"B=255")
  GL_ASSERT_EQUAL_DESC(c.a(),100,"A=100")
  GL_TEST_END()
}

void TestHexConstructorWithA ()
{
  GL_TEST_BEGIN("Hex Constructor with Alpha value")
  gl::Color c (0xF23456,0x32);
  GL_ASSERT_EQUAL_DESC(c.r(),242,"R=242")
  GL_ASSERT_EQUAL_DESC(c.g(),52,"G=52")
  GL_ASSERT_EQUAL_DESC(c.b(),86,"B=86")
  GL_ASSERT_EQUAL_DESC(c.a(),50,"A=50")
  GL_TEST_END()
}

void TestHexConstructorColorString ()
{
  GL_TEST_BEGIN("Color string Constructor")
  gl::Color c ("orange");
  GL_ASSERT_EQUAL_DESC(c.r(),237,"R=237")
  GL_ASSERT_EQUAL_DESC(c.g(),145,"G=145")
  GL_ASSERT_EQUAL_DESC(c.b(),33,"B=33")
  GL_ASSERT_EQUAL_DESC(c.a(),100,"A=100")
  GL_TEST_END()
}

void TestHexConstructorInvalidColorString ()
{
  GL_TEST_BEGIN("Invalid color string Constructor")
  gl::Color c ("Forty-Two");
  GL_ASSERT_EQUAL_DESC(c.r(),255,"R=255")
  GL_ASSERT_EQUAL_DESC(c.g(),255,"G=255")
  GL_ASSERT_EQUAL_DESC(c.b(),255,"B=255")
  GL_ASSERT_EQUAL_DESC(c.a(),100,"A=100")
  GL_TEST_END()
}

void TestEqualityOperator ()
{
  GL_TEST_BEGIN("Equality Operator")
  gl::Color c1 (1,2,3,4);
  gl::Color c2 (1,2,3,4);
  GL_ASSERT_THROW(c1==c2)
  GL_TEST_END()
}
void TestInequalityOperator ()
{
  GL_TEST_BEGIN("Inequality Constructor")
  gl::Color c1 (1,2,3,4);
  gl::Color c2 (1,2,3,5);
  GL_ASSERT_THROW(c1!=c2)
  GL_TEST_END()
}

void TestRGBString ()
{
  GL_TEST_BEGIN("RBG String output")
  gl::Color c1 (1,2,3,4);
  GL_ASSERT_EQUAL_STRING(c1.RGB(),"010203")
  gl::Color c2 (0,0,3,4);
  GL_ASSERT_EQUAL_STRING(c2.RGB(),"000003")
  GL_TEST_END()
}

void TestRGBAString ()
{
  GL_TEST_BEGIN("RBGA String output")
  gl::Color c1 (1,2,3,4);
  GL_ASSERT_EQUAL_STRING(c1.RGBA(),"01020304")
  gl::Color c2 (0,0,3,4);
  GL_ASSERT_EQUAL_STRING(c2.RGBA(),"00000304")
  GL_TEST_END()
}

void TestHexInt ()
{
  GL_TEST_BEGIN("Hex Int output")
  gl::Color c1 (1,2,3,4);
  GL_ASSERT_EQUAL(c1.hex(),01020304)
  gl::Color c2 (0,0,3,4);
  GL_ASSERT_EQUAL(c2.hex(),00000304)
  GL_TEST_END()
}

void TestHexUpdate ()
{
  GL_TEST_BEGIN("Hex Update")
  gl::Color c (1,2,3,4);
  c.hex(0x050607);
  GL_ASSERT_EQUAL_DESC(c.r(),5,"R=5")
  GL_ASSERT_EQUAL_DESC(c.g(),6,"G=6")
  GL_ASSERT_EQUAL_DESC(c.b(),7,"B=7")
  GL_ASSERT_EQUAL_DESC(c.a(),4,"A=4")
  GL_TEST_END()
}

void TestHexUpdateWithA ()
{
  GL_TEST_BEGIN("Hex Update with Alpha value")
  gl::Color c (1,2,3,4);
  c.hex(0x050607,0x8);
  GL_ASSERT_EQUAL_DESC(c.r(),5,"R=5")
  GL_ASSERT_EQUAL_DESC(c.g(),6,"G=6")
  GL_ASSERT_EQUAL_DESC(c.b(),7,"B=7")
  GL_ASSERT_EQUAL_DESC(c.a(),8,"A=8")
  GL_TEST_END()
}

void TestDirectUpdate ()
{
  GL_TEST_BEGIN("Direct Update of all values")
  gl::Color c (1,2,3,4);
  c.r(5);
  c.g(6);
  c.b(7);
  c.a(8);
  GL_ASSERT_EQUAL_DESC(c.r(),5,"R=5")
  GL_ASSERT_EQUAL_DESC(c.g(),6,"G=6")
  GL_ASSERT_EQUAL_DESC(c.b(),7,"B=7")
  GL_ASSERT_EQUAL_DESC(c.a(),8,"A=8")
  GL_TEST_END()
}

int main(int argc, char const *argv[])
{
  TestEmptyConstructor();
  TestRGBConstructor();
  TestRGBAConstructor();
  TestRGBAConstructorForcedIntoRangeFromAbove();
  TestRGBAConstructorForcedIntoRangeFromBelow();
  TestDoubleRGBConstructor();
  TestDoubleRGBAConstructor();
  TestHexConstructorRandom();
  TestHexConstructorBlack();
  TestHexConstructorWithA();
  TestHexConstructorColorString();
  TestHexConstructorInvalidColorString();
  TestEqualityOperator();
  TestInequalityOperator();
  TestRGBString();
  TestRGBAString();
  TestHexUpdate();
  TestHexUpdateWithA();
  TestDirectUpdate();
  
  return 0;
}
