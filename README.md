# Harris Corner Detection Algorithm Implementation

### Introduction

* This repo includes my solution of the given homework(5/3) in the scope of the Introduction to Image Understanding(CENG391) course which is given as a technical elective in 2019-2020 Fall semester by Computer Engineering Department at Izmir Institute of Technology.

* (*)README.md file uses some parts of the official Homework Doc to better express the purpose of the Homework.

* All solutions implemented on top of the base code.


### Problem*

* Write a new member function Image::harris_corner that takes three single precision floating numbers as parameters:

1. A Harris cornerness score threshold,
2. The value of k in the Harris cornerness score function,
3. The sigma value for the smoothing of the Ix^2 Iy^2 and IxIy arrays.

* The function should compute Harris corners and return an std::vector of the following structure

```C++
struct Keypoint {
    float x;
    float y;
    float score;
};
```

### Implementation and Result Showcase

* I have prepared a sh script to add small automation to my compile process. Therefore you can compile given files with this script. Compilation process uses valgrind to check and find any memory leak my occur and this check takes time to complete.If you want you can disable it inside of the compile.sh file.

* I have implemented methods in the problem statement and some others to help me to solve the problems more effectively.

#### Setup

* When you compile with compile.sh it runs the program once with valgrind. After that you can also run it yourself.

```bash
$ sh compile.sh
$ ./build/image-test
```

* You can play with image_test.cc to get different results. However don't forget to compile whenever you made a change :)

```C++
int main(int argc, char** argv)
{
     Image* img = new Image(4, 4, 1);
     img->read_pnm("small_watch.pgm");
     vector<ceng391::Keypoint> points = img->harris_corners(2000,1,1.2);

     for(int i = 0; i < points.size(); i++) {
          cout<<i<<". Keypoint: ("<<points.at(i).x<<","<<points.at(i).y<<") Score:"<<points.at(i).score<<endl;

     }

     delete img;

     return EXIT_SUCCESS;
}
```

![alt text](https://github.com/feyil/Harris-Corner-Detection-Implementation/blob/master/screenshots/keypoint.png "smooth")