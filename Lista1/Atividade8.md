## a. Configuração dos buffers (VBO, VAO e EBO)

### 1. Vértices e Cores:

- **P1**: (0.0, 0.6) com cor vermelho (1.0, 0.0, 0.0)
- **P2**: (-0.6, -0.5) com cor verde (0.0, 1.0, 0.0)
- **P3**: (0.6, -0.3) com cor azul (0.0, 0.0, 1.0)

### 2. Vertex Buffer Object (VBO):

O **VBO** conterá tanto os dados de posição dos vértices quanto suas respectivas cores.

```cpp
float vertices[] = {
    // Posição          // Cor
     0.0f,  0.6f,       1.0f, 0.0f, 0.0f,   // P1 (vermelho)
    -0.6f, -0.5f,       0.0f, 1.0f, 0.0f,   // P2 (verde)
     0.6f, -0.3f,       0.0f, 0.0f, 1.0f    // P3 (azul)
};
```

### 3. Vertex Array Object (VAO):

- O **VAO** armazenará as configurações de estado associadas aos atributos de vértice, como a ligação do VBO e o mapeamento dos atributos de posição e cor.
- No **VAO**, configuramos os atributos com glVertexAttribPointer para indicar como interpretar os dados no VBO:

```cpp
glBindVertexArray(VAO);

// Configurar o VBO
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// Atributo da posição (2 floats: x, y)
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// Atributo da cor (3 floats: r, g, b)
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
glEnableVertexAttribArray(1);
```

### 4. Element Buffer Object (EBO) (opcional, mas recomendado para reutilização de vértices):

O EBO pode ser usado para definir a ordem dos vértices e desenhar o triângulo. Nesse caso, a ordem dos índices seria:

```cpp
unsigned int indices[] = {
    0, 1, 2 // Índices dos vértices P1, P2, P3
};

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```

## b. Identificação dos atributos no Vertex Shader:

No vertex shader, você precisa declarar e utilizar dois atributos de entrada: um para a posição do vértice e outro para a cor. Esses atributos são identificados pelas localizações usadas em `glVertexAttribPointer`, que nesse caso foram 0 para a posição e 1 para a cor.

Um exemplo de vertex shader poderia ser assim:

```cpp
#version 330 core
layout (location = 0) in vec2 aPos;   // Posição do vértice
layout (location = 1) in vec3 aColor; // Cor do vértice

out vec3 vertexColor; // Passa a cor para o fragment shader

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0); // Transforma a posição para 4D
    vertexColor = aColor;               // Atribui a cor à variável de saída
}
```

Nesse vertex shader:

- `aPos` (posição) está ligado ao location 0, onde configuramos os dois primeiros floats (x e y).
- `aColor` (cor) está ligado ao location 1, onde configuramos os três floats (r, g, b).

## Resumo:

- **VBO** contém dados de posição e cor.
- **VAO** armazena as configurações para os atributos de posição e cor.
- No vertex shader, os atributos são identificados pelas localizações especificadas `(layout(location = 0)` para posição e layout `(location = 1)` para cor.
