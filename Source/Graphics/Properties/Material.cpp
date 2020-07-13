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


#include "Material.h"
#include <sstream>

#include "System/GUI/GUILayer.h"

void Material::SubmitAsUniform(Shader &pShader, unsigned int index) {

  std::stringstream str;
  str << "u_Materials[" << index << "]";
  std::string base = str.str();

  pShader.Vec3( (base + ".Ambient").c_str(), Ambient);
  pShader.Vec3( (base + ".Diffuse").c_str(), Diffuse);
  pShader.Vec3( (base + ".Specular").c_str(), Specular);
  pShader.Float( (base + ".Shine").c_str(), Shine);
  pShader.Float( (base + ".Dissolve").c_str(), Dissolve);
}

void Material::DisplayWithGUI() {
  ImGui::ColorEdit3((Name + ".Ambient").c_str(), &Ambient.x);
  ImGui::ColorEdit3((Name + ".Diffuse").c_str(), &Diffuse.x);
  ImGui::ColorEdit3((Name + ".Specular").c_str(), &Specular.x);
  ImGui::DragFloat((Name + ".Shine").c_str(), &Shine, 2.0f, 0.0f, 128.0f);
//  ImGui::DragFloat((Name + ".Dissolve").c_str(), &Dissolve, 0.01f, 0.0f, 1.0f);
}
