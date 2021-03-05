#include "params.h"

#include <cstdint>
#include <complex>

char file_name[] = "out.gif";

//variables for animation.
//fps kind of depends on application viewing the gif so increasing the
//number of frames will increase the time the animation takes
int num_frames = 300;
int num_active_angle_frames = 30;
int num_active_contour_frames = 30;

int delay = 1;

//height difference between contour lines. Affects line thickness,
//because if height difference is 1, about num_active_contour_frames / num_frames
//percent of the values between 1 and 2 are highlighted at any time.
//so it's either a lot of thin lines or a few thick lines
long double height_difference = 1;


//highlight t mod h = |f(z)| mod h or t mod h = log(|f(z)|) mod h
//it's sometimes helpful
bool logarithmic_contour_lines = true;

//size of image
int width = 2000;
int height = 2000;

//bounds of the graphs
long double x_min = -10;
long double x_max =  10;
long double y_min = -10;
long double y_max =  10;

//log_2(number of colors)
int palette_bit_depth = 2;

//colors in r, g, b
uint8_t colors[] = {
            0x4f, 0x04, 0x12, // none active
            0x88, 0x4d, 0xa3, // angle active
            0x9d, 0xa3, 0x4d //  contour active
            //the way the program works now, it doesn't check if
            //both are active
        };


//the function to display. 
std::complex<long double> function(std::complex<long double> z) {
    std::complex<long double> ans = 0;
    for(long double i=0; i<100; i += 1) {
        ans += std::pow(std::complex<long double>(i,0),-z);
    }
    return ans;
}
