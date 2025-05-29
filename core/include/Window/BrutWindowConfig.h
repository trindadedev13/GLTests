#ifndef BRUT_WINDOW_CONFIG_HPP
#define BRUT_WINDOW_CONFIG_HPP

#define GL_WINDOW_NAME "Brut"

#if defined(BRUT_ANDROID)
#define GL_WINDOW_WIDTH 600
#define GL_WINDOW_HEIGHT 1000
#define BRUT_DEVICE_NAME "termux_x11"
#else
#define GL_WINDOW_WIDTH 720
#define GL_WINDOW_HEIGHT 1560
#define BRUT_DEVICE_NAME "linux"
#endif

#endif
