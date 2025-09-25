#include "Renderer.h"
#include "Utils.h"
#include "glm/ext.hpp"

namespace aie
{
    void SetUniform(const Shader& shad, GLuint location, const glm::mat4& value)
    {

        glProgramUniformMatrix4fv(shad.Program, location, 1, GL_FALSE, glm::value_ptr(value));


    }
    void Draw(const Shader& shad, const Geometry& geo)
    {
        // bind the shader program
        glUseProgram(shad.Program);
        // bind the VAO
        glBindVertexArray(geo.Vao);

        // draw the object
        glDrawElements(GL_TRIANGLES, geo.Size, GL_UNSIGNED_INT, 0);
    }
    void FreeShader(Shader& shad)
    {
        glDeleteProgram(shad.Program);
        shad = {};
    }
    Shader MakeShader(const char* vertSource, const char* fragsource)
    {
        Shader newShad = {};
        newShad.Program = glCreateProgram();

        GLuint vert = glCreateShader(GL_VERTEX_SHADER);
        GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vert, 1, &vertSource, 0);
        glShaderSource(frag, 1, &fragsource, 0);
        glCompileShader(vert);
        glCompileShader(frag);

        // attach shaders
        glAttachShader(newShad.Program, vert);
        glAttachShader(newShad.Program, frag);

        // link shaders
        glLinkProgram(newShad.Program);

        assert(CheckShader(newShad));


        // delete shaders
        glDeleteShader(vert);
        glDeleteShader(frag);

        // return the shader object



        return newShad;
    }
    Shader LoadShader(const char* vertPath, const char* fragpath)
    {
        std::string VertSource = DumpToString(vertPath);
        std::string FragSource = DumpToString(fragpath);

        return MakeShader(VertSource.c_str(), FragSource.c_str());
    }
    Geometry MakeGeometry(const Vertex* const Verts, GLsizei VertCount, const GLuint* const Indicies, GLsizei IndexCount)
    {

        Geometry NewGeo = {};
        NewGeo.Size = IndexCount;

        glGenVertexArrays(1, &NewGeo.Vao);
        glGenBuffers(1, &NewGeo.Vbo);
        glGenBuffers(1, &NewGeo.Ibo);

        glBindVertexArray(NewGeo.Vao);
        glBindBuffer(GL_ARRAY_BUFFER, NewGeo.Vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NewGeo.Ibo);

        glBufferData(GL_ARRAY_BUFFER, VertCount * sizeof(Vertex), Verts, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount * sizeof(GLuint), Indicies, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return NewGeo;
    }

    void FreeGeometry(Geometry& Geo)
    {
        glDeleteBuffers(1, &Geo.Vbo);
        glDeleteBuffers(1, &Geo.Ibo);
        glDeleteVertexArrays(1, &Geo.Vao);

        Geo = {};
    }

    bool CheckShader(Shader& Shad)
    {
        GLint status = GL_FALSE;
        glGetProgramiv(Shad.Program, GL_LINK_STATUS, &status);
        if (status != GL_TRUE)
        {
            GLint logLength = 0;
            glGetProgramiv(Shad.Program, GL_INFO_LOG_LENGTH, &logLength);
            GLchar* log = new GLchar[logLength];
            glGetProgramInfoLog(Shad.Program, logLength, 0, log);

            fprintf(stderr, "%s\n", log);

            delete[] log;

        }

        return status == GL_TRUE;
    }

}