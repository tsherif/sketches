#ifndef SIMPLE_OPENGL_LOADER
#define SIMPLE_OPENGL_LOADER 1
#define __gl_glcorearb_h_ 1

#ifndef SOL_MAJOR_VERSION
#define SOL_MAJOR_VERSION 1
#endif

#ifndef SOL_MINOR_VERSION
#define SOL_MINOR_VERSION 0
#endif

#define SOL_TEST_VERSION(major, minor) major < SOL_MAJOR_VERSION || major == SOL_MAJOR_VERSION && minor <= SOL_MINOR_VERSION


#ifdef __cplusplus
extern "C" {
#endif

/*
** Copyright 2013-2020 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#endif

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif

/* glcorearb.h is for use with OpenGL core profile implementations.
** It should should be placed in the same directory as gl.h and
** included as <GL/glcorearb.h>.
**
** glcorearb.h includes only APIs in the latest OpenGL core profile
** implementation together with APIs in newer ARB extensions which 
** can be supported by the core profile. It does not, and never will
** include functionality removed from the core profile, such as
** fixed-function vertex and fragment processing.
**
** Do not #include both <GL/glcorearb.h> and either of <GL/gl.h> or
** <GL/glext.h> in the same source file.
*/

/* Generated C header for:
 * API: gl
 * Profile: core
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: glcore
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#ifndef __khrplatform_h_
#define __khrplatform_h_

/*
** Copyright (c) 2008-2018 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

/* Khronos platform-specific types and definitions.
 *
 * The master copy of khrplatform.h is maintained in the Khronos EGL
 * Registry repository at https://github.com/KhronosGroup/EGL-Registry
 * The last semantic modification to khrplatform.h was at commit ID:
 *      67a3e0864c2d75ea5287b9f3d2eb74a745936692
 *
 * Adopters may modify this file to suit their platform. Adopters are
 * encouraged to submit platform specific modifications to the Khronos
 * group so that they can be included in future versions of this file.
 * Please submit changes by filing pull requests or issues on
 * the EGL Registry repository linked above.
 *
 *
 * See the Implementer's Guidelines for information about where this file
 * should be located on your system and for more details of its use:
 *    http://www.khronos.org/registry/implementers_guide.pdf
 *
 * This file should be included as
 *        #include <KHR/khrplatform.h>
 * by Khronos client API header files that use its types and defines.
 *
 * The types in khrplatform.h should only be used to define API-specific types.
 *
 * Types defined in khrplatform.h:
 *    khronos_int8_t              signed   8  bit
 *    khronos_uint8_t             unsigned 8  bit
 *    khronos_int16_t             signed   16 bit
 *    khronos_uint16_t            unsigned 16 bit
 *    khronos_int32_t             signed   32 bit
 *    khronos_uint32_t            unsigned 32 bit
 *    khronos_int64_t             signed   64 bit
 *    khronos_uint64_t            unsigned 64 bit
 *    khronos_intptr_t            signed   same number of bits as a pointer
 *    khronos_uintptr_t           unsigned same number of bits as a pointer
 *    khronos_ssize_t             signed   size
 *    khronos_usize_t             unsigned size
 *    khronos_float_t             signed   32 bit floating point
 *    khronos_time_ns_t           unsigned 64 bit time in nanoseconds
 *    khronos_utime_nanoseconds_t unsigned time interval or absolute time in
 *                                         nanoseconds
 *    khronos_stime_nanoseconds_t signed time interval in nanoseconds
 *    khronos_boolean_enum_t      enumerated boolean type. This should
 *      only be used as a base type when a client API's boolean type is
 *      an enum. Client APIs which use an integer or other type for
 *      booleans cannot use this as the base type for their boolean.
 *
 * Tokens defined in khrplatform.h:
 *
 *    KHRONOS_FALSE, KHRONOS_TRUE Enumerated boolean false/true values.
 *
 *    KHRONOS_SUPPORT_INT64 is 1 if 64 bit integers are supported; otherwise 0.
 *    KHRONOS_SUPPORT_FLOAT is 1 if floats are supported; otherwise 0.
 *
 * Calling convention macros defined in this file:
 *    KHRONOS_APICALL
 *    KHRONOS_APIENTRY
 *    KHRONOS_APIATTRIBUTES
 *
 * These may be used in function prototypes as:
 *
 *      KHRONOS_APICALL void KHRONOS_APIENTRY funcname(
 *                                  int arg1,
 *                                  int arg2) KHRONOS_APIATTRIBUTES;
 */

#if defined(__SCITECH_SNAP__) && !defined(KHRONOS_STATIC)
#   define KHRONOS_STATIC 1
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APICALL
 *-------------------------------------------------------------------------
 * This precedes the return type of the function in the function prototype.
 */
#if defined(KHRONOS_STATIC)
    /* If the preprocessor constant KHRONOS_STATIC is defined, make the
     * header compatible with static linking. */
#   define KHRONOS_APICALL
#elif defined(_WIN32)
#   define KHRONOS_APICALL __declspec(dllimport)
#elif defined (__SYMBIAN32__)
#   define KHRONOS_APICALL IMPORT_C
#elif defined(__ANDROID__)
#   define KHRONOS_APICALL __attribute__((visibility("default")))
#else
#   define KHRONOS_APICALL
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIENTRY
 *-------------------------------------------------------------------------
 * This follows the return type of the function  and precedes the function
 * name in the function prototype.
 */
#if defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
    /* Win32 but not WinCE */
#   define KHRONOS_APIENTRY __stdcall
#else
#   define KHRONOS_APIENTRY
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIATTRIBUTES
 *-------------------------------------------------------------------------
 * This follows the closing parenthesis of the function prototype arguments.
 */
#if defined (__ARMCC_2__)
#define KHRONOS_APIATTRIBUTES __softfp
#else
#define KHRONOS_APIATTRIBUTES
#endif

/*-------------------------------------------------------------------------
 * basic type definitions
 *-----------------------------------------------------------------------*/
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)


/*
 * Using <stdint.h>
 */
#include <stdint.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(__VMS ) || defined(__sgi)

/*
 * Using <inttypes.h>
 */
#include <inttypes.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(_WIN32) && !defined(__SCITECH_SNAP__)

/*
 * Win32
 */
typedef __int32                 khronos_int32_t;
typedef unsigned __int32        khronos_uint32_t;
typedef __int64                 khronos_int64_t;
typedef unsigned __int64        khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(__sun__) || defined(__digital__)

/*
 * Sun or Digital
 */
typedef int                     khronos_int32_t;
typedef unsigned int            khronos_uint32_t;
#if defined(__arch64__) || defined(_LP64)
typedef long int                khronos_int64_t;
typedef unsigned long int       khronos_uint64_t;
#else
typedef long long int           khronos_int64_t;
typedef unsigned long long int  khronos_uint64_t;
#endif /* __arch64__ */
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif 0

/*
 * Hypothetical platform with no float or int64 support
 */
typedef int                     khronos_int32_t;
typedef unsigned int            khronos_uint32_t;
#define KHRONOS_SUPPORT_INT64   0
#define KHRONOS_SUPPORT_FLOAT   0

#else

/*
 * Generic fallback
 */
#include <stdint.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#endif


/*
 * Types that are (so far) the same on all platforms
 */
typedef signed   char          khronos_int8_t;
typedef unsigned char          khronos_uint8_t;
typedef signed   short int     khronos_int16_t;
typedef unsigned short int     khronos_uint16_t;

/*
 * Types that differ between LLP64 and LP64 architectures - in LLP64,
 * pointers are 64 bits, but 'long' is still 32 bits. Win64 appears
 * to be the only LLP64 architecture in current use.
 */
#ifdef _WIN64
typedef signed   long long int khronos_intptr_t;
typedef unsigned long long int khronos_uintptr_t;
typedef signed   long long int khronos_ssize_t;
typedef unsigned long long int khronos_usize_t;
#else
typedef signed   long  int     khronos_intptr_t;
typedef unsigned long  int     khronos_uintptr_t;
typedef signed   long  int     khronos_ssize_t;
typedef unsigned long  int     khronos_usize_t;
#endif

#if KHRONOS_SUPPORT_FLOAT
/*
 * Float type
 */
typedef          float         khronos_float_t;
#endif

#if KHRONOS_SUPPORT_INT64
/* Time types
 *
 * These types can be used to represent a time interval in nanoseconds or
 * an absolute Unadjusted System Time.  Unadjusted System Time is the number
 * of nanoseconds since some arbitrary system event (e.g. since the last
 * time the system booted).  The Unadjusted System Time is an unsigned
 * 64 bit value that wraps back to 0 every 584 years.  Time intervals
 * may be either signed or unsigned.
 */
typedef khronos_uint64_t       khronos_utime_nanoseconds_t;
typedef khronos_int64_t        khronos_stime_nanoseconds_t;
#endif

/*
 * Dummy value used to pad enum types to 32 bits.
 */
#ifndef KHRONOS_MAX_ENUM
#define KHRONOS_MAX_ENUM 0x7FFFFFFF
#endif

/*
 * Enumerated boolean type
 *
 * Values other than zero should be considered to be true.  Therefore
 * comparisons should not be made against KHRONOS_TRUE.
 */
typedef enum {
    KHRONOS_FALSE = 0,
    KHRONOS_TRUE  = 1,
    KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = KHRONOS_MAX_ENUM
} khronos_boolean_enum_t;

#endif /* __khrplatform_h_ */


