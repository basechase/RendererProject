#include "Context.h"
#include "Renderer.h"
#include "glfw/glfw3.h"
#include <GLFW/glfw3.h>

using namespace aie;


    
int main()
{
   
    Context Window;
    Window.Init(640, 480, "Hello Window");
    
    Vertex triVerts[] =
    {
      { { -.5f, -.5f, 0, 1 } },
      { { .5f, -.5f, 0, 1 } },
      { { 0,  .5f, 0, 1 } }
    };

    unsigned int triIndices[] = { 0, 1, 2 };
    Geometry basicTriangleGeo = MakeGeometry(triVerts, 3, triIndices, 3);

    const char* basicVert =
        "#version 430 core\n"
        "layout (location = 0) in vec4 position;\n"
        "void main() { gl_Position = position; }";

    const char* basicFrag =
        "#version 430 core\n"
        "out vec4 vertColor;\n"
        "void main() { vertColor = vec4(1.0, 0.0, 0.0, 1.0); }";

    Shader basicShad = MakeShader(basicVert, basicFrag);

    while (!Window.ShouldClose())
    {
        Window.Tick();
        Window.Clear();
        Draw(basicShad, basicTriangleGeo);

    }



    Window.Term();
    return 0;
}