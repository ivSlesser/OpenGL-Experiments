// MIT License
//
// Copyright (c) 2020 Ian Vincent Slesser
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// Adapated from Ken Perlin's 2002 Java implementation of Improved Noise
// https://cs.nyu.edu/~perlin/noise/
// https://mrl.nyu.edu/~perlin/paper445.pdf

#include "Common.h"

#define DEFAULT_PERLIN_SEED 100

class Perlin {
 protected:
 private:
  int seed;
  std::vector<int> p;

 private:
  void GenerateBaseData();
  double Fade(double t);
  double Lerp(double t, double a, double b);
  double Grad(int hash, double x, double y, double z);
  double Get(double x, double y, double z);

 public:
  Perlin(int seed = DEFAULT_PERLIN_SEED);
  virtual ~Perlin();

  double Noise(int octaves, double persistence, double x, double y = 0.0, double z = 0.0);
};

