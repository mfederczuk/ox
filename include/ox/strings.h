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

#ifndef OX_STRINGS_H
#define OX_STRINGS_H

/**
 * Usage string. Requires one format argument. (argv[0])
 */
#define OX_USAGE_FMT_STR "usage: %s"

/**
 * Help string. Requires one format argument. (argv[0])
 */
#define OX_HELP_FMT_STR \
	OX_USAGE_FMT_STR "\n" \
	"" // TODO

/**
 * Version info string.
 */
#define OX_VERSION_INFO_STR \
	"ox 0.1.0\n" \
	"Copyright (C) 2021 Michael Federczuk\n" \
	"License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n" \
	"This is free software: you are free to change and redistribute it.\n" \
	"There is NO WARRANTY, to the extent permitted by law.\n" \
	"\n" \
	"Written by Michael Federczuk."

#endif /* OX_STRINGS_H */