#if SOL_TEST_VERSION(1, 0)
typedef void GLvoid;
typedef unsigned int GLenum;
typedef khronos_float_t GLfloat;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLbitfield;
typedef double GLdouble;
typedef unsigned int GLuint;
typedef unsigned char GLboolean;
typedef khronos_uint8_t GLubyte;
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_FALSE                          0
#define GL_TRUE                           1
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
#define GL_NONE                           0
#define GL_FRONT_LEFT                     0x0400
#define GL_FRONT_RIGHT                    0x0401
#define GL_BACK_LEFT                      0x0402
#define GL_BACK_RIGHT                     0x0403
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_LEFT                           0x0406
#define GL_RIGHT                          0x0407
#define GL_FRONT_AND_BACK                 0x0408
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_OUT_OF_MEMORY                  0x0505
#define GL_CW                             0x0900
#define GL_CCW                            0x0901
#define GL_POINT_SIZE                     0x0B11
#define GL_POINT_SIZE_RANGE               0x0B12
#define GL_POINT_SIZE_GRANULARITY         0x0B13
#define GL_LINE_SMOOTH                    0x0B20
#define GL_LINE_WIDTH                     0x0B21
#define GL_LINE_WIDTH_RANGE               0x0B22
#define GL_LINE_WIDTH_GRANULARITY         0x0B23
#define GL_POLYGON_MODE                   0x0B40
#define GL_POLYGON_SMOOTH                 0x0B41
#define GL_CULL_FACE                      0x0B44
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_TEST                     0x0B71
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_STENCIL_TEST                   0x0B90
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_VIEWPORT                       0x0BA2
#define GL_DITHER                         0x0BD0
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1
#define GL_BLEND                          0x0BE2
#define GL_LOGIC_OP_MODE                  0x0BF0
#define GL_DRAW_BUFFER                    0x0C01
#define GL_READ_BUFFER                    0x0C02
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_DOUBLEBUFFER                   0x0C32
#define GL_STEREO                         0x0C33
#define GL_LINE_SMOOTH_HINT               0x0C52
#define GL_POLYGON_SMOOTH_HINT            0x0C53
#define GL_UNPACK_SWAP_BYTES              0x0CF0
#define GL_UNPACK_LSB_FIRST               0x0CF1
#define GL_UNPACK_ROW_LENGTH              0x0CF2
#define GL_UNPACK_SKIP_ROWS               0x0CF3
#define GL_UNPACK_SKIP_PIXELS             0x0CF4
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_SWAP_BYTES                0x0D00
#define GL_PACK_LSB_FIRST                 0x0D01
#define GL_PACK_ROW_LENGTH                0x0D02
#define GL_PACK_SKIP_ROWS                 0x0D03
#define GL_PACK_SKIP_PIXELS               0x0D04
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_TEXTURE_WIDTH                  0x1000
#define GL_TEXTURE_HEIGHT                 0x1001
#define GL_TEXTURE_BORDER_COLOR           0x1004
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F
#define GL_TEXTURE                        0x1702
#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802
#define GL_STENCIL_INDEX                  0x1901
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_REPEAT                         0x2901
typedef void (APIENTRYP PFNGLCULLFACEPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLFRONTFACEPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLHINTPROC) (GLenum target, GLenum mode);
typedef void (APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat width);
typedef void (APIENTRYP PFNGLPOINTSIZEPROC) (GLfloat size);
typedef void (APIENTRYP PFNGLPOLYGONMODEPROC) (GLenum face, GLenum mode);
typedef void (APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXIMAGE1DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLDRAWBUFFERPROC) (GLenum buf);
typedef void (APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
typedef void (APIENTRYP PFNGLCLEARDEPTHPROC) (GLdouble depth);
typedef void (APIENTRYP PFNGLSTENCILMASKPROC) (GLuint mask);
typedef void (APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
typedef void (APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLENABLEPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLFINISHPROC) (void);
typedef void (APIENTRYP PFNGLFLUSHPROC) (void);
typedef void (APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
typedef void (APIENTRYP PFNGLLOGICOPPROC) (GLenum opcode);
typedef void (APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
typedef void (APIENTRYP PFNGLPIXELSTOREFPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
typedef void (APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
typedef void (APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *data);
typedef void (APIENTRYP PFNGLGETDOUBLEVPROC) (GLenum pname, GLdouble *data);
typedef GLenum (APIENTRYP PFNGLGETERRORPROC) (void);
typedef void (APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *data);
typedef void (APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *data);
typedef const GLubyte *(APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
typedef void (APIENTRYP PFNGLGETTEXIMAGEPROC) (GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum target, GLint level, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum target, GLint level, GLenum pname, GLint *params);
typedef GLboolean (APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLDEPTHRANGEPROC) (GLdouble n, GLdouble f);
typedef void (APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLCULLFACEPROC glCullFace = NULL;
PFNGLFRONTFACEPROC glFrontFace = NULL;
PFNGLHINTPROC glHint = NULL;
PFNGLLINEWIDTHPROC glLineWidth = NULL;
PFNGLPOINTSIZEPROC glPointSize = NULL;
PFNGLPOLYGONMODEPROC glPolygonMode = NULL;
PFNGLSCISSORPROC glScissor = NULL;
PFNGLTEXPARAMETERFPROC glTexParameterf = NULL;
PFNGLTEXPARAMETERFVPROC glTexParameterfv = NULL;
PFNGLTEXPARAMETERIPROC glTexParameteri = NULL;
PFNGLTEXPARAMETERIVPROC glTexParameteriv = NULL;
PFNGLTEXIMAGE1DPROC glTexImage1D = NULL;
PFNGLTEXIMAGE2DPROC glTexImage2D = NULL;
PFNGLDRAWBUFFERPROC glDrawBuffer = NULL;
PFNGLCLEARPROC glClear = NULL;
PFNGLCLEARCOLORPROC glClearColor = NULL;
PFNGLCLEARSTENCILPROC glClearStencil = NULL;
PFNGLCLEARDEPTHPROC glClearDepth = NULL;
PFNGLSTENCILMASKPROC glStencilMask = NULL;
PFNGLCOLORMASKPROC glColorMask = NULL;
PFNGLDEPTHMASKPROC glDepthMask = NULL;
PFNGLDISABLEPROC glDisable = NULL;
PFNGLENABLEPROC glEnable = NULL;
PFNGLFINISHPROC glFinish = NULL;
PFNGLFLUSHPROC glFlush = NULL;
PFNGLBLENDFUNCPROC glBlendFunc = NULL;
PFNGLLOGICOPPROC glLogicOp = NULL;
PFNGLSTENCILFUNCPROC glStencilFunc = NULL;
PFNGLSTENCILOPPROC glStencilOp = NULL;
PFNGLDEPTHFUNCPROC glDepthFunc = NULL;
PFNGLPIXELSTOREFPROC glPixelStoref = NULL;
PFNGLPIXELSTOREIPROC glPixelStorei = NULL;
PFNGLREADBUFFERPROC glReadBuffer = NULL;
PFNGLREADPIXELSPROC glReadPixels = NULL;
PFNGLGETBOOLEANVPROC glGetBooleanv = NULL;
PFNGLGETDOUBLEVPROC glGetDoublev = NULL;
PFNGLGETERRORPROC glGetError = NULL;
PFNGLGETFLOATVPROC glGetFloatv = NULL;
PFNGLGETINTEGERVPROC glGetIntegerv = NULL;
PFNGLGETSTRINGPROC glGetString = NULL;
PFNGLGETTEXIMAGEPROC glGetTexImage = NULL;
PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfv = NULL;
PFNGLGETTEXPARAMETERIVPROC glGetTexParameteriv = NULL;
PFNGLGETTEXLEVELPARAMETERFVPROC glGetTexLevelParameterfv = NULL;
PFNGLGETTEXLEVELPARAMETERIVPROC glGetTexLevelParameteriv = NULL;
PFNGLISENABLEDPROC glIsEnabled = NULL;
PFNGLDEPTHRANGEPROC glDepthRange = NULL;
PFNGLVIEWPORTPROC glViewport = NULL;
#endif /* GL_VERSION_1_0 */

#if SOL_TEST_VERSION(1, 1)
typedef khronos_float_t GLclampf;
typedef double GLclampd;
#define GL_COLOR_LOGIC_OP                 0x0BF2
#define GL_POLYGON_OFFSET_UNITS           0x2A00
#define GL_POLYGON_OFFSET_POINT           0x2A01
#define GL_POLYGON_OFFSET_LINE            0x2A02
#define GL_POLYGON_OFFSET_FILL            0x8037
#define GL_POLYGON_OFFSET_FACTOR          0x8038
#define GL_TEXTURE_BINDING_1D             0x8068
#define GL_TEXTURE_BINDING_2D             0x8069
#define GL_TEXTURE_INTERNAL_FORMAT        0x1003
#define GL_TEXTURE_RED_SIZE               0x805C
#define GL_TEXTURE_GREEN_SIZE             0x805D
#define GL_TEXTURE_BLUE_SIZE              0x805E
#define GL_TEXTURE_ALPHA_SIZE             0x805F
#define GL_DOUBLE                         0x140A
#define GL_PROXY_TEXTURE_1D               0x8063
#define GL_PROXY_TEXTURE_2D               0x8064
#define GL_R3_G3_B2                       0x2A10
#define GL_RGB4                           0x804F
#define GL_RGB5                           0x8050
#define GL_RGB8                           0x8051
#define GL_RGB10                          0x8052
#define GL_RGB12                          0x8053
#define GL_RGB16                          0x8054
#define GL_RGBA2                          0x8055
#define GL_RGBA4                          0x8056
#define GL_RGB5_A1                        0x8057
#define GL_RGBA8                          0x8058
#define GL_RGB10_A2                       0x8059
#define GL_RGBA12                         0x805A
#define GL_RGBA16                         0x805B
#define GL_VERTEX_ARRAY                   0x8074
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices);
typedef void (APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, void **params);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat factor, GLfloat units);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, const GLuint *textures);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
typedef GLboolean (APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
PFNGLDRAWARRAYSPROC glDrawArrays = NULL;
PFNGLDRAWELEMENTSPROC glDrawElements = NULL;
PFNGLGETPOINTERVPROC glGetPointerv = NULL;
PFNGLPOLYGONOFFSETPROC glPolygonOffset = NULL;
PFNGLCOPYTEXIMAGE1DPROC glCopyTexImage1D = NULL;
PFNGLCOPYTEXIMAGE2DPROC glCopyTexImage2D = NULL;
PFNGLCOPYTEXSUBIMAGE1DPROC glCopyTexSubImage1D = NULL;
PFNGLCOPYTEXSUBIMAGE2DPROC glCopyTexSubImage2D = NULL;
PFNGLTEXSUBIMAGE1DPROC glTexSubImage1D = NULL;
PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D = NULL;
PFNGLBINDTEXTUREPROC glBindTexture = NULL;
PFNGLDELETETEXTURESPROC glDeleteTextures = NULL;
PFNGLGENTEXTURESPROC glGenTextures = NULL;
PFNGLISTEXTUREPROC glIsTexture = NULL;
#endif /* GL_VERSION_1_1 */

#if SOL_TEST_VERSION(1, 2)
#define GL_UNSIGNED_BYTE_3_3_2            0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
#define GL_UNSIGNED_INT_10_10_10_2        0x8036
#define GL_TEXTURE_BINDING_3D             0x806A
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_UNSIGNED_BYTE_2_3_3_REV        0x8362
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV       0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV     0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV     0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#define GL_BGR                            0x80E0
#define GL_BGRA                           0x80E1
#define GL_MAX_ELEMENTS_VERTICES          0x80E8
#define GL_MAX_ELEMENTS_INDICES           0x80E9
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_MIN_LOD                0x813A
#define GL_TEXTURE_MAX_LOD                0x813B
#define GL_TEXTURE_BASE_LEVEL             0x813C
#define GL_TEXTURE_MAX_LEVEL              0x813D
#define GL_SMOOTH_POINT_SIZE_RANGE        0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY  0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE        0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY  0x0B23
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices);
typedef void (APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = NULL;
PFNGLTEXIMAGE3DPROC glTexImage3D = NULL;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = NULL;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = NULL;
#endif /* GL_VERSION_1_2 */

#if SOL_TEST_VERSION(1, 3)
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_SAMPLE_COVERAGE                0x80A0
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_TEXTURE_CUBE_MAP               0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP         0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C
#define GL_COMPRESSED_RGB                 0x84ED
#define GL_COMPRESSED_RGBA                0x84EE
#define GL_TEXTURE_COMPRESSION_HINT       0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE  0x86A0
#define GL_TEXTURE_COMPRESSED             0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#define GL_CLAMP_TO_BORDER                0x812D
typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat value, GLboolean invert);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint level, void *img);
PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLSAMPLECOVERAGEPROC glSampleCoverage = NULL;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D = NULL;
PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage = NULL;
#endif /* GL_VERSION_1_3 */

#if SOL_TEST_VERSION(1, 4)
#define GL_BLEND_DST_RGB                  0x80C8
#define GL_BLEND_SRC_RGB                  0x80C9
#define GL_BLEND_DST_ALPHA                0x80CA
#define GL_BLEND_SRC_ALPHA                0x80CB
#define GL_POINT_FADE_THRESHOLD_SIZE      0x8128
#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7
#define GL_MIRRORED_REPEAT                0x8370
#define GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#define GL_TEXTURE_LOD_BIAS               0x8501
#define GL_INCR_WRAP                      0x8507
#define GL_DECR_WRAP                      0x8508
#define GL_TEXTURE_DEPTH_SIZE             0x884A
#define GL_TEXTURE_COMPARE_MODE           0x884C
#define GL_TEXTURE_COMPARE_FUNC           0x884D
#define GL_BLEND_COLOR                    0x8005
#define GL_BLEND_EQUATION                 0x8009
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#define GL_CONSTANT_ALPHA                 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#define GL_FUNC_ADD                       0x8006
#define GL_FUNC_REVERSE_SUBTRACT          0x800B
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_MIN                            0x8007
#define GL_MAX                            0x8008
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSPROC) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSPROC) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC) (GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIPROC) (GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIVPROC) (GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = NULL;
PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays = NULL;
PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements = NULL;
PFNGLPOINTPARAMETERFPROC glPointParameterf = NULL;
PFNGLPOINTPARAMETERFVPROC glPointParameterfv = NULL;
PFNGLPOINTPARAMETERIPROC glPointParameteri = NULL;
PFNGLPOINTPARAMETERIVPROC glPointParameteriv = NULL;
PFNGLBLENDCOLORPROC glBlendColor = NULL;
PFNGLBLENDEQUATIONPROC glBlendEquation = NULL;
#endif /* GL_VERSION_1_4 */

#if SOL_TEST_VERSION(1, 5)
typedef khronos_ssize_t GLsizeiptr;
typedef khronos_intptr_t GLintptr;
#define GL_BUFFER_SIZE                    0x8764
#define GL_BUFFER_USAGE                   0x8765
#define GL_QUERY_COUNTER_BITS             0x8864
#define GL_CURRENT_QUERY                  0x8865
#define GL_QUERY_RESULT                   0x8866
#define GL_QUERY_RESULT_AVAILABLE         0x8867
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_ARRAY_BUFFER_BINDING           0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GL_READ_ONLY                      0x88B8
#define GL_WRITE_ONLY                     0x88B9
#define GL_READ_WRITE                     0x88BA
#define GL_BUFFER_ACCESS                  0x88BB
#define GL_BUFFER_MAPPED                  0x88BC
#define GL_BUFFER_MAP_POINTER             0x88BD
#define GL_STREAM_DRAW                    0x88E0
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_DRAW                    0x88E4
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA
#define GL_SAMPLES_PASSED                 0x8914
#define GL_SRC1_ALPHA                     0x8589
typedef void (APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
typedef void (APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, const GLuint *ids);
typedef GLboolean (APIENTRYP PFNGLISQUERYPROC) (GLuint id);
typedef void (APIENTRYP PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
typedef void (APIENTRYP PFNGLENDQUERYPROC) (GLenum target);
typedef void (APIENTRYP PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC) (GLuint id, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef GLboolean (APIENTRYP PFNGLISBUFFERPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, void *data);
typedef void *(APIENTRYP PFNGLMAPBUFFERPROC) (GLenum target, GLenum access);
typedef GLboolean (APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum target);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, void **params);
PFNGLGENQUERIESPROC glGenQueries = NULL;
PFNGLDELETEQUERIESPROC glDeleteQueries = NULL;
PFNGLISQUERYPROC glIsQuery = NULL;
PFNGLBEGINQUERYPROC glBeginQuery = NULL;
PFNGLENDQUERYPROC glEndQuery = NULL;
PFNGLGETQUERYIVPROC glGetQueryiv = NULL;
PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv = NULL;
PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLISBUFFERPROC glIsBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData = NULL;
PFNGLMAPBUFFERPROC glMapBuffer = NULL;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = NULL;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = NULL;
PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = NULL;
#endif /* GL_VERSION_1_5 */

#if SOL_TEST_VERSION(2, 0)
typedef char GLchar;
typedef khronos_int16_t GLshort;
typedef khronos_int8_t GLbyte;
typedef khronos_uint16_t GLushort;
#define GL_BLEND_EQUATION_RGB             0x8009
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED    0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE       0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE     0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE       0x8625
#define GL_CURRENT_VERTEX_ATTRIB          0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE      0x8642
#define GL_VERTEX_ATTRIB_ARRAY_POINTER    0x8645
#define GL_STENCIL_BACK_FUNC              0x8800
#define GL_STENCIL_BACK_FAIL              0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GL_MAX_DRAW_BUFFERS               0x8824
#define GL_DRAW_BUFFER0                   0x8825
#define GL_DRAW_BUFFER1                   0x8826
#define GL_DRAW_BUFFER2                   0x8827
#define GL_DRAW_BUFFER3                   0x8828
#define GL_DRAW_BUFFER4                   0x8829
#define GL_DRAW_BUFFER5                   0x882A
#define GL_DRAW_BUFFER6                   0x882B
#define GL_DRAW_BUFFER7                   0x882C
#define GL_DRAW_BUFFER8                   0x882D
#define GL_DRAW_BUFFER9                   0x882E
#define GL_DRAW_BUFFER10                  0x882F
#define GL_DRAW_BUFFER11                  0x8830
#define GL_DRAW_BUFFER12                  0x8831
#define GL_DRAW_BUFFER13                  0x8832
#define GL_DRAW_BUFFER14                  0x8833
#define GL_DRAW_BUFFER15                  0x8834
#define GL_BLEND_EQUATION_ALPHA           0x883D
#define GL_MAX_VERTEX_ATTRIBS             0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS  0x8B4A
#define GL_MAX_VARYING_FLOATS             0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_SHADER_TYPE                    0x8B4F
#define GL_FLOAT_VEC2                     0x8B50
#define GL_FLOAT_VEC3                     0x8B51
#define GL_FLOAT_VEC4                     0x8B52
#define GL_INT_VEC2                       0x8B53
#define GL_INT_VEC3                       0x8B54
#define GL_INT_VEC4                       0x8B55
#define GL_BOOL                           0x8B56
#define GL_BOOL_VEC2                      0x8B57
#define GL_BOOL_VEC3                      0x8B58
#define GL_BOOL_VEC4                      0x8B59
#define GL_FLOAT_MAT2                     0x8B5A
#define GL_FLOAT_MAT3                     0x8B5B
#define GL_FLOAT_MAT4                     0x8B5C
#define GL_SAMPLER_1D                     0x8B5D
#define GL_SAMPLER_2D                     0x8B5E
#define GL_SAMPLER_3D                     0x8B5F
#define GL_SAMPLER_CUBE                   0x8B60
#define GL_SAMPLER_1D_SHADOW              0x8B61
#define GL_SAMPLER_2D_SHADOW              0x8B62
#define GL_DELETE_STATUS                  0x8B80
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_ATTACHED_SHADERS               0x8B85
#define GL_ACTIVE_UNIFORMS                0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH      0x8B87
#define GL_SHADER_SOURCE_LENGTH           0x8B88
#define GL_ACTIVE_ATTRIBUTES              0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH    0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#define GL_CURRENT_PROGRAM                0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN      0x8CA0
#define GL_LOWER_LEFT                     0x8CA1
#define GL_UPPER_LEFT                     0x8CA2
#define GL_STENCIL_BACK_REF               0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK        0x8CA4
#define GL_STENCIL_BACK_WRITEMASK         0x8CA5
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
typedef void (APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, const GLenum *bufs);
typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
typedef void (APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const GLchar *name);
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
typedef void (APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
typedef GLint (APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat *params);
typedef void (APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBDVPROC) (GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, void **pointer);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPROC) (GLuint program);
typedef GLboolean (APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void (APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DPROC) (GLuint index, GLdouble x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SPROC) (GLuint index, GLshort x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SPROC) (GLuint index, GLshort x, GLshort y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NBVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NIVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NSVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUSVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4BVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4USVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate = NULL;
PFNGLDRAWBUFFERSPROC glDrawBuffers = NULL;
PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = NULL;
PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate = NULL;
PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLDETACHSHADERPROC glDetachShader = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = NULL;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = NULL;
PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders = NULL;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETSHADERSOURCEPROC glGetShaderSource = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLGETUNIFORMFVPROC glGetUniformfv = NULL;
PFNGLGETUNIFORMIVPROC glGetUniformiv = NULL;
PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv = NULL;
PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv = NULL;
PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = NULL;
PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = NULL;
PFNGLISPROGRAMPROC glIsProgram = NULL;
PFNGLISSHADERPROC glIsShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLUNIFORM1FPROC glUniform1f = NULL;
PFNGLUNIFORM2FPROC glUniform2f = NULL;
PFNGLUNIFORM3FPROC glUniform3f = NULL;
PFNGLUNIFORM4FPROC glUniform4f = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM2IPROC glUniform2i = NULL;
PFNGLUNIFORM3IPROC glUniform3i = NULL;
PFNGLUNIFORM4IPROC glUniform4i = NULL;
PFNGLUNIFORM1FVPROC glUniform1fv = NULL;
PFNGLUNIFORM2FVPROC glUniform2fv = NULL;
PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
PFNGLUNIFORM1IVPROC glUniform1iv = NULL;
PFNGLUNIFORM2IVPROC glUniform2iv = NULL;
PFNGLUNIFORM3IVPROC glUniform3iv = NULL;
PFNGLUNIFORM4IVPROC glUniform4iv = NULL;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
PFNGLVALIDATEPROGRAMPROC glValidateProgram = NULL;
PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d = NULL;
PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv = NULL;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = NULL;
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = NULL;
PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s = NULL;
PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv = NULL;
PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d = NULL;
PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv = NULL;
PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f = NULL;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = NULL;
PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s = NULL;
PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv = NULL;
PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d = NULL;
PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv = NULL;
PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f = NULL;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = NULL;
PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s = NULL;
PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv = NULL;
PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv = NULL;
PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv = NULL;
PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv = NULL;
PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub = NULL;
PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv = NULL;
PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv = NULL;
PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv = NULL;
PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv = NULL;
PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d = NULL;
PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv = NULL;
PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f = NULL;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = NULL;
PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv = NULL;
PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s = NULL;
PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv = NULL;
PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv = NULL;
PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv = NULL;
PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
#endif /* GL_VERSION_2_0 */

#if SOL_TEST_VERSION(2, 1)
#define GL_PIXEL_PACK_BUFFER              0x88EB
#define GL_PIXEL_UNPACK_BUFFER            0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING      0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING    0x88EF
#define GL_FLOAT_MAT2x3                   0x8B65
#define GL_FLOAT_MAT2x4                   0x8B66
#define GL_FLOAT_MAT3x2                   0x8B67
#define GL_FLOAT_MAT3x4                   0x8B68
#define GL_FLOAT_MAT4x2                   0x8B69
#define GL_FLOAT_MAT4x3                   0x8B6A
#define GL_SRGB                           0x8C40
#define GL_SRGB8                          0x8C41
#define GL_SRGB_ALPHA                     0x8C42
#define GL_SRGB8_ALPHA8                   0x8C43
#define GL_COMPRESSED_SRGB                0x8C48
#define GL_COMPRESSED_SRGB_ALPHA          0x8C49
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = NULL;
PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = NULL;
PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = NULL;
PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = NULL;
PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = NULL;
PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = NULL;
#endif /* GL_VERSION_2_1 */

#if SOL_TEST_VERSION(3, 0)
typedef khronos_uint16_t GLhalf;
#define GL_COMPARE_REF_TO_TEXTURE         0x884E
#define GL_CLIP_DISTANCE0                 0x3000
#define GL_CLIP_DISTANCE1                 0x3001
#define GL_CLIP_DISTANCE2                 0x3002
#define GL_CLIP_DISTANCE3                 0x3003
#define GL_CLIP_DISTANCE4                 0x3004
#define GL_CLIP_DISTANCE5                 0x3005
#define GL_CLIP_DISTANCE6                 0x3006
#define GL_CLIP_DISTANCE7                 0x3007
#define GL_MAX_CLIP_DISTANCES             0x0D32
#define GL_MAJOR_VERSION                  0x821B
#define GL_MINOR_VERSION                  0x821C
#define GL_NUM_EXTENSIONS                 0x821D
#define GL_CONTEXT_FLAGS                  0x821E
#define GL_COMPRESSED_RED                 0x8225
#define GL_COMPRESSED_RG                  0x8226
#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 0x00000001
#define GL_RGBA32F                        0x8814
#define GL_RGB32F                         0x8815
#define GL_RGBA16F                        0x881A
#define GL_RGB16F                         0x881B
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER    0x88FD
#define GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#define GL_MIN_PROGRAM_TEXEL_OFFSET       0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET       0x8905
#define GL_CLAMP_READ_COLOR               0x891C
#define GL_FIXED_ONLY                     0x891D
#define GL_MAX_VARYING_COMPONENTS         0x8B4B
#define GL_TEXTURE_1D_ARRAY               0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY         0x8C19
#define GL_TEXTURE_2D_ARRAY               0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY         0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY       0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#define GL_R11F_G11F_B10F                 0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#define GL_RGB9_E5                        0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#define GL_TEXTURE_SHARED_SIZE            0x8C3F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8C85
#define GL_PRIMITIVES_GENERATED           0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#define GL_RASTERIZER_DISCARD             0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#define GL_INTERLEAVED_ATTRIBS            0x8C8C
#define GL_SEPARATE_ATTRIBS               0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER      0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8C8F
#define GL_RGBA32UI                       0x8D70
#define GL_RGB32UI                        0x8D71
#define GL_RGBA16UI                       0x8D76
#define GL_RGB16UI                        0x8D77
#define GL_RGBA8UI                        0x8D7C
#define GL_RGB8UI                         0x8D7D
#define GL_RGBA32I                        0x8D82
#define GL_RGB32I                         0x8D83
#define GL_RGBA16I                        0x8D88
#define GL_RGB16I                         0x8D89
#define GL_RGBA8I                         0x8D8E
#define GL_RGB8I                          0x8D8F
#define GL_RED_INTEGER                    0x8D94
#define GL_GREEN_INTEGER                  0x8D95
#define GL_BLUE_INTEGER                   0x8D96
#define GL_RGB_INTEGER                    0x8D98
#define GL_RGBA_INTEGER                   0x8D99
#define GL_BGR_INTEGER                    0x8D9A
#define GL_BGRA_INTEGER                   0x8D9B
#define GL_SAMPLER_1D_ARRAY               0x8DC0
#define GL_SAMPLER_2D_ARRAY               0x8DC1
#define GL_SAMPLER_1D_ARRAY_SHADOW        0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#define GL_SAMPLER_CUBE_SHADOW            0x8DC5
#define GL_UNSIGNED_INT_VEC2              0x8DC6
#define GL_UNSIGNED_INT_VEC3              0x8DC7
#define GL_UNSIGNED_INT_VEC4              0x8DC8
#define GL_INT_SAMPLER_1D                 0x8DC9
#define GL_INT_SAMPLER_2D                 0x8DCA
#define GL_INT_SAMPLER_3D                 0x8DCB
#define GL_INT_SAMPLER_CUBE               0x8DCC
#define GL_INT_SAMPLER_1D_ARRAY           0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#define GL_UNSIGNED_INT_SAMPLER_1D        0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY  0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#define GL_QUERY_WAIT                     0x8E13
#define GL_QUERY_NO_WAIT                  0x8E14
#define GL_QUERY_BY_REGION_WAIT           0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT        0x8E16
#define GL_BUFFER_ACCESS_FLAGS            0x911F
#define GL_BUFFER_MAP_LENGTH              0x9120
#define GL_BUFFER_MAP_OFFSET              0x9121
#define GL_DEPTH_COMPONENT32F             0x8CAC
#define GL_DEPTH32F_STENCIL8              0x8CAD
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#define GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_DEFAULT            0x8218
#define GL_FRAMEBUFFER_UNDEFINED          0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT       0x821A
#define GL_MAX_RENDERBUFFER_SIZE          0x84E8
#define GL_DEPTH_STENCIL                  0x84F9
#define GL_UNSIGNED_INT_24_8              0x84FA
#define GL_DEPTH24_STENCIL8               0x88F0
#define GL_TEXTURE_STENCIL_SIZE           0x88F1
#define GL_TEXTURE_RED_TYPE               0x8C10
#define GL_TEXTURE_GREEN_TYPE             0x8C11
#define GL_TEXTURE_BLUE_TYPE              0x8C12
#define GL_TEXTURE_ALPHA_TYPE             0x8C13
#define GL_TEXTURE_DEPTH_TYPE             0x8C16
#define GL_UNSIGNED_NORMALIZED            0x8C17
#define GL_FRAMEBUFFER_BINDING            0x8CA6
#define GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#define GL_RENDERBUFFER_BINDING           0x8CA7
#define GL_READ_FRAMEBUFFER               0x8CA8
#define GL_DRAW_FRAMEBUFFER               0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#define GL_RENDERBUFFER_SAMPLES           0x8CAB
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#define GL_FRAMEBUFFER_COMPLETE           0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#define GL_COLOR_ATTACHMENT0              0x8CE0
#define GL_COLOR_ATTACHMENT1              0x8CE1
#define GL_COLOR_ATTACHMENT2              0x8CE2
#define GL_COLOR_ATTACHMENT3              0x8CE3
#define GL_COLOR_ATTACHMENT4              0x8CE4
#define GL_COLOR_ATTACHMENT5              0x8CE5
#define GL_COLOR_ATTACHMENT6              0x8CE6
#define GL_COLOR_ATTACHMENT7              0x8CE7
#define GL_COLOR_ATTACHMENT8              0x8CE8
#define GL_COLOR_ATTACHMENT9              0x8CE9
#define GL_COLOR_ATTACHMENT10             0x8CEA
#define GL_COLOR_ATTACHMENT11             0x8CEB
#define GL_COLOR_ATTACHMENT12             0x8CEC
#define GL_COLOR_ATTACHMENT13             0x8CED
#define GL_COLOR_ATTACHMENT14             0x8CEE
#define GL_COLOR_ATTACHMENT15             0x8CEF
#define GL_COLOR_ATTACHMENT16             0x8CF0
#define GL_COLOR_ATTACHMENT17             0x8CF1
#define GL_COLOR_ATTACHMENT18             0x8CF2
#define GL_COLOR_ATTACHMENT19             0x8CF3
#define GL_COLOR_ATTACHMENT20             0x8CF4
#define GL_COLOR_ATTACHMENT21             0x8CF5
#define GL_COLOR_ATTACHMENT22             0x8CF6
#define GL_COLOR_ATTACHMENT23             0x8CF7
#define GL_COLOR_ATTACHMENT24             0x8CF8
#define GL_COLOR_ATTACHMENT25             0x8CF9
#define GL_COLOR_ATTACHMENT26             0x8CFA
#define GL_COLOR_ATTACHMENT27             0x8CFB
#define GL_COLOR_ATTACHMENT28             0x8CFC
#define GL_COLOR_ATTACHMENT29             0x8CFD
#define GL_COLOR_ATTACHMENT30             0x8CFE
#define GL_COLOR_ATTACHMENT31             0x8CFF
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_STENCIL_ATTACHMENT             0x8D20
#define GL_FRAMEBUFFER                    0x8D40
#define GL_RENDERBUFFER                   0x8D41
#define GL_RENDERBUFFER_WIDTH             0x8D42
#define GL_RENDERBUFFER_HEIGHT            0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT   0x8D44
#define GL_STENCIL_INDEX1                 0x8D46
#define GL_STENCIL_INDEX4                 0x8D47
#define GL_STENCIL_INDEX8                 0x8D48
#define GL_STENCIL_INDEX16                0x8D49
#define GL_RENDERBUFFER_RED_SIZE          0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE        0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE         0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE        0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE        0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE      0x8D55
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#define GL_MAX_SAMPLES                    0x8D57
#define GL_FRAMEBUFFER_SRGB               0x8DB9
#define GL_HALF_FLOAT                     0x140B
#define GL_MAP_READ_BIT                   0x0001
#define GL_MAP_WRITE_BIT                  0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT       0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT      0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT         0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT         0x0020
#define GL_COMPRESSED_RED_RGTC1           0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1    0x8DBC
#define GL_COMPRESSED_RG_RGTC2            0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2     0x8DBE
#define GL_RG                             0x8227
#define GL_RG_INTEGER                     0x8228
#define GL_R8                             0x8229
#define GL_R16                            0x822A
#define GL_RG8                            0x822B
#define GL_RG16                           0x822C
#define GL_R16F                           0x822D
#define GL_R32F                           0x822E
#define GL_RG16F                          0x822F
#define GL_RG32F                          0x8230
#define GL_R8I                            0x8231
#define GL_R8UI                           0x8232
#define GL_R16I                           0x8233
#define GL_R16UI                          0x8234
#define GL_R32I                           0x8235
#define GL_R32UI                          0x8236
#define GL_RG8I                           0x8237
#define GL_RG8UI                          0x8238
#define GL_RG16I                          0x8239
#define GL_RG16UI                         0x823A
#define GL_RG32I                          0x823B
#define GL_RG32UI                         0x823C
#define GL_VERTEX_ARRAY_BINDING           0x85B5
typedef void (APIENTRYP PFNGLCOLORMASKIPROC) (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum target, GLuint index, GLboolean *data);
typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum target, GLuint index, GLint *data);
typedef void (APIENTRYP PFNGLENABLEIPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLDISABLEIPROC) (GLenum target, GLuint index);
typedef GLboolean (APIENTRYP PFNGLISENABLEDIPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitiveMode);
typedef void (APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLCLAMPCOLORPROC) (GLenum target, GLenum clamp);
typedef void (APIENTRYP PFNGLBEGINCONDITIONALRENDERPROC) (GLuint id, GLenum mode);
typedef void (APIENTRYP PFNGLENDCONDITIONALRENDERPROC) (void);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint index, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IPROC) (GLuint index, GLint x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IPROC) (GLuint index, GLint x, GLint y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IPROC) (GLuint index, GLint x, GLint y, GLint z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIPROC) (GLuint index, GLuint x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIPROC) (GLuint index, GLuint x, GLuint y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4BVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4USVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint program, GLint location, GLuint *params);
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONPROC) (GLuint program, GLuint color, const GLchar *name);
typedef GLint (APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
typedef void (APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
typedef void (APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, const GLuint *params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef const GLubyte *(APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
typedef GLboolean (APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, const GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef GLboolean (APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, const GLuint *framebuffers);
typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
typedef GLenum (APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE1DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum target);
typedef void (APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void *(APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef GLboolean (APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
PFNGLCOLORMASKIPROC glColorMaski = NULL;
PFNGLGETBOOLEANI_VPROC glGetBooleani_v = NULL;
PFNGLGETINTEGERI_VPROC glGetIntegeri_v = NULL;
PFNGLENABLEIPROC glEnablei = NULL;
PFNGLDISABLEIPROC glDisablei = NULL;
PFNGLISENABLEDIPROC glIsEnabledi = NULL;
PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback = NULL;
PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback = NULL;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange = NULL;
PFNGLBINDBUFFERBASEPROC glBindBufferBase = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying = NULL;
PFNGLCLAMPCOLORPROC glClampColor = NULL;
PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender = NULL;
PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender = NULL;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = NULL;
PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = NULL;
PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = NULL;
PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i = NULL;
PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i = NULL;
PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i = NULL;
PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = NULL;
PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui = NULL;
PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui = NULL;
PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui = NULL;
PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = NULL;
PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv = NULL;
PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv = NULL;
PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv = NULL;
PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = NULL;
PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv = NULL;
PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv = NULL;
PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv = NULL;
PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = NULL;
PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv = NULL;
PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv = NULL;
PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv = NULL;
PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv = NULL;
PFNGLGETUNIFORMUIVPROC glGetUniformuiv = NULL;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation = NULL;
PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation = NULL;
PFNGLUNIFORM1UIPROC glUniform1ui = NULL;
PFNGLUNIFORM2UIPROC glUniform2ui = NULL;
PFNGLUNIFORM3UIPROC glUniform3ui = NULL;
PFNGLUNIFORM4UIPROC glUniform4ui = NULL;
PFNGLUNIFORM1UIVPROC glUniform1uiv = NULL;
PFNGLUNIFORM2UIVPROC glUniform2uiv = NULL;
PFNGLUNIFORM3UIVPROC glUniform3uiv = NULL;
PFNGLUNIFORM4UIVPROC glUniform4uiv = NULL;
PFNGLTEXPARAMETERIIVPROC glTexParameterIiv = NULL;
PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv = NULL;
PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv = NULL;
PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv = NULL;
PFNGLCLEARBUFFERIVPROC glClearBufferiv = NULL;
PFNGLCLEARBUFFERUIVPROC glClearBufferuiv = NULL;
PFNGLCLEARBUFFERFVPROC glClearBufferfv = NULL;
PFNGLCLEARBUFFERFIPROC glClearBufferfi = NULL;
PFNGLGETSTRINGIPROC glGetStringi = NULL;
PFNGLISRENDERBUFFERPROC glIsRenderbuffer = NULL;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = NULL;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = NULL;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = NULL;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv = NULL;
PFNGLISFRAMEBUFFERPROC glIsFramebuffer = NULL;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = NULL;
PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL;
PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D = NULL;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv = NULL;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = NULL;
PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample = NULL;
PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer = NULL;
PFNGLMAPBUFFERRANGEPROC glMapBufferRange = NULL;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLISVERTEXARRAYPROC glIsVertexArray = NULL;
#endif /* GL_VERSION_3_0 */

#if SOL_TEST_VERSION(3, 1)
#define GL_SAMPLER_2D_RECT                0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW         0x8B64
#define GL_SAMPLER_BUFFER                 0x8DC2
#define GL_INT_SAMPLER_2D_RECT            0x8DCD
#define GL_INT_SAMPLER_BUFFER             0x8DD0
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT   0x8DD5
#define GL_UNSIGNED_INT_SAMPLER_BUFFER    0x8DD8
#define GL_TEXTURE_BUFFER                 0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE        0x8C2B
#define GL_TEXTURE_BINDING_BUFFER         0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8C2D
#define GL_TEXTURE_RECTANGLE              0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE      0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE        0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE     0x84F8
#define GL_R8_SNORM                       0x8F94
#define GL_RG8_SNORM                      0x8F95
#define GL_RGB8_SNORM                     0x8F96
#define GL_RGBA8_SNORM                    0x8F97
#define GL_R16_SNORM                      0x8F98
#define GL_RG16_SNORM                     0x8F99
#define GL_RGB16_SNORM                    0x8F9A
#define GL_RGBA16_SNORM                   0x8F9B
#define GL_SIGNED_NORMALIZED              0x8F9C
#define GL_PRIMITIVE_RESTART              0x8F9D
#define GL_PRIMITIVE_RESTART_INDEX        0x8F9E
#define GL_COPY_READ_BUFFER               0x8F36
#define GL_COPY_WRITE_BUFFER              0x8F37
#define GL_UNIFORM_BUFFER                 0x8A11
#define GL_UNIFORM_BUFFER_BINDING         0x8A28
#define GL_UNIFORM_BUFFER_START           0x8A29
#define GL_UNIFORM_BUFFER_SIZE            0x8A2A
#define GL_MAX_VERTEX_UNIFORM_BLOCKS      0x8A2B
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS    0x8A2C
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS    0x8A2D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS    0x8A2E
#define GL_MAX_UNIFORM_BUFFER_BINDINGS    0x8A2F
#define GL_MAX_UNIFORM_BLOCK_SIZE         0x8A30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8A32
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#define GL_ACTIVE_UNIFORM_BLOCKS          0x8A36
#define GL_UNIFORM_TYPE                   0x8A37
#define GL_UNIFORM_SIZE                   0x8A38
#define GL_UNIFORM_NAME_LENGTH            0x8A39
#define GL_UNIFORM_BLOCK_INDEX            0x8A3A
#define GL_UNIFORM_OFFSET                 0x8A3B
#define GL_UNIFORM_ARRAY_STRIDE           0x8A3C
#define GL_UNIFORM_MATRIX_STRIDE          0x8A3D
#define GL_UNIFORM_IS_ROW_MAJOR           0x8A3E
#define GL_UNIFORM_BLOCK_BINDING          0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE        0x8A40
#define GL_UNIFORM_BLOCK_NAME_LENGTH      0x8A41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS  0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8A45
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#define GL_INVALID_INDEX                  0xFFFFFFFFu
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
typedef void (APIENTRYP PFNGLTEXBUFFERPROC) (GLenum target, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLPRIMITIVERESTARTINDEXPROC) (GLuint index);
typedef void (APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMNAMEPROC) (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
typedef GLuint (APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint program, const GLchar *uniformBlockName);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
typedef void (APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = NULL;
PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced = NULL;
PFNGLTEXBUFFERPROC glTexBuffer = NULL;
PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex = NULL;
PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData = NULL;
PFNGLGETUNIFORMINDICESPROC glGetUniformIndices = NULL;
PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv = NULL;
PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex = NULL;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv = NULL;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding = NULL;
#endif /* GL_VERSION_3_1 */

#if SOL_TEST_VERSION(3, 2)
typedef struct __GLsync *GLsync;
typedef khronos_uint64_t GLuint64;
typedef khronos_int64_t GLint64;
#define GL_CONTEXT_CORE_PROFILE_BIT       0x00000001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#define GL_LINES_ADJACENCY                0x000A
#define GL_LINE_STRIP_ADJACENCY           0x000B
#define GL_TRIANGLES_ADJACENCY            0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY       0x000D
#define GL_PROGRAM_POINT_SIZE             0x8642
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#define GL_GEOMETRY_SHADER                0x8DD9
#define GL_GEOMETRY_VERTICES_OUT          0x8916
#define GL_GEOMETRY_INPUT_TYPE            0x8917
#define GL_GEOMETRY_OUTPUT_TYPE           0x8918
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES   0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8DE1
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS   0x9122
#define GL_MAX_GEOMETRY_INPUT_COMPONENTS  0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#define GL_MAX_FRAGMENT_INPUT_COMPONENTS  0x9125
#define GL_CONTEXT_PROFILE_MASK           0x9126
#define GL_DEPTH_CLAMP                    0x864F
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8E4C
#define GL_FIRST_VERTEX_CONVENTION        0x8E4D
#define GL_LAST_VERTEX_CONVENTION         0x8E4E
#define GL_PROVOKING_VERTEX               0x8E4F
#define GL_TEXTURE_CUBE_MAP_SEAMLESS      0x884F
#define GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#define GL_OBJECT_TYPE                    0x9112
#define GL_SYNC_CONDITION                 0x9113
#define GL_SYNC_STATUS                    0x9114
#define GL_SYNC_FLAGS                     0x9115
#define GL_SYNC_FENCE                     0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#define GL_UNSIGNALED                     0x9118
#define GL_SIGNALED                       0x9119
#define GL_ALREADY_SIGNALED               0x911A
#define GL_TIMEOUT_EXPIRED                0x911B
#define GL_CONDITION_SATISFIED            0x911C
#define GL_WAIT_FAILED                    0x911D
#define GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#define GL_SYNC_FLUSH_COMMANDS_BIT        0x00000001
#define GL_SAMPLE_POSITION                0x8E50
#define GL_SAMPLE_MASK                    0x8E51
#define GL_SAMPLE_MASK_VALUE              0x8E52
#define GL_MAX_SAMPLE_MASK_WORDS          0x8E59
#define GL_TEXTURE_2D_MULTISAMPLE         0x9100
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE   0x9101
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_SAMPLES                0x9106
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#define GL_SAMPLER_2D_MULTISAMPLE         0x9108
#define GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY   0x910B
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
#define GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#define GL_MAX_DEPTH_TEXTURE_SAMPLES      0x910F
#define GL_MAX_INTEGER_SAMPLES            0x9110
typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex);
typedef void (APIENTRYP PFNGLPROVOKINGVERTEXPROC) (GLenum mode);
typedef GLsync (APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
typedef GLboolean (APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
typedef void (APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
typedef GLenum (APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *data);
typedef void (APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei count, GLsizei *length, GLint *values);
typedef void (APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum target, GLuint index, GLint64 *data);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum target, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLTEXIMAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXIMAGE3DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint index, GLfloat *val);
typedef void (APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint maskNumber, GLbitfield mask);
PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex = NULL;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glDrawRangeElementsBaseVertex = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glDrawElementsInstancedBaseVertex = NULL;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertex = NULL;
PFNGLPROVOKINGVERTEXPROC glProvokingVertex = NULL;
PFNGLFENCESYNCPROC glFenceSync = NULL;
PFNGLISSYNCPROC glIsSync = NULL;
PFNGLDELETESYNCPROC glDeleteSync = NULL;
PFNGLCLIENTWAITSYNCPROC glClientWaitSync = NULL;
PFNGLWAITSYNCPROC glWaitSync = NULL;
PFNGLGETINTEGER64VPROC glGetInteger64v = NULL;
PFNGLGETSYNCIVPROC glGetSynciv = NULL;
PFNGLGETINTEGER64I_VPROC glGetInteger64i_v = NULL;
PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v = NULL;
PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture = NULL;
PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample = NULL;
PFNGLTEXIMAGE3DMULTISAMPLEPROC glTexImage3DMultisample = NULL;
PFNGLGETMULTISAMPLEFVPROC glGetMultisamplefv = NULL;
PFNGLSAMPLEMASKIPROC glSampleMaski = NULL;
#endif /* GL_VERSION_3_2 */

#if SOL_TEST_VERSION(3, 3)
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR    0x88FE
#define GL_SRC1_COLOR                     0x88F9
#define GL_ONE_MINUS_SRC1_COLOR           0x88FA
#define GL_ONE_MINUS_SRC1_ALPHA           0x88FB
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS   0x88FC
#define GL_ANY_SAMPLES_PASSED             0x8C2F
#define GL_SAMPLER_BINDING                0x8919
#define GL_RGB10_A2UI                     0x906F
#define GL_TEXTURE_SWIZZLE_R              0x8E42
#define GL_TEXTURE_SWIZZLE_G              0x8E43
#define GL_TEXTURE_SWIZZLE_B              0x8E44
#define GL_TEXTURE_SWIZZLE_A              0x8E45
#define GL_TEXTURE_SWIZZLE_RGBA           0x8E46
#define GL_TIME_ELAPSED                   0x88BF
#define GL_TIMESTAMP                      0x8E28
#define GL_INT_2_10_10_10_REV             0x8D9F
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) (GLuint program, GLuint colorNumber, GLuint index, const GLchar *name);
typedef GLint (APIENTRYP PFNGLGETFRAGDATAINDEXPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei count, GLuint *samplers);
typedef void (APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei count, const GLuint *samplers);
typedef GLboolean (APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
typedef void (APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, const GLfloat *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, const GLuint *param);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLQUERYCOUNTERPROC) (GLuint id, GLenum target);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTI64VPROC) (GLuint id, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUI64VPROC) (GLuint id, GLenum pname, GLuint64 *params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint index, GLuint divisor);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glBindFragDataLocationIndexed = NULL;
PFNGLGETFRAGDATAINDEXPROC glGetFragDataIndex = NULL;
PFNGLGENSAMPLERSPROC glGenSamplers = NULL;
PFNGLDELETESAMPLERSPROC glDeleteSamplers = NULL;
PFNGLISSAMPLERPROC glIsSampler = NULL;
PFNGLBINDSAMPLERPROC glBindSampler = NULL;
PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri = NULL;
PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv = NULL;
PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf = NULL;
PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv = NULL;
PFNGLSAMPLERPARAMETERIIVPROC glSamplerParameterIiv = NULL;
PFNGLSAMPLERPARAMETERIUIVPROC glSamplerParameterIuiv = NULL;
PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv = NULL;
PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIiv = NULL;
PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv = NULL;
PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameterIuiv = NULL;
PFNGLQUERYCOUNTERPROC glQueryCounter = NULL;
PFNGLGETQUERYOBJECTI64VPROC glGetQueryObjecti64v = NULL;
PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v = NULL;
PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor = NULL;
PFNGLVERTEXATTRIBP1UIPROC glVertexAttribP1ui = NULL;
PFNGLVERTEXATTRIBP1UIVPROC glVertexAttribP1uiv = NULL;
PFNGLVERTEXATTRIBP2UIPROC glVertexAttribP2ui = NULL;
PFNGLVERTEXATTRIBP2UIVPROC glVertexAttribP2uiv = NULL;
PFNGLVERTEXATTRIBP3UIPROC glVertexAttribP3ui = NULL;
PFNGLVERTEXATTRIBP3UIVPROC glVertexAttribP3uiv = NULL;
PFNGLVERTEXATTRIBP4UIPROC glVertexAttribP4ui = NULL;
PFNGLVERTEXATTRIBP4UIVPROC glVertexAttribP4uiv = NULL;
#endif /* GL_VERSION_3_3 */

#if SOL_TEST_VERSION(4, 0)
#define GL_SAMPLE_SHADING                 0x8C36
#define GL_MIN_SAMPLE_SHADING_VALUE       0x8C37
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5F
#define GL_TEXTURE_CUBE_MAP_ARRAY         0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY   0x900B
#define GL_SAMPLER_CUBE_MAP_ARRAY         0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW  0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY     0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#define GL_DRAW_INDIRECT_BUFFER           0x8F3F
#define GL_DRAW_INDIRECT_BUFFER_BINDING   0x8F43
#define GL_GEOMETRY_SHADER_INVOCATIONS    0x887F
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8E5B
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8E5C
#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8E5D
#define GL_MAX_VERTEX_STREAMS             0x8E71
#define GL_DOUBLE_VEC2                    0x8FFC
#define GL_DOUBLE_VEC3                    0x8FFD
#define GL_DOUBLE_VEC4                    0x8FFE
#define GL_DOUBLE_MAT2                    0x8F46
#define GL_DOUBLE_MAT3                    0x8F47
#define GL_DOUBLE_MAT4                    0x8F48
#define GL_DOUBLE_MAT2x3                  0x8F49
#define GL_DOUBLE_MAT2x4                  0x8F4A
#define GL_DOUBLE_MAT3x2                  0x8F4B
#define GL_DOUBLE_MAT3x4                  0x8F4C
#define GL_DOUBLE_MAT4x2                  0x8F4D
#define GL_DOUBLE_MAT4x3                  0x8F4E
#define GL_ACTIVE_SUBROUTINES             0x8DE5
#define GL_ACTIVE_SUBROUTINE_UNIFORMS     0x8DE6
#define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 0x8E47
#define GL_ACTIVE_SUBROUTINE_MAX_LENGTH   0x8E48
#define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 0x8E49
#define GL_MAX_SUBROUTINES                0x8DE7
#define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 0x8DE8
#define GL_NUM_COMPATIBLE_SUBROUTINES     0x8E4A
#define GL_COMPATIBLE_SUBROUTINES         0x8E4B
#define GL_PATCHES                        0x000E
#define GL_PATCH_VERTICES                 0x8E72
#define GL_PATCH_DEFAULT_INNER_LEVEL      0x8E73
#define GL_PATCH_DEFAULT_OUTER_LEVEL      0x8E74
#define GL_TESS_CONTROL_OUTPUT_VERTICES   0x8E75
#define GL_TESS_GEN_MODE                  0x8E76
#define GL_TESS_GEN_SPACING               0x8E77
#define GL_TESS_GEN_VERTEX_ORDER          0x8E78
#define GL_TESS_GEN_POINT_MODE            0x8E79
#define GL_ISOLINES                       0x8E7A
#define GL_FRACTIONAL_ODD                 0x8E7B
#define GL_FRACTIONAL_EVEN                0x8E7C
#define GL_MAX_PATCH_VERTICES             0x8E7D
#define GL_MAX_TESS_GEN_LEVEL             0x8E7E
#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E7F
#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E80
#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#define GL_MAX_TESS_PATCH_COMPONENTS      0x8E84
#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8E85
#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8E89
#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8E8A
#define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 0x886C
#define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 0x886D
#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E1E
#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E1F
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 0x84F0
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84F1
#define GL_TESS_EVALUATION_SHADER         0x8E87
#define GL_TESS_CONTROL_SHADER            0x8E88
#define GL_TRANSFORM_FEEDBACK             0x8E22
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 0x8E23
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 0x8E70
typedef void (APIENTRYP PFNGLMINSAMPLESHADINGPROC) (GLfloat value);
typedef void (APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint buf, GLenum mode);
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint buf, GLenum src, GLenum dst);
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum mode, const void *indirect);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const void *indirect);
typedef void (APIENTRYP PFNGLUNIFORM1DPROC) (GLint location, GLdouble x);
typedef void (APIENTRYP PFNGLUNIFORM2DPROC) (GLint location, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLUNIFORM3DPROC) (GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLUNIFORM4DPROC) (GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLUNIFORM1DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM2DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM3DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM4DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLGETUNIFORMDVPROC) (GLuint program, GLint location, GLdouble *params);
typedef GLint (APIENTRYP PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC) (GLuint program, GLenum shadertype, const GLchar *name);
typedef GLuint (APIENTRYP PFNGLGETSUBROUTINEINDEXPROC) (GLuint program, GLenum shadertype, const GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC) (GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINENAMEPROC) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLUNIFORMSUBROUTINESUIVPROC) (GLenum shadertype, GLsizei count, const GLuint *indices);
typedef void (APIENTRYP PFNGLGETUNIFORMSUBROUTINEUIVPROC) (GLenum shadertype, GLint location, GLuint *params);
typedef void (APIENTRYP PFNGLGETPROGRAMSTAGEIVPROC) (GLuint program, GLenum shadertype, GLenum pname, GLint *values);
typedef void (APIENTRYP PFNGLPATCHPARAMETERIPROC) (GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLPATCHPARAMETERFVPROC) (GLenum pname, const GLfloat *values);
typedef void (APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum target, GLuint id);
typedef void (APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, const GLuint *ids);
typedef void (APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
typedef GLboolean (APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
typedef void (APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKPROC) (GLenum mode, GLuint id);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC) (GLenum mode, GLuint id, GLuint stream);
typedef void (APIENTRYP PFNGLBEGINQUERYINDEXEDPROC) (GLenum target, GLuint index, GLuint id);
typedef void (APIENTRYP PFNGLENDQUERYINDEXEDPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLGETQUERYINDEXEDIVPROC) (GLenum target, GLuint index, GLenum pname, GLint *params);
PFNGLMINSAMPLESHADINGPROC glMinSampleShading = NULL;
PFNGLBLENDEQUATIONIPROC glBlendEquationi = NULL;
PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei = NULL;
PFNGLBLENDFUNCIPROC glBlendFunci = NULL;
PFNGLBLENDFUNCSEPARATEIPROC glBlendFuncSeparatei = NULL;
PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirect = NULL;
PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirect = NULL;
PFNGLUNIFORM1DPROC glUniform1d = NULL;
PFNGLUNIFORM2DPROC glUniform2d = NULL;
PFNGLUNIFORM3DPROC glUniform3d = NULL;
PFNGLUNIFORM4DPROC glUniform4d = NULL;
PFNGLUNIFORM1DVPROC glUniform1dv = NULL;
PFNGLUNIFORM2DVPROC glUniform2dv = NULL;
PFNGLUNIFORM3DVPROC glUniform3dv = NULL;
PFNGLUNIFORM4DVPROC glUniform4dv = NULL;
PFNGLUNIFORMMATRIX2DVPROC glUniformMatrix2dv = NULL;
PFNGLUNIFORMMATRIX3DVPROC glUniformMatrix3dv = NULL;
PFNGLUNIFORMMATRIX4DVPROC glUniformMatrix4dv = NULL;
PFNGLUNIFORMMATRIX2X3DVPROC glUniformMatrix2x3dv = NULL;
PFNGLUNIFORMMATRIX2X4DVPROC glUniformMatrix2x4dv = NULL;
PFNGLUNIFORMMATRIX3X2DVPROC glUniformMatrix3x2dv = NULL;
PFNGLUNIFORMMATRIX3X4DVPROC glUniformMatrix3x4dv = NULL;
PFNGLUNIFORMMATRIX4X2DVPROC glUniformMatrix4x2dv = NULL;
PFNGLUNIFORMMATRIX4X3DVPROC glUniformMatrix4x3dv = NULL;
PFNGLGETUNIFORMDVPROC glGetUniformdv = NULL;
PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glGetSubroutineUniformLocation = NULL;
PFNGLGETSUBROUTINEINDEXPROC glGetSubroutineIndex = NULL;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformiv = NULL;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformName = NULL;
PFNGLGETACTIVESUBROUTINENAMEPROC glGetActiveSubroutineName = NULL;
PFNGLUNIFORMSUBROUTINESUIVPROC glUniformSubroutinesuiv = NULL;
PFNGLGETUNIFORMSUBROUTINEUIVPROC glGetUniformSubroutineuiv = NULL;
PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageiv = NULL;
PFNGLPATCHPARAMETERIPROC glPatchParameteri = NULL;
PFNGLPATCHPARAMETERFVPROC glPatchParameterfv = NULL;
PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback = NULL;
PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks = NULL;
PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks = NULL;
PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback = NULL;
PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback = NULL;
PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback = NULL;
PFNGLDRAWTRANSFORMFEEDBACKPROC glDrawTransformFeedback = NULL;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glDrawTransformFeedbackStream = NULL;
PFNGLBEGINQUERYINDEXEDPROC glBeginQueryIndexed = NULL;
PFNGLENDQUERYINDEXEDPROC glEndQueryIndexed = NULL;
PFNGLGETQUERYINDEXEDIVPROC glGetQueryIndexediv = NULL;
#endif /* GL_VERSION_4_0 */

#if SOL_TEST_VERSION(4, 1)
#define GL_FIXED                          0x140C
#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#define GL_LOW_FLOAT                      0x8DF0
#define GL_MEDIUM_FLOAT                   0x8DF1
#define GL_HIGH_FLOAT                     0x8DF2
#define GL_LOW_INT                        0x8DF3
#define GL_MEDIUM_INT                     0x8DF4
#define GL_HIGH_INT                       0x8DF5
#define GL_SHADER_COMPILER                0x8DFA
#define GL_SHADER_BINARY_FORMATS          0x8DF8
#define GL_NUM_SHADER_BINARY_FORMATS      0x8DF9
#define GL_MAX_VERTEX_UNIFORM_VECTORS     0x8DFB
#define GL_MAX_VARYING_VECTORS            0x8DFC
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS   0x8DFD
#define GL_RGB565                         0x8D62
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257
#define GL_PROGRAM_BINARY_LENGTH          0x8741
#define GL_NUM_PROGRAM_BINARY_FORMATS     0x87FE
#define GL_PROGRAM_BINARY_FORMATS         0x87FF
#define GL_VERTEX_SHADER_BIT              0x00000001
#define GL_FRAGMENT_SHADER_BIT            0x00000002
#define GL_GEOMETRY_SHADER_BIT            0x00000004
#define GL_TESS_CONTROL_SHADER_BIT        0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT     0x00000010
#define GL_ALL_SHADER_BITS                0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE              0x8258
#define GL_ACTIVE_PROGRAM                 0x8259
#define GL_PROGRAM_PIPELINE_BINDING       0x825A
#define GL_MAX_VIEWPORTS                  0x825B
#define GL_VIEWPORT_SUBPIXEL_BITS         0x825C
#define GL_VIEWPORT_BOUNDS_RANGE          0x825D
#define GL_LAYER_PROVOKING_VERTEX         0x825E
#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX 0x825F
#define GL_UNDEFINED_VERTEX               0x8260
typedef void (APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (void);
typedef void (APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei count, const GLuint *shaders, GLenum binaryFormat, const void *binary, GLsizei length);
typedef void (APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
typedef void (APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
typedef void (APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint program, GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint program);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei count, const GLchar *const*strings);
typedef void (APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, const GLuint *pipelines);
typedef void (APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint program, GLint location, GLint v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint program, GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DPROC) (GLuint program, GLint location, GLdouble v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint program, GLint location, GLuint v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint program, GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DPROC) (GLuint index, GLdouble x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLDVPROC) (GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRYP PFNGLVIEWPORTARRAYVPROC) (GLuint first, GLsizei count, const GLfloat *v);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLSCISSORARRAYVPROC) (GLuint first, GLsizei count, const GLint *v);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDPROC) (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLDEPTHRANGEARRAYVPROC) (GLuint first, GLsizei count, const GLdouble *v);
typedef void (APIENTRYP PFNGLDEPTHRANGEINDEXEDPROC) (GLuint index, GLdouble n, GLdouble f);
typedef void (APIENTRYP PFNGLGETFLOATI_VPROC) (GLenum target, GLuint index, GLfloat *data);
typedef void (APIENTRYP PFNGLGETDOUBLEI_VPROC) (GLenum target, GLuint index, GLdouble *data);
PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler = NULL;
PFNGLSHADERBINARYPROC glShaderBinary = NULL;
PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat = NULL;
PFNGLDEPTHRANGEFPROC glDepthRangef = NULL;
PFNGLCLEARDEPTHFPROC glClearDepthf = NULL;
PFNGLGETPROGRAMBINARYPROC glGetProgramBinary = NULL;
PFNGLPROGRAMBINARYPROC glProgramBinary = NULL;
PFNGLPROGRAMPARAMETERIPROC glProgramParameteri = NULL;
PFNGLUSEPROGRAMSTAGESPROC glUseProgramStages = NULL;
PFNGLACTIVESHADERPROGRAMPROC glActiveShaderProgram = NULL;
PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv = NULL;
PFNGLBINDPROGRAMPIPELINEPROC glBindProgramPipeline = NULL;
PFNGLDELETEPROGRAMPIPELINESPROC glDeleteProgramPipelines = NULL;
PFNGLGENPROGRAMPIPELINESPROC glGenProgramPipelines = NULL;
PFNGLISPROGRAMPIPELINEPROC glIsProgramPipeline = NULL;
PFNGLGETPROGRAMPIPELINEIVPROC glGetProgramPipelineiv = NULL;
PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i = NULL;
PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1iv = NULL;
PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f = NULL;
PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fv = NULL;
PFNGLPROGRAMUNIFORM1DPROC glProgramUniform1d = NULL;
PFNGLPROGRAMUNIFORM1DVPROC glProgramUniform1dv = NULL;
PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1ui = NULL;
PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uiv = NULL;
PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2i = NULL;
PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2iv = NULL;
PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f = NULL;
PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fv = NULL;
PFNGLPROGRAMUNIFORM2DPROC glProgramUniform2d = NULL;
PFNGLPROGRAMUNIFORM2DVPROC glProgramUniform2dv = NULL;
PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2ui = NULL;
PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uiv = NULL;
PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3i = NULL;
PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3iv = NULL;
PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f = NULL;
PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv = NULL;
PFNGLPROGRAMUNIFORM3DPROC glProgramUniform3d = NULL;
PFNGLPROGRAMUNIFORM3DVPROC glProgramUniform3dv = NULL;
PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3ui = NULL;
PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uiv = NULL;
PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i = NULL;
PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4iv = NULL;
PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f = NULL;
PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv = NULL;
PFNGLPROGRAMUNIFORM4DPROC glProgramUniform4d = NULL;
PFNGLPROGRAMUNIFORM4DVPROC glProgramUniform4dv = NULL;
PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4ui = NULL;
PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uiv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2DVPROC glProgramUniformMatrix2dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC glProgramUniformMatrix3dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC glProgramUniformMatrix4dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glProgramUniformMatrix2x3dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glProgramUniformMatrix3x2dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glProgramUniformMatrix2x4dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glProgramUniformMatrix4x2dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glProgramUniformMatrix3x4dv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glProgramUniformMatrix4x3dv = NULL;
PFNGLVALIDATEPROGRAMPIPELINEPROC glValidateProgramPipeline = NULL;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC glGetProgramPipelineInfoLog = NULL;
PFNGLVERTEXATTRIBL1DPROC glVertexAttribL1d = NULL;
PFNGLVERTEXATTRIBL2DPROC glVertexAttribL2d = NULL;
PFNGLVERTEXATTRIBL3DPROC glVertexAttribL3d = NULL;
PFNGLVERTEXATTRIBL4DPROC glVertexAttribL4d = NULL;
PFNGLVERTEXATTRIBL1DVPROC glVertexAttribL1dv = NULL;
PFNGLVERTEXATTRIBL2DVPROC glVertexAttribL2dv = NULL;
PFNGLVERTEXATTRIBL3DVPROC glVertexAttribL3dv = NULL;
PFNGLVERTEXATTRIBL4DVPROC glVertexAttribL4dv = NULL;
PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttribLPointer = NULL;
PFNGLGETVERTEXATTRIBLDVPROC glGetVertexAttribLdv = NULL;
PFNGLVIEWPORTARRAYVPROC glViewportArrayv = NULL;
PFNGLVIEWPORTINDEXEDFPROC glViewportIndexedf = NULL;
PFNGLVIEWPORTINDEXEDFVPROC glViewportIndexedfv = NULL;
PFNGLSCISSORARRAYVPROC glScissorArrayv = NULL;
PFNGLSCISSORINDEXEDPROC glScissorIndexed = NULL;
PFNGLSCISSORINDEXEDVPROC glScissorIndexedv = NULL;
PFNGLDEPTHRANGEARRAYVPROC glDepthRangeArrayv = NULL;
PFNGLDEPTHRANGEINDEXEDPROC glDepthRangeIndexed = NULL;
PFNGLGETFLOATI_VPROC glGetFloati_v = NULL;
PFNGLGETDOUBLEI_VPROC glGetDoublei_v = NULL;
#endif /* GL_VERSION_4_1 */

#if SOL_TEST_VERSION(4, 2)
#define GL_COPY_READ_BUFFER_BINDING       0x8F36
#define GL_COPY_WRITE_BUFFER_BINDING      0x8F37
#define GL_TRANSFORM_FEEDBACK_ACTIVE      0x8E24
#define GL_TRANSFORM_FEEDBACK_PAUSED      0x8E23
#define GL_UNPACK_COMPRESSED_BLOCK_WIDTH  0x9127
#define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT 0x9128
#define GL_UNPACK_COMPRESSED_BLOCK_DEPTH  0x9129
#define GL_UNPACK_COMPRESSED_BLOCK_SIZE   0x912A
#define GL_PACK_COMPRESSED_BLOCK_WIDTH    0x912B
#define GL_PACK_COMPRESSED_BLOCK_HEIGHT   0x912C
#define GL_PACK_COMPRESSED_BLOCK_DEPTH    0x912D
#define GL_PACK_COMPRESSED_BLOCK_SIZE     0x912E
#define GL_NUM_SAMPLE_COUNTS              0x9380
#define GL_MIN_MAP_BUFFER_ALIGNMENT       0x90BC
#define GL_ATOMIC_COUNTER_BUFFER          0x92C0
#define GL_ATOMIC_COUNTER_BUFFER_BINDING  0x92C1
#define GL_ATOMIC_COUNTER_BUFFER_START    0x92C2
#define GL_ATOMIC_COUNTER_BUFFER_SIZE     0x92C3
#define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE 0x92C4
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS 0x92C5
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES 0x92C6
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER 0x92C7
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER 0x92C8
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 0x92C9
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER 0x92CA
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER 0x92CB
#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 0x92CC
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92CD
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92CE
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92CF
#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#define GL_MAX_VERTEX_ATOMIC_COUNTERS     0x92D2
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS   0x92D5
#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#define GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 0x92D8
#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 0x92DC
#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS  0x92D9
#define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX 0x92DA
#define GL_UNSIGNED_INT_ATOMIC_COUNTER    0x92DB
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT      0x00000002
#define GL_UNIFORM_BARRIER_BIT            0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT      0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
#define GL_COMMAND_BARRIER_BIT            0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT       0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT     0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT      0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT        0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT     0x00001000
#define GL_ALL_BARRIER_BITS               0xFFFFFFFF
#define GL_MAX_IMAGE_UNITS                0x8F38
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 0x8F39
#define GL_IMAGE_BINDING_NAME             0x8F3A
#define GL_IMAGE_BINDING_LEVEL            0x8F3B
#define GL_IMAGE_BINDING_LAYERED          0x8F3C
#define GL_IMAGE_BINDING_LAYER            0x8F3D
#define GL_IMAGE_BINDING_ACCESS           0x8F3E
#define GL_IMAGE_1D                       0x904C
#define GL_IMAGE_2D                       0x904D
#define GL_IMAGE_3D                       0x904E
#define GL_IMAGE_2D_RECT                  0x904F
#define GL_IMAGE_CUBE                     0x9050
#define GL_IMAGE_BUFFER                   0x9051
#define GL_IMAGE_1D_ARRAY                 0x9052
#define GL_IMAGE_2D_ARRAY                 0x9053
#define GL_IMAGE_CUBE_MAP_ARRAY           0x9054
#define GL_IMAGE_2D_MULTISAMPLE           0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY     0x9056
#define GL_INT_IMAGE_1D                   0x9057
#define GL_INT_IMAGE_2D                   0x9058
#define GL_INT_IMAGE_3D                   0x9059
#define GL_INT_IMAGE_2D_RECT              0x905A
#define GL_INT_IMAGE_CUBE                 0x905B
#define GL_INT_IMAGE_BUFFER               0x905C
#define GL_INT_IMAGE_1D_ARRAY             0x905D
#define GL_INT_IMAGE_2D_ARRAY             0x905E
#define GL_INT_IMAGE_CUBE_MAP_ARRAY       0x905F
#define GL_INT_IMAGE_2D_MULTISAMPLE       0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x9061
#define GL_UNSIGNED_INT_IMAGE_1D          0x9062
#define GL_UNSIGNED_INT_IMAGE_2D          0x9063
#define GL_UNSIGNED_INT_IMAGE_3D          0x9064
#define GL_UNSIGNED_INT_IMAGE_2D_RECT     0x9065
#define GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#define GL_UNSIGNED_INT_IMAGE_BUFFER      0x9067
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY    0x9068
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE 0x906B
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x906C
#define GL_MAX_IMAGE_SAMPLES              0x906D
#define GL_IMAGE_BINDING_FORMAT           0x906E
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 0x90C8
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#define GL_MAX_VERTEX_IMAGE_UNIFORMS      0x90CA
#define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
#define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS    0x90CD
#define GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#define GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#define GL_COMPRESSED_RGBA_BPTC_UNORM     0x8E8C
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM 0x8E8D
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT 0x8E8E
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT 0x8E8F
#define GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC) (GLuint program, GLuint bufferIndex, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
typedef void (APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
typedef void (APIENTRYP PFNGLTEXSTORAGE1DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC) (GLenum mode, GLuint id, GLsizei instancecount);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC) (GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glDrawArraysInstancedBaseInstance = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glDrawElementsInstancedBaseInstance = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glDrawElementsInstancedBaseVertexBaseInstance = NULL;
PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ = NULL;
PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glGetActiveAtomicCounterBufferiv = NULL;
PFNGLBINDIMAGETEXTUREPROC glBindImageTexture = NULL;
PFNGLMEMORYBARRIERPROC glMemoryBarrier = NULL;
PFNGLTEXSTORAGE1DPROC glTexStorage1D = NULL;
PFNGLTEXSTORAGE2DPROC glTexStorage2D = NULL;
PFNGLTEXSTORAGE3DPROC glTexStorage3D = NULL;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glDrawTransformFeedbackInstanced = NULL;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC glDrawTransformFeedbackStreamInstanced = NULL;
#endif /* GL_VERSION_4_2 */

#if SOL_TEST_VERSION(4, 3)
typedef void (APIENTRY  *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#define GL_NUM_SHADING_LANGUAGE_VERSIONS  0x82E9
#define GL_VERTEX_ATTRIB_ARRAY_LONG       0x874E
#define GL_COMPRESSED_RGB8_ETC2           0x9274
#define GL_COMPRESSED_SRGB8_ETC2          0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#define GL_COMPRESSED_R11_EAC             0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#define GL_COMPRESSED_RG11_EAC            0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#define GL_PRIMITIVE_RESTART_FIXED_INDEX  0x8D69
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#define GL_MAX_ELEMENT_INDEX              0x8D6B
#define GL_COMPUTE_SHADER                 0x91B9
#define GL_MAX_COMPUTE_UNIFORM_BLOCKS     0x91BB
#define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#define GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 0x8262
#define GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263
#define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#define GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266
#define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0x90EB
#define GL_MAX_COMPUTE_WORK_GROUP_COUNT   0x91BE
#define GL_MAX_COMPUTE_WORK_GROUP_SIZE    0x91BF
#define GL_COMPUTE_WORK_GROUP_SIZE        0x8267
#define GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER 0x90EC
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 0x90ED
#define GL_DISPATCH_INDIRECT_BUFFER       0x90EE
#define GL_DISPATCH_INDIRECT_BUFFER_BINDING 0x90EF
#define GL_COMPUTE_SHADER_BIT             0x00000020
#define GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION        0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM      0x8245
#define GL_DEBUG_SOURCE_API               0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM     0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER   0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY       0x8249
#define GL_DEBUG_SOURCE_APPLICATION       0x824A
#define GL_DEBUG_SOURCE_OTHER             0x824B
#define GL_DEBUG_TYPE_ERROR               0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#define GL_DEBUG_TYPE_PORTABILITY         0x824F
#define GL_DEBUG_TYPE_PERFORMANCE         0x8250
#define GL_DEBUG_TYPE_OTHER               0x8251
#define GL_MAX_DEBUG_MESSAGE_LENGTH       0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES      0x9144
#define GL_DEBUG_LOGGED_MESSAGES          0x9145
#define GL_DEBUG_SEVERITY_HIGH            0x9146
#define GL_DEBUG_SEVERITY_MEDIUM          0x9147
#define GL_DEBUG_SEVERITY_LOW             0x9148
#define GL_DEBUG_TYPE_MARKER              0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP          0x8269
#define GL_DEBUG_TYPE_POP_GROUP           0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH    0x826C
#define GL_DEBUG_GROUP_STACK_DEPTH        0x826D
#define GL_BUFFER                         0x82E0
#define GL_SHADER                         0x82E1
#define GL_PROGRAM                        0x82E2
#define GL_QUERY                          0x82E3
#define GL_PROGRAM_PIPELINE               0x82E4
#define GL_SAMPLER                        0x82E6
#define GL_MAX_LABEL_LENGTH               0x82E8
#define GL_DEBUG_OUTPUT                   0x92E0
#define GL_CONTEXT_FLAG_DEBUG_BIT         0x00000002
#define GL_MAX_UNIFORM_LOCATIONS          0x826E
#define GL_FRAMEBUFFER_DEFAULT_WIDTH      0x9310
#define GL_FRAMEBUFFER_DEFAULT_HEIGHT     0x9311
#define GL_FRAMEBUFFER_DEFAULT_LAYERS     0x9312
#define GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#define GL_MAX_FRAMEBUFFER_WIDTH          0x9315
#define GL_MAX_FRAMEBUFFER_HEIGHT         0x9316
#define GL_MAX_FRAMEBUFFER_LAYERS         0x9317
#define GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#define GL_INTERNALFORMAT_SUPPORTED       0x826F
#define GL_INTERNALFORMAT_PREFERRED       0x8270
#define GL_INTERNALFORMAT_RED_SIZE        0x8271
#define GL_INTERNALFORMAT_GREEN_SIZE      0x8272
#define GL_INTERNALFORMAT_BLUE_SIZE       0x8273
#define GL_INTERNALFORMAT_ALPHA_SIZE      0x8274
#define GL_INTERNALFORMAT_DEPTH_SIZE      0x8275
#define GL_INTERNALFORMAT_STENCIL_SIZE    0x8276
#define GL_INTERNALFORMAT_SHARED_SIZE     0x8277
#define GL_INTERNALFORMAT_RED_TYPE        0x8278
#define GL_INTERNALFORMAT_GREEN_TYPE      0x8279
#define GL_INTERNALFORMAT_BLUE_TYPE       0x827A
#define GL_INTERNALFORMAT_ALPHA_TYPE      0x827B
#define GL_INTERNALFORMAT_DEPTH_TYPE      0x827C
#define GL_INTERNALFORMAT_STENCIL_TYPE    0x827D
#define GL_MAX_WIDTH                      0x827E
#define GL_MAX_HEIGHT                     0x827F
#define GL_MAX_DEPTH                      0x8280
#define GL_MAX_LAYERS                     0x8281
#define GL_MAX_COMBINED_DIMENSIONS        0x8282
#define GL_COLOR_COMPONENTS               0x8283
#define GL_DEPTH_COMPONENTS               0x8284
#define GL_STENCIL_COMPONENTS             0x8285
#define GL_COLOR_RENDERABLE               0x8286
#define GL_DEPTH_RENDERABLE               0x8287
#define GL_STENCIL_RENDERABLE             0x8288
#define GL_FRAMEBUFFER_RENDERABLE         0x8289
#define GL_FRAMEBUFFER_RENDERABLE_LAYERED 0x828A
#define GL_FRAMEBUFFER_BLEND              0x828B
#define GL_READ_PIXELS                    0x828C
#define GL_READ_PIXELS_FORMAT             0x828D
#define GL_READ_PIXELS_TYPE               0x828E
#define GL_TEXTURE_IMAGE_FORMAT           0x828F
#define GL_TEXTURE_IMAGE_TYPE             0x8290
#define GL_GET_TEXTURE_IMAGE_FORMAT       0x8291
#define GL_GET_TEXTURE_IMAGE_TYPE         0x8292
#define GL_MIPMAP                         0x8293
#define GL_MANUAL_GENERATE_MIPMAP         0x8294
#define GL_AUTO_GENERATE_MIPMAP           0x8295
#define GL_COLOR_ENCODING                 0x8296
#define GL_SRGB_READ                      0x8297
#define GL_SRGB_WRITE                     0x8298
#define GL_FILTER                         0x829A
#define GL_VERTEX_TEXTURE                 0x829B
#define GL_TESS_CONTROL_TEXTURE           0x829C
#define GL_TESS_EVALUATION_TEXTURE        0x829D
#define GL_GEOMETRY_TEXTURE               0x829E
#define GL_FRAGMENT_TEXTURE               0x829F
#define GL_COMPUTE_TEXTURE                0x82A0
#define GL_TEXTURE_SHADOW                 0x82A1
#define GL_TEXTURE_GATHER                 0x82A2
#define GL_TEXTURE_GATHER_SHADOW          0x82A3
#define GL_SHADER_IMAGE_LOAD              0x82A4
#define GL_SHADER_IMAGE_STORE             0x82A5
#define GL_SHADER_IMAGE_ATOMIC            0x82A6
#define GL_IMAGE_TEXEL_SIZE               0x82A7
#define GL_IMAGE_COMPATIBILITY_CLASS      0x82A8
#define GL_IMAGE_PIXEL_FORMAT             0x82A9
#define GL_IMAGE_PIXEL_TYPE               0x82AA
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST 0x82AC
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST 0x82AD
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE 0x82AE
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE 0x82AF
#define GL_TEXTURE_COMPRESSED_BLOCK_WIDTH 0x82B1
#define GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT 0x82B2
#define GL_TEXTURE_COMPRESSED_BLOCK_SIZE  0x82B3
#define GL_CLEAR_BUFFER                   0x82B4
#define GL_TEXTURE_VIEW                   0x82B5
#define GL_VIEW_COMPATIBILITY_CLASS       0x82B6
#define GL_FULL_SUPPORT                   0x82B7
#define GL_CAVEAT_SUPPORT                 0x82B8
#define GL_IMAGE_CLASS_4_X_32             0x82B9
#define GL_IMAGE_CLASS_2_X_32             0x82BA
#define GL_IMAGE_CLASS_1_X_32             0x82BB
#define GL_IMAGE_CLASS_4_X_16             0x82BC
#define GL_IMAGE_CLASS_2_X_16             0x82BD
#define GL_IMAGE_CLASS_1_X_16             0x82BE
#define GL_IMAGE_CLASS_4_X_8              0x82BF
#define GL_IMAGE_CLASS_2_X_8              0x82C0
#define GL_IMAGE_CLASS_1_X_8              0x82C1
#define GL_IMAGE_CLASS_11_11_10           0x82C2
#define GL_IMAGE_CLASS_10_10_10_2         0x82C3
#define GL_VIEW_CLASS_128_BITS            0x82C4
#define GL_VIEW_CLASS_96_BITS             0x82C5
#define GL_VIEW_CLASS_64_BITS             0x82C6
#define GL_VIEW_CLASS_48_BITS             0x82C7
#define GL_VIEW_CLASS_32_BITS             0x82C8
#define GL_VIEW_CLASS_24_BITS             0x82C9
#define GL_VIEW_CLASS_16_BITS             0x82CA
#define GL_VIEW_CLASS_8_BITS              0x82CB
#define GL_VIEW_CLASS_S3TC_DXT1_RGB       0x82CC
#define GL_VIEW_CLASS_S3TC_DXT1_RGBA      0x82CD
#define GL_VIEW_CLASS_S3TC_DXT3_RGBA      0x82CE
#define GL_VIEW_CLASS_S3TC_DXT5_RGBA      0x82CF
#define GL_VIEW_CLASS_RGTC1_RED           0x82D0
#define GL_VIEW_CLASS_RGTC2_RG            0x82D1
#define GL_VIEW_CLASS_BPTC_UNORM          0x82D2
#define GL_VIEW_CLASS_BPTC_FLOAT          0x82D3
#define GL_UNIFORM                        0x92E1
#define GL_UNIFORM_BLOCK                  0x92E2
#define GL_PROGRAM_INPUT                  0x92E3
#define GL_PROGRAM_OUTPUT                 0x92E4
#define GL_BUFFER_VARIABLE                0x92E5
#define GL_SHADER_STORAGE_BLOCK           0x92E6
#define GL_VERTEX_SUBROUTINE              0x92E8
#define GL_TESS_CONTROL_SUBROUTINE        0x92E9
#define GL_TESS_EVALUATION_SUBROUTINE     0x92EA
#define GL_GEOMETRY_SUBROUTINE            0x92EB
#define GL_FRAGMENT_SUBROUTINE            0x92EC
#define GL_COMPUTE_SUBROUTINE             0x92ED
#define GL_VERTEX_SUBROUTINE_UNIFORM      0x92EE
#define GL_TESS_CONTROL_SUBROUTINE_UNIFORM 0x92EF
#define GL_TESS_EVALUATION_SUBROUTINE_UNIFORM 0x92F0
#define GL_GEOMETRY_SUBROUTINE_UNIFORM    0x92F1
#define GL_FRAGMENT_SUBROUTINE_UNIFORM    0x92F2
#define GL_COMPUTE_SUBROUTINE_UNIFORM     0x92F3
#define GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#define GL_ACTIVE_RESOURCES               0x92F5
#define GL_MAX_NAME_LENGTH                0x92F6
#define GL_MAX_NUM_ACTIVE_VARIABLES       0x92F7
#define GL_MAX_NUM_COMPATIBLE_SUBROUTINES 0x92F8
#define GL_NAME_LENGTH                    0x92F9
#define GL_TYPE                           0x92FA
#define GL_ARRAY_SIZE                     0x92FB
#define GL_OFFSET                         0x92FC
#define GL_BLOCK_INDEX                    0x92FD
#define GL_ARRAY_STRIDE                   0x92FE
#define GL_MATRIX_STRIDE                  0x92FF
#define GL_IS_ROW_MAJOR                   0x9300
#define GL_ATOMIC_COUNTER_BUFFER_INDEX    0x9301
#define GL_BUFFER_BINDING                 0x9302
#define GL_BUFFER_DATA_SIZE               0x9303
#define GL_NUM_ACTIVE_VARIABLES           0x9304
#define GL_ACTIVE_VARIABLES               0x9305
#define GL_REFERENCED_BY_VERTEX_SHADER    0x9306
#define GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#define GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#define GL_REFERENCED_BY_GEOMETRY_SHADER  0x9309
#define GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#define GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#define GL_TOP_LEVEL_ARRAY_SIZE           0x930C
#define GL_TOP_LEVEL_ARRAY_STRIDE         0x930D
#define GL_LOCATION                       0x930E
#define GL_LOCATION_INDEX                 0x930F
#define GL_IS_PER_PATCH                   0x92E7
#define GL_SHADER_STORAGE_BUFFER          0x90D2
#define GL_SHADER_STORAGE_BUFFER_BINDING  0x90D3
#define GL_SHADER_STORAGE_BUFFER_START    0x90D4
#define GL_SHADER_STORAGE_BUFFER_SIZE     0x90D5
#define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 0x90D6
#define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 0x90D7
#define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 0x90D8
#define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 0x90D9
#define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 0x90DA
#define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 0x90DB
#define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 0x90DC
#define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 0x90DD
#define GL_MAX_SHADER_STORAGE_BLOCK_SIZE  0x90DE
#define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 0x90DF
#define GL_SHADER_STORAGE_BARRIER_BIT     0x00002000
#define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#define GL_DEPTH_STENCIL_TEXTURE_MODE     0x90EA
#define GL_TEXTURE_BUFFER_OFFSET          0x919D
#define GL_TEXTURE_BUFFER_SIZE            0x919E
#define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 0x919F
#define GL_TEXTURE_VIEW_MIN_LEVEL         0x82DB
#define GL_TEXTURE_VIEW_NUM_LEVELS        0x82DC
#define GL_TEXTURE_VIEW_MIN_LAYER         0x82DD
#define GL_TEXTURE_VIEW_NUM_LAYERS        0x82DE
#define GL_TEXTURE_IMMUTABLE_LEVELS       0x82DF
#define GL_VERTEX_ATTRIB_BINDING          0x82D4
#define GL_VERTEX_ATTRIB_RELATIVE_OFFSET  0x82D5
#define GL_VERTEX_BINDING_DIVISOR         0x82D6
#define GL_VERTEX_BINDING_OFFSET          0x82D7
#define GL_VERTEX_BINDING_STRIDE          0x82D8
#define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82D9
#define GL_MAX_VERTEX_ATTRIB_BINDINGS     0x82DA
#define GL_VERTEX_BINDING_BUFFER          0x8F4F
typedef void (APIENTRYP PFNGLCLEARBUFFERDATAPROC) (GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARBUFFERSUBDATAPROC) (GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr indirect);
typedef void (APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
typedef void (APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATI64VPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 *params);
typedef void (APIENTRYP PFNGLINVALIDATETEXSUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLINVALIDATETEXIMAGEPROC) (GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERSUBDATAPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERDATAPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum target, GLsizei numAttachments, const GLenum *attachments);
typedef void (APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTPROC) (GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
typedef GLuint (APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei count, GLsizei *length, GLint *params);
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void (APIENTRYP PFNGLSHADERSTORAGEBLOCKBINDINGPROC) (GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
typedef void (APIENTRYP PFNGLTEXBUFFERRANGEPROC) (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXTUREVIEWPROC) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
typedef void (APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint divisor);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, const void *userParam);
typedef GLuint (APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef void (APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum source, GLuint id, GLsizei length, const GLchar *message);
typedef void (APIENTRYP PFNGLPOPDEBUGGROUPPROC) (void);
typedef void (APIENTRYP PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
typedef void (APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void (APIENTRYP PFNGLOBJECTPTRLABELPROC) (const void *ptr, GLsizei length, const GLchar *label);
typedef void (APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
PFNGLCLEARBUFFERDATAPROC glClearBufferData = NULL;
PFNGLCLEARBUFFERSUBDATAPROC glClearBufferSubData = NULL;
PFNGLDISPATCHCOMPUTEPROC glDispatchCompute = NULL;
PFNGLDISPATCHCOMPUTEINDIRECTPROC glDispatchComputeIndirect = NULL;
PFNGLCOPYIMAGESUBDATAPROC glCopyImageSubData = NULL;
PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteri = NULL;
PFNGLGETFRAMEBUFFERPARAMETERIVPROC glGetFramebufferParameteriv = NULL;
PFNGLGETINTERNALFORMATI64VPROC glGetInternalformati64v = NULL;
PFNGLINVALIDATETEXSUBIMAGEPROC glInvalidateTexSubImage = NULL;
PFNGLINVALIDATETEXIMAGEPROC glInvalidateTexImage = NULL;
PFNGLINVALIDATEBUFFERSUBDATAPROC glInvalidateBufferSubData = NULL;
PFNGLINVALIDATEBUFFERDATAPROC glInvalidateBufferData = NULL;
PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer = NULL;
PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer = NULL;
PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirect = NULL;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirect = NULL;
PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceiv = NULL;
PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndex = NULL;
PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName = NULL;
PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv = NULL;
PFNGLGETPROGRAMRESOURCELOCATIONPROC glGetProgramResourceLocation = NULL;
PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glGetProgramResourceLocationIndex = NULL;
PFNGLSHADERSTORAGEBLOCKBINDINGPROC glShaderStorageBlockBinding = NULL;
PFNGLTEXBUFFERRANGEPROC glTexBufferRange = NULL;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisample = NULL;
PFNGLTEXSTORAGE3DMULTISAMPLEPROC glTexStorage3DMultisample = NULL;
PFNGLTEXTUREVIEWPROC glTextureView = NULL;
PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer = NULL;
PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormat = NULL;
PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormat = NULL;
PFNGLVERTEXATTRIBLFORMATPROC glVertexAttribLFormat = NULL;
PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBinding = NULL;
PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisor = NULL;
PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl = NULL;
PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsert = NULL;
PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback = NULL;
PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLog = NULL;
PFNGLPUSHDEBUGGROUPPROC glPushDebugGroup = NULL;
PFNGLPOPDEBUGGROUPPROC glPopDebugGroup = NULL;
PFNGLOBJECTLABELPROC glObjectLabel = NULL;
PFNGLGETOBJECTLABELPROC glGetObjectLabel = NULL;
PFNGLOBJECTPTRLABELPROC glObjectPtrLabel = NULL;
PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabel = NULL;
#endif /* GL_VERSION_4_3 */

#if SOL_TEST_VERSION(4, 4)
#define GL_MAX_VERTEX_ATTRIB_STRIDE       0x82E5
#define GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#define GL_TEXTURE_BUFFER_BINDING         0x8C2A
#define GL_MAP_PERSISTENT_BIT             0x0040
#define GL_MAP_COHERENT_BIT               0x0080
#define GL_DYNAMIC_STORAGE_BIT            0x0100
#define GL_CLIENT_STORAGE_BIT             0x0200
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT 0x00004000
#define GL_BUFFER_IMMUTABLE_STORAGE       0x821F
#define GL_BUFFER_STORAGE_FLAGS           0x8220
#define GL_CLEAR_TEXTURE                  0x9365
#define GL_LOCATION_COMPONENT             0x934A
#define GL_TRANSFORM_FEEDBACK_BUFFER_INDEX 0x934B
#define GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE 0x934C
#define GL_QUERY_BUFFER                   0x9192
#define GL_QUERY_BUFFER_BARRIER_BIT       0x00008000
#define GL_QUERY_BUFFER_BINDING           0x9193
#define GL_QUERY_RESULT_NO_WAIT           0x9194
#define GL_MIRROR_CLAMP_TO_EDGE           0x8743
typedef void (APIENTRYP PFNGLBUFFERSTORAGEPROC) (GLenum target, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (APIENTRYP PFNGLCLEARTEXIMAGEPROC) (GLuint texture, GLint level, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARTEXSUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLBINDBUFFERSBASEPROC) (GLenum target, GLuint first, GLsizei count, const GLuint *buffers);
typedef void (APIENTRYP PFNGLBINDBUFFERSRANGEPROC) (GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes);
typedef void (APIENTRYP PFNGLBINDTEXTURESPROC) (GLuint first, GLsizei count, const GLuint *textures);
typedef void (APIENTRYP PFNGLBINDSAMPLERSPROC) (GLuint first, GLsizei count, const GLuint *samplers);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTURESPROC) (GLuint first, GLsizei count, const GLuint *textures);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERSPROC) (GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
PFNGLBUFFERSTORAGEPROC glBufferStorage = NULL;
PFNGLCLEARTEXIMAGEPROC glClearTexImage = NULL;
PFNGLCLEARTEXSUBIMAGEPROC glClearTexSubImage = NULL;
PFNGLBINDBUFFERSBASEPROC glBindBuffersBase = NULL;
PFNGLBINDBUFFERSRANGEPROC glBindBuffersRange = NULL;
PFNGLBINDTEXTURESPROC glBindTextures = NULL;
PFNGLBINDSAMPLERSPROC glBindSamplers = NULL;
PFNGLBINDIMAGETEXTURESPROC glBindImageTextures = NULL;
PFNGLBINDVERTEXBUFFERSPROC glBindVertexBuffers = NULL;
#endif /* GL_VERSION_4_4 */

#if SOL_TEST_VERSION(4, 5)
#define GL_CONTEXT_LOST                   0x0507
#define GL_NEGATIVE_ONE_TO_ONE            0x935E
#define GL_ZERO_TO_ONE                    0x935F
#define GL_CLIP_ORIGIN                    0x935C
#define GL_CLIP_DEPTH_MODE                0x935D
#define GL_QUERY_WAIT_INVERTED            0x8E17
#define GL_QUERY_NO_WAIT_INVERTED         0x8E18
#define GL_QUERY_BY_REGION_WAIT_INVERTED  0x8E19
#define GL_QUERY_BY_REGION_NO_WAIT_INVERTED 0x8E1A
#define GL_MAX_CULL_DISTANCES             0x82F9
#define GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES 0x82FA
#define GL_TEXTURE_TARGET                 0x1006
#define GL_QUERY_TARGET                   0x82EA
#define GL_GUILTY_CONTEXT_RESET           0x8253
#define GL_INNOCENT_CONTEXT_RESET         0x8254
#define GL_UNKNOWN_CONTEXT_RESET          0x8255
#define GL_RESET_NOTIFICATION_STRATEGY    0x8256
#define GL_LOSE_CONTEXT_ON_RESET          0x8252
#define GL_NO_RESET_NOTIFICATION          0x8261
#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT 0x00000004
#define GL_CONTEXT_RELEASE_BEHAVIOR       0x82FB
#define GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
typedef void (APIENTRYP PFNGLCLIPCONTROLPROC) (GLenum origin, GLenum depth);
typedef void (APIENTRYP PFNGLCREATETRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC) (GLuint xfb, GLuint index, GLuint buffer);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC) (GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKIVPROC) (GLuint xfb, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI_VPROC) (GLuint xfb, GLenum pname, GLuint index, GLint *param);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI64_VPROC) (GLuint xfb, GLenum pname, GLuint index, GLint64 *param);
typedef void (APIENTRYP PFNGLCREATEBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSTORAGEPROC) (GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (APIENTRYP PFNGLNAMEDBUFFERDATAPROC) (GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSUBDATAPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (APIENTRYP PFNGLCOPYNAMEDBUFFERSUBDATAPROC) (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERDATAPROC) (GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERSUBDATAPROC) (GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void *(APIENTRYP PFNGLMAPNAMEDBUFFERPROC) (GLuint buffer, GLenum access);
typedef void *(APIENTRYP PFNGLMAPNAMEDBUFFERRANGEPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef GLboolean (APIENTRYP PFNGLUNMAPNAMEDBUFFERPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERIVPROC) (GLuint buffer, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERI64VPROC) (GLuint buffer, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPOINTERVPROC) (GLuint buffer, GLenum pname, void **params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERSUBDATAPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, void *data);
typedef void (APIENTRYP PFNGLCREATEFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC) (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC) (GLuint framebuffer, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC) (GLuint framebuffer, GLenum buf);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC) (GLuint framebuffer, GLsizei n, const GLenum *bufs);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC) (GLuint framebuffer, GLenum src);
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC) (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments);
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC) (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERIVPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFVPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFIPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef void (APIENTRYP PFNGLBLITNAMEDFRAMEBUFFERPROC) (GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef GLenum (APIENTRYP PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC) (GLuint framebuffer, GLenum target);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC) (GLuint framebuffer, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLCREATERENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEPROC) (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC) (GLuint renderbuffer, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLCREATETEXTURESPROC) (GLenum target, GLsizei n, GLuint *textures);
typedef void (APIENTRYP PFNGLTEXTUREBUFFERPROC) (GLuint texture, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLTEXTUREBUFFERRANGEPROC) (GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE1DPROC) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DPROC) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DPROC) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE1DPROC) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE2DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE3DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE1DPROC) (GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE2DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE3DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFPROC) (GLuint texture, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFVPROC) (GLuint texture, GLenum pname, const GLfloat *param);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIPROC) (GLuint texture, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIIVPROC) (GLuint texture, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIUIVPROC) (GLuint texture, GLenum pname, const GLuint *params);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIVPROC) (GLuint texture, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLGENERATETEXTUREMIPMAPPROC) (GLuint texture);
typedef void (APIENTRYP PFNGLBINDTEXTUREUNITPROC) (GLuint unit, GLuint texture);
typedef void (APIENTRYP PFNGLGETTEXTUREIMAGEPROC) (GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC) (GLuint texture, GLint level, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERFVPROC) (GLuint texture, GLint level, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERIVPROC) (GLuint texture, GLint level, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERFVPROC) (GLuint texture, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIIVPROC) (GLuint texture, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIUIVPROC) (GLuint texture, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIVPROC) (GLuint texture, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLCREATEVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef void (APIENTRYP PFNGLDISABLEVERTEXARRAYATTRIBPROC) (GLuint vaobj, GLuint index);
typedef void (APIENTRYP PFNGLENABLEVERTEXARRAYATTRIBPROC) (GLuint vaobj, GLuint index);
typedef void (APIENTRYP PFNGLVERTEXARRAYELEMENTBUFFERPROC) (GLuint vaobj, GLuint buffer);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERPROC) (GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERSPROC) (GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBBINDINGPROC) (GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBFORMATPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBIFORMATPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBLFORMATPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYBINDINGDIVISORPROC) (GLuint vaobj, GLuint bindingindex, GLuint divisor);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYIVPROC) (GLuint vaobj, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXEDIVPROC) (GLuint vaobj, GLuint index, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXED64IVPROC) (GLuint vaobj, GLuint index, GLenum pname, GLint64 *param);
typedef void (APIENTRYP PFNGLCREATESAMPLERSPROC) (GLsizei n, GLuint *samplers);
typedef void (APIENTRYP PFNGLCREATEPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
typedef void (APIENTRYP PFNGLCREATEQUERIESPROC) (GLenum target, GLsizei n, GLuint *ids);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTI64VPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTIVPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUI64VPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUIVPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
typedef void (APIENTRYP PFNGLGETTEXTURESUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels);
typedef GLenum (APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC) (void);
typedef void (APIENTRYP PFNGLGETNCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint lod, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETNTEXIMAGEPROC) (GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETNUNIFORMDVPROC) (GLuint program, GLint location, GLsizei bufSize, GLdouble *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMFVPROC) (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMIVPROC) (GLuint program, GLint location, GLsizei bufSize, GLint *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMUIVPROC) (GLuint program, GLint location, GLsizei bufSize, GLuint *params);
typedef void (APIENTRYP PFNGLREADNPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
typedef void (APIENTRYP PFNGLTEXTUREBARRIERPROC) (void);
PFNGLCLIPCONTROLPROC glClipControl = NULL;
PFNGLCREATETRANSFORMFEEDBACKSPROC glCreateTransformFeedbacks = NULL;
PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC glTransformFeedbackBufferBase = NULL;
PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC glTransformFeedbackBufferRange = NULL;
PFNGLGETTRANSFORMFEEDBACKIVPROC glGetTransformFeedbackiv = NULL;
PFNGLGETTRANSFORMFEEDBACKI_VPROC glGetTransformFeedbacki_v = NULL;
PFNGLGETTRANSFORMFEEDBACKI64_VPROC glGetTransformFeedbacki64_v = NULL;
PFNGLCREATEBUFFERSPROC glCreateBuffers = NULL;
PFNGLNAMEDBUFFERSTORAGEPROC glNamedBufferStorage = NULL;
PFNGLNAMEDBUFFERDATAPROC glNamedBufferData = NULL;
PFNGLNAMEDBUFFERSUBDATAPROC glNamedBufferSubData = NULL;
PFNGLCOPYNAMEDBUFFERSUBDATAPROC glCopyNamedBufferSubData = NULL;
PFNGLCLEARNAMEDBUFFERDATAPROC glClearNamedBufferData = NULL;
PFNGLCLEARNAMEDBUFFERSUBDATAPROC glClearNamedBufferSubData = NULL;
PFNGLMAPNAMEDBUFFERPROC glMapNamedBuffer = NULL;
PFNGLMAPNAMEDBUFFERRANGEPROC glMapNamedBufferRange = NULL;
PFNGLUNMAPNAMEDBUFFERPROC glUnmapNamedBuffer = NULL;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC glFlushMappedNamedBufferRange = NULL;
PFNGLGETNAMEDBUFFERPARAMETERIVPROC glGetNamedBufferParameteriv = NULL;
PFNGLGETNAMEDBUFFERPARAMETERI64VPROC glGetNamedBufferParameteri64v = NULL;
PFNGLGETNAMEDBUFFERPOINTERVPROC glGetNamedBufferPointerv = NULL;
PFNGLGETNAMEDBUFFERSUBDATAPROC glGetNamedBufferSubData = NULL;
PFNGLCREATEFRAMEBUFFERSPROC glCreateFramebuffers = NULL;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC glNamedFramebufferRenderbuffer = NULL;
PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC glNamedFramebufferParameteri = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC glNamedFramebufferTexture = NULL;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC glNamedFramebufferTextureLayer = NULL;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC glNamedFramebufferDrawBuffer = NULL;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC glNamedFramebufferDrawBuffers = NULL;
PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC glNamedFramebufferReadBuffer = NULL;
PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC glInvalidateNamedFramebufferData = NULL;
PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC glInvalidateNamedFramebufferSubData = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERIVPROC glClearNamedFramebufferiv = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC glClearNamedFramebufferuiv = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERFVPROC glClearNamedFramebufferfv = NULL;
PFNGLCLEARNAMEDFRAMEBUFFERFIPROC glClearNamedFramebufferfi = NULL;
PFNGLBLITNAMEDFRAMEBUFFERPROC glBlitNamedFramebuffer = NULL;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC glCheckNamedFramebufferStatus = NULL;
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC glGetNamedFramebufferParameteriv = NULL;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetNamedFramebufferAttachmentParameteriv = NULL;
PFNGLCREATERENDERBUFFERSPROC glCreateRenderbuffers = NULL;
PFNGLNAMEDRENDERBUFFERSTORAGEPROC glNamedRenderbufferStorage = NULL;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC glNamedRenderbufferStorageMultisample = NULL;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC glGetNamedRenderbufferParameteriv = NULL;
PFNGLCREATETEXTURESPROC glCreateTextures = NULL;
PFNGLTEXTUREBUFFERPROC glTextureBuffer = NULL;
PFNGLTEXTUREBUFFERRANGEPROC glTextureBufferRange = NULL;
PFNGLTEXTURESTORAGE1DPROC glTextureStorage1D = NULL;
PFNGLTEXTURESTORAGE2DPROC glTextureStorage2D = NULL;
PFNGLTEXTURESTORAGE3DPROC glTextureStorage3D = NULL;
PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC glTextureStorage2DMultisample = NULL;
PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC glTextureStorage3DMultisample = NULL;
PFNGLTEXTURESUBIMAGE1DPROC glTextureSubImage1D = NULL;
PFNGLTEXTURESUBIMAGE2DPROC glTextureSubImage2D = NULL;
PFNGLTEXTURESUBIMAGE3DPROC glTextureSubImage3D = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC glCompressedTextureSubImage1D = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC glCompressedTextureSubImage2D = NULL;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC glCompressedTextureSubImage3D = NULL;
PFNGLCOPYTEXTURESUBIMAGE1DPROC glCopyTextureSubImage1D = NULL;
PFNGLCOPYTEXTURESUBIMAGE2DPROC glCopyTextureSubImage2D = NULL;
PFNGLCOPYTEXTURESUBIMAGE3DPROC glCopyTextureSubImage3D = NULL;
PFNGLTEXTUREPARAMETERFPROC glTextureParameterf = NULL;
PFNGLTEXTUREPARAMETERFVPROC glTextureParameterfv = NULL;
PFNGLTEXTUREPARAMETERIPROC glTextureParameteri = NULL;
PFNGLTEXTUREPARAMETERIIVPROC glTextureParameterIiv = NULL;
PFNGLTEXTUREPARAMETERIUIVPROC glTextureParameterIuiv = NULL;
PFNGLTEXTUREPARAMETERIVPROC glTextureParameteriv = NULL;
PFNGLGENERATETEXTUREMIPMAPPROC glGenerateTextureMipmap = NULL;
PFNGLBINDTEXTUREUNITPROC glBindTextureUnit = NULL;
PFNGLGETTEXTUREIMAGEPROC glGetTextureImage = NULL;
PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC glGetCompressedTextureImage = NULL;
PFNGLGETTEXTURELEVELPARAMETERFVPROC glGetTextureLevelParameterfv = NULL;
PFNGLGETTEXTURELEVELPARAMETERIVPROC glGetTextureLevelParameteriv = NULL;
PFNGLGETTEXTUREPARAMETERFVPROC glGetTextureParameterfv = NULL;
PFNGLGETTEXTUREPARAMETERIIVPROC glGetTextureParameterIiv = NULL;
PFNGLGETTEXTUREPARAMETERIUIVPROC glGetTextureParameterIuiv = NULL;
PFNGLGETTEXTUREPARAMETERIVPROC glGetTextureParameteriv = NULL;
PFNGLCREATEVERTEXARRAYSPROC glCreateVertexArrays = NULL;
PFNGLDISABLEVERTEXARRAYATTRIBPROC glDisableVertexArrayAttrib = NULL;
PFNGLENABLEVERTEXARRAYATTRIBPROC glEnableVertexArrayAttrib = NULL;
PFNGLVERTEXARRAYELEMENTBUFFERPROC glVertexArrayElementBuffer = NULL;
PFNGLVERTEXARRAYVERTEXBUFFERPROC glVertexArrayVertexBuffer = NULL;
PFNGLVERTEXARRAYVERTEXBUFFERSPROC glVertexArrayVertexBuffers = NULL;
PFNGLVERTEXARRAYATTRIBBINDINGPROC glVertexArrayAttribBinding = NULL;
PFNGLVERTEXARRAYATTRIBFORMATPROC glVertexArrayAttribFormat = NULL;
PFNGLVERTEXARRAYATTRIBIFORMATPROC glVertexArrayAttribIFormat = NULL;
PFNGLVERTEXARRAYATTRIBLFORMATPROC glVertexArrayAttribLFormat = NULL;
PFNGLVERTEXARRAYBINDINGDIVISORPROC glVertexArrayBindingDivisor = NULL;
PFNGLGETVERTEXARRAYIVPROC glGetVertexArrayiv = NULL;
PFNGLGETVERTEXARRAYINDEXEDIVPROC glGetVertexArrayIndexediv = NULL;
PFNGLGETVERTEXARRAYINDEXED64IVPROC glGetVertexArrayIndexed64iv = NULL;
PFNGLCREATESAMPLERSPROC glCreateSamplers = NULL;
PFNGLCREATEPROGRAMPIPELINESPROC glCreateProgramPipelines = NULL;
PFNGLCREATEQUERIESPROC glCreateQueries = NULL;
PFNGLGETQUERYBUFFEROBJECTI64VPROC glGetQueryBufferObjecti64v = NULL;
PFNGLGETQUERYBUFFEROBJECTIVPROC glGetQueryBufferObjectiv = NULL;
PFNGLGETQUERYBUFFEROBJECTUI64VPROC glGetQueryBufferObjectui64v = NULL;
PFNGLGETQUERYBUFFEROBJECTUIVPROC glGetQueryBufferObjectuiv = NULL;
PFNGLMEMORYBARRIERBYREGIONPROC glMemoryBarrierByRegion = NULL;
PFNGLGETTEXTURESUBIMAGEPROC glGetTextureSubImage = NULL;
PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC glGetCompressedTextureSubImage = NULL;
PFNGLGETGRAPHICSRESETSTATUSPROC glGetGraphicsResetStatus = NULL;
PFNGLGETNCOMPRESSEDTEXIMAGEPROC glGetnCompressedTexImage = NULL;
PFNGLGETNTEXIMAGEPROC glGetnTexImage = NULL;
PFNGLGETNUNIFORMDVPROC glGetnUniformdv = NULL;
PFNGLGETNUNIFORMFVPROC glGetnUniformfv = NULL;
PFNGLGETNUNIFORMIVPROC glGetnUniformiv = NULL;
PFNGLGETNUNIFORMUIVPROC glGetnUniformuiv = NULL;
PFNGLREADNPIXELSPROC glReadnPixels = NULL;
PFNGLTEXTUREBARRIERPROC glTextureBarrier = NULL;
#endif /* GL_VERSION_4_5 */

#if SOL_TEST_VERSION(4, 6)
#define GL_SHADER_BINARY_FORMAT_SPIR_V    0x9551
#define GL_SPIR_V_BINARY                  0x9552
#define GL_PARAMETER_BUFFER               0x80EE
#define GL_PARAMETER_BUFFER_BINDING       0x80EF
#define GL_CONTEXT_FLAG_NO_ERROR_BIT      0x00000008
#define GL_VERTICES_SUBMITTED             0x82EE
#define GL_PRIMITIVES_SUBMITTED           0x82EF
#define GL_VERTEX_SHADER_INVOCATIONS      0x82F0
#define GL_TESS_CONTROL_SHADER_PATCHES    0x82F1
#define GL_TESS_EVALUATION_SHADER_INVOCATIONS 0x82F2
#define GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED 0x82F3
#define GL_FRAGMENT_SHADER_INVOCATIONS    0x82F4
#define GL_COMPUTE_SHADER_INVOCATIONS     0x82F5
#define GL_CLIPPING_INPUT_PRIMITIVES      0x82F6
#define GL_CLIPPING_OUTPUT_PRIMITIVES     0x82F7
#define GL_POLYGON_OFFSET_CLAMP           0x8E1B
#define GL_SPIR_V_EXTENSIONS              0x9553
#define GL_NUM_SPIR_V_EXTENSIONS          0x9554
#define GL_TEXTURE_MAX_ANISOTROPY         0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY     0x84FF
#define GL_TRANSFORM_FEEDBACK_OVERFLOW    0x82EC
#define GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW 0x82ED
typedef void (APIENTRYP PFNGLSPECIALIZESHADERPROC) (GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC) (GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC) (GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETCLAMPPROC) (GLfloat factor, GLfloat units, GLfloat clamp);
PFNGLSPECIALIZESHADERPROC glSpecializeShader = NULL;
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC glMultiDrawArraysIndirectCount = NULL;
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC glMultiDrawElementsIndirectCount = NULL;
PFNGLPOLYGONOFFSETCLAMPPROC glPolygonOffsetClamp = NULL;
#endif /* GL_VERSION_4_6 */

extern void* sol_loadOpenGLFunction(const char* name);

void sol_loadOpenGL() {

#if SOL_TEST_VERSION(1, 0)
    glCullFace = (PFNGLCULLFACEPROC) sol_loadOpenGLFunction("glCullFace");
    glFrontFace = (PFNGLFRONTFACEPROC) sol_loadOpenGLFunction("glFrontFace");
    glHint = (PFNGLHINTPROC) sol_loadOpenGLFunction("glHint");
    glLineWidth = (PFNGLLINEWIDTHPROC) sol_loadOpenGLFunction("glLineWidth");
    glPointSize = (PFNGLPOINTSIZEPROC) sol_loadOpenGLFunction("glPointSize");
    glPolygonMode = (PFNGLPOLYGONMODEPROC) sol_loadOpenGLFunction("glPolygonMode");
    glScissor = (PFNGLSCISSORPROC) sol_loadOpenGLFunction("glScissor");
    glTexParameterf = (PFNGLTEXPARAMETERFPROC) sol_loadOpenGLFunction("glTexParameterf");
    glTexParameterfv = (PFNGLTEXPARAMETERFVPROC) sol_loadOpenGLFunction("glTexParameterfv");
    glTexParameteri = (PFNGLTEXPARAMETERIPROC) sol_loadOpenGLFunction("glTexParameteri");
    glTexParameteriv = (PFNGLTEXPARAMETERIVPROC) sol_loadOpenGLFunction("glTexParameteriv");
    glTexImage1D = (PFNGLTEXIMAGE1DPROC) sol_loadOpenGLFunction("glTexImage1D");
    glTexImage2D = (PFNGLTEXIMAGE2DPROC) sol_loadOpenGLFunction("glTexImage2D");
    glDrawBuffer = (PFNGLDRAWBUFFERPROC) sol_loadOpenGLFunction("glDrawBuffer");
    glClear = (PFNGLCLEARPROC) sol_loadOpenGLFunction("glClear");
    glClearColor = (PFNGLCLEARCOLORPROC) sol_loadOpenGLFunction("glClearColor");
    glClearStencil = (PFNGLCLEARSTENCILPROC) sol_loadOpenGLFunction("glClearStencil");
    glClearDepth = (PFNGLCLEARDEPTHPROC) sol_loadOpenGLFunction("glClearDepth");
    glStencilMask = (PFNGLSTENCILMASKPROC) sol_loadOpenGLFunction("glStencilMask");
    glColorMask = (PFNGLCOLORMASKPROC) sol_loadOpenGLFunction("glColorMask");
    glDepthMask = (PFNGLDEPTHMASKPROC) sol_loadOpenGLFunction("glDepthMask");
    glDisable = (PFNGLDISABLEPROC) sol_loadOpenGLFunction("glDisable");
    glEnable = (PFNGLENABLEPROC) sol_loadOpenGLFunction("glEnable");
    glFinish = (PFNGLFINISHPROC) sol_loadOpenGLFunction("glFinish");
    glFlush = (PFNGLFLUSHPROC) sol_loadOpenGLFunction("glFlush");
    glBlendFunc = (PFNGLBLENDFUNCPROC) sol_loadOpenGLFunction("glBlendFunc");
    glLogicOp = (PFNGLLOGICOPPROC) sol_loadOpenGLFunction("glLogicOp");
    glStencilFunc = (PFNGLSTENCILFUNCPROC) sol_loadOpenGLFunction("glStencilFunc");
    glStencilOp = (PFNGLSTENCILOPPROC) sol_loadOpenGLFunction("glStencilOp");
    glDepthFunc = (PFNGLDEPTHFUNCPROC) sol_loadOpenGLFunction("glDepthFunc");
    glPixelStoref = (PFNGLPIXELSTOREFPROC) sol_loadOpenGLFunction("glPixelStoref");
    glPixelStorei = (PFNGLPIXELSTOREIPROC) sol_loadOpenGLFunction("glPixelStorei");
    glReadBuffer = (PFNGLREADBUFFERPROC) sol_loadOpenGLFunction("glReadBuffer");
    glReadPixels = (PFNGLREADPIXELSPROC) sol_loadOpenGLFunction("glReadPixels");
    glGetBooleanv = (PFNGLGETBOOLEANVPROC) sol_loadOpenGLFunction("glGetBooleanv");
    glGetDoublev = (PFNGLGETDOUBLEVPROC) sol_loadOpenGLFunction("glGetDoublev");
    glGetError = (PFNGLGETERRORPROC) sol_loadOpenGLFunction("glGetError");
    glGetFloatv = (PFNGLGETFLOATVPROC) sol_loadOpenGLFunction("glGetFloatv");
    glGetIntegerv = (PFNGLGETINTEGERVPROC) sol_loadOpenGLFunction("glGetIntegerv");
    glGetString = (PFNGLGETSTRINGPROC) sol_loadOpenGLFunction("glGetString");
    glGetTexImage = (PFNGLGETTEXIMAGEPROC) sol_loadOpenGLFunction("glGetTexImage");
    glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC) sol_loadOpenGLFunction("glGetTexParameterfv");
    glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC) sol_loadOpenGLFunction("glGetTexParameteriv");
    glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC) sol_loadOpenGLFunction("glGetTexLevelParameterfv");
    glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC) sol_loadOpenGLFunction("glGetTexLevelParameteriv");
    glIsEnabled = (PFNGLISENABLEDPROC) sol_loadOpenGLFunction("glIsEnabled");
    glDepthRange = (PFNGLDEPTHRANGEPROC) sol_loadOpenGLFunction("glDepthRange");
    glViewport = (PFNGLVIEWPORTPROC) sol_loadOpenGLFunction("glViewport");
#endif /* GL_VERSION_1_0 */

#if SOL_TEST_VERSION(1, 1)
    glDrawArrays = (PFNGLDRAWARRAYSPROC) sol_loadOpenGLFunction("glDrawArrays");
    glDrawElements = (PFNGLDRAWELEMENTSPROC) sol_loadOpenGLFunction("glDrawElements");
    glGetPointerv = (PFNGLGETPOINTERVPROC) sol_loadOpenGLFunction("glGetPointerv");
    glPolygonOffset = (PFNGLPOLYGONOFFSETPROC) sol_loadOpenGLFunction("glPolygonOffset");
    glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC) sol_loadOpenGLFunction("glCopyTexImage1D");
    glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC) sol_loadOpenGLFunction("glCopyTexImage2D");
    glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC) sol_loadOpenGLFunction("glCopyTexSubImage1D");
    glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) sol_loadOpenGLFunction("glCopyTexSubImage2D");
    glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC) sol_loadOpenGLFunction("glTexSubImage1D");
    glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC) sol_loadOpenGLFunction("glTexSubImage2D");
    glBindTexture = (PFNGLBINDTEXTUREPROC) sol_loadOpenGLFunction("glBindTexture");
    glDeleteTextures = (PFNGLDELETETEXTURESPROC) sol_loadOpenGLFunction("glDeleteTextures");
    glGenTextures = (PFNGLGENTEXTURESPROC) sol_loadOpenGLFunction("glGenTextures");
    glIsTexture = (PFNGLISTEXTUREPROC) sol_loadOpenGLFunction("glIsTexture");
#endif /* GL_VERSION_1_1 */

#if SOL_TEST_VERSION(1, 2)
    glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) sol_loadOpenGLFunction("glDrawRangeElements");
    glTexImage3D = (PFNGLTEXIMAGE3DPROC) sol_loadOpenGLFunction("glTexImage3D");
    glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) sol_loadOpenGLFunction("glTexSubImage3D");
    glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC) sol_loadOpenGLFunction("glCopyTexSubImage3D");
