/*
 * Copyright (c) 2022 Michael Federczuk
 *
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * AND
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

// Version 1.2.0 (https://github.com/mfederczuk/cross-support)

#ifndef CROSS_SUPPORT_CORE_H
#define CROSS_SUPPORT_CORE_H 1

#if (defined(CROSS_SUPPORT_MISC_H) || (CROSS_SUPPORT_MISC_H + 0))
	#error Include 'cross_support_core.h' before 'cross_support_misc.h'
#endif

// === language standards =========================================================================================== //

#define CROSS_SUPPORT_C99    ((__STDC_VERSION__ + 0) >= 199901L)
#define CROSS_SUPPORT_C11    ((__STDC_VERSION__ + 0) >= 201112L)
#define CROSS_SUPPORT_C18    ((__STDC_VERSION__ + 0) >= 201710L)
#define CROSS_SUPPORT_C23    ((__STDC_VERSION__ + 0) >= 202300L) // unofficial

#define CROSS_SUPPORT_CXX     (__cplusplus      + 0)
#define CROSS_SUPPORT_CXX98  ((__cplusplus      + 0) >= 199711L)
#define CROSS_SUPPORT_CXX11  ((__cplusplus      + 0) >= 201103L)
#define CROSS_SUPPORT_CXX17  ((__cplusplus      + 0) >= 201703L)
#define CROSS_SUPPORT_CXX14  ((__cplusplus      + 0) >= 201402L)
#define CROSS_SUPPORT_CXX20  ((__cplusplus      + 0) >= 202002L)
#define CROSS_SUPPORT_CXX23  ((__cplusplus      + 0) >= 202300L) // unofficial

// === kernels / operating systems ================================================================================== //

#define CROSS_SUPPORT_LINUX  ((__linux__ + 0) || (linux + 0) || (__linux + 0))

#if ((BSD + 0) || \
     (__FreeBSD__ + 0)      || defined(__FreeBSD_kernel__) || (__FreeBSD_version + 0) || \
     defined(__NetBSD__)    || (__NetBSD_Version__ + 0) || \
     defined(__OpenBSD__)   || \
     defined(__bsdi__)      || \
     defined(__DragonFly__) || \
     defined(_SYSTYPE_BSD))

	#define CROSS_SUPPORT_BSD  1
#else
	#define CROSS_SUPPORT_BSD  0
#endif

#if (defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__)))
	#define CROSS_SUPPORT_MACOS  1
#else
	#define CROSS_SUPPORT_MACOS  0
#endif

#if (defined(_WIN64) || defined(_WIN32) || defined(_WIN16))
	#define CROSS_SUPPORT_WINDOWS  1
#else
	#define CROSS_SUPPORT_WINDOWS  0
#endif


#define CROSS_SUPPORT_UNIX_LIKE  ((__unix__ + 0) || (unix + 0) || (__unix + 0) || \
                                  CROSS_SUPPORT_LINUX || \
                                  CROSS_SUPPORT_BSD || \
                                  CROSS_SUPPORT_MACOS)

// === compilers ==================================================================================================== //

#define CROSS_SUPPORT_GCC_LEAST(major, minor) \
	(((__GNUC__ + 0) > (major)) || \
	 (((__GNUC__ + 0) == (major)) && ((__GNUC_MINOR__ + 0) >= (minor))))

#ifdef __clang__
	#define CROSS_SUPPORT_CLANG  1
#else
	#define CROSS_SUPPORT_CLANG  0
#endif

#define CROSS_SUPPORT_MSVC  (_MSC_VER + 0)

// === C/C++ compatibility ========================================================================================== //

#if CROSS_SUPPORT_CXX98
	#define CROSS_SUPPORT_EXTERN_C_BEGIN  extern "C" {
	#define CROSS_SUPPORT_EXTERN_C_END    }
#else
	#define CROSS_SUPPORT_EXTERN_C_BEGIN
	#define CROSS_SUPPORT_EXTERN_C_END
#endif

#if CROSS_SUPPORT_CXX17
	#define cross_support_constexpr_func  constexpr
#elif CROSS_SUPPORT_C99
	#define cross_support_constexpr_func  static inline
#else
	#define cross_support_constexpr_func  static
#endif
/**
 * Deprecated. Use `cross_support_constexpr_func` instead.
 */
#define cross_support_constexpr  cross_support_constexpr_func

// === attributes =================================================================================================== //

#if (CROSS_SUPPORT_GCC_LEAST(2,5) || CROSS_SUPPORT_CLANG)
	/**
	 * Use this instead of `cross_support_attr_pure` unless the function takes a pointer or reference.
	 */
	#define cross_support_attr_const  __attribute__((__const__))
