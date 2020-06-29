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


#include "Plane.h"

Plane::Plane(glm::vec4 color, const glm::vec3 &pos,
			 const glm::vec2 &size, float resolution) {

  const float uvX = 1.0f / (size.x - 1);
  const float uvZ = 1.0f / (size.y - 1);

  // Create the base vertices.
  unsigned vertex = 0;
  for (unsigned x = 0; x < size.x; ++x) {
	for (unsigned z = 0; z < size.y; ++z) {
	  float xp = pos.x + x * resolution;
	  float zp = pos.z + z * resolution;
	  vertices.push_back({{xp, pos.y, zp}, color, {z * uvZ, x * uvX}, {0.0f, 1.0f, 0.0f}});
	}
  }

  // Create indices
  unsigned offset = 0;
  for (unsigned z = 0; z < size.y - 1; ++z) {
	unsigned Z = z * (size.x);
	unsigned ZN = (z + 1) * (size.x);
	for (unsigned x = 0; x < size.x - 1; ++x) {
	  indices.push_back(Z + x); // A
	  indices.push_back(ZN + x + 1); // C
	  indices.push_back(ZN + x); // D

	  indices.push_back(ZN + x + 1); // C
	  indices.push_back(Z + x); // A
	  indices.push_back(Z + x + 1); // B
	}
  }
}
