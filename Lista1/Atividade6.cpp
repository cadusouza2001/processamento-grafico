#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
#include <math.h>
// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

struct Geometry
{
	GLuint VAO;
	int numVertices;
};

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// Protótipos das funções
int setupShader();
int setupGeometry();

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

// Código fonte do Vertex Shader (em GLSL): ainda hardcoded
const GLchar *vertexShaderSource = "#version 400\n"
								   "layout (location = 0) in vec3 position;\n"
								   "void main()\n"
								   "{\n"
								   //...pode ter mais linhas de código aqui!
								   "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
								   "}\0";

// Códifo fonte do Fragment Shader (em GLSL): ainda hardcoded
const GLchar *fragmentShaderSource = "#version 400\n"
									 "uniform vec4 inputColor;\n"
									 "out vec4 color;\n"
									 "void main()\n"
									 "{\n"
									 "color = inputColor;\n"
									 "}\n\0";

Geometry setupCircleGeometry()
{
	const int numVertices = 100;
	const float radius = 0.25f;
	const float centerX = -0.5f; // Shifted to the left
	const float centerY = 0.5f;

	std::vector<float> vertices;
	for (int i = 0; i < numVertices; ++i)
	{
		float angle = 2.0f * M_PI * float(i) / float(numVertices);
		float x = radius * cos(angle) + centerX;
		float y = radius * sin(angle) + centerY;
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f); // z-coordinate
	}

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return {VAO, numVertices};
}

Geometry setupOctagonGeometry()
{
	const int numVertices = 8;
	const float radius = 0.25f;
	const float centerX = 0.5f; // Shifted to the right
	const float centerY = 0.5f;

	std::vector<float> vertices;
	for (int i = 0; i < numVertices; ++i)
	{
		float angle = 2.0f * M_PI * float(i) / float(numVertices);
		float x = radius * cos(angle) + centerX;
		float y = radius * sin(angle) + centerY;
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f); // z-coordinate
	}

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return {VAO, numVertices};
}

Geometry setupPacmanGeometry()
{
	const int numVertices = 100;
	const float radius = 0.25f;
	const float centerX = -0.5f;
	const float centerY = -0.5f; // Shifted down

	std::vector<float> vertices;
	vertices.push_back(centerX); // Center of the circle
	vertices.push_back(centerY);
	vertices.push_back(0.0f);

	for (int i = 0; i < numVertices; ++i)
	{
		float angle = 2.0f * M_PI * float(i) / float(numVertices);
		if (angle < M_PI / 4 || angle > 7 * M_PI / 4)
			continue; // Skip the mouth section
		float x = radius * cos(angle) + centerX;
		float y = radius * sin(angle) + centerY;
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f); // z-coordinate
	}

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return {VAO, static_cast<int>(vertices.size() / 3)};
}

Geometry setupPizzaSliceGeometry()
{
	const int numVertices = 50;
	const float radius = 0.25f;
	const float centerX = 0.5f;	 // Shifted to the right
	const float centerY = -0.5f; // Shifted down

	std::vector<float> vertices;
	vertices.push_back(centerX); // Center of the circle
	vertices.push_back(centerY);
	vertices.push_back(0.0f);

	// Circular arc vertices
	for (int i = 0; i <= numVertices; ++i)
	{
		float angle = (-M_PI / 6.0f) + (M_PI / 3.0f) * float(i) / float(numVertices); // -30 to 30 degrees for the slice
		float x = radius * cos(angle) + centerX;
		float y = radius * sin(angle) + centerY;
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f); // z-coordinate
	}

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return {VAO, static_cast<int>(vertices.size() / 3)};
}

Geometry setupStarGeometry()
{
	const int numVertices = 10; // 5 points, each with an inner and outer vertex
	const float outerRadius = 0.25f;
	const float innerRadius = outerRadius * 0.5f; // Inner radius is half of the outer radius
	const float centerX = 0.0f;
	const float centerY = 0.0f;

	std::vector<float> vertices;

	for (int i = 0; i < numVertices; ++i)
	{
		float angle = M_PI / 5.0f * i;							 // 36 degrees for each vertex
		float radius = (i % 2 != 0) ? outerRadius : innerRadius; // Alternate between outer and inner vertices
		float x = radius * cos(angle) + centerX;
		float y = radius * sin(angle) + centerY;
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f); // z-coordinate
	}

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return {VAO, numVertices};
}

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	// Criação da janela GLFW
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Formas Geométricas! -- Carlos", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// Obtendo as informações de versão
	const GLubyte *renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte *version = glGetString(GL_VERSION);	/* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Compilando e buildando o programa de shader
	GLuint shaderID = setupShader();

	// Gerando buffers para a geometria do círculo, do octógono, do Pacman, da pizza slice e da estrela
	Geometry circle = setupCircleGeometry();
	Geometry octagon = setupOctagonGeometry();
	Geometry pacman = setupPacmanGeometry();
	Geometry pizzaSlice = setupPizzaSliceGeometry();
	Geometry star = setupStarGeometry();

	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a variáveis do tipo uniform em GLSL para armazenar esse tipo de info
	// que não está nos buffers
	GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");

	glUseProgram(shaderID);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw filled circle
		glBindVertexArray(circle.VAO);
		glUniform4f(colorLoc, 0.5f, 0.0f, 0.5f, 1.0f); // Purple color for the filled circle
		glDrawArrays(GL_TRIANGLE_FAN, 0, circle.numVertices);

		// Draw octagon outline
		glBindVertexArray(octagon.VAO);
		glUniform4f(colorLoc, 0.0f, 0.5f, 0.5f, 1.0f); // Cyan color for the octagon
		glDrawArrays(GL_LINE_LOOP, 0, octagon.numVertices);

		// Draw Pacman
		glBindVertexArray(pacman.VAO);
		glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f); // Yellow color for the Pacman
		glDrawArrays(GL_TRIANGLE_FAN, 0, pacman.numVertices);

		// Draw pizza slice
		glBindVertexArray(pizzaSlice.VAO);
		glUniform4f(colorLoc, 1.0f, 0.5f, 0.0f, 1.0f); // Orange color for the pizza slice
		glDrawArrays(GL_TRIANGLE_FAN, 0, pizzaSlice.numVertices);

		// Draw star
		glBindVertexArray(star.VAO);
		glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f); // White color for the star
		glDrawArrays(GL_TRIANGLE_FAN, 0, star.numVertices);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &circle.VAO);
	glDeleteVertexArrays(1, &octagon.VAO);
	glDeleteVertexArrays(1, &pacman.VAO);
	glDeleteVertexArrays(1, &pizzaSlice.VAO);
	glDeleteVertexArrays(1, &star.VAO);
	glfwTerminate();
	return 0;
}

// Função de callback de teclado - só pode ter uma instância (deve ser estática se
// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

// Esta função está bastante hardcoded - objetivo é compilar e "buildar" um programa de
//  shader simples e único neste exemplo de código
//  O código fonte do vertex e fragment shader está nos arrays vertexShaderSource e
//  fragmentShader source no iniçio deste arquivo
//  A função retorna o identificador do programa de shader
int setupShader()
{
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Checando erros de compilação (exibição via log no terminal)
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Checando erros de compilação (exibição via log no terminal)
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	// Linkando os shaders e criando o identificador do programa de shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Checando por erros de linkagem
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
				  << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
