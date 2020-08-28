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


#include "Transform.h"

Transform::Transform(const glm::vec3 &_t, const glm::vec3 &_s, const glm::vec3 &_r)
    : t(_t), s(_s), r(_r) {
  // As we are creating a non-default transform, we need to set Model matrix.
  tf = glm::translate(glm::mat4(1.0f), t) *
      glm::eulerAngleYXZ(r.y, r.x, r.z) *
      glm::scale(glm::mat4(1.0f), s);
}

const glm::mat4 &Transform::Transformation() {
  // Only need to update if the bit is set.
  if (update) {
    tf = glm::translate(glm::mat4(1.0f), t) *
        glm::eulerAngleYXZ(glm::radians(r.y), glm::radians(-r.x), glm::radians(-r.z)) *
        glm::scale(glm::mat4(1.0f), s);
      update = false;
  }
  // Always return from cache.
  return tf;
}