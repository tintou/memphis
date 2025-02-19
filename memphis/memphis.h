/*
 * Memphis - Cairo Rederer for OSM in C
 * Copyright (C) 2009  Simon Wenner <simon@wenner.ch>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __MEMPHIS_H__
#define __MEMPHIS_H__

/**
 * SECTION:memphis
 * @short_description: OpenStreetMap rendering library.
 *
 * Libmemphis is a generic glib/cairo based OSM renderer library.
 * It draws maps on arbitrary cairo surfaces. 
 */

#include <glib.h>

#include "memphis-map.h"
#include "memphis-rule-set.h"
#include "memphis-rule.h"
#include "memphis-renderer.h"
#include "memphis-data-pool.h"
#include "memphis-debug.h"

#endif /* __MEMPHIS_H__ */
