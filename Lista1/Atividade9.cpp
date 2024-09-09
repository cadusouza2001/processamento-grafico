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
Geometry setupRectangleGeometry(float width, float height, float centerX, float centerY);
Geometry setupTriangleGeometry(float base, float height, float centerX, float centerY);

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

// Código fonte do Vertex Shader (em GLSL): ainda hardcoded
const GLchar *vertexShaderSource = "#version 400\n"
								   "layout (location = 0) in vec3 position;\n"
								   "void main()\n"
								   "{\n"
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

Geometry setupRectangleGeometry(float width, float height, float centerX, float centerY)
{
	std::vector<float> vertices = {
		centerX - width / 2, centerY - height / 2, 0.0f,
		centerX + width / 2, centerY - height / 2, 0.0f,
		centerX + width / 2, centerY + height / 2, 0.0f,
		centerX - width / 2, centerY + height / 2, 0.0f};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return {VAO, 4};
}

Geometry setupTriangleGeometry(float base, float height, float centerX, float centerY)
{
	std::vector<float> vertices = {
		centerX, centerY + height / 2, 0.0f,
		centerX - base / 2, centerY - height / 2, 0.0f,
		centerX + base / 2, centerY - height / 2, 0.0f};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return {VAO, 3};
}

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	// Criação da janela GLFW
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Casa! -- Carlos", nullptr, nullptr);
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

	// Gerando buffers para a geometria da casa
	Geometry walls = setupRectangleGeometry(0.5f, 0.5f, 0.0f, -0.25f);
	Geometry roof = setupTriangleGeometry(0.6f, 0.4f, 0.0f, 0.20f);
	Geometry door = setupRectangleGeometry(0.1f, 0.2f, 0.0f, -0.40f);
	Geometry houseWindow = setupRectangleGeometry(0.1f, 0.1f, 0.15f, -0.20f);

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

		// Draw walls
		glBindVertexArray(walls.VAO);
		glUniform4f(colorLoc, 0.5f, 0.35f, 0.05f, 1.0f); // Brown color for the walls
		glDrawArrays(GL_TRIANGLE_FAN, 0, walls.numVertices);

		// Draw roof
		glBindVertexArray(roof.VAO);
		glUniform4f(colorLoc, 0.8f, 0.0f, 0.0f, 1.0f); // Red color for the roof
		glDrawArrays(GL_TRIANGLES, 0, roof.numVertices);

		// Draw door
		glBindVertexArray(door.VAO);
		glUniform4f(colorLoc, 0.3f, 0.15f, 0.05f, 1.0f); // Dark brown color for the door
		glDrawArrays(GL_TRIANGLE_FAN, 0, door.numVertices);

		// Draw window
		glBindVertexArray(houseWindow.VAO);
		glUniform4f(colorLoc, 0.0f, 0.5f, 0.8f, 1.0f); // Blue color for the window
		glDrawArrays(GL_TRIANGLE_FAN, 0, houseWindow.numVertices);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &walls.VAO);
	glDeleteVertexArrays(1, &roof.VAO);
	glDeleteVertexArrays(1, &door.VAO);
	glDeleteVertexArrays(1, &houseWindow.VAO);
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