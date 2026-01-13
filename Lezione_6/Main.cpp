// texture 1D, 2D e 3D
// Importiamo una immagine

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// Shader -> funzioni che runnano su GPU, hanno Input e Output
// Prima riga -> versione GLSL da usare
// input "aPos", layout aiutra a lettere i dati dei vertici
// al "layout 0" abbiamo un vec3
// il main assegna a gl_Position un vec4, diamo in "output" la gl_Position


// Il Fragment da in output un FragColor

// Se una primitiva ha colori diversi per ogni vertice allora openGL crea
// automaticamente il gradiente


// Vertici
GLfloat vertices[] =
{ //               COORDINATE    /     COLORi           //
	-0.5f, -0.5f , 0.0f,     1.0f, 0.0f,  0.0f,
	 -0.5f, 0.5f , 0.0f,     0.0f, 1.0f, 0.00f,
	 0.5f,  0.5f , 0.0f,     0.0f, 0.0f,  1.0f,
	 0.5f, -0.5f , 0.0f,     1.0f, 1.0f,  1.0f
};

// Indices per ordine vertici
GLuint indices[] =
{
	0, 2, 1,
	0, 3, 2
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Lezione 5", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);



	Shader shaderProgram("default.vert", "default.frag");



	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); // Dobbiamo specificare dove sia l'uniform

	// Dobbiamo caricare l'immagine

	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Pe entrambi gli assi 

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);





	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f); // Otteniamo l'uniform, cambia sulla base del tipo di dato che usciamo
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}