#ifndef MATH_UTIL_H
#define MATH_UTIL_H


// 最大最小值
#define MATH_MIN(a, b)            (((a) < (b)) ? (a) : (b))
#define MATH_MAX(a, b)            (((a) > (b)) ? (a) : (b))

// 浮点数比较 是否相等
#define MATH_FLOAT_EQUAL(v1, v2) (abs(v1 - v2) < std::numeric_limits<float>::epsilon())

// 浮点数 是否为0
#define MATH_FLOAT_EQUAL_0(v) (abs(v) < std::numeric_limits<float>::epsilon())


// 度数 ==> 弧度
/**Util macro for conversion from degrees to radians.*/
#define MATH_DEG_TO_RAD(x)        ((x) * 0.0174532925f)
// 弧度 ==> 度数
/**Util macro for conversion from radians to degrees.*/
#define MATH_RAD_TO_DEG(x)        ((x) * 57.29577951f)


/**
 * Util macro for const float such as epsilon, small float and float precision tolerance.
 */
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_EPSILON                0.000001f


#define PI 3.1415926535897932


#endif  // MATH_UTIL_H