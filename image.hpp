// ------------------------------
// Written by Mustafa Ozuysal
// Contact <mustafaozuysal@iyte.edu.tr> for comments and bug reports
// ------------------------------
// Copyright (c) 2018, Mustafa Ozuysal
// All rights reserved.
// ------------------------------
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holders nor the
//       names of his/its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
// ------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ------------------------------
#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <ostream>
#include <memory>
#include <vector>

using std::cerr;
using std::clog;
using std::cos;
using std::endl;
using std::exp;
using std::ifstream;
using std::ios;
using std::memset;
using std::ofstream;
using std::sin;
using std::string;
using std::unique_ptr;
using std::vector;


#include "util.hpp"

namespace ceng391 {

class Image {
public:
        Image(int width, int height, int n_channels, int step = -1);
        ~Image();

        static Image* new_gray(int width, int height);
        static Image* new_rgb(int width, int height);

        int w   () const { return m_width; }
        int h   () const { return m_height; }
        int n_ch() const { return m_n_channels; }
        int step() const { return m_step; }

        uchar*       data()       { return m_data; }
        const uchar* data() const { return m_data; }
        uchar*       data(int y)       { return m_data + y*m_step; }
        const uchar* data(int y) const { return m_data + y*m_step; }

        void set_rect(int x, int y, int width, int height, uchar value);
        void set_rect(int x, int y, int width, int height, uchar red, uchar green, uchar blue);
        void set(uchar value) { set_rect(0, 0, m_width, m_height, value); }
        void set_zero() { set(0); }

        void to_grayscale();
        void to_rgb();

        void rotate(Image *rotated, double theta, double tx, double ty) const;
        void rotate_centered(Image *rotated, double theta) const;

        template <typename T> void smooth_x(float sigma, T data) {
        
                if (m_n_channels != 1) {
                        cerr << "Smooth-x only works on grayscale images!" << endl;
                        return;
                }

                int k = 0;
                unique_ptr<float []> kernel(gaussian_kernel(sigma, &k));

                int l = k / 2;
                unique_ptr<float []>  buffer(new float[m_width + 2 * l]);

                for (int y = 0; y < m_height - 1; ++y) {
                        T row_data = data + y * m_width;
                        copy_to_buffer<T>(buffer.get(), row_data, m_width, l, 1);
                        convolve_buffer(buffer.get(), m_width, kernel.get(), k);
                        copy_from_buffer<T>(row_data, buffer.get(), m_width, 1);
                }
        }
        template <typename T> void smooth_y(float sigma, T data) {
                if (m_n_channels != 1) {
                        cerr << "Smooth-x only works on grayscale images!" << endl;
                        return;
                }

                int k = 0;
                unique_ptr<float []> kernel(gaussian_kernel(sigma, &k));

                int l = k / 2;
                unique_ptr<float []>  buffer(new float[m_height + 2 * l]);

                for (int x = 0; x < m_width - 1; ++x) {
                        copy_to_buffer<T>(buffer.get(), data + x, m_height, l, m_step);
                        convolve_buffer(buffer.get(), m_height, kernel.get(), k);
                        copy_from_buffer<T>(data + x, buffer.get(), m_height, m_step);
                }
        }
        template <typename T> void smooth(float sigma_x, float sigma_y, T data) {
                smooth_x<T>(sigma_x, data);
                smooth_y<T>(sigma_y, data);
        }

        short *deriv_x() const;
        short *deriv_y() const;

        std::vector<Keypoint> harris_corners(float threshold, float k, float sigma);
        short* computeImultiplyI(short* Ix, short* Iy);

        bool write_pnm(const std::string& filename) const;
        bool read_pnm (const std::string& filename);
private:
        int m_width;
        int m_height;
        int m_n_channels;
        int m_step;
        uchar* m_data;
};

}

#endif
