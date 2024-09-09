## 1. O que é a GLSL? Quais os dois tipos de shaders são obrigatórios no pipeline programável da versão atual que trabalhamos em aula e o que eles processam?

A **GLSL** (OpenGL Shading Language) é a linguagem de programação usada para escrever shaders no OpenGL. Shaders são pequenos programas que rodam diretamente na GPU e que determinam como as informações gráficas, como vértices e pixels, serão processadas e exibidas.

Os dois tipos de shaders obrigatórios no pipeline programável da versão atual (OpenGL 3.3 core e superiores) são:

- **Vertex Shader**: Processa os **vértices** de um objeto. Ele transforma a posição de cada vértice e pode passar dados como cores e texturas para os próximos estágios do pipeline. Cada vértice processado gera uma saída para a próxima etapa.

- **Fragment Shader**: Processa os **fragmentos** (basicamente os "pixels" antes de serem finalizados) e define a cor final de cada pixel da cena. Ele pode misturar cores, aplicar iluminação, e combinar informações de textura para determinar o aspecto final do pixel.

---

## 2. O que são primitivas gráficas? Como fazemos o armazenamento dos vértices na OpenGL?

As **primitivas gráficas** são as formas geométricas básicas que a OpenGL usa para construir imagens mais complexas. Exemplos de primitivas são:

- **Pontos (Points)**
- **Linhas (Lines)**
- **Triângulos (Triangles)**

Na OpenGL, o armazenamento dos vértices ocorre dentro de buffers especiais chamados de **Vertex Buffer Objects (VBOs)**. Os vértices são armazenados em arrays de dados, que contêm as coordenadas dos vértices e, possivelmente, outras informações como cores e normais.

Esses dados são carregados da CPU para a memória da GPU através dos **VBOs**, permitindo que o processamento seja feito de maneira mais eficiente e acelerada.

---

## 3. Explique o que é VBO, VAO e EBO, e como se relacionam

### VBO (Vertex Buffer Object):

O **VBO** é um buffer que armazena os dados dos vértices, como posições, cores, coordenadas de textura, etc. Ele envia esses dados da CPU para a memória da GPU, onde serão processados. O VBO permite que o armazenamento e a manipulação dos vértices sejam feitos de forma eficiente pela GPU.

### VAO (Vertex Array Object):

O **VAO** armazena as configurações de como os vértices do VBO devem ser processados pela GPU. Ele mantém o estado de quais atributos (como posições ou cores) estão associados a cada vértice e como eles devem ser interpretados (por exemplo, quantos componentes por vértice, qual é o tipo de dado, etc.). Toda vez que queremos desenhar algo, basta **vincular (bind)** o VAO, e ele carregará as configurações corretas para os shaders.

### EBO (Element Buffer Object):

O **EBO** é um buffer que armazena **índices** para os vértices. Ele permite referenciar múltiplos vértices repetidos sem a necessidade de duplicar os dados no VBO. Isso é útil, por exemplo, ao desenhar triângulos com vértices compartilhados. Com o EBO, você pode usar índices para dizer à OpenGL como reutilizar vértices já definidos, otimizando o uso da memória.

### Relação entre VBO, VAO e EBO:

- **VBO** armazena os dados brutos dos vértices.
- **VAO** organiza e define como esses dados serão usados nos shaders.
- **EBO** permite otimizar o uso dos vértices por meio do uso de índices.

### Gráfico de Relacionamento:

```plaintext
 CPU                          GPU
 +-----------+          +------------------+
 |           |          |                  |
 |           |          |   VAO            |
 |           |          |  +--------------+|
 |           |          |  |              ||
 |   VBO     | -------->|  |  Configura   ||
 |  (Vértices)          |  |  atributos   ||
 |           |          |  |  dos VBOs    ||
 |           |          |  +--------------+|
 |           |          |                  |
 |           |          |   EBO            |
 |           | -------->|  +--------------+|
 |           |          |  |  Índices dos ||
 +-----------+          |  |  vértices    ||
                        |  +--------------+|
                        |                  |
                        +------------------+
```

- O VBO contém os dados dos vértices que são enviados para a GPU.
- O VAO vincula os atributos dos vértices e define como serão processados.
- O EBO contém os índices que definem como os vértices serão reutilizados.
  Agora, a OpenGL pode processar eficientemente os dados e desenhar a cena.
