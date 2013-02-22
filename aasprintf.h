#include <alloca.h>
#include <stdio.h>

#pragma once

/*
 * (v)aasprintf macro:
 * alloca based asprintf
 *
 * usage: 
 *   char *aasprintf(int length, char* fmt, ...)
 *   char *vaasprintf(int length, char* fmt, va_list ap)
 *
 * length is the length of the buffer to initially allocate,
 *   if the resulting string is longer, a larger buffer wil get allocated.
 *
 * all arguments exept length and ap are side_effect safe.
 *
 * currently up to 64 parameters alowed.
 */

#define aasprintf(length, ...) ({\
	pp_foreach(_aasprintf_store_element, pp_delim_none, __VA_ARGS__)\
	int _len = 0;\
	char* _buf = alloca(length);\
	_len = snprintf(_buf, length, pp_foreach(_aasprintf_get_element, pp_delim_comma, __VA_ARGS__)); \
	if (_len >= length){\
		_buf = alloca(_len + 1 - length); \
		_len = snprintf(_buf, _len+1, pp_foreach(_aasprintf_get_element, pp_delim_comma, __VA_ARGS__)); \
	}\
	_len >= 0? _buf: NULL; })

#define vaasprintf(length, fmt, ap) ({\
	int _len = 0;\
	char* _buf = alloca(length);\
	typeof(fmt) _fmt = (fmt);\
	va_list _arglist;\
	va_copy(_arglist,ap);\
	_len = vsnprintf(_buf, length, _fmt, _arglist);\
	va_end(_arglist);\
	if (_len >= length){\
		_buf = alloca(_len + 1 - length);\
		va_copy(_arglist,ap);\
		_len = vsnprintf(_buf, _len+1, _fmt, _arglist);\
		va_end(_arglist);\
	}\
	_len >= 0? _buf: NULL; })

#define _aasprintf_store_element(N, a) typeof(a) cat(_arglist_,N) = (a);
#define _aasprintf_get_element(N, a) cat(_arglist_,N)

#define __cat(a,b) a##b
#define cat(a,b) __cat(a,b)

#define _pp_a129(\
	_00,_01,_02,_03,_04,_05,_06,_07,_08,_09,_0A,_0B,_0C,_0D,_0E,_0F,\
	_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_1A,_1B,_1C,_1D,_1E,_1F,\
	_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_2A,_2B,_2C,_2D,_2E,_2F,\
	_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_3A,_3B,_3C,_3D,_3E,_3F,\
	_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_4A,_4B,_4C,_4D,_4E,_4F,\
	_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_5A,_5B,_5C,_5D,_5E,_5F,\
	_60,_61,_62,_63,_64,_65,_66,_67,_68,_69,_6A,_6B,_6C,_6D,_6E,_6F,\
	_70,_71,_72,_73,_74,_75,_76,_77,_78,_79,_7A,_7B,_7C,_7D,_7E,_7F,\
	_80, ...) _80
#define pp_chose_comma(y,n,...) _pp_a129(__VA_ARGS__,\
	y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,\
	y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,\
	y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,\
	y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,y,n)
#define pp_delim_comma() ,
#define pp_delim_and() &&
#define pp_delim_or() ||
#define pp_delim_none()

#define pp_foreach(f, d, ...) pp_chose_comma(_pp_loop_next,_pp_forempty,0, ##__VA_ARGS__)\
		(0,__VA_ARGS__)(f, d, 1, __VA_ARGS__)

