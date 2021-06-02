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

#ifndef OX_PROJECT_CONFIGURATION_H
#define OX_PROJECT_CONFIGURATION_H

#include <ox/annotations.h>
#include <ox/types.h>

/**
 * DESCRIPTION:
 *   Tries to find a project configuration file in the current working directory.
 *
 *   When an appropriate project configuration file is found, `*project_configuration_filename_pointer` is initialized
 *   with a string that contains the filename.
 *   This string is stored in statically allocated memory. Do not pass it to free(3)!
 *
 *   When no appropriate project configuration file is found, `*project_configuration_filename_pointer` is initialized
 *   with `NULL`.
 *
 * RETURN VALUE:
 *   When an error occurs, `OX_RET_STATUS_FAILURE` is returned, `*project_configuration_filename_pointer` is left
 *   uninitialized and `errno` is set appropriately, otherwise `OX_RET_STATUS_SUCCESS` is returned.
 *
 * ERRORS:
 *   ELOOP         Too many symbolic links were encountered in resolving pathname.
 *   ENAMETOOLONG  (current working directory + project configuration filename) is too long.
 *   ENOTDIR       A component used as a directory in the current working directory is not, in fact, a directory.
 *                 (may happen if the current working directory gets removed and then replaced with a file after process
 *                  start)
 *   EIO           An I/O error occurred.
 *   ENOMEM        Insufficient kernel memory was available.
 */
ox_ret_status_t ox_find_project_configuration_file(
	OX_NON_NULLABLE(OX_UNINITIALIZED(const_cstr_t)*) project_configuration_filename_pointer
);

#endif /* OX_PROJECT_CONFIGURATION_H */
