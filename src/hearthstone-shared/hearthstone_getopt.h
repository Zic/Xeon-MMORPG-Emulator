/*
 * Aspire Hearthstone
 * Copyright (C) 2008 - 2009 AspireDev <http://www.aspiredev.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _HEARTHSTONE_GETOPT_H
#define _HEARTHSTONE_GETOPT_H

/* getopt() wrapper */
#define hearthstone_no_argument            0
#define hearthstone_required_argument      1
#define hearthstone_optional_argument      2
struct hearthstone_option
{
	const char *name;
	int has_arg;
	int *flag;
	int val;
};
extern char hearthstone_optarg[514];
int hearthstone_getopt_long_only (int ___argc, char *const *___argv, const char *__shortopts, const struct hearthstone_option *__longopts, int *__longind);

#endif