#endif /* GL_VERSION_1_2 */

#if SOL_TEST_VERSION(1, 3)
    glActiveTexture = (PFNGLACTIVETEXTUREPROC) sol_loadOpenGLFunction("glActiveTexture");
    glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) sol_loadOpenGLFunction("glSampleCoverage");
    glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC) sol_loadOpenGLFunction("glCompressedTexImage3D");
    glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) sol_loadOpenGLFunction("glCompressedTexImage2D");
    glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC) sol_loadOpenGLFunction("glCompressedTexImage1D");
    glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) sol_loadOpenGLFunction("glCompressedTexSubImage3D");
    glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) sol_loadOpenGLFunction("glCompressedTexSubImage2D");
    glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) sol_loadOpenGLFunction("glCompressedTexSubImage1D");
    glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC) sol_loadOpenGLFunction("glGetCompressedTexImage");
#endif /* GL_VERSION_1_3 */

#if SOL_TEST_VERSION(1, 4)
    glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC) sol_loadOpenGLFunction("glBlendFuncSeparate");
    glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC) sol_loadOpenGLFunction("glMultiDrawArrays");
    glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC) sol_loadOpenGLFunction("glMultiDrawElements");
    glPointParameterf = (PFNGLPOINTPARAMETERFPROC) sol_loadOpenGLFunction("glPointParameterf");
    glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC) sol_loadOpenGLFunction("glPointParameterfv");
    glPointParameteri = (PFNGLPOINTPARAMETERIPROC) sol_loadOpenGLFunction("glPointParameteri");
    glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC) sol_loadOpenGLFunction("glPointParameteriv");
    glBlendColor = (PFNGLBLENDCOLORPROC) sol_loadOpenGLFunction("glBlendColor");
    glBlendEquation = (PFNGLBLENDEQUATIONPROC) sol_loadOpenGLFunction("glBlendEquation");
