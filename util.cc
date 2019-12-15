// ------------------------------
// Written by Mustafa Ozuysal
// Contact <mustafaozuysal@iyte.edu.tr> for comments and bug reports
// ------------------------------
// Copyright (c) 2019, Mustafa Ozuysal
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
#include "util.hpp"

#include <cmath>

#include "image.hpp"

using std::ceil;
using std::exp;

namespace ceng391 {

Image *short_to_image(const short *ptr, int width, int height)
{
        Image *img = Image::new_gray(width, height);
        for (int y = 0; y < height; ++y) {
                const short *row = ptr + y * width;
                uchar *irow = img->data(y);
                for (int x = 0; x < width; ++x) {
                        irow[x] = (row[x] + 255) / 2;
                }
        }

        return img;
}

float *gaussian_kernel(float sigma, int *k)
{
        int l = ceil(2.0f * sigma);
        *k = 2 * l + 1;
        float *kernel = new float[*k];
        float sum = 0.0f;
        for (int i = 0; i < *k; ++i) {
                int x = i - l;
                kernel[i] = exp(-0.5f * x * x / sigma / sigma);
                sum += kernel[i];
        }
        for (int i = 0; i < *k; ++i)
                kernel[i] /= sum;

        return kernel;
}

void copy_to_buffer(float *buffer, const uchar *src, int n, int border_size,
                    int stride)
{
        for (int i = 0; i < n; ++i)
                buffer[border_size + i] = src[i * stride];

        for (int i = 0; i < border_size; ++i) {
                buffer[i] = buffer[border_size];
                buffer[i + n + border_size] = buffer[border_size + n - 1];
        }
}

void convolve_buffer(float *buffer, int n, const float *kernel, int k)
{
        for (int i = 0; i < n; ++i) {
                float sum = 0.0f;
                for (int j = 0; j < k; ++j) {
                        sum += kernel[j] * buffer[i + j];
                }
                buffer[i] = sum;
        }
}

void copy_from_buffer(uchar *dest, const float *buffer, int n, int stride)
{
        for (int i = 0; i < n; ++i)
                dest[i * stride] = buffer[i];
}

}
