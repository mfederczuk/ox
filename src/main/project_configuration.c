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

#include <errno.h>
#include <ox/annotations.h>
#include <ox/project_configuration.h>
#include <ox/types.h>
#include <ox/utils.h>
#include <stddef.h>
#include <unistd.h>

struct filename {
	const_cstr_t string;
	size_t length;
};

#define make_filename(filename_string) \
	{ \
		.string = filename_string, \
		.length = array_size(filename_string) - 1 \
	}

/**
 * Stores all possible filenames of configuration names ordered from highest to lowest priority.
 * To save on computational time at runtime (but sacrificing binary size) the length is stored alongside the string.
 */
static const struct filename filenames[] = {
	make_filename("ox-project.yaml"),
	make_filename("ox-project.yml"),
	make_filename("project.yaml"),
	make_filename("project.yml")
};

#undef make_filename

ox_ret_status_t ox_find_project_configuration_file(
	OX_NON_NULLABLE(OX_UNINITIALIZED(const_cstr_t)*) project_configuration_filename_pointer
) {
	const struct filename* filename = NULL;

	for(size_t i = 0; i < array_size(filenames); ++i) {
		// Checking if the file exists and the current user has read access to it.
		errno = 0;
		if(access(filenames[i].string, F_OK | R_OK) == 0) {
			filename = filenames + i;
			break;
		}

		// ||| access(2) error handling |||
		// vvv                          vvv

		if(errno == EACCES || errno == ENOENT) {
			// TODO: Handle ENOENT better by checking if `filenames[i].string` is a dangling symbolic link (and then
			//       ignore it and try the next possible filename). Otherwise return `OX_RET_STATUS_FAILURE` and leave
			//       `errno` at `ENOENT`.
			//       From access(2):
			//           ENOENT  A component of pathname does not exist or is a dangling symbolic link.

			// TODO: Handle EACCES better by checking (before the access(2) call on the possible filename) if the
			//       current user has search permissions for the CWD. If not, return `OX_RET_STATUS_FAILURE` and leave
			//       `errno` at `EACCES`.
			//       Then, handle it better by separating the access(2) `F_OK` and `R_OK` calls.
			//       If the file exists, but the current user doesn't have read access to the file, find some way to
			//       communicate that back to the calling function. (different return type with 3 values?)
			//       From access(2):
			//           EACCES  The requested access would be denied to the file, or search permission is denied for
			//                   one of the directories in the path prefix of pathname.  (See also path_resolution(7).)

			// Both of these error cases can be ignored for now since they only occur in rare occasions.
			continue;
		}

		return OX_RET_STATUS_FAILURE;
	}

	*project_configuration_filename_pointer = (filename != NULL
	                                           ? filename->string
	                                           : NULL);

	return OX_RET_STATUS_SUCCESS;
}
