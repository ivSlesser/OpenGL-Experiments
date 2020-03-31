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


#include "PCHeader.h"
#include "QuadModule.h"

#include "../Graphics/Quad.h"
#include "../Graphics/Triangle.h"

void QuadModule::OnInit() {
  std::vector<Vertex> vertices = Quad::Vertices();
  VAO.Bind();
  VBO.Init(vertices);
  VAO.SetLayout();

  std::vector<unsigned> indices = Quad::Indices();
  IBO.Init(indices);

}

void QuadModule::OnUpdate(double dt) {
  VAO.Bind();
  IBO.Bind();
  glDrawElements(GL_TRIANGLES, Quad::IndexCount(), GL_UNSIGNED_INT, 0);
}
