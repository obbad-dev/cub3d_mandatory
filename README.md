    # cub3d_mandatory

    MiniLibX raycasting project rendering a 3D maze from a 2D map.

    ## Architecture
    - Parser: reads `.cub` file for texture paths, floor/ceiling colors, and map grid; validates enclosure and one player start.
    - Raycasting: DDA per ray, perpendicular distance correction, texture column selection, optional sprite/z-buffer handling.
    - Input/render: keyboard move/turn, MiniLibX window with per-frame redraws.

    ## Build & Run
    - Requires MiniLibX deps.
    - `make` → builds the viewer.
    - Run: `./cube3D maps/valid_map.cub` (binary name may vary).

    ## Technical Notes
    - Ensure map lines are rectangular after trimming; reject unknown characters.
    - Normalize direction vector; step sizes derived from ray dir to avoid fisheye.

    ## Author
    Oualid Obbad (@oualidobbad)