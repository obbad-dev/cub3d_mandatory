# cub3d_mandatory

Full Wolfenstein-style 3D raycasting engine using MiniLibX — parses `.cub` scene files, casts 1920 rays via DDA, renders textured walls at 1920×1080 with directional textures, configurable floor/ceiling colors, and a toggleable minimap.

## Project Overview
- What it does: reads a `.cub` configuration file specifying wall textures (NO/SO/WE/EA), floor/ceiling RGB colors, and a 2D map grid; renders a real-time 3D perspective view using raycasting.
- Use cases: understanding raycasting math, DDA line-stepping, texture mapping, and real-time rendering pipelines.
- Problem solved: transforms a 2D tile map into a navigable 3D environment with textured walls and player movement.

## Architecture & Design
- **Data structures** (`header.h`):
  - `t_data`: central state — MLX handles, player position `(px, py)`, angle, FOV, map grid, textures (NO/SO/WE/EA), floor/ceiling colors, key states, minimap toggle, sprint speed.
  - `t_cast`: per-ray state — end point, distance, ray angle, facing flags (up/down/left/right), wall height, texture coordinates, horizontal/vertical hit flag.
  - `t_keys`: boolean key state tracking for smooth multi-key input (WASD + arrows + ESC + F1 + Shift).
- **Modules**:
  - `parsing/`: `.cub` file reader — validates textures, colors, map enclosure, player start position.
  - `dda_algo/`: DDA raycasting — horizontal and vertical intersection detection, distance comparison, hit point selection.
  - `draw_window/`: MLX window creation, image buffer management, per-frame rendering.
  - `texture/`: texture loading via MLX, pixel color extraction, texture coordinate mapping.
  - `gnl/`: get_next_line for file reading.

## Core Concepts (with code)
- DDA ray–wall intersection (choosing closest hit):
```c
// dda_algo/dda_algo.c
void dda_algo(t_data *data, t_cast *cast)
{
    facing_player(cast);  // set facing_up/down/left/right
    horizonlat_inter(data, cast, &end_hor_x, &end_hor_y);
    vertical_inter(data, cast, &end_ver_x, &end_ver_y);
    dist_hor = distance(data->px, data->py, end_hor_x, end_hor_y);
    dist_ver = distance(data->px, data->py, end_ver_x, end_ver_y);
    if (dist_hor < dist_ver)
        set_hit(cast, end_hor_x, end_hor_y, dist_hor);
    else
        set_hit(cast, end_ver_x, end_ver_y, dist_ver);
}
```
- Perpendicular distance for fisheye correction:
```c
// Projection: wall_height = TILE_SIZE / perpendicular_distance * dist_to_projection_plane
cast->dist_perpo = cast->distance * cos(cast->ray_angle - data->angle_direction);
cast->tall_wall = (TILE_SIZE / cast->dist_perpo) * cast->dist_proj_plan;
```

## Code Walkthrough
1) `main.c`: validate `.cub` extension, read file into content array, init textures, extract textures/colors, parse map, launch window.
2) `parsing/`: `fill_content()` reads file via GNL; `extract_textures_colors()` identifies NO/SO/WE/EA paths and F/C RGB values; `parse_map()` validates enclosure, player count, and valid characters.
3) `dda_algo/`: for each of 1920 rays, `dda_algo()` finds horizontal and vertical wall hits, picks the closest, records hit type for texture selection.
4) `draw_window/`: creates MLX window (1920×1080), sets up key hooks, enters render loop; `dda_and_rendring()` casts all rays and calls `render3d()` per ray.
5) `player_movement.c`: `mov_player()` reads key states, applies MOVE_SPEED (with Shift sprint), checks wall collision via `check_wall()`, updates rotation.
6) `mini_map.c`: when F1 toggled, draws a scaled-down (0.1×) overlay of the map grid.

## Installation & Setup
- Requires: MiniLibX (Linux X11), `libX11-dev`, `libXext-dev`, `libbsd-dev`, `make`, `cc`.
- Build: `make` → produces `cube3D`.
- Run: `./cube3D maps/map.cub`.

## Usage Guide
- **WASD**: move forward/back/strafe.
- **Left/Right arrows**: rotate view.
- **Shift**: sprint.
- **F1**: toggle minimap overlay.
- **ESC**: quit.

## Technical Deep Dive
- **Resolution**: 1920×1080 with `TILE_SIZE=64`, `NUM_RAYS=1920` (one ray per pixel column).
- **DDA**: steps along grid lines in both horizontal and vertical directions simultaneously; O(map_dimension) per ray worst case.
- **Texture mapping**: selects NO/SO/WE/EA texture based on ray facing direction and hit type (horizontal vs vertical); `tex_x` derived from fractional hit position.
- **Fisheye fix**: perpendicular distance = `raw_distance * cos(ray_angle - player_angle)` prevents barrel distortion.
- **Input**: key press/release tracking via `t_keys` struct enables smooth simultaneous movement (e.g., strafe + rotate).

## Improvements & Future Work
- Add sprite rendering with z-buffer sorting.
- Implement mouse-look for smoother rotation.
- Add floor/ceiling texture mapping.
- Optimize rendering with dirty-rectangle updates.

## Author
Oualid Obbad (@oualidobbad)