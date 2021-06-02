/*
 * Simple to configure C & C++ build system.
 * Copyright (C) 2021  Michael Federczuk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef OX_TYPES_H
#define OX_TYPES_H

/**
 * Type alias for a mutable C string.
 */
typedef char* cstr_t;

/**
 * Type alias for an immutable C string.
 */
typedef const char* const_cstr_t;

/**
 * Common return type for a function that can fail or succeed.
 *
 * THIS IS NOT A REPLACEMENT FOR true/false!!!
 * A function "fails" only when an error occurs!
 * So when `OX_RET_STATUS_FAILURE` is returned, `errno` should probably be queried.
 */
typedef enum {
	OX_RET_STATUS_SUCCESS = 0,
	OX_RET_STATUS_FAILURE = 1
} ox_ret_status_t;

#endif /* OX_TYPES_H */
