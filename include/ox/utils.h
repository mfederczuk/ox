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

#ifndef OX_UTILS_H
#define OX_UTILS_H

/**
 * Calculates the size of an array.
 * This parameter must be an actual array, NOT just a pointer.
 */
#define array_size(array) (sizeof(array) / sizeof(*(array)))

#endif /* OX_UTILS_H */