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


#pragma once

#include "Common.h"

class Transform {

 protected:
  glm::vec3 t = glm::vec3(0.0f);
  glm::vec3 r = glm::vec3(0.0f);
  glm::vec3 s = glm::vec3(1.0f);
  glm::mat4 tf = glm::mat4(1.0f);
  bool update = false;
  // -------------------------------------------------------------------------------------------------------------------

 public:
  Transform() {}
  virtual ~Transform() {}
  Transform(const glm::vec3 &_t, const glm::vec3 &_s = glm::vec3(1.0f), const glm::vec3 &_r = glm::vec3(0.0f));

  const glm::mat4 &Transformation();

  inline const glm::vec3 &GetTranslate() const { return t; }
  inline const glm::vec3 &GetScale() const { return s; }
  inline const glm::vec3 &GetRotate() const { return r; }

  inline glm::vec3 &GetTranslate() { return t; }
  inline glm::vec3 &GetScale() { return s; }
  inline glm::vec3 &GetRotate() { return r; }

  inline Transform *AddTranslate(const glm::vec3 &_add) {
    update = true;
    t += _add;
    return this;
  }

  inline Transform *AddTranslate(const float value) {
    update = true;
    t += value;
    return this;
  }

  inline Transform *AddRotate(const glm::vec3 &_add) {
    update = true;
    r += _add;
    return this;
  }

  inline Transform *AddRotate(const float value) {
    update = true;
    r += value;
    return this;
  }

  inline Transform *AddScale(const glm::vec3 &_add) {
    update = true;
    s += _add;
    return this;
  }

  inline Transform *AddScale(const float value) {
    update = true;
    s += value;
    return this;
  }

  inline Transform *SetTranslate(const glm::vec3 &_t = glm::vec3(1.0f)) {
    update = true;
    t = _t;
    return this;
  }

  inline Transform *SetScale(const glm::vec3 &_s = glm::vec3(1.0f)) {
    update = true;
    s = _s;
    return this;
  }

  inline Transform *SetRotate(const glm::vec3 &_r = glm::vec3(1.0f)) {
    update = true;
    r = _r;
    return this;
  }
};
