#include "gifenc.h"
#include "params.h"

#include <chrono>
#include <cmath>
#include <complex>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

std::unique_ptr<std::vector<std::vector<uint8_t>>> getFrames(
    const std::function<std::complex<long double>(std::complex<long double>)> &f) {

    auto frames = std::make_unique<std::vector<std::vector<uint8_t>>>(
        num_frames, std::vector<uint8_t>(width * height));
    //for every pixel, ...
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            auto value
                = f(std::complex<long double>(x_min + ((long double) i / width) * (x_max - x_min),
                    y_max + ((long double) j / height) * (y_min - y_max)));
            int location_index = (width * j + i);

            //(the abs of a complex value is its magnitude)
            long double d = std::abs(value);
            if (logarithmic_contour_lines) {
                d = logl(d);
            }
            int contour_frame = 0;
            if (std::isnormal(d)) {
                contour_frame = fmodl(d, height_difference) * num_frames / height_difference;
            }
            if (contour_frame < 0) {
                contour_frame = (contour_frame % num_frames) + num_frames;
            }
            for (int k = 0; k < num_active_contour_frames; k++) {
                int active_frame = (contour_frame + k) % num_frames;
                (*frames)[active_frame][location_index] = 1;
            }

            d = std::arg(value);
            if (!std::isnormal(d))
                d = 0;
            if (d < 0)
                d += 2 * M_PI;
            int angle_frame = d * num_frames / (2 * M_PI);

            for (int k = 0; k < num_active_angle_frames; k++) {
                int active_frame = (angle_frame + k) % num_frames;
                (*frames)[active_frame][location_index] = 2;
            }
        }
        std::cout << i << " / width = " << width << std::endl;
    }
    return frames;
}

int main() {
    auto before_frames = std::chrono::high_resolution_clock::now();
    auto frames = getFrames(function);
    auto after_frames = std::chrono::high_resolution_clock::now();

    ge_GIF *gif = ge_new_gif(file_name, width, height, colors,

        palette_bit_depth,
        0 // for infinite loop
    );

    std::cout << "writing..." << std::endl;
    auto before_fwrite = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_frames; i++) {
        for (int j = 0; j < width * height; j++)
            gif->frame[j] = (*frames)[i][j];
        ge_add_frame(gif, delay);
        std::cout << i << " / num frames = " << num_frames << std::endl;
    }
    auto after_fwrite = std::chrono::high_resolution_clock::now();
    ge_close_gif(gif);

    auto frame_duration
        = std::chrono::duration_cast<std::chrono::microseconds>(after_frames - before_frames);
    auto fwrite_duration
        = std::chrono::duration_cast<std::chrono::microseconds>(after_fwrite - before_fwrite);

    FILE *p_file = NULL;
    p_file = fopen(file_name, "rb");
    fseek(p_file, 0, SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    double file_size = size / 1000000.0;
    std::cout << "function duration (s) :      " << frame_duration.count() / 1000000.0 << std::endl;
    std::cout << "file write duration (s) : " << fwrite_duration.count() / 1000000.0 << std::endl;
    std::cout << "file size (mb) :          " << file_size << std::endl;
    return 0;
}