#define _pp_forempty(...) pp_empty
#define pp_empty(...)
#define _pp_loop_next(N, ...) cat(_pp_loop_, pp_chose_comma(N,Z,__VA_ARGS__))
#define _pp_loop_Z(f, d, N, a)      f(N, a)
#define _pp_loop_0(f, d, N, a, ...) f(N, a) d() _pp_loop_next(N,__VA_ARGS__)(f, d, 2, __VA_ARGS__)
#define _pp_loop_1(f, d, N, a, ...) f(N, a) d() _pp_loop_next(N,__VA_ARGS__)(f, d, 3, __VA_ARGS__)
#define _pp_loop_2(f, d, N, a, ...) f(N, a) d() _pp_loop_next(N,__VA_ARGS__)(f, d, 4, __VA_ARGS__)
#define _pp_loop_3(f, d, N, a, ...) f(N, a) d() _pp_loop_next(N,__VA_ARGS__)(f, d, 5, __VA_ARGS__)
#define _pp_loop_4(f, d, N, a, ...) f(N, a) d() _pp_loop_next(N,__VA_ARGS__)(f, d, 6, __VA_ARGS__)
#define _pp_loop_5(f, d, N, a, ...) f(N, a) d() _pp_loop_next(N,__VA_ARGS__)(f, d, 7, __VA_ARGS__)
#define _pp_loop_6(f, d, N, a, ...) f(N, a) d() _pp_loop_next(N,__VA_ARGS__)(f, d, 8, __VA_ARGS__)
#define _pp_loop_7(f, d, N, a, ...) f(N, a) d() _pp_loop_next(N,__VA_ARGS__)(f, d, 9, __VA_ARGS__)
#define _pp_loop_8(f, d, N, a, ...) f(N, a) d() _pp_loop_next(N,__VA_ARGS__)(f, d, 10, __VA_ARGS__)
#define _pp_loop_9(f, d, N, a, ...) f(N, a) d() _pp_loop_next(N,__VA_ARGS__)(f, 11, __VA_ARGS__)
#define _pp_loop_10(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 12, __VA_ARGS__)
#define _pp_loop_11(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 13, __VA_ARGS__)
#define _pp_loop_12(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 14, __VA_ARGS__)
#define _pp_loop_13(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 15, __VA_ARGS__)
#define _pp_loop_14(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 16, __VA_ARGS__)
#define _pp_loop_15(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 17, __VA_ARGS__)
#define _pp_loop_16(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 18, __VA_ARGS__)
#define _pp_loop_17(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 19, __VA_ARGS__)
#define _pp_loop_18(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 20, __VA_ARGS__)
#define _pp_loop_19(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 21, __VA_ARGS__)
#define _pp_loop_20(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 22, __VA_ARGS__)
#define _pp_loop_21(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 23, __VA_ARGS__)
#define _pp_loop_22(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 24, __VA_ARGS__)
#define _pp_loop_23(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 25, __VA_ARGS__)
#define _pp_loop_24(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 26, __VA_ARGS__)
#define _pp_loop_25(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 27, __VA_ARGS__)
#define _pp_loop_26(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 28, __VA_ARGS__)
#define _pp_loop_27(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 29, __VA_ARGS__)
#define _pp_loop_28(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 30, __VA_ARGS__)
#define _pp_loop_29(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 31, __VA_ARGS__)
#define _pp_loop_30(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 32, __VA_ARGS__)
#define _pp_loop_31(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 33, __VA_ARGS__)
#define _pp_loop_32(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 34, __VA_ARGS__)
#define _pp_loop_33(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 35, __VA_ARGS__)
#define _pp_loop_34(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 36, __VA_ARGS__)
#define _pp_loop_35(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 37, __VA_ARGS__)
#define _pp_loop_36(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 38, __VA_ARGS__)
#define _pp_loop_37(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 39, __VA_ARGS__)
#define _pp_loop_38(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 40, __VA_ARGS__)
#define _pp_loop_39(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 41, __VA_ARGS__)
#define _pp_loop_40(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 42, __VA_ARGS__)
#define _pp_loop_41(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 43, __VA_ARGS__)
#define _pp_loop_42(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 44, __VA_ARGS__)
#define _pp_loop_43(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 45, __VA_ARGS__)
#define _pp_loop_44(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 46, __VA_ARGS__)
#define _pp_loop_45(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 47, __VA_ARGS__)
#define _pp_loop_46(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 48, __VA_ARGS__)
#define _pp_loop_47(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 49, __VA_ARGS__)
#define _pp_loop_48(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 50, __VA_ARGS__)
#define _pp_loop_49(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 51, __VA_ARGS__)
#define _pp_loop_50(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 52, __VA_ARGS__)
#define _pp_loop_51(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 53, __VA_ARGS__)
#define _pp_loop_52(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 54, __VA_ARGS__)
#define _pp_loop_53(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 55, __VA_ARGS__)
#define _pp_loop_54(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 56, __VA_ARGS__)
#define _pp_loop_55(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 57, __VA_ARGS__)
#define _pp_loop_56(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 58, __VA_ARGS__)
#define _pp_loop_57(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 59, __VA_ARGS__)
#define _pp_loop_58(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 60, __VA_ARGS__)
#define _pp_loop_59(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 61, __VA_ARGS__)
#define _pp_loop_60(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 62, __VA_ARGS__)
#define _pp_loop_61(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 63, __VA_ARGS__)
#define _pp_loop_62(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 64, __VA_ARGS__)
#define _pp_loop_63(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 65, __VA_ARGS__)
#define _pp_loop_64(f, N, a, ...) f(N, a) _pp_loop_next(N,__VA_ARGS__)(f, 66, __VA_ARGS__)
