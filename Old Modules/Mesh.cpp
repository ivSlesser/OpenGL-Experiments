//// MIT License
////
//// Copyright (c) 2020 Ian Vincent Slesser
////
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files(the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions :
////
//// The above copyright notice and this permission notice shall be included in all
//// copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//// SOFTWARE.
//
//
//#include "Mesh.h"
//
//bool Mesh::Load(const std::vector<Vertex> &pVertices, const std::vector<unsigned int> &pIndices, const Material &pMaterial) {
//
//  // Create vertex buffer
//  VertexCount = pVertices.size();
//  VAO.Bind();
//  VBO.Init(pVertices);
//  VAO.SetLayout();
//
//  // Create index buffer
//  IndexCount = pIndices.size();
//  IBO.Init(pIndices);
//
//  iMaterial = pMaterial;
//
//  return true;
//}
//
//bool Mesh::LoadInstanced(const std::vector<Vertex> &pVertices,
//                         const std::vector<unsigned int> &pIndices,
//                         const std::vector<glm::mat4> &pMatrices,
//                         const Material &pMaterial) {
//
//  auto res = Load(pVertices, pIndices, pMaterial);
//
//  if (!res) {
//    return false;
//  }
//
//  VAO.AttachInstancedMatrixBuffer(pMatrices);
//
//  return true;
//}
