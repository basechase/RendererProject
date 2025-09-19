#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace aie
{
    

    
    struct Shader 
    {
        GLuint Program;
    };
    
    struct Vertex
    {
        glm::vec4 Pos;
        glm::vec4 Color;
    };

    struct Geometry
    {
        GLuint Vao = 0, Vbo = 0, Ibo = 0;
        GLuint Size = 0;
    };

   
    void Draw(const Shader& shad, const Geometry& geo);
    void FreeShader(Shader& shad);
    Shader MakeShader(const char* vertSource, const char* fragsource);
    Geometry MakeGeometry(const Vertex* const Verts, GLsizei VertCount, const GLuint* const Indicies, GLsizei IndexCount);
    void FreeGeometry(Geometry& Geo);

   
}