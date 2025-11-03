#include "header.h"
#include <sys/time.h>

// Get current time in seconds
double get_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

// Initialize FPS tracking
void init_fps(t_data *data)
{
    data->last_frame_time = get_time();
    data->current_frame_time = 0;
    data->delta_time = 0;
    data->fps = 0;
    data->frame_count = 0;
    data->fps_update_timer = 0;
}

// Update FPS counter (call this every frame)
void update_fps(t_data *data)
{
    data->current_frame_time = get_time();
    data->delta_time = data->current_frame_time - data->last_frame_time;
    data->last_frame_time = data->current_frame_time;
    
    data->frame_count++;
    data->fps_update_timer += data->delta_time;
    
    // Update FPS display every 0.5 seconds (smoother display)
    if (data->fps_update_timer >= 0.5)
    {
        data->fps = (int)(data->frame_count / data->fps_update_timer);
        data->frame_count = 0;
        data->fps_update_timer = 0;
    }
}