#else
	#define cross_support_attr_const
#endif

#if (CROSS_SUPPORT_GCC_LEAST(2,96) || CROSS_SUPPORT_CLANG)
	/**
	 * Only use this instead of `cross_support_attr_const` when a function takes a pointer or reference.
	 */
	#define cross_support_attr_pure  __attribute__((__pure__))
#else
	#define cross_support_attr_pure
#endif


#if (CROSS_SUPPORT_CXX11 || CROSS_SUPPORT_C23)
	#define cross_support_noreturn  [[noreturn]]
#elif CROSS_SUPPORT_C11
	#define cross_support_noreturn  _Noreturn
#else
	#define cross_support_noreturn
#endif
#if (CROSS_SUPPORT_GCC_LEAST(3,1) || CROSS_SUPPORT_CLANG)
	#define cross_support_attr_noreturn  __attribute__((__noreturn__))
#else
	#define cross_support_attr_noreturn
#endif


#if (CROSS_SUPPORT_GCC_LEAST(3,1) || CROSS_SUPPORT_CLANG)
	#define cross_support_attr_always_inline  __attribute__((__always_inline__))
	#define cross_support_attr_unused         __attribute__((__unused__))
#else
	#define cross_support_attr_always_inline
	#define cross_support_attr_unused
#endif


#if (CROSS_SUPPORT_CXX17 || CROSS_SUPPORT_C23)
	#define cross_support_nodiscard  [[nodiscard]]
#else
	#define cross_support_nodiscard
#endif
#if (CROSS_SUPPORT_GCC_LEAST(3,4) || CROSS_SUPPORT_CLANG)
	#define cross_support_attr_warn_unused_result  __attribute__((__warn_unused_result__))
#else
	#define cross_support_attr_warn_unused_result
#endif


#if (CROSS_SUPPORT_GCC_LEAST(3,3) || CROSS_SUPPORT_CLANG)
	#define cross_support_attr_nonnull(...)  __attribute__((__nonnull__(__VA_ARGS__)))
	#define cross_support_attr_nonnull_all   __attribute__((__nonnull__))
#else
	#define cross_support_attr_nonnull(...)
	#define cross_support_attr_nonnull_all
#endif


#if (CROSS_SUPPORT_GCC_LEAST(4,3) || CROSS_SUPPORT_CLANG)
	#define cross_support_attr_hot   __attribute__((__hot__))
	#define cross_support_attr_cold  __attribute__((__cold__))
#else
	#define cross_support_attr_hot
	#define cross_support_attr_cold
#endif

// === branch optimization ========================================================================================== //

#if CROSS_SUPPORT_CXX20
	#define cross_support_if_likely(condition)    if(condition) [[likely]]
	#define cross_support_if_unlikely(condition)  if(condition) [[unlikely]]
#elif (CROSS_SUPPORT_GCC_LEAST(3,0) || CROSS_SUPPORT_CLANG)
	#if CROSS_SUPPORT_CXX
		#define cross_support_if_likely(condition)    if(__builtin_expect(static_cast<long>(static_cast<bool>(condition)), static_cast<long>(true)))
		#define cross_support_if_unlikely(condition)  if(__builtin_expect(static_cast<long>(static_cast<bool>(condition)), static_cast<long>(false)))
	#elif CROSS_SUPPORT_C23
		#define cross_support_if_likely(condition)    if(__builtin_expect((long)(bool)(condition), (long)(true)))
		#define cross_support_if_unlikely(condition)  if(__builtin_expect((long)(bool)(condition), (long)(false)))
	#elif CROSS_SUPPORT_C99
		#define cross_support_if_likely(condition)    if(__builtin_expect((long)(_Bool)(condition), 1L))
		#define cross_support_if_unlikely(condition)  if(__builtin_expect((long)(_Bool)(condition), 0L))
	#else
		#define cross_support_if_likely(condition)    if(__builtin_expect((long)!!(condition), 1L))
		#define cross_support_if_unlikely(condition)  if(__builtin_expect((long)!!(condition), 0L))
	#endif
#else
	#define cross_support_if_likely(condition)    if(condition)
	#define cross_support_if_unlikely(condition)  if(condition)
#endif

// === other ======================================================================================================== //

#if (defined(__has_include) || CROSS_SUPPORT_CXX17)
	#define CROSS_SUPPORT_HAS_INCLUDE_AVAILABLE  1
#else
	#define CROSS_SUPPORT_HAS_INCLUDE_AVAILABLE  0
#endif

#endif /* CROSS_SUPPORT_CORE_H */
