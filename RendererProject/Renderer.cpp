#include "Renderer.h"
#include "Utils.h"
#include "glm/ext.hpp"
#define STB_IMAGE_IMPLEMENTATION 1
#include <stb_image.h>

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
        //position location 0
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        //uvs location 1
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);





        //unbind buffers to prevent accidental modification
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

    void SetUniform(const Shader& shad, GLuint location, const glm::vec3& value)
    {
        glProgramUniform3fv(shad.Program, location, 1, glm::value_ptr(value));
    }

    void SetUniform(const Shader& shad, GLuint location, const float& value)
    {
        glProgramUniform1fv(shad.Program, location, 1, &value);
    }

    Texture MakeTexture(unsigned Width, unsigned Height, unsigned Channels, const unsigned char* Pixels)
    {
        //create reuturn object
        //setup encoding so opengl understands
        //create a texture obbject in opengl and bind it
        // buffer in the texture data
        //describe the data
        //return 

        Texture RetVal = { 0, Width, Height, Channels };
        GLenum OGLFormat = GL_RED;
        switch (Channels)
        {

            case 1:
                OGLFormat = GL_RED; //monochrome
                break;
            case 2:
                OGLFormat = GL_RG; 
                break;
            case 3:
                OGLFormat = GL_RGB; //color or data
                break;
            case 4:
                OGLFormat = GL_RGBA; //color or data that needs a fourth channel
                break;
            default:
                assert(false && "Unknown channel configuration");
        }
        glGenTextures(1, &RetVal.Handle);
        glBindTexture(GL_TEXTURE_2D, RetVal.Handle);

        glTexImage2D(GL_TEXTURE_2D,
            0,
            OGLFormat,
            Width,
            Height,
            0,
            OGLFormat,
            GL_UNSIGNED_BYTE,
            Pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        return RetVal;


       
    }

    Texture LoadTexture(const char* ImagePath)
    {
        //create variables to be filled in by stb
        int ImageWidth = 0;
        int ImageHeight = 0;
        int ImageFormat = 0;
        

        unsigned char* RawPixelData = nullptr;

        //create reutnr value
        Texture RetVal = {};
        


        //do da load load the texture

        stbi_set_flip_vertically_on_load(true);
        RawPixelData = stbi_load(ImagePath,
            &ImageWidth,
            &ImageHeight,
            &ImageFormat,
            STBI_default);

        assert(RawPixelData != nullptr && " FAILED LAODING IMAGE DID BAD!!");

        RetVal = MakeTexture(ImageWidth, ImageHeight, ImageFormat, RawPixelData);
        stbi_image_free(RawPixelData);

        return RetVal;

        //return texture

    }

    void SetUniform(const Shader& Shad, GLuint Location, const Texture& Tex, int TextureSlot)
    {
        //specifiy the texure slot we want to activate
        //bind the texture to that slo
        
        
        
        glActiveTexture(GL_TEXTURE0 + TextureSlot);
        glBindTexture(GL_TEXTURE_2D, Tex.Handle);

        // specify that texture slot as the value for that uniform
        glProgramUniform1i(Shad.Program, Location, TextureSlot);
    }

    void FreeTexture(Texture& tex)
    {
        glDeleteTextures(1, &tex.Handle);
        tex = {};
    }

}