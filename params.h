#include <complex>
#include <cstdint>

extern char file_name[];

extern int num_frames;
extern int num_active_angle_frames;
extern int num_active_contour_frames;
extern int delay;

extern long double height_difference;
extern bool logarithmic_contour_lines;

extern int width;
extern int height;

extern long double x_min;
extern long double x_max;
extern long double y_min;
extern long double y_max;

extern int palette_bit_depth;
extern uint8_t colors[9];

std::complex<long double> function(std::complex<long double> z);
