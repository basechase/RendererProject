#include "Context.h"
#include "Renderer.h"
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

using namespace aie;

    
    const char* BasicCameraVert =
        "#version 430 core\n"
        "layout (location = 0) uniform mat4 proj;\n"
        "layout (location = 1) uniform mat4 view;\n"
        "layout (location = 2) uniform mat4 model;";

    
    


int main()
{
    
    

    Context Window;
    Window.Init(640, 480, "Hello Window");
    
    Vertex triVerts[] =
    {
      { { -.5f, -.5f, 0, 1  }, {0.0f, 0.0f} },               // bottom left
      { { .5f, -.5f, 0, 1  },  {1.0f, 0.0f}} ,             // bottom right
      { { 0,  .5f, 0, 1 } ,     { 0.5f, 1.0f } },               // top middle
    };

    unsigned int triIndices[] = { 0, 1, 2 };

    Geometry basicTriangleGeo = MakeGeometry(triVerts, 3, triIndices, 3);


    Shader BasicShadFromFile = LoadShader("res/shad/basicVert.vert", "res/shad/basicFrag.frag");
    Shader CameraShader = LoadShader("res/shad/basicCamera.vert", "res/shad/basicFrag.frag");
    Shader TexShad = LoadShader("res/shad/basicCamera.vert", "res/shad/Text.frag");
    
    //Shader basicShad = MakeShader(basicVert, basicFrag);
    glm::mat4 Triangle_Model = glm::identity<glm::mat4>();
    
   glm::mat4 Camera_Proj = glm::perspective(
   //projetion matrix - transforms view space into clip space(that -1 to +1 zone)
       glm::radians(45.0f), //fov
       640.0f/480.0f, //aspect ratio
       0.10f, //near-plane
       1000.0f //far plane
   );


    // view matrix- makes things relative to camera - puts camera at center of the world
   glm::mat4 Camera_View = glm::lookAt
        (glm::vec3(0, 1, 20),
        glm::vec3(0, 5, 0),
        glm::vec3(0, 1, 0));




    //model matrix - this is the object- will transform object into world space


     //SetUniform(BasicShadFromFile, 4, 3.0f);

    while (!Window.ShouldClose())
    {
        
        Window.Tick();
        Window.Clear();
        //setup my uniforms
        SetUniform(TexShad, 0, Camera_Proj);
       SetUniform(TexShad, 1, Camera_View);
        SetUniform(TexShad, 2, Triangle_Model);
        
        
        Draw(TexShad, basicTriangleGeo);

    }
    FreeGeometry(basicTriangleGeo);
    FreeShader(BasicShadFromFile);


    Window.Term();
    return 0;
}