A configuração `mat4 projection = ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);` define uma matriz de projeção ortográfica usando a função `ortho` da biblioteca GLM. Esta matriz define um volume de visualização ortográfico 2D onde:

- O limite esquerdo está em 0.0f.
- O limite direito está em 800.0f.
- O limite inferior está em 600.0f.
- O limite superior está em 0.0f.
- O plano de recorte próximo está em -1.0f.
- O plano de recorte distante está em 1.0f.

#### Desenhando Objetos na Tela

Quando você desenha objetos usando esta matriz de projeção, suas coordenadas são mapeadas diretamente para coordenadas na tela:

A origem (0, 0) está no canto superior esquerdo da tela.
O ponto (800, 600) está no canto inferior direito da tela.

#### Posicionando Objetos

Dada esta configuração, posicionar objetos dentro do intervalo (0, 0) a (800, 600) os colocará na área visível da tela. Por exemplo:

- Um objeto em (400, 300) será posicionado no centro da tela.
- Um objeto em (0, 0) será posicionado no canto superior esquerdo.
- Um objeto em (800, 600) será posicionado no canto inferior direito.

#### Utilidade Dessa Configuração

Esta projeção ortográfica é particularmente útil para renderização 2D, como em:

- Interfaces de Usuário (UI): Permite colocar elementos da interface diretamente usando coordenadas de pixel.
- Jogos 2D: Simplifica o processo de posicionamento de sprites e outros elementos 2D.
- Aplicações Gráficas: Oferece uma maneira direta de mapear coordenadas da aplicação para coordenadas na tela sem distorção de perspectiva.

Usando esta configuração, você pode controlar facilmente o layout e o posicionamento de objetos na tela de maneira previsível, tornando-a ideal para aplicações onde é necessário uma visão 2D.
