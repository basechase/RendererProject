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
        glm::vec4 Normals;
        glm::vec2 UVs;

    };

    struct Geometry
    {
        GLuint Vao = 0, Vbo = 0, Ibo = 0;
        GLuint Size = 0;
    };

    struct Texture 
    {
        GLuint Handle; // oppen gl texture name
        unsigned Width, Height, Channels;
    };


    void SetUniform(const Shader& shad, GLuint location, const glm::mat4& value);
    void Draw(const Shader& shad, const Geometry& geo);
    void FreeShader(Shader& shad);
    Shader MakeShader(const char* vertSource, const char* fragsource);
    Shader LoadShader(const char* vertPath, const char* fragpath);
    Geometry MakeGeometry(const Vertex* const Verts, GLsizei VertCount, const GLuint* const Indicies, GLsizei IndexCount);
    void FreeGeometry(Geometry& Geo);

    bool CheckShader(Shader& Shad);
    
    
    //will allow assigning vec3 uniforms in shaders
   
    void SetUniform(const Shader& shad, GLuint location, const glm::vec3& value);
    void SetUniform(const Shader& shad, GLuint location, const float& value);


    //Creates a texutre in opengl 
    //param width thexture width in poixels
    //param channels numbers of channesl (1-r, 2-rg, 3-rbg, 4 -rgba)
    //param pixels pointer to pixel buffer
    //return the texture
    Texture MakeTexture(unsigned Width, unsigned Height, unsigned Channels, const unsigned char* Pixels);
    //frees a texture in opemg;
    //param Tex The texture (to be 0 afrer freed
    Texture LoadTexture(const char* ImagePath);

    void SetUniform(const Shader& Shad, GLuint Location, const Texture& Tex, int TextureSlot);
    // assign a texture to a texture slot then assign that slot number as the unform value
    //shad the shader
    //locatiomn th loc should match whats given in shader source code
    //tex the actual texture object
    //texture slot the slot that will be actually assinged to the shader
    void FreeTexture(Texture& tex);

    Geometry LoadGeometry(const char* filePath);
    
}