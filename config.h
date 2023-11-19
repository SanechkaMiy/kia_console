#ifndef _CONFIG_H_
#define _CONFIG_H_

//#define BKZ_PC

/**/
#ifndef BKZ_PC
#define const
#define sin sinf
#define asin asinf
#define cos cosf
#define acos acosf
#define tan tanf
#define atan atanf
#define atan2 atan2f
#define pow powf
#define sqrt sqrtf
#define fabs fabsf
#define fmod fmodf
#define inline __inline

#endif
/**/
#ifdef BKZ_PC
typedef double _double;
#else
typedef float  _double;
#endif

#endif
