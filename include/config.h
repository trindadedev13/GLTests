#ifndef CONFIG_H
#define CONFIG_H

#define GL_WINDOW_NAME ""

#define GCG_RUNNING_PATH RUNNING_PATH

#if defined(GCG_PLATFORM_TERMUX_X11)
#define GL_WINDOW_WIDTH 600
#define GL_WINDOW_HEIGHT 1000
#define GCG_DEVICE_NAME "termux_x11"
#elif defined(GCG_PLATFORM_LINUX)
#define GL_WINDOW_WIDTH 600
#define GL_WINDOW_HEIGHT 600
#define GCG_DEVICE_NAME "linux"
#else
#error "No valid device macro defined"
#endif

#endif