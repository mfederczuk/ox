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

#include <ox/project_configuration.h>
#include <stdio.h>
#include <errno.h>

int main() {
	const_cstr_t project_configuration_file_path;
	errno = 0;
	if(ox_find_project_configuration_file(&project_configuration_file_path) != OX_RET_STATUS_SUCCESS) {
		// TODO: error handling
		return 1;
	}

	// TODO: remove the read access check from `ox_find_project_configuration_file`
	// TODO: check if we have read access to `project_configuration_file_path`

	return 0;
}
