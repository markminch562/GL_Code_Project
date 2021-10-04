#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <bitset>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../LoadSystems/ShaderSystem.h"
#include "../LoadSystems/Shader.h"
#include "InputSystem/include/View.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <thread>
namespace uniform = ShaderSystems::UniformContext;

struct InputStorage
{
    //this should hold a vector of callables

};
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{

    glm::vec3* position = static_cast<glm::vec3*>(glfwGetWindowUserPointer(window));
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    glm::vec3* position = static_cast<glm::vec3*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_A )
        position->x += -0.2;
    if(key == GLFW_KEY_D )
        position->x += 0.2;
    if (key == GLFW_KEY_S )
        position->y += -0.2;
    if(key == GLFW_KEY_W )
        position->y += 0.2;
    if(key == GLFW_KEY_UP)
        position->z += 0.2f;
    if(key == GLFW_KEY_DOWN)
        position->z += -0.2f;
}
glm::mat4 getUserData(GLFWwindow* window)
{
    glm::vec3* position = static_cast<glm::vec3*>(glfwGetWindowUserPointer(window));
    glm::vec3 cameraPosition = *position + glm::vec3(0.0f, 0.0f, -3.0f);
    glm::mat4 view(1.0f);
    return glm::translate(view,cameraPosition);
}




int main() {

    auto path = std::filesystem::current_path();
    std::cout<<path<<std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(640, 480, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    auto Program = ShaderSystems::CreateShader("../../ShaderFiles/Basic.glsl");
   // std::cout<<Program.getData(GL_FRAGMENT_SHADER)<<std::endl;
    ShaderSystems::CompileProgram(Program);
    unsigned int ShaderID = Program.getShaderID();

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
    };
    float normals[]
    {
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            0.0f,  0.0f, 1.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f
    };

    unsigned int vbo, vao, ebo;
    glm::vec3 position(0.0f, 0.0f, 0.0f);
    glfwSetWindowUserPointer(window,&position);
    glfwSetKeyCallback(window, key_callback);
    glGenBuffers(1, &vbo);
    glGenBuffers(1,&ebo);

    glGenVertexArrays(1, &vao);
    //you bind the vao so that it can be associated with the vbo later
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices)+sizeof(normals), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), &normals);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(vertices)));
    glEnableVertexAttribArray(1);





    //glBindBuffer clears out the the current setting when set to 0 if we wanted to adjust it again we
    //could use glBindBuffer(vbo) again
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glm::mat4 projection = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view = glm::mat4(1.0f);
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);

    std::vector<glm::mat4> models(16, glm::mat4(1.0f));
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model    = glm::mat4(1.0f);
        glm::mat4 view2 = glm::mat4(1.0);
        //model is the object so we only translate and rotate it
        model = glm::rotate(model, (float)glfwGetTime()/2, glm::vec3(0.5f, 1.0f, 0.0f));
        int indexPosition = 0;
        for(int i = 0; i <4; i++){
            for(int j = 0; j<4; j++)
            {
                float xOff = i*1.1f;
                float yOff = j*1.1f;
                models[indexPosition] = glm::translate(model, glm::vec3(xOff, yOff, 0.0f));
                indexPosition++;
            }
        }
        glUseProgram(ShaderID);

        uniform::setMat4(ShaderID, "projection", projection);
        uniform::setMat4(ShaderID, "view", getUserData(window));
        for(auto& iter : models) {

            uniform::setMat4(ShaderID, "model", iter);
            // draw our first triangle
            glBindVertexArray(vbo); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES,0, 36);
        }
        // glBindVertexArray(0); // no need to unbind it every time

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &vbo);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(ShaderID);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();


    return 0;
}