#endif /* GL_VERSION_1_4 */

#if SOL_TEST_VERSION(1, 5)
    glGenQueries = (PFNGLGENQUERIESPROC) sol_loadOpenGLFunction("glGenQueries");
    glDeleteQueries = (PFNGLDELETEQUERIESPROC) sol_loadOpenGLFunction("glDeleteQueries");
    glIsQuery = (PFNGLISQUERYPROC) sol_loadOpenGLFunction("glIsQuery");
    glBeginQuery = (PFNGLBEGINQUERYPROC) sol_loadOpenGLFunction("glBeginQuery");
    glEndQuery = (PFNGLENDQUERYPROC) sol_loadOpenGLFunction("glEndQuery");
    glGetQueryiv = (PFNGLGETQUERYIVPROC) sol_loadOpenGLFunction("glGetQueryiv");
    glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC) sol_loadOpenGLFunction("glGetQueryObjectiv");
    glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC) sol_loadOpenGLFunction("glGetQueryObjectuiv");
    glBindBuffer = (PFNGLBINDBUFFERPROC) sol_loadOpenGLFunction("glBindBuffer");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) sol_loadOpenGLFunction("glDeleteBuffers");
    glGenBuffers = (PFNGLGENBUFFERSPROC) sol_loadOpenGLFunction("glGenBuffers");
    glIsBuffer = (PFNGLISBUFFERPROC) sol_loadOpenGLFunction("glIsBuffer");
    glBufferData = (PFNGLBUFFERDATAPROC) sol_loadOpenGLFunction("glBufferData");
    glBufferSubData = (PFNGLBUFFERSUBDATAPROC) sol_loadOpenGLFunction("glBufferSubData");
    glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC) sol_loadOpenGLFunction("glGetBufferSubData");
    glMapBuffer = (PFNGLMAPBUFFERPROC) sol_loadOpenGLFunction("glMapBuffer");
    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) sol_loadOpenGLFunction("glUnmapBuffer");
    glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) sol_loadOpenGLFunction("glGetBufferParameteriv");
    glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) sol_loadOpenGLFunction("glGetBufferPointerv");
