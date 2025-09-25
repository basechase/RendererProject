#include "Context.h"
#include "Renderer.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
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
      { { -.5f, -.5f, 0, 1 } }, // bottom left
      { { .5f, -.5f, 0, 1 } },  // bottom right
      { { 0,  .5f, 0, 1 } }     // top middle
    };

    unsigned int triIndices[] = { 0, 1, 2 };

    Geometry basicTriangleGeo = MakeGeometry(triVerts, 3, triIndices, 3);


    Shader BasicShadFromFile = LoadShader("res/shad/basicVert.vert", "res/shad/basicFrag.frag");
    Shader CameraShader = LoadShader("res/shad/basicCamera.vert", "res/shad/basicFrag.frag");

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
        SetUniform(CameraShader, 0, Camera_Proj);
       SetUniform(CameraShader, 1, Camera_View);
        SetUniform(CameraShader, 2, Triangle_Model);

        
        Draw(CameraShader, basicTriangleGeo);

    }
    FreeGeometry(basicTriangleGeo);
    FreeShader(BasicShadFromFile);


    Window.Term();
    return 0;
}