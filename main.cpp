#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

const char *vertexShaderCode = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "}\0";

const char *fragmentShaderCode = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main(void) {

    // Start GLFW and create a window to be used
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    // If we failed to create a window, then return
    if (window == NULL) {
        std::cout << "Failed to create a valid GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the current window the context
    // Which essentially assigns the window the underlying main thread
    glfwMakeContextCurrent(window);

    // Load the GLAD file
    // This produces bindings for OpenGL as the function pointers can be quite verbose
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Generate a viewport which is the same size of our window
    glViewport(0, 0, 800, 600);
    // Create a framebuffer resize callback for re-adjusting the viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ============================================================    
    // Generate one vertex buffer, and assign it's name to VBO
    // The name is just an integer that is yet to be used
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    // Actually generates the buffer to fill with values
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy the vertex data into the data buffer
    // GL_STATIC_DRAW is chosen as the triangle vertex shouldn't really change
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // ============================================================   

    // VERTEX SHADER
    // ============================================================
    // Set the name of the vertexShader by create a shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Pass the source code to the shader and attempt compilation
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    // Verify that it actually compiled
    int successVertex;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);

    // If we failed, print the compilation error message and terminate
    if (!successVertex) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation error: " << infoLog << std::endl;
        glfwTerminate();
        return -1;
    } 
    // ============================================================    

    // FRAGMENT SHADER
    // ============================================================    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    int successFragment;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);
    if (!successFragment) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment shader compilation error: " << infoLog << std::endl;
        glfwTerminate();
        return -1;
    }
    // ============================================================

    // Continue to display the windows until we've reached a stop position
    while (!glfwWindowShouldClose(window)) {

        // Process input from keyboard
        process_input(window);

        // Set the colour that the clear window should show
        glClearColor(.2f, .3f, .3f, 1.0f);
        // Using the colour buffer bit, we tell gl to clear the colour buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Swaps the two buffers, which is essential to a none-flickering screen
        // Generally, you should one buffer whilst you paint another
        // which will swapped in
        glfwSwapBuffers(window);
        // Check for new events from the event queue, which are generated by possible callbacks
        // This would for example check for resize events via the framebuffer callback
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Framebuffer call back, which just updates the viewport to the what the next size
// of the window is
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Checks for use input and updates accordingly
void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}