#endif /* GL_VERSION_1_5 */

#if SOL_TEST_VERSION(2, 0)
    glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC) sol_loadOpenGLFunction("glBlendEquationSeparate");
    glDrawBuffers = (PFNGLDRAWBUFFERSPROC) sol_loadOpenGLFunction("glDrawBuffers");
    glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC) sol_loadOpenGLFunction("glStencilOpSeparate");
    glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC) sol_loadOpenGLFunction("glStencilFuncSeparate");
    glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC) sol_loadOpenGLFunction("glStencilMaskSeparate");
    glAttachShader = (PFNGLATTACHSHADERPROC) sol_loadOpenGLFunction("glAttachShader");
    glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) sol_loadOpenGLFunction("glBindAttribLocation");
    glCompileShader = (PFNGLCOMPILESHADERPROC) sol_loadOpenGLFunction("glCompileShader");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC) sol_loadOpenGLFunction("glCreateProgram");
    glCreateShader = (PFNGLCREATESHADERPROC) sol_loadOpenGLFunction("glCreateShader");
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC) sol_loadOpenGLFunction("glDeleteProgram");
    glDeleteShader = (PFNGLDELETESHADERPROC) sol_loadOpenGLFunction("glDeleteShader");
    glDetachShader = (PFNGLDETACHSHADERPROC) sol_loadOpenGLFunction("glDetachShader");
    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) sol_loadOpenGLFunction("glDisableVertexAttribArray");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) sol_loadOpenGLFunction("glEnableVertexAttribArray");
    glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC) sol_loadOpenGLFunction("glGetActiveAttrib");
    glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC) sol_loadOpenGLFunction("glGetActiveUniform");
    glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC) sol_loadOpenGLFunction("glGetAttachedShaders");
    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) sol_loadOpenGLFunction("glGetAttribLocation");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC) sol_loadOpenGLFunction("glGetProgramiv");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) sol_loadOpenGLFunction("glGetProgramInfoLog");
    glGetShaderiv = (PFNGLGETSHADERIVPROC) sol_loadOpenGLFunction("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) sol_loadOpenGLFunction("glGetShaderInfoLog");
    glGetShaderSource = (PFNGLGETSHADERSOURCEPROC) sol_loadOpenGLFunction("glGetShaderSource");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) sol_loadOpenGLFunction("glGetUniformLocation");
    glGetUniformfv = (PFNGLGETUNIFORMFVPROC) sol_loadOpenGLFunction("glGetUniformfv");
    glGetUniformiv = (PFNGLGETUNIFORMIVPROC) sol_loadOpenGLFunction("glGetUniformiv");
    glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC) sol_loadOpenGLFunction("glGetVertexAttribdv");
    glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC) sol_loadOpenGLFunction("glGetVertexAttribfv");
    glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC) sol_loadOpenGLFunction("glGetVertexAttribiv");
    glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC) sol_loadOpenGLFunction("glGetVertexAttribPointerv");
    glIsProgram = (PFNGLISPROGRAMPROC) sol_loadOpenGLFunction("glIsProgram");
    glIsShader = (PFNGLISSHADERPROC) sol_loadOpenGLFunction("glIsShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC) sol_loadOpenGLFunction("glLinkProgram");
    glShaderSource = (PFNGLSHADERSOURCEPROC) sol_loadOpenGLFunction("glShaderSource");
    glUseProgram = (PFNGLUSEPROGRAMPROC) sol_loadOpenGLFunction("glUseProgram");
    glUniform1f = (PFNGLUNIFORM1FPROC) sol_loadOpenGLFunction("glUniform1f");
    glUniform2f = (PFNGLUNIFORM2FPROC) sol_loadOpenGLFunction("glUniform2f");
    glUniform3f = (PFNGLUNIFORM3FPROC) sol_loadOpenGLFunction("glUniform3f");
    glUniform4f = (PFNGLUNIFORM4FPROC) sol_loadOpenGLFunction("glUniform4f");
    glUniform1i = (PFNGLUNIFORM1IPROC) sol_loadOpenGLFunction("glUniform1i");
    glUniform2i = (PFNGLUNIFORM2IPROC) sol_loadOpenGLFunction("glUniform2i");
    glUniform3i = (PFNGLUNIFORM3IPROC) sol_loadOpenGLFunction("glUniform3i");
    glUniform4i = (PFNGLUNIFORM4IPROC) sol_loadOpenGLFunction("glUniform4i");
    glUniform1fv = (PFNGLUNIFORM1FVPROC) sol_loadOpenGLFunction("glUniform1fv");
    glUniform2fv = (PFNGLUNIFORM2FVPROC) sol_loadOpenGLFunction("glUniform2fv");
    glUniform3fv = (PFNGLUNIFORM3FVPROC) sol_loadOpenGLFunction("glUniform3fv");
    glUniform4fv = (PFNGLUNIFORM4FVPROC) sol_loadOpenGLFunction("glUniform4fv");
    glUniform1iv = (PFNGLUNIFORM1IVPROC) sol_loadOpenGLFunction("glUniform1iv");
    glUniform2iv = (PFNGLUNIFORM2IVPROC) sol_loadOpenGLFunction("glUniform2iv");
    glUniform3iv = (PFNGLUNIFORM3IVPROC) sol_loadOpenGLFunction("glUniform3iv");
    glUniform4iv = (PFNGLUNIFORM4IVPROC) sol_loadOpenGLFunction("glUniform4iv");
    glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC) sol_loadOpenGLFunction("glUniformMatrix2fv");
    glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC) sol_loadOpenGLFunction("glUniformMatrix3fv");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) sol_loadOpenGLFunction("glUniformMatrix4fv");
    glValidateProgram = (PFNGLVALIDATEPROGRAMPROC) sol_loadOpenGLFunction("glValidateProgram");
    glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC) sol_loadOpenGLFunction("glVertexAttrib1d");
    glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC) sol_loadOpenGLFunction("glVertexAttrib1dv");
    glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC) sol_loadOpenGLFunction("glVertexAttrib1f");
    glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC) sol_loadOpenGLFunction("glVertexAttrib1fv");
    glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC) sol_loadOpenGLFunction("glVertexAttrib1s");
    glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC) sol_loadOpenGLFunction("glVertexAttrib1sv");
    glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC) sol_loadOpenGLFunction("glVertexAttrib2d");
    glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC) sol_loadOpenGLFunction("glVertexAttrib2dv");
    glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC) sol_loadOpenGLFunction("glVertexAttrib2f");
    glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC) sol_loadOpenGLFunction("glVertexAttrib2fv");
    glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC) sol_loadOpenGLFunction("glVertexAttrib2s");
    glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC) sol_loadOpenGLFunction("glVertexAttrib2sv");
    glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC) sol_loadOpenGLFunction("glVertexAttrib3d");
    glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC) sol_loadOpenGLFunction("glVertexAttrib3dv");
    glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC) sol_loadOpenGLFunction("glVertexAttrib3f");
    glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC) sol_loadOpenGLFunction("glVertexAttrib3fv");
    glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC) sol_loadOpenGLFunction("glVertexAttrib3s");
    glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC) sol_loadOpenGLFunction("glVertexAttrib3sv");
    glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC) sol_loadOpenGLFunction("glVertexAttrib4Nbv");
    glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC) sol_loadOpenGLFunction("glVertexAttrib4Niv");
    glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC) sol_loadOpenGLFunction("glVertexAttrib4Nsv");
    glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC) sol_loadOpenGLFunction("glVertexAttrib4Nub");
    glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC) sol_loadOpenGLFunction("glVertexAttrib4Nubv");
    glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC) sol_loadOpenGLFunction("glVertexAttrib4Nuiv");
    glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC) sol_loadOpenGLFunction("glVertexAttrib4Nusv");
    glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC) sol_loadOpenGLFunction("glVertexAttrib4bv");
    glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC) sol_loadOpenGLFunction("glVertexAttrib4d");
    glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC) sol_loadOpenGLFunction("glVertexAttrib4dv");
    glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC) sol_loadOpenGLFunction("glVertexAttrib4f");
    glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC) sol_loadOpenGLFunction("glVertexAttrib4fv");
    glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC) sol_loadOpenGLFunction("glVertexAttrib4iv");
    glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC) sol_loadOpenGLFunction("glVertexAttrib4s");
    glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC) sol_loadOpenGLFunction("glVertexAttrib4sv");
    glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC) sol_loadOpenGLFunction("glVertexAttrib4ubv");
    glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC) sol_loadOpenGLFunction("glVertexAttrib4uiv");
    glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC) sol_loadOpenGLFunction("glVertexAttrib4usv");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) sol_loadOpenGLFunction("glVertexAttribPointer");
