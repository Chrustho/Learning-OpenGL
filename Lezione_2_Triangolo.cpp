#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



int run_Triangolo()
{

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 800, "Triangolo", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);


	gladLoadGL();


	glViewport(0, 0, 800, 800);


	// Equivalente in GL di unsigned int
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Diamo il riferimento al codice dello shader scritto primo
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Bisogna compilare il Vertex Shader per farlo eseguire dalla GPU
	glCompileShader(vertexShader);

	// Bisogna ripetere la stessa identica cosa per il Fragment Shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);



	// Creiamo uno "shaderProgram" per la gestione dei vari shader
	GLuint shaderProgram = glCreateProgram();


	// Diamo allo shaderProgram i due shader creati
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Linkiamo tutti gli shader al programma
	glLinkProgram(shaderProgram);

	// Li possiamo eliminare perchè ormai sono linkati al programma
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// Coordinate dei vertici
	// OpenGL tratta vertici normalizzati con coordinate tra -1 e 1
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f 
	};

	// Inviare dati tra CPU e GPU è lento e costoso, e spesso conviene farlo tramite 
	// dei grandi buffer (diversi da Front e Back buffer)

	GLuint VAO, VBO;
	// VBO -> Buffer effettivo di vertici
	// VAO -> Puntatori a uno o più VBOs

	// Generiamo i buffer specificando che si tratta di buffer 
	// con un solo elemento all'interno
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	// Il binding rende l'oggetto passato l'oggetto "corrente"
	glBindVertexArray(VAO);

	// Binding di VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Introdcuiamo i vertici nel VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Stream -> vertici modificati una volta ed usati qualche volta
	// Static -> vertici modificati una volta ed usati molte volte
	// Dynamic -> vertici modificati moltte volte ed usati molte volte



	// Configuriamo il VAO così openGL saprà come 
	// posizione, numero valori, tipo, (serve per gli interi), stride, offset per inizio dei vertici
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Ora OpenGL saprà come usarlo, 0 per la posizione del Vertex Attribute
	glEnableVertexAttribArray(0);

	// Bind VBA e VBO su 0, è importante che l'ordine delle funzioni sia corretto
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Usiamo il programma compilato prima
		glUseProgram(shaderProgram);

		// Binding di VAO
		glBindVertexArray(VAO);

		// Creiamo il triangolo con le primitive di OpenGL
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap dei buffer per aggiornamento immagine
		glfwSwapBuffers(window);

		glfwPollEvents();
	}



	// Eliminiamo oggetti creati
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}