# cub3d_mandatory

## Description
MiniLibX raycasting project rendering a 3D maze.

## Features
- Map parsing/validation and DDA raycasting.
- Textured walls and player movement.

## Technologies Used
- C, MiniLibX, Makefile.

## Installation
- Install MiniLibX deps, then run `make`.

## Usage
- `./cube3D maps/valid_map.cub` to launch the viewer.

## Example
- Rotate/move with arrow/WASD keys inside the maze.

## Technical Notes
- Parses `.cub` for textures, colors, and map; validates walls enclosure and player start.
- Raycasting via DDA: compute step/delta distances per ray, pick wall hit, and choose texture column.
- Z-buffer used for sprites/door ordering if implemented; MiniLibX handles window and image buffers.

## Author
- Oualid Obbad (@oualidobbad)