#endif /* GL_VERSION_2_0 */

#if SOL_TEST_VERSION(2, 1)
    glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC) sol_loadOpenGLFunction("glUniformMatrix2x3fv");
    glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC) sol_loadOpenGLFunction("glUniformMatrix3x2fv");
    glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC) sol_loadOpenGLFunction("glUniformMatrix2x4fv");
    glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC) sol_loadOpenGLFunction("glUniformMatrix4x2fv");
    glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC) sol_loadOpenGLFunction("glUniformMatrix3x4fv");
    glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC) sol_loadOpenGLFunction("glUniformMatrix4x3fv");
#endif /* GL_VERSION_2_1 */

#if SOL_TEST_VERSION(3, 0)
    glColorMaski = (PFNGLCOLORMASKIPROC) sol_loadOpenGLFunction("glColorMaski");
    glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC) sol_loadOpenGLFunction("glGetBooleani_v");
    glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC) sol_loadOpenGLFunction("glGetIntegeri_v");
    glEnablei = (PFNGLENABLEIPROC) sol_loadOpenGLFunction("glEnablei");
    glDisablei = (PFNGLDISABLEIPROC) sol_loadOpenGLFunction("glDisablei");
    glIsEnabledi = (PFNGLISENABLEDIPROC) sol_loadOpenGLFunction("glIsEnabledi");
    glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC) sol_loadOpenGLFunction("glBeginTransformFeedback");
    glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC) sol_loadOpenGLFunction("glEndTransformFeedback");
    glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC) sol_loadOpenGLFunction("glBindBufferRange");
    glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) sol_loadOpenGLFunction("glBindBufferBase");
    glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC) sol_loadOpenGLFunction("glTransformFeedbackVaryings");
    glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) sol_loadOpenGLFunction("glGetTransformFeedbackVarying");
    glClampColor = (PFNGLCLAMPCOLORPROC) sol_loadOpenGLFunction("glClampColor");
    glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC) sol_loadOpenGLFunction("glBeginConditionalRender");
    glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC) sol_loadOpenGLFunction("glEndConditionalRender");
    glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC) sol_loadOpenGLFunction("glVertexAttribIPointer");
    glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC) sol_loadOpenGLFunction("glGetVertexAttribIiv");
    glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC) sol_loadOpenGLFunction("glGetVertexAttribIuiv");
    glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC) sol_loadOpenGLFunction("glVertexAttribI1i");
    glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC) sol_loadOpenGLFunction("glVertexAttribI2i");
    glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC) sol_loadOpenGLFunction("glVertexAttribI3i");
    glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC) sol_loadOpenGLFunction("glVertexAttribI4i");
    glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC) sol_loadOpenGLFunction("glVertexAttribI1ui");
    glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC) sol_loadOpenGLFunction("glVertexAttribI2ui");
    glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC) sol_loadOpenGLFunction("glVertexAttribI3ui");
    glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC) sol_loadOpenGLFunction("glVertexAttribI4ui");
    glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC) sol_loadOpenGLFunction("glVertexAttribI1iv");
    glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC) sol_loadOpenGLFunction("glVertexAttribI2iv");
    glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC) sol_loadOpenGLFunction("glVertexAttribI3iv");
    glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC) sol_loadOpenGLFunction("glVertexAttribI4iv");
    glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC) sol_loadOpenGLFunction("glVertexAttribI1uiv");
    glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC) sol_loadOpenGLFunction("glVertexAttribI2uiv");
    glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC) sol_loadOpenGLFunction("glVertexAttribI3uiv");
    glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC) sol_loadOpenGLFunction("glVertexAttribI4uiv");
    glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC) sol_loadOpenGLFunction("glVertexAttribI4bv");
    glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC) sol_loadOpenGLFunction("glVertexAttribI4sv");
    glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC) sol_loadOpenGLFunction("glVertexAttribI4ubv");
    glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC) sol_loadOpenGLFunction("glVertexAttribI4usv");
    glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC) sol_loadOpenGLFunction("glGetUniformuiv");
    glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC) sol_loadOpenGLFunction("glBindFragDataLocation");
    glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC) sol_loadOpenGLFunction("glGetFragDataLocation");
    glUniform1ui = (PFNGLUNIFORM1UIPROC) sol_loadOpenGLFunction("glUniform1ui");
    glUniform2ui = (PFNGLUNIFORM2UIPROC) sol_loadOpenGLFunction("glUniform2ui");
    glUniform3ui = (PFNGLUNIFORM3UIPROC) sol_loadOpenGLFunction("glUniform3ui");
    glUniform4ui = (PFNGLUNIFORM4UIPROC) sol_loadOpenGLFunction("glUniform4ui");
    glUniform1uiv = (PFNGLUNIFORM1UIVPROC) sol_loadOpenGLFunction("glUniform1uiv");
    glUniform2uiv = (PFNGLUNIFORM2UIVPROC) sol_loadOpenGLFunction("glUniform2uiv");
    glUniform3uiv = (PFNGLUNIFORM3UIVPROC) sol_loadOpenGLFunction("glUniform3uiv");
    glUniform4uiv = (PFNGLUNIFORM4UIVPROC) sol_loadOpenGLFunction("glUniform4uiv");
    glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC) sol_loadOpenGLFunction("glTexParameterIiv");
    glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC) sol_loadOpenGLFunction("glTexParameterIuiv");
    glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC) sol_loadOpenGLFunction("glGetTexParameterIiv");
    glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC) sol_loadOpenGLFunction("glGetTexParameterIuiv");
    glClearBufferiv = (PFNGLCLEARBUFFERIVPROC) sol_loadOpenGLFunction("glClearBufferiv");
    glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC) sol_loadOpenGLFunction("glClearBufferuiv");
    glClearBufferfv = (PFNGLCLEARBUFFERFVPROC) sol_loadOpenGLFunction("glClearBufferfv");
    glClearBufferfi = (PFNGLCLEARBUFFERFIPROC) sol_loadOpenGLFunction("glClearBufferfi");
    glGetStringi = (PFNGLGETSTRINGIPROC) sol_loadOpenGLFunction("glGetStringi");
    glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) sol_loadOpenGLFunction("glIsRenderbuffer");
    glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) sol_loadOpenGLFunction("glBindRenderbuffer");
    glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) sol_loadOpenGLFunction("glDeleteRenderbuffers");
    glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) sol_loadOpenGLFunction("glGenRenderbuffers");
    glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) sol_loadOpenGLFunction("glRenderbufferStorage");
    glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) sol_loadOpenGLFunction("glGetRenderbufferParameteriv");
    glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) sol_loadOpenGLFunction("glIsFramebuffer");
    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) sol_loadOpenGLFunction("glBindFramebuffer");
    glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) sol_loadOpenGLFunction("glDeleteFramebuffers");
    glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) sol_loadOpenGLFunction("glGenFramebuffers");
    glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) sol_loadOpenGLFunction("glCheckFramebufferStatus");
    glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) sol_loadOpenGLFunction("glFramebufferTexture1D");
    glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) sol_loadOpenGLFunction("glFramebufferTexture2D");
    glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) sol_loadOpenGLFunction("glFramebufferTexture3D");
    glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) sol_loadOpenGLFunction("glFramebufferRenderbuffer");
    glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) sol_loadOpenGLFunction("glGetFramebufferAttachmentParameteriv");
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) sol_loadOpenGLFunction("glGenerateMipmap");
    glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC) sol_loadOpenGLFunction("glBlitFramebuffer");
    glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) sol_loadOpenGLFunction("glRenderbufferStorageMultisample");
    glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC) sol_loadOpenGLFunction("glFramebufferTextureLayer");
    glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC) sol_loadOpenGLFunction("glMapBufferRange");
    glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC) sol_loadOpenGLFunction("glFlushMappedBufferRange");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) sol_loadOpenGLFunction("glBindVertexArray");
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) sol_loadOpenGLFunction("glDeleteVertexArrays");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) sol_loadOpenGLFunction("glGenVertexArrays");
    glIsVertexArray = (PFNGLISVERTEXARRAYPROC) sol_loadOpenGLFunction("glIsVertexArray");
