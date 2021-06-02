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

#ifndef OX_ANNOTATIONS_H
#define OX_ANNOTATIONS_H

/**
 * A struct field or parameter type annotated with this macro might/may contain an uninitialized value.
 */
#define OX_UNINITIALIZED(type) type

/**
 * A struct field or return type annotated with this macro is a pointer that is either `NULL` or points to a block of
 * dynamically allocated memory (created with either malloc(3), calloc(3) or realloc(3)).
 *
 * Return values are generally safe to call free(3) on, but it isn't safe for struct fields.
 */
#define OX_ALLOCATED(pointer_type) pointer_type

/**
 * A struct field, return or parameter pointer type annotated with this macro may be `NULL`.
 */
#define OX_NULLABLE(pointer_type) pointer_type
/**
 * A struct field or return pointer type annotated with this macro will not be `NULL`.
 *
 * A parameter pointer type annotated with this macro must not be `NULL`.
 * It is considered to be undefined behavior if a `NULL` pointer is passed.
 */
#define OX_NON_NULLABLE(pointer_type) pointer_type

#endif /* OX_ANNOTATIONS_H */
