#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

static const unsigned int SCR_WIDTH = 800;
static const unsigned int SCR_HEIGHT = 600;

int run_primaFinestra()
{
    // Inizializzazione glfw
    glfwInit();

    // Specifica della versione di OpenGL utilizzata
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Specifica del tipo di profilo, in questo caso "Core"
    // perchè non ci interessa la compatibilità con versioni precedenti
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creazione di una GLFWwindow di 800 x 600 pixel, con specifica del nome
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    
    // Controllo di eventuali
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

int run_Finestra_Colorata() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 800, 800);

    glClearColor(0.50f, 0.50f, 0.50f, 0.50f);

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    float time = float(glfwGetTime());
    float rot = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // Aggiungere glfwSwapBuffers nel ciclo while genera un flickering dei colori della finestra
        //glfwSwapBuffers(window);
        
        float curr_t = float(glfwGetTime());

        if (curr_t - time > 0.1f )
        {
            rot += curr_t - time;
            time = curr_t;
        }

        glClearColor(float(sin(rot))*0.7, float(cos(rot))*0.7, float(tan(rot))*0.7, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}