#endif /* GL_VERSION_3_0 */

#if SOL_TEST_VERSION(3, 1)
    glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) sol_loadOpenGLFunction("glDrawArraysInstanced");
    glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC) sol_loadOpenGLFunction("glDrawElementsInstanced");
    glTexBuffer = (PFNGLTEXBUFFERPROC) sol_loadOpenGLFunction("glTexBuffer");
    glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC) sol_loadOpenGLFunction("glPrimitiveRestartIndex");
    glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC) sol_loadOpenGLFunction("glCopyBufferSubData");
    glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC) sol_loadOpenGLFunction("glGetUniformIndices");
    glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC) sol_loadOpenGLFunction("glGetActiveUniformsiv");
    glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC) sol_loadOpenGLFunction("glGetActiveUniformName");
    glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC) sol_loadOpenGLFunction("glGetUniformBlockIndex");
    glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC) sol_loadOpenGLFunction("glGetActiveUniformBlockiv");
    glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) sol_loadOpenGLFunction("glGetActiveUniformBlockName");
    glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC) sol_loadOpenGLFunction("glUniformBlockBinding");
#endif /* GL_VERSION_3_1 */

#if SOL_TEST_VERSION(3, 2)
    glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC) sol_loadOpenGLFunction("glDrawElementsBaseVertex");
    glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) sol_loadOpenGLFunction("glDrawRangeElementsBaseVertex");
    glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) sol_loadOpenGLFunction("glDrawElementsInstancedBaseVertex");
    glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) sol_loadOpenGLFunction("glMultiDrawElementsBaseVertex");
    glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC) sol_loadOpenGLFunction("glProvokingVertex");
    glFenceSync = (PFNGLFENCESYNCPROC) sol_loadOpenGLFunction("glFenceSync");
    glIsSync = (PFNGLISSYNCPROC) sol_loadOpenGLFunction("glIsSync");
    glDeleteSync = (PFNGLDELETESYNCPROC) sol_loadOpenGLFunction("glDeleteSync");
    glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC) sol_loadOpenGLFunction("glClientWaitSync");
    glWaitSync = (PFNGLWAITSYNCPROC) sol_loadOpenGLFunction("glWaitSync");
    glGetInteger64v = (PFNGLGETINTEGER64VPROC) sol_loadOpenGLFunction("glGetInteger64v");
    glGetSynciv = (PFNGLGETSYNCIVPROC) sol_loadOpenGLFunction("glGetSynciv");
    glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC) sol_loadOpenGLFunction("glGetInteger64i_v");
    glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC) sol_loadOpenGLFunction("glGetBufferParameteri64v");
    glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC) sol_loadOpenGLFunction("glFramebufferTexture");
    glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC) sol_loadOpenGLFunction("glTexImage2DMultisample");
    glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC) sol_loadOpenGLFunction("glTexImage3DMultisample");
    glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC) sol_loadOpenGLFunction("glGetMultisamplefv");
    glSampleMaski = (PFNGLSAMPLEMASKIPROC) sol_loadOpenGLFunction("glSampleMaski");
#endif /* GL_VERSION_3_2 */

#if SOL_TEST_VERSION(3, 3)
    glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) sol_loadOpenGLFunction("glBindFragDataLocationIndexed");
    glGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC) sol_loadOpenGLFunction("glGetFragDataIndex");
    glGenSamplers = (PFNGLGENSAMPLERSPROC) sol_loadOpenGLFunction("glGenSamplers");
    glDeleteSamplers = (PFNGLDELETESAMPLERSPROC) sol_loadOpenGLFunction("glDeleteSamplers");
    glIsSampler = (PFNGLISSAMPLERPROC) sol_loadOpenGLFunction("glIsSampler");
    glBindSampler = (PFNGLBINDSAMPLERPROC) sol_loadOpenGLFunction("glBindSampler");
    glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC) sol_loadOpenGLFunction("glSamplerParameteri");
    glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC) sol_loadOpenGLFunction("glSamplerParameteriv");
    glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC) sol_loadOpenGLFunction("glSamplerParameterf");
    glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC) sol_loadOpenGLFunction("glSamplerParameterfv");
    glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC) sol_loadOpenGLFunction("glSamplerParameterIiv");
    glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC) sol_loadOpenGLFunction("glSamplerParameterIuiv");
    glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC) sol_loadOpenGLFunction("glGetSamplerParameteriv");
    glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC) sol_loadOpenGLFunction("glGetSamplerParameterIiv");
    glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC) sol_loadOpenGLFunction("glGetSamplerParameterfv");
    glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC) sol_loadOpenGLFunction("glGetSamplerParameterIuiv");
    glQueryCounter = (PFNGLQUERYCOUNTERPROC) sol_loadOpenGLFunction("glQueryCounter");
    glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC) sol_loadOpenGLFunction("glGetQueryObjecti64v");
    glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC) sol_loadOpenGLFunction("glGetQueryObjectui64v");
    glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC) sol_loadOpenGLFunction("glVertexAttribDivisor");
    glVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC) sol_loadOpenGLFunction("glVertexAttribP1ui");
    glVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC) sol_loadOpenGLFunction("glVertexAttribP1uiv");
    glVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC) sol_loadOpenGLFunction("glVertexAttribP2ui");
    glVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC) sol_loadOpenGLFunction("glVertexAttribP2uiv");
    glVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC) sol_loadOpenGLFunction("glVertexAttribP3ui");
    glVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC) sol_loadOpenGLFunction("glVertexAttribP3uiv");
    glVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC) sol_loadOpenGLFunction("glVertexAttribP4ui");
    glVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC) sol_loadOpenGLFunction("glVertexAttribP4uiv");
#endif /* GL_VERSION_3_3 */

#if SOL_TEST_VERSION(4, 0)
    glMinSampleShading = (PFNGLMINSAMPLESHADINGPROC) sol_loadOpenGLFunction("glMinSampleShading");
    glBlendEquationi = (PFNGLBLENDEQUATIONIPROC) sol_loadOpenGLFunction("glBlendEquationi");
    glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC) sol_loadOpenGLFunction("glBlendEquationSeparatei");
    glBlendFunci = (PFNGLBLENDFUNCIPROC) sol_loadOpenGLFunction("glBlendFunci");
    glBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC) sol_loadOpenGLFunction("glBlendFuncSeparatei");
    glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC) sol_loadOpenGLFunction("glDrawArraysIndirect");
    glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC) sol_loadOpenGLFunction("glDrawElementsIndirect");
    glUniform1d = (PFNGLUNIFORM1DPROC) sol_loadOpenGLFunction("glUniform1d");
    glUniform2d = (PFNGLUNIFORM2DPROC) sol_loadOpenGLFunction("glUniform2d");
    glUniform3d = (PFNGLUNIFORM3DPROC) sol_loadOpenGLFunction("glUniform3d");
    glUniform4d = (PFNGLUNIFORM4DPROC) sol_loadOpenGLFunction("glUniform4d");
    glUniform1dv = (PFNGLUNIFORM1DVPROC) sol_loadOpenGLFunction("glUniform1dv");
    glUniform2dv = (PFNGLUNIFORM2DVPROC) sol_loadOpenGLFunction("glUniform2dv");
    glUniform3dv = (PFNGLUNIFORM3DVPROC) sol_loadOpenGLFunction("glUniform3dv");
    glUniform4dv = (PFNGLUNIFORM4DVPROC) sol_loadOpenGLFunction("glUniform4dv");
    glUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC) sol_loadOpenGLFunction("glUniformMatrix2dv");
    glUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC) sol_loadOpenGLFunction("glUniformMatrix3dv");
    glUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC) sol_loadOpenGLFunction("glUniformMatrix4dv");
    glUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC) sol_loadOpenGLFunction("glUniformMatrix2x3dv");
    glUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC) sol_loadOpenGLFunction("glUniformMatrix2x4dv");
    glUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC) sol_loadOpenGLFunction("glUniformMatrix3x2dv");
    glUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC) sol_loadOpenGLFunction("glUniformMatrix3x4dv");
    glUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC) sol_loadOpenGLFunction("glUniformMatrix4x2dv");
    glUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC) sol_loadOpenGLFunction("glUniformMatrix4x3dv");
    glGetUniformdv = (PFNGLGETUNIFORMDVPROC) sol_loadOpenGLFunction("glGetUniformdv");
    glGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC) sol_loadOpenGLFunction("glGetSubroutineUniformLocation");
    glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC) sol_loadOpenGLFunction("glGetSubroutineIndex");
    glGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC) sol_loadOpenGLFunction("glGetActiveSubroutineUniformiv");
    glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC) sol_loadOpenGLFunction("glGetActiveSubroutineUniformName");
    glGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC) sol_loadOpenGLFunction("glGetActiveSubroutineName");
    glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC) sol_loadOpenGLFunction("glUniformSubroutinesuiv");
    glGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC) sol_loadOpenGLFunction("glGetUniformSubroutineuiv");
    glGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC) sol_loadOpenGLFunction("glGetProgramStageiv");
    glPatchParameteri = (PFNGLPATCHPARAMETERIPROC) sol_loadOpenGLFunction("glPatchParameteri");
    glPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC) sol_loadOpenGLFunction("glPatchParameterfv");
    glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC) sol_loadOpenGLFunction("glBindTransformFeedback");
    glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC) sol_loadOpenGLFunction("glDeleteTransformFeedbacks");
    glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC) sol_loadOpenGLFunction("glGenTransformFeedbacks");
    glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC) sol_loadOpenGLFunction("glIsTransformFeedback");
    glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC) sol_loadOpenGLFunction("glPauseTransformFeedback");
    glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC) sol_loadOpenGLFunction("glResumeTransformFeedback");
    glDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC) sol_loadOpenGLFunction("glDrawTransformFeedback");
    glDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC) sol_loadOpenGLFunction("glDrawTransformFeedbackStream");
    glBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC) sol_loadOpenGLFunction("glBeginQueryIndexed");
    glEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC) sol_loadOpenGLFunction("glEndQueryIndexed");
    glGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC) sol_loadOpenGLFunction("glGetQueryIndexediv");
#endif /* GL_VERSION_4_0 */

#if SOL_TEST_VERSION(4, 1)
    glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC) sol_loadOpenGLFunction("glReleaseShaderCompiler");
    glShaderBinary = (PFNGLSHADERBINARYPROC) sol_loadOpenGLFunction("glShaderBinary");
    glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC) sol_loadOpenGLFunction("glGetShaderPrecisionFormat");
    glDepthRangef = (PFNGLDEPTHRANGEFPROC) sol_loadOpenGLFunction("glDepthRangef");
    glClearDepthf = (PFNGLCLEARDEPTHFPROC) sol_loadOpenGLFunction("glClearDepthf");
    glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC) sol_loadOpenGLFunction("glGetProgramBinary");
    glProgramBinary = (PFNGLPROGRAMBINARYPROC) sol_loadOpenGLFunction("glProgramBinary");
    glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC) sol_loadOpenGLFunction("glProgramParameteri");
    glUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC) sol_loadOpenGLFunction("glUseProgramStages");
    glActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC) sol_loadOpenGLFunction("glActiveShaderProgram");
    glCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC) sol_loadOpenGLFunction("glCreateShaderProgramv");
    glBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC) sol_loadOpenGLFunction("glBindProgramPipeline");
    glDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC) sol_loadOpenGLFunction("glDeleteProgramPipelines");
    glGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC) sol_loadOpenGLFunction("glGenProgramPipelines");
    glIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC) sol_loadOpenGLFunction("glIsProgramPipeline");
    glGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC) sol_loadOpenGLFunction("glGetProgramPipelineiv");
    glProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC) sol_loadOpenGLFunction("glProgramUniform1i");
    glProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC) sol_loadOpenGLFunction("glProgramUniform1iv");
    glProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC) sol_loadOpenGLFunction("glProgramUniform1f");
    glProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC) sol_loadOpenGLFunction("glProgramUniform1fv");
    glProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC) sol_loadOpenGLFunction("glProgramUniform1d");
    glProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC) sol_loadOpenGLFunction("glProgramUniform1dv");
    glProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC) sol_loadOpenGLFunction("glProgramUniform1ui");
    glProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC) sol_loadOpenGLFunction("glProgramUniform1uiv");
    glProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC) sol_loadOpenGLFunction("glProgramUniform2i");
    glProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC) sol_loadOpenGLFunction("glProgramUniform2iv");
    glProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC) sol_loadOpenGLFunction("glProgramUniform2f");
    glProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC) sol_loadOpenGLFunction("glProgramUniform2fv");
    glProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC) sol_loadOpenGLFunction("glProgramUniform2d");
    glProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC) sol_loadOpenGLFunction("glProgramUniform2dv");
    glProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC) sol_loadOpenGLFunction("glProgramUniform2ui");
    glProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC) sol_loadOpenGLFunction("glProgramUniform2uiv");
    glProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC) sol_loadOpenGLFunction("glProgramUniform3i");
    glProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC) sol_loadOpenGLFunction("glProgramUniform3iv");
    glProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC) sol_loadOpenGLFunction("glProgramUniform3f");
    glProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC) sol_loadOpenGLFunction("glProgramUniform3fv");
    glProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC) sol_loadOpenGLFunction("glProgramUniform3d");
    glProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC) sol_loadOpenGLFunction("glProgramUniform3dv");
    glProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC) sol_loadOpenGLFunction("glProgramUniform3ui");
    glProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC) sol_loadOpenGLFunction("glProgramUniform3uiv");
    glProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC) sol_loadOpenGLFunction("glProgramUniform4i");
    glProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC) sol_loadOpenGLFunction("glProgramUniform4iv");
    glProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC) sol_loadOpenGLFunction("glProgramUniform4f");
    glProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC) sol_loadOpenGLFunction("glProgramUniform4fv");
    glProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC) sol_loadOpenGLFunction("glProgramUniform4d");
    glProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC) sol_loadOpenGLFunction("glProgramUniform4dv");
    glProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC) sol_loadOpenGLFunction("glProgramUniform4ui");
    glProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC) sol_loadOpenGLFunction("glProgramUniform4uiv");
    glProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix2fv");
    glProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix3fv");
    glProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix4fv");
    glProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix2dv");
    glProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix3dv");
    glProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix4dv");
    glProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix2x3fv");
    glProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix3x2fv");
    glProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix2x4fv");
    glProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix4x2fv");
    glProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix3x4fv");
    glProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix4x3fv");
    glProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix2x3dv");
    glProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix3x2dv");
    glProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix2x4dv");
    glProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix4x2dv");
    glProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix3x4dv");
    glProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) sol_loadOpenGLFunction("glProgramUniformMatrix4x3dv");
    glValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC) sol_loadOpenGLFunction("glValidateProgramPipeline");
    glGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC) sol_loadOpenGLFunction("glGetProgramPipelineInfoLog");
    glVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC) sol_loadOpenGLFunction("glVertexAttribL1d");
    glVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC) sol_loadOpenGLFunction("glVertexAttribL2d");
    glVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC) sol_loadOpenGLFunction("glVertexAttribL3d");
    glVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC) sol_loadOpenGLFunction("glVertexAttribL4d");
    glVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC) sol_loadOpenGLFunction("glVertexAttribL1dv");
    glVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC) sol_loadOpenGLFunction("glVertexAttribL2dv");
    glVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC) sol_loadOpenGLFunction("glVertexAttribL3dv");
    glVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC) sol_loadOpenGLFunction("glVertexAttribL4dv");
    glVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC) sol_loadOpenGLFunction("glVertexAttribLPointer");
    glGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC) sol_loadOpenGLFunction("glGetVertexAttribLdv");
    glViewportArrayv = (PFNGLVIEWPORTARRAYVPROC) sol_loadOpenGLFunction("glViewportArrayv");
    glViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC) sol_loadOpenGLFunction("glViewportIndexedf");
    glViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC) sol_loadOpenGLFunction("glViewportIndexedfv");
    glScissorArrayv = (PFNGLSCISSORARRAYVPROC) sol_loadOpenGLFunction("glScissorArrayv");
    glScissorIndexed = (PFNGLSCISSORINDEXEDPROC) sol_loadOpenGLFunction("glScissorIndexed");
    glScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC) sol_loadOpenGLFunction("glScissorIndexedv");
    glDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC) sol_loadOpenGLFunction("glDepthRangeArrayv");
    glDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC) sol_loadOpenGLFunction("glDepthRangeIndexed");
    glGetFloati_v = (PFNGLGETFLOATI_VPROC) sol_loadOpenGLFunction("glGetFloati_v");
    glGetDoublei_v = (PFNGLGETDOUBLEI_VPROC) sol_loadOpenGLFunction("glGetDoublei_v");
#endif /* GL_VERSION_4_1 */

#if SOL_TEST_VERSION(4, 2)
    glDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC) sol_loadOpenGLFunction("glDrawArraysInstancedBaseInstance");
    glDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC) sol_loadOpenGLFunction("glDrawElementsInstancedBaseInstance");
    glDrawElementsInstancedBaseVertexBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC) sol_loadOpenGLFunction("glDrawElementsInstancedBaseVertexBaseInstance");
    glGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC) sol_loadOpenGLFunction("glGetInternalformativ");
    glGetActiveAtomicCounterBufferiv = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC) sol_loadOpenGLFunction("glGetActiveAtomicCounterBufferiv");
    glBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC) sol_loadOpenGLFunction("glBindImageTexture");
    glMemoryBarrier = (PFNGLMEMORYBARRIERPROC) sol_loadOpenGLFunction("glMemoryBarrier");
    glTexStorage1D = (PFNGLTEXSTORAGE1DPROC) sol_loadOpenGLFunction("glTexStorage1D");
    glTexStorage2D = (PFNGLTEXSTORAGE2DPROC) sol_loadOpenGLFunction("glTexStorage2D");
    glTexStorage3D = (PFNGLTEXSTORAGE3DPROC) sol_loadOpenGLFunction("glTexStorage3D");
    glDrawTransformFeedbackInstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC) sol_loadOpenGLFunction("glDrawTransformFeedbackInstanced");
    glDrawTransformFeedbackStreamInstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC) sol_loadOpenGLFunction("glDrawTransformFeedbackStreamInstanced");
