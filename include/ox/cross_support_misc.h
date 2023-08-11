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

#ifndef CROSS_SUPPORT_MISC_H
#define CROSS_SUPPORT_MISC_H 1

#if (!(defined(CROSS_SUPPORT_CORE_H)) && !(CROSS_SUPPORT_CORE_H + 0))
	#error Include 'cross_support_core.h' before 'cross_support_misc.h'
#endif

// === kernels / operating systems ================================================================================== //

#if CROSS_SUPPORT_LINUX
	#include <linux/version.h>

	#define CROSS_SUPPORT_LINUX_LEAST(major, patchlevel, sublevel) \
		(LINUX_VERSION_CODE >= KERNEL_VERSION(major, patchlevel, sublevel))
#else
	#define CROSS_SUPPORT_LINUX_LEAST(major, patchlevel, sublevel)  0
#endif


#if CROSS_SUPPORT_HAS_INCLUDE_AVAILABLE
	#if __has_include(<unistd.h>)
		#include <unistd.h>
	#endif
#elif CROSS_SUPPORT_UNIX_LIKE
	#include <unistd.h>
#endif

#define CROSS_SUPPORT_POSIX        (_POSIX_VERSION + 0)
#define CROSS_SUPPORT_POSIX_2001  ((_POSIX_VERSION + 0) >= 200112L)
#define CROSS_SUPPORT_POSIX_2008  ((_POSIX_VERSION + 0) >= 200809L)

// === libraries ==================================================================================================== //

#if CROSS_SUPPORT_HAS_INCLUDE_AVAILABLE
	#if __has_include(<features.h>)
		#include <features.h>
	#endif
#endif

#if (!(defined(__GLIBC__))       && !(defined(__GLIBC_MINOR__)) && \
     !(defined(__GNU_LIBRARY__)) && !(defined(__GNU_LIBRARY_MINOR__)))

	#if CROSS_SUPPORT_CXX
		#include <climits>
	#else
		#include <limits.h>
	#endif
#endif

#define CROSS_SUPPORT_GLIBC_LEAST(major, minor) \
	(                                                           \
		(                                                       \
			((major) >= 6)                                      \
			&&                                                  \
			(                                                   \
				((__GLIBC__ + 0) > (major))                     \
				||                                              \
				(                                               \
					((__GLIBC__       + 0) == (major))          \
					&&                                          \
					((__GLIBC_MINOR__ + 0) >= (minor))          \
				)                                               \
			)                                                   \
		)                                                       \
		||                                                      \
		(                                                       \
			(((major) < 6))                                     \
			&&                                                  \
			(                                                   \
				((__GNU_LIBRARY__ + 0) > (major))               \
				||                                              \
				(                                               \
					((__GNU_LIBRARY__       + 0) == (major))    \
					&&                                          \
					((__GNU_LIBRARY_MINOR__ + 0) >= (minor))    \
				)                                               \
			)                                                   \
		)                                                       \
	)

// === C/C++ compatibility ========================================================================================== //

#if CROSS_SUPPORT_CXX11
	#define cross_support_nullptr  nullptr
#elif CROSS_SUPPORT_CXX
	#include <cstddef>
	#define cross_support_nullptr  NULL
#elif CROSS_SUPPORT_C23
	#define cross_support_nullptr  nullptr
#else
	#include <stddef.h>
	#define cross_support_nullptr  NULL
#endif

// === attributes =================================================================================================== //

#if (defined(cross_support_noreturn) && !CROSS_SUPPORT_CXX11 && !CROSS_SUPPORT_C23 && CROSS_SUPPORT_C11)
	#include <stdnoreturn.h>
	#undef  cross_support_noreturn
	#define cross_support_noreturn  noreturn
#endif

// === UB optimization ============================================================================================== //

#if CROSS_SUPPORT_CXX23
	#include <utility>
	#define cross_support_unreachable()  ::std::unreachable()
#elif CROSS_SUPPORT_C23
	#include <stddef.h>
	#define cross_support_unreachable()  unreachable()
#elif (CROSS_SUPPORT_GCC_LEAST(4,5) || CROSS_SUPPORT_CLANG)
	#define cross_support_unreachable()  __builtin_unreachable()
#elif CROSS_SUPPORT_MSVC
	#define cross_support_unreachable()  __assume(0)
#else
	#if CROSS_SUPPORT_CXX
		#include <cassert>
	#else
		#include <assert.h>
	#endif

	// using `assert` because some implementations have noreturn optimizations
	#define cross_support_unreachable()  assert(0)
#endif

// === branch optimization ========================================================================================== //

#if (defined(cross_support_if_likely) && \
     !CROSS_SUPPORT_CXX20 && \
     (CROSS_SUPPORT_GCC_LEAST(3,0) || CROSS_SUPPORT_CLANG) && \
     !CROSS_SUPPORT_CXX && \
     !CROSS_SUPPORT_C23 && \
     CROSS_SUPPORT_C99)

	#include <stdbool.h>
	#undef  cross_support_if_likely
	#define cross_support_if_likely(condition)    if(__builtin_expect((long)(bool)(condition), (long)(true)))
#endif

#if (defined(cross_support_if_unlikely) && \
     !CROSS_SUPPORT_CXX20 && \
     (CROSS_SUPPORT_GCC_LEAST(3,0) || CROSS_SUPPORT_CLANG) && \
     !CROSS_SUPPORT_CXX && \
     !CROSS_SUPPORT_C23 && \
     CROSS_SUPPORT_C99)

	#include <stdbool.h>
	#undef  cross_support_if_unlikely
	#define cross_support_if_unlikely(condition)  if(__builtin_expect((long)(bool)(condition), (long)(false)))
#endif

// === other ======================================================================================================== //

#if CROSS_SUPPORT_CXX11
	#define cross_support_static_assert(expr, msg)  static_assert(expr, msg)
#elif CROSS_SUPPORT_C11
	#include <assert.h>

	#define cross_support_static_assert(expr, msg)  static_assert(expr, msg)
#else
	#if CROSS_SUPPORT_CXX
		#include <cassert>
	#else
		#include <assert.h>
	#endif

	#define cross_support_static_assert(expr, msg)  assert(((void)(msg), (expr)))
#endif

#if CROSS_SUPPORT_CXX17
	#define cross_support_static_assert_nomsg(expr)  static_assert(expr)
#elif CROSS_SUPPORT_CXX11
	#define cross_support_static_assert_nomsg(expr)  static_assert(expr, "Static assertion failed")
#elif CROSS_SUPPORT_C23
	#define cross_support_static_assert_nomsg(expr)  static_assert(expr)
#elif CROSS_SUPPORT_C11
	#include <assert.h>

	#define cross_support_static_assert_nomsg(expr)  static_assert(expr, "Static assertion failed")
#else
	#if CROSS_SUPPORT_CXX
		#include <cassert>
	#else
		#include <assert.h>
	#endif

	#define cross_support_static_assert_nomsg(expr)  assert(expr)
#endif

#endif /* CROSS_SUPPORT_MISC_H */
