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

#include <memphis/memphis.h>
#include <stdlib.h>
#include <glib/gstdio.h>

#define RESOLUTION 256

int main (int argc, char **argv) {
  g_autoptr(MemphisRenderer) r = NULL;
  g_autoptr(MemphisRuleSet) rules = NULL;
  g_autoptr(MemphisMap) map = NULL;
  cairo_surface_t *surface;
  cairo_t *cr;
  gint i, j, maxx, maxy;
  gchar *path, *mapfile;
  gint zoom_level;

  if (argc > 1)
    zoom_level = atoi(argv[1]);
  else
    zoom_level = 14;

  if (argc > 2)
    mapfile = argv[2];
  else
    mapfile = "map.osm";

  g_mkdir ("tiles", 0755);

  memphis_debug_set_print_progress (TRUE);

  rules = memphis_rule_set_new ();
  memphis_rule_set_load_from_file (rules, "default-rules.xml", NULL);

  map = memphis_map_new ();
  GError *err = NULL;
  memphis_map_load_from_file (map, mapfile, &err);
  if (err != NULL) {
    g_print ("Error: %s\n", err->message);
    return -1;
  }

  r = memphis_renderer_new_full (rules, map);
  memphis_renderer_set_resolution (r, RESOLUTION);
  g_print ("Tile resolution: %u\n", memphis_renderer_get_resolution (r));

  maxx = memphis_renderer_get_max_x_tile (r, zoom_level);
  maxy = memphis_renderer_get_max_y_tile (r, zoom_level);
  i = memphis_renderer_get_min_x_tile (r, zoom_level);
  
  for (; i <= maxx; i++)
    {
      j = memphis_renderer_get_min_y_tile (r, zoom_level);
      for (; j <= maxy; j++)
        {
          surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
              RESOLUTION, RESOLUTION);
          cr =  cairo_create(surface);
          path = g_strdup_printf ("tiles/%i_%i.png", i, j);

          g_print ("Drawing tile: %i, %i\n", i, j);
          memphis_renderer_draw_tile (r, cr, i, j, zoom_level);
          cairo_surface_write_to_png(surface, path);
          
          g_free (path);
          cairo_destroy(cr);
          cairo_surface_destroy(surface);
        }
    }

  return 0;
}