#endif /* GL_VERSION_4_2 */

#if SOL_TEST_VERSION(4, 3)
    glClearBufferData = (PFNGLCLEARBUFFERDATAPROC) sol_loadOpenGLFunction("glClearBufferData");
    glClearBufferSubData = (PFNGLCLEARBUFFERSUBDATAPROC) sol_loadOpenGLFunction("glClearBufferSubData");
    glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC) sol_loadOpenGLFunction("glDispatchCompute");
    glDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC) sol_loadOpenGLFunction("glDispatchComputeIndirect");
    glCopyImageSubData = (PFNGLCOPYIMAGESUBDATAPROC) sol_loadOpenGLFunction("glCopyImageSubData");
    glFramebufferParameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC) sol_loadOpenGLFunction("glFramebufferParameteri");
    glGetFramebufferParameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC) sol_loadOpenGLFunction("glGetFramebufferParameteriv");
    glGetInternalformati64v = (PFNGLGETINTERNALFORMATI64VPROC) sol_loadOpenGLFunction("glGetInternalformati64v");
    glInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC) sol_loadOpenGLFunction("glInvalidateTexSubImage");
    glInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC) sol_loadOpenGLFunction("glInvalidateTexImage");
    glInvalidateBufferSubData = (PFNGLINVALIDATEBUFFERSUBDATAPROC) sol_loadOpenGLFunction("glInvalidateBufferSubData");
    glInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC) sol_loadOpenGLFunction("glInvalidateBufferData");
    glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC) sol_loadOpenGLFunction("glInvalidateFramebuffer");
    glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC) sol_loadOpenGLFunction("glInvalidateSubFramebuffer");
    glMultiDrawArraysIndirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC) sol_loadOpenGLFunction("glMultiDrawArraysIndirect");
    glMultiDrawElementsIndirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC) sol_loadOpenGLFunction("glMultiDrawElementsIndirect");
    glGetProgramInterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC) sol_loadOpenGLFunction("glGetProgramInterfaceiv");
    glGetProgramResourceIndex = (PFNGLGETPROGRAMRESOURCEINDEXPROC) sol_loadOpenGLFunction("glGetProgramResourceIndex");
    glGetProgramResourceName = (PFNGLGETPROGRAMRESOURCENAMEPROC) sol_loadOpenGLFunction("glGetProgramResourceName");
    glGetProgramResourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC) sol_loadOpenGLFunction("glGetProgramResourceiv");
    glGetProgramResourceLocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC) sol_loadOpenGLFunction("glGetProgramResourceLocation");
    glGetProgramResourceLocationIndex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC) sol_loadOpenGLFunction("glGetProgramResourceLocationIndex");
    glShaderStorageBlockBinding = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC) sol_loadOpenGLFunction("glShaderStorageBlockBinding");
    glTexBufferRange = (PFNGLTEXBUFFERRANGEPROC) sol_loadOpenGLFunction("glTexBufferRange");
    glTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC) sol_loadOpenGLFunction("glTexStorage2DMultisample");
    glTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC) sol_loadOpenGLFunction("glTexStorage3DMultisample");
    glTextureView = (PFNGLTEXTUREVIEWPROC) sol_loadOpenGLFunction("glTextureView");
    glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC) sol_loadOpenGLFunction("glBindVertexBuffer");
    glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC) sol_loadOpenGLFunction("glVertexAttribFormat");
    glVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC) sol_loadOpenGLFunction("glVertexAttribIFormat");
    glVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC) sol_loadOpenGLFunction("glVertexAttribLFormat");
    glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC) sol_loadOpenGLFunction("glVertexAttribBinding");
    glVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC) sol_loadOpenGLFunction("glVertexBindingDivisor");
    glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC) sol_loadOpenGLFunction("glDebugMessageControl");
    glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC) sol_loadOpenGLFunction("glDebugMessageInsert");
    glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC) sol_loadOpenGLFunction("glDebugMessageCallback");
    glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC) sol_loadOpenGLFunction("glGetDebugMessageLog");
    glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC) sol_loadOpenGLFunction("glPushDebugGroup");
    glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC) sol_loadOpenGLFunction("glPopDebugGroup");
    glObjectLabel = (PFNGLOBJECTLABELPROC) sol_loadOpenGLFunction("glObjectLabel");
    glGetObjectLabel = (PFNGLGETOBJECTLABELPROC) sol_loadOpenGLFunction("glGetObjectLabel");
    glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC) sol_loadOpenGLFunction("glObjectPtrLabel");
    glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC) sol_loadOpenGLFunction("glGetObjectPtrLabel");
#endif /* GL_VERSION_4_3 */

#if SOL_TEST_VERSION(4, 4)
    glBufferStorage = (PFNGLBUFFERSTORAGEPROC) sol_loadOpenGLFunction("glBufferStorage");
    glClearTexImage = (PFNGLCLEARTEXIMAGEPROC) sol_loadOpenGLFunction("glClearTexImage");
    glClearTexSubImage = (PFNGLCLEARTEXSUBIMAGEPROC) sol_loadOpenGLFunction("glClearTexSubImage");
    glBindBuffersBase = (PFNGLBINDBUFFERSBASEPROC) sol_loadOpenGLFunction("glBindBuffersBase");
    glBindBuffersRange = (PFNGLBINDBUFFERSRANGEPROC) sol_loadOpenGLFunction("glBindBuffersRange");
    glBindTextures = (PFNGLBINDTEXTURESPROC) sol_loadOpenGLFunction("glBindTextures");
    glBindSamplers = (PFNGLBINDSAMPLERSPROC) sol_loadOpenGLFunction("glBindSamplers");
    glBindImageTextures = (PFNGLBINDIMAGETEXTURESPROC) sol_loadOpenGLFunction("glBindImageTextures");
    glBindVertexBuffers = (PFNGLBINDVERTEXBUFFERSPROC) sol_loadOpenGLFunction("glBindVertexBuffers");
#endif /* GL_VERSION_4_4 */

#if SOL_TEST_VERSION(4, 5)
    glClipControl = (PFNGLCLIPCONTROLPROC) sol_loadOpenGLFunction("glClipControl");
    glCreateTransformFeedbacks = (PFNGLCREATETRANSFORMFEEDBACKSPROC) sol_loadOpenGLFunction("glCreateTransformFeedbacks");
    glTransformFeedbackBufferBase = (PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC) sol_loadOpenGLFunction("glTransformFeedbackBufferBase");
    glTransformFeedbackBufferRange = (PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC) sol_loadOpenGLFunction("glTransformFeedbackBufferRange");
    glGetTransformFeedbackiv = (PFNGLGETTRANSFORMFEEDBACKIVPROC) sol_loadOpenGLFunction("glGetTransformFeedbackiv");
    glGetTransformFeedbacki_v = (PFNGLGETTRANSFORMFEEDBACKI_VPROC) sol_loadOpenGLFunction("glGetTransformFeedbacki_v");
    glGetTransformFeedbacki64_v = (PFNGLGETTRANSFORMFEEDBACKI64_VPROC) sol_loadOpenGLFunction("glGetTransformFeedbacki64_v");
    glCreateBuffers = (PFNGLCREATEBUFFERSPROC) sol_loadOpenGLFunction("glCreateBuffers");
    glNamedBufferStorage = (PFNGLNAMEDBUFFERSTORAGEPROC) sol_loadOpenGLFunction("glNamedBufferStorage");
    glNamedBufferData = (PFNGLNAMEDBUFFERDATAPROC) sol_loadOpenGLFunction("glNamedBufferData");
    glNamedBufferSubData = (PFNGLNAMEDBUFFERSUBDATAPROC) sol_loadOpenGLFunction("glNamedBufferSubData");
    glCopyNamedBufferSubData = (PFNGLCOPYNAMEDBUFFERSUBDATAPROC) sol_loadOpenGLFunction("glCopyNamedBufferSubData");
    glClearNamedBufferData = (PFNGLCLEARNAMEDBUFFERDATAPROC) sol_loadOpenGLFunction("glClearNamedBufferData");
    glClearNamedBufferSubData = (PFNGLCLEARNAMEDBUFFERSUBDATAPROC) sol_loadOpenGLFunction("glClearNamedBufferSubData");
    glMapNamedBuffer = (PFNGLMAPNAMEDBUFFERPROC) sol_loadOpenGLFunction("glMapNamedBuffer");
    glMapNamedBufferRange = (PFNGLMAPNAMEDBUFFERRANGEPROC) sol_loadOpenGLFunction("glMapNamedBufferRange");
    glUnmapNamedBuffer = (PFNGLUNMAPNAMEDBUFFERPROC) sol_loadOpenGLFunction("glUnmapNamedBuffer");
    glFlushMappedNamedBufferRange = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC) sol_loadOpenGLFunction("glFlushMappedNamedBufferRange");
    glGetNamedBufferParameteriv = (PFNGLGETNAMEDBUFFERPARAMETERIVPROC) sol_loadOpenGLFunction("glGetNamedBufferParameteriv");
    glGetNamedBufferParameteri64v = (PFNGLGETNAMEDBUFFERPARAMETERI64VPROC) sol_loadOpenGLFunction("glGetNamedBufferParameteri64v");
    glGetNamedBufferPointerv = (PFNGLGETNAMEDBUFFERPOINTERVPROC) sol_loadOpenGLFunction("glGetNamedBufferPointerv");
    glGetNamedBufferSubData = (PFNGLGETNAMEDBUFFERSUBDATAPROC) sol_loadOpenGLFunction("glGetNamedBufferSubData");
    glCreateFramebuffers = (PFNGLCREATEFRAMEBUFFERSPROC) sol_loadOpenGLFunction("glCreateFramebuffers");
    glNamedFramebufferRenderbuffer = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC) sol_loadOpenGLFunction("glNamedFramebufferRenderbuffer");
    glNamedFramebufferParameteri = (PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC) sol_loadOpenGLFunction("glNamedFramebufferParameteri");
    glNamedFramebufferTexture = (PFNGLNAMEDFRAMEBUFFERTEXTUREPROC) sol_loadOpenGLFunction("glNamedFramebufferTexture");
    glNamedFramebufferTextureLayer = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC) sol_loadOpenGLFunction("glNamedFramebufferTextureLayer");
    glNamedFramebufferDrawBuffer = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC) sol_loadOpenGLFunction("glNamedFramebufferDrawBuffer");
    glNamedFramebufferDrawBuffers = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC) sol_loadOpenGLFunction("glNamedFramebufferDrawBuffers");
    glNamedFramebufferReadBuffer = (PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC) sol_loadOpenGLFunction("glNamedFramebufferReadBuffer");
    glInvalidateNamedFramebufferData = (PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC) sol_loadOpenGLFunction("glInvalidateNamedFramebufferData");
    glInvalidateNamedFramebufferSubData = (PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC) sol_loadOpenGLFunction("glInvalidateNamedFramebufferSubData");
    glClearNamedFramebufferiv = (PFNGLCLEARNAMEDFRAMEBUFFERIVPROC) sol_loadOpenGLFunction("glClearNamedFramebufferiv");
    glClearNamedFramebufferuiv = (PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC) sol_loadOpenGLFunction("glClearNamedFramebufferuiv");
    glClearNamedFramebufferfv = (PFNGLCLEARNAMEDFRAMEBUFFERFVPROC) sol_loadOpenGLFunction("glClearNamedFramebufferfv");
    glClearNamedFramebufferfi = (PFNGLCLEARNAMEDFRAMEBUFFERFIPROC) sol_loadOpenGLFunction("glClearNamedFramebufferfi");
    glBlitNamedFramebuffer = (PFNGLBLITNAMEDFRAMEBUFFERPROC) sol_loadOpenGLFunction("glBlitNamedFramebuffer");
    glCheckNamedFramebufferStatus = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC) sol_loadOpenGLFunction("glCheckNamedFramebufferStatus");
    glGetNamedFramebufferParameteriv = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC) sol_loadOpenGLFunction("glGetNamedFramebufferParameteriv");
    glGetNamedFramebufferAttachmentParameteriv = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC) sol_loadOpenGLFunction("glGetNamedFramebufferAttachmentParameteriv");
    glCreateRenderbuffers = (PFNGLCREATERENDERBUFFERSPROC) sol_loadOpenGLFunction("glCreateRenderbuffers");
    glNamedRenderbufferStorage = (PFNGLNAMEDRENDERBUFFERSTORAGEPROC) sol_loadOpenGLFunction("glNamedRenderbufferStorage");
    glNamedRenderbufferStorageMultisample = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC) sol_loadOpenGLFunction("glNamedRenderbufferStorageMultisample");
    glGetNamedRenderbufferParameteriv = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC) sol_loadOpenGLFunction("glGetNamedRenderbufferParameteriv");
    glCreateTextures = (PFNGLCREATETEXTURESPROC) sol_loadOpenGLFunction("glCreateTextures");
    glTextureBuffer = (PFNGLTEXTUREBUFFERPROC) sol_loadOpenGLFunction("glTextureBuffer");
    glTextureBufferRange = (PFNGLTEXTUREBUFFERRANGEPROC) sol_loadOpenGLFunction("glTextureBufferRange");
    glTextureStorage1D = (PFNGLTEXTURESTORAGE1DPROC) sol_loadOpenGLFunction("glTextureStorage1D");
    glTextureStorage2D = (PFNGLTEXTURESTORAGE2DPROC) sol_loadOpenGLFunction("glTextureStorage2D");
    glTextureStorage3D = (PFNGLTEXTURESTORAGE3DPROC) sol_loadOpenGLFunction("glTextureStorage3D");
    glTextureStorage2DMultisample = (PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC) sol_loadOpenGLFunction("glTextureStorage2DMultisample");
    glTextureStorage3DMultisample = (PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC) sol_loadOpenGLFunction("glTextureStorage3DMultisample");
    glTextureSubImage1D = (PFNGLTEXTURESUBIMAGE1DPROC) sol_loadOpenGLFunction("glTextureSubImage1D");
    glTextureSubImage2D = (PFNGLTEXTURESUBIMAGE2DPROC) sol_loadOpenGLFunction("glTextureSubImage2D");
    glTextureSubImage3D = (PFNGLTEXTURESUBIMAGE3DPROC) sol_loadOpenGLFunction("glTextureSubImage3D");
    glCompressedTextureSubImage1D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC) sol_loadOpenGLFunction("glCompressedTextureSubImage1D");
    glCompressedTextureSubImage2D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC) sol_loadOpenGLFunction("glCompressedTextureSubImage2D");
    glCompressedTextureSubImage3D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC) sol_loadOpenGLFunction("glCompressedTextureSubImage3D");
    glCopyTextureSubImage1D = (PFNGLCOPYTEXTURESUBIMAGE1DPROC) sol_loadOpenGLFunction("glCopyTextureSubImage1D");
    glCopyTextureSubImage2D = (PFNGLCOPYTEXTURESUBIMAGE2DPROC) sol_loadOpenGLFunction("glCopyTextureSubImage2D");
    glCopyTextureSubImage3D = (PFNGLCOPYTEXTURESUBIMAGE3DPROC) sol_loadOpenGLFunction("glCopyTextureSubImage3D");
    glTextureParameterf = (PFNGLTEXTUREPARAMETERFPROC) sol_loadOpenGLFunction("glTextureParameterf");
    glTextureParameterfv = (PFNGLTEXTUREPARAMETERFVPROC) sol_loadOpenGLFunction("glTextureParameterfv");
    glTextureParameteri = (PFNGLTEXTUREPARAMETERIPROC) sol_loadOpenGLFunction("glTextureParameteri");
    glTextureParameterIiv = (PFNGLTEXTUREPARAMETERIIVPROC) sol_loadOpenGLFunction("glTextureParameterIiv");
    glTextureParameterIuiv = (PFNGLTEXTUREPARAMETERIUIVPROC) sol_loadOpenGLFunction("glTextureParameterIuiv");
    glTextureParameteriv = (PFNGLTEXTUREPARAMETERIVPROC) sol_loadOpenGLFunction("glTextureParameteriv");
    glGenerateTextureMipmap = (PFNGLGENERATETEXTUREMIPMAPPROC) sol_loadOpenGLFunction("glGenerateTextureMipmap");
    glBindTextureUnit = (PFNGLBINDTEXTUREUNITPROC) sol_loadOpenGLFunction("glBindTextureUnit");
    glGetTextureImage = (PFNGLGETTEXTUREIMAGEPROC) sol_loadOpenGLFunction("glGetTextureImage");
    glGetCompressedTextureImage = (PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC) sol_loadOpenGLFunction("glGetCompressedTextureImage");
    glGetTextureLevelParameterfv = (PFNGLGETTEXTURELEVELPARAMETERFVPROC) sol_loadOpenGLFunction("glGetTextureLevelParameterfv");
    glGetTextureLevelParameteriv = (PFNGLGETTEXTURELEVELPARAMETERIVPROC) sol_loadOpenGLFunction("glGetTextureLevelParameteriv");
    glGetTextureParameterfv = (PFNGLGETTEXTUREPARAMETERFVPROC) sol_loadOpenGLFunction("glGetTextureParameterfv");
    glGetTextureParameterIiv = (PFNGLGETTEXTUREPARAMETERIIVPROC) sol_loadOpenGLFunction("glGetTextureParameterIiv");
    glGetTextureParameterIuiv = (PFNGLGETTEXTUREPARAMETERIUIVPROC) sol_loadOpenGLFunction("glGetTextureParameterIuiv");
    glGetTextureParameteriv = (PFNGLGETTEXTUREPARAMETERIVPROC) sol_loadOpenGLFunction("glGetTextureParameteriv");
    glCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC) sol_loadOpenGLFunction("glCreateVertexArrays");
    glDisableVertexArrayAttrib = (PFNGLDISABLEVERTEXARRAYATTRIBPROC) sol_loadOpenGLFunction("glDisableVertexArrayAttrib");
    glEnableVertexArrayAttrib = (PFNGLENABLEVERTEXARRAYATTRIBPROC) sol_loadOpenGLFunction("glEnableVertexArrayAttrib");
    glVertexArrayElementBuffer = (PFNGLVERTEXARRAYELEMENTBUFFERPROC) sol_loadOpenGLFunction("glVertexArrayElementBuffer");
    glVertexArrayVertexBuffer = (PFNGLVERTEXARRAYVERTEXBUFFERPROC) sol_loadOpenGLFunction("glVertexArrayVertexBuffer");
    glVertexArrayVertexBuffers = (PFNGLVERTEXARRAYVERTEXBUFFERSPROC) sol_loadOpenGLFunction("glVertexArrayVertexBuffers");
    glVertexArrayAttribBinding = (PFNGLVERTEXARRAYATTRIBBINDINGPROC) sol_loadOpenGLFunction("glVertexArrayAttribBinding");
    glVertexArrayAttribFormat = (PFNGLVERTEXARRAYATTRIBFORMATPROC) sol_loadOpenGLFunction("glVertexArrayAttribFormat");
    glVertexArrayAttribIFormat = (PFNGLVERTEXARRAYATTRIBIFORMATPROC) sol_loadOpenGLFunction("glVertexArrayAttribIFormat");
    glVertexArrayAttribLFormat = (PFNGLVERTEXARRAYATTRIBLFORMATPROC) sol_loadOpenGLFunction("glVertexArrayAttribLFormat");
    glVertexArrayBindingDivisor = (PFNGLVERTEXARRAYBINDINGDIVISORPROC) sol_loadOpenGLFunction("glVertexArrayBindingDivisor");
    glGetVertexArrayiv = (PFNGLGETVERTEXARRAYIVPROC) sol_loadOpenGLFunction("glGetVertexArrayiv");
    glGetVertexArrayIndexediv = (PFNGLGETVERTEXARRAYINDEXEDIVPROC) sol_loadOpenGLFunction("glGetVertexArrayIndexediv");
    glGetVertexArrayIndexed64iv = (PFNGLGETVERTEXARRAYINDEXED64IVPROC) sol_loadOpenGLFunction("glGetVertexArrayIndexed64iv");
    glCreateSamplers = (PFNGLCREATESAMPLERSPROC) sol_loadOpenGLFunction("glCreateSamplers");
    glCreateProgramPipelines = (PFNGLCREATEPROGRAMPIPELINESPROC) sol_loadOpenGLFunction("glCreateProgramPipelines");
    glCreateQueries = (PFNGLCREATEQUERIESPROC) sol_loadOpenGLFunction("glCreateQueries");
    glGetQueryBufferObjecti64v = (PFNGLGETQUERYBUFFEROBJECTI64VPROC) sol_loadOpenGLFunction("glGetQueryBufferObjecti64v");
    glGetQueryBufferObjectiv = (PFNGLGETQUERYBUFFEROBJECTIVPROC) sol_loadOpenGLFunction("glGetQueryBufferObjectiv");
    glGetQueryBufferObjectui64v = (PFNGLGETQUERYBUFFEROBJECTUI64VPROC) sol_loadOpenGLFunction("glGetQueryBufferObjectui64v");
    glGetQueryBufferObjectuiv = (PFNGLGETQUERYBUFFEROBJECTUIVPROC) sol_loadOpenGLFunction("glGetQueryBufferObjectuiv");
    glMemoryBarrierByRegion = (PFNGLMEMORYBARRIERBYREGIONPROC) sol_loadOpenGLFunction("glMemoryBarrierByRegion");
    glGetTextureSubImage = (PFNGLGETTEXTURESUBIMAGEPROC) sol_loadOpenGLFunction("glGetTextureSubImage");
    glGetCompressedTextureSubImage = (PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC) sol_loadOpenGLFunction("glGetCompressedTextureSubImage");
    glGetGraphicsResetStatus = (PFNGLGETGRAPHICSRESETSTATUSPROC) sol_loadOpenGLFunction("glGetGraphicsResetStatus");
    glGetnCompressedTexImage = (PFNGLGETNCOMPRESSEDTEXIMAGEPROC) sol_loadOpenGLFunction("glGetnCompressedTexImage");
    glGetnTexImage = (PFNGLGETNTEXIMAGEPROC) sol_loadOpenGLFunction("glGetnTexImage");
    glGetnUniformdv = (PFNGLGETNUNIFORMDVPROC) sol_loadOpenGLFunction("glGetnUniformdv");
    glGetnUniformfv = (PFNGLGETNUNIFORMFVPROC) sol_loadOpenGLFunction("glGetnUniformfv");
    glGetnUniformiv = (PFNGLGETNUNIFORMIVPROC) sol_loadOpenGLFunction("glGetnUniformiv");
    glGetnUniformuiv = (PFNGLGETNUNIFORMUIVPROC) sol_loadOpenGLFunction("glGetnUniformuiv");
    glReadnPixels = (PFNGLREADNPIXELSPROC) sol_loadOpenGLFunction("glReadnPixels");
    glTextureBarrier = (PFNGLTEXTUREBARRIERPROC) sol_loadOpenGLFunction("glTextureBarrier");
#endif /* GL_VERSION_4_5 */

#if SOL_TEST_VERSION(4, 6)
    glSpecializeShader = (PFNGLSPECIALIZESHADERPROC) sol_loadOpenGLFunction("glSpecializeShader");
    glMultiDrawArraysIndirectCount = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC) sol_loadOpenGLFunction("glMultiDrawArraysIndirectCount");
    glMultiDrawElementsIndirectCount = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC) sol_loadOpenGLFunction("glMultiDrawElementsIndirectCount");
    glPolygonOffsetClamp = (PFNGLPOLYGONOFFSETCLAMPPROC) sol_loadOpenGLFunction("glPolygonOffsetClamp");
#endif /* GL_VERSION_4_6 */	

}

#ifdef __cplusplus
}
#endif

#endif
