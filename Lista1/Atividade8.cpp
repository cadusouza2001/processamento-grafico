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
Geometry setupTriangleGeometry();

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

// Código fonte do Vertex Shader (em GLSL): ainda hardcoded
const GLchar *vertexShaderSource = "#version 400\n"
								   "layout (location = 0) in vec3 position;\n"
								   "layout (location = 1) in vec3 color;\n"
								   "out vec3 fragColor;\n"
								   "void main()\n"
								   "{\n"
								   "gl_Position = vec4(position, 1.0);\n"
								   "fragColor = color;\n"
								   "}\0";

// Código fonte do Fragment Shader (em GLSL): ainda hardcoded
const GLchar *fragmentShaderSource = "#version 400\n"
									 "in vec3 fragColor;\n"
									 "out vec4 color;\n"
									 "uniform bool useSolidColor;\n"
									 "void main()\n"
									 "{\n"
									 "if (useSolidColor)\n"
									 "color = vec4(0.0, 0.0, 1.0, 1.0);\n"
									 "else\n"
									 "color = vec4(fragColor, 1.0);\n"
									 "}\n\0";

Geometry setupTriangleGeometry()
{
	// Vertex data: positions and colors
	float vertices[] = {
		// Positions        // Colors
		0.0f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f,	  // P1: Red
		-0.6f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // P2: Green
		0.6f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f	  // P3: Blue
	};

	GLuint VBO, VAO;
	// Gerar e vincular o Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Gerar e vincular o Vertex Buffer Object (VBO)
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configurar os atributos de posição dos vértices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// Configurar os atributos de cor dos vértices
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Desvincular o VAO
	glBindVertexArray(0);

	return {VAO, 3};
}

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	// Criação da janela GLFW
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Colored Triangle", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros de funções da OpenGL
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

	// Gerando buffers para a geometria do triângulo
	Geometry triangle = setupTriangleGeometry();

	// Usando o programa de shader
	glUseProgram(shaderID);

	// Obter a localização do uniform para useSolidColor
	GLint useSolidColorLocation = glGetUniformLocation(shaderID, "useSolidColor");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Desenhar o contorno do triângulo com cor sólida azul
		glUniform1i(useSolidColorLocation, GL_TRUE);
		glBindVertexArray(triangle.VAO);
		glDrawArrays(GL_LINE_LOOP, 0, triangle.numVertices);

		// Desenhar os vértices com suas respectivas cores e aumentar o tamanho dos pontos
		glUniform1i(useSolidColorLocation, GL_FALSE);
		glPointSize(10.0f);
		glDrawArrays(GL_POINTS, 0, triangle.numVertices);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	// Limpar os recursos
	glDeleteVertexArrays(1, &triangle.VAO);
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
//  fragmentShader source no início deste arquivo
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