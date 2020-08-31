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

#include "Framework/GL/VertexArray.h"
#include "Framework/GL/VertexBuffer.h"
#include "Framework/GL/IndexBuffer.h"

// TODO: Draw Commands. ?
// TODO: Material ID's

struct Mesh {
  std::string Name;               // Name of the mesh, must be unique

  VertexArray VAO;                // Holds vertex layout configuration
  VertexBuffer VBO;               // Holds mesh vertices
  IndexBuffer IBO;                // Holds mesh indices

  uint32_t VertexCount{0};        // Number of vertices it contains
  uint32_t IndexCount{0};         // Number of indices it contains

  /**
   * Create the mesh from vertex and index data.
   *
   * @param pName                   Unique name for the mesh
   * @param pVertices               Input vertex data
   * @param pIndices                Input index data
   */
  void Create(std::string pName, const std::vector<Vertex> &pVertices, const std::vector<uint32_t> &pIndices) {
    Name = pName;
    CreateVertexData(pVertices);

    if (pIndices.size() > 0) {
      IndexCount = pIndices.size();
      IBO.Create(pIndices);
    }
  }

  /**
   * Create a mesh from vertex data, with no indexing of vertices.
   *
   * @param pName                   Unique name for the mesh
   * @param pVertices               Input vertex data
   */
  void Create(std::string pName, const std::vector<Vertex> &pVertices) {
    Name = pName;
    CreateVertexData(pVertices);
  }

  /**
   * Destroy the mesh, clearing data from its components.
   */
  void Destroy() {
    IBO.Destroy();
    VBO.Destroy();
    VAO.Destroy();
  }

  /**
   * Bind the mesh
   */
  void Bind() {
    VAO.Bind();

    if (IndexCount != 0) {
      IBO.Bind();
    }
  }

 private:

  // Used to remove duplicate code from the Create() functions.
  void CreateVertexData(const std::vector<Vertex> &pVertices) {
    VertexCount = pVertices.size();

    VAO.Bind();
    VBO.Create(pVertices);
    VAO.SetLayout();
  }
};