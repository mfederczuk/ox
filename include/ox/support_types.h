/*
 * Copyright (c) 2023 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef OX_SUPPORT_TYPES_H
#define OX_SUPPORT_TYPES_H

/**
 * Type alias for a mutable C string.
 */
typedef char* cstr_t;

/**
 * Type alias for an immutable C string.
 */
typedef const char* const_cstr_t;


/**
 * Common return type for functions that can either succeed or fail, similar to command exit codes.
 *
 * This is *not* a replacement for a boolean. A function only "fails" if an error occurred.
 *
 * For most functions, if the status `OX_RETURN_STATUS_SUCCESS` is NOT returned,
 * then `errno` should probably be examined.
 */
enum OxReturnStatus {
	OX_RETURN_STATUS_SUCCESS = 0,
	OX_RETURN_STATUS_FAILURE = 1,
};

#endif /* OX_SUPPORT_TYPES_H */
