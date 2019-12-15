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
#include <cstdlib>
#include <iostream>

#include "image.hpp"


using ceng391::Image;
using ceng391::short_to_image;
using std::cout;
using std::endl;

int main(int argc, char** argv)
{
     Image* img = new Image(4, 4, 1);
     img->read_pnm("small_watch.pgm");
     img->harris_corners(1,1,1);

     short *dx = img->deriv_x();
     short *dy = img->deriv_y();

     // dx = img->computeImultiplyI(dx, dx);
     cout << "Derivatives computed" << endl;

     Image *dx_img = short_to_image(dx, img->w(), img->h());
     Image *dy_img = short_to_image(dy, img->w(), img->h());
     dx_img->write_pnm("/tmp/dx");
     dy_img->write_pnm("/tmp/dy");

     //    cout << "(" << gray->w() << "x" << gray->h() << ") channels: "
     //         << gray->n_ch() << " step: " << gray->step() << endl;
     //    gray->set_zero();
     //    gray->set_rect(32, 32, 64, 64, 255);
     //    gray->write_pnm("/tmp/test_image_gray");
     //    delete gray;

     //    Image* rgb = Image::new_rgb(128, 128);
     //    cout << "(" << rgb->w() << "x" << rgb->h() << ") channels: "
     //         << rgb->n_ch() << " step: " << rgb->step() << endl;
     //    rgb->set_zero();
     //    rgb->set_rect(32, 32, 64, 64, 255, 0, 255);
     //    rgb->write_pnm("/tmp/test_image_rgb");
     //    delete rgb;

     //    Image img(4, 4, 1);
     //    img.read_pnm("/tmp/test_image_gray.pgm");
     //    img.to_rgb();
     //    img.write_pnm("/tmp/test_image_gray2rgb");

     //    img.read_pnm("/tmp/test_image_rgb.ppm");
     //    img.to_grayscale();
     //    img.write_pnm("/tmp/test_image_rgb2gray");

     //    img.read_pnm("../small_city.pgm");
     //    Image rotated(img.w()*2, img.h()*2, 1);
     //    double theta = 45.0 * 3.1415926 / 180;
     //    img.rotate_centered(&rotated, theta);
     //    rotated.write_pnm("/tmp/small_city_crotated_45");

     //    short *dx = img.deriv_x();
     //    short *dy = img.deriv_y();
     //    cout << "Derivatives computed" << endl;

     //    Image *dx_img = short_to_image(dx, img.w(), img.h());
     //    Image *dy_img = short_to_image(dy, img.w(), img.h());
     //    dx_img->write_pnm("/tmp/dx");
     //    dy_img->write_pnm("/tmp/dy");

        float sigma_x = 1.0f;
        float sigma_y = 2.5f;
        img->smooth<>(sigma_x, sigma_y, dx);
        img->write_pnm("/tmp/smoothed_xy");


          dx_img = short_to_image(dx, img->w(), img->h());
          dy_img = short_to_image(dy, img->w(), img->h());
          dx_img->write_pnm("/tmp/dx");
          dy_img->write_pnm("/tmp/dy");

     //    delete [] dx;
     //    delete [] dy;
     //    delete dx_img;
     //    delete dy_img;

        return EXIT_SUCCESS;
}

