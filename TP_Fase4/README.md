# Fase 4 — Normais, Texturas e Iluminação

Quarta e última fase do projeto de **Computação Gráfica**, com o objetivo de obter uma representação dinâmica e mais realista das cenas, através da adição de normais, coordenadas de textura e iluminação — culminando numa recriação animada do Sistema Solar.

## Descrição

Esta fase estende o motor gráfico das fases anteriores em duas frentes:

- **generator** — cada primitiva (`plane`, `box`, `cone`, `sphere`, `ring`, `patch`) passa a calcular, além dos pontos, o **vetor normal** e as **coordenadas de textura** de cada vértice, escrevendo os três conjuntos de valores no ficheiro `.3d`;
- **engine** — passa a suportar **iluminação** (point, directional e spot), **materiais** por modelo (componentes difusa, ambiente, especular, emissiva e shininess) e **texturas 2D** (via DevIL), lidas e associadas aos modelos através dos novos buffers de normais e coordenadas de textura.

## Tecnologias

- **C++**
- **OpenGL / GLUT / GLEW** — renderização, VBOs e iluminação
- **DevIL** — carregamento de texturas
- **CMake**
- **tinyxml2**

## Novidades face à Fase 3

- **Ficheiro `.3d` com 3 blocos por vértice** — ponto, normal e coordenada de textura, em vez de apenas o ponto
- **Normais por primitiva** — calculadas de forma analítica para cada tipo de geometria: planos e ring com normal constante, cone com base + faces laterais (trigonometria + semelhança de triângulos), esfera como vetor normalizado centro→superfície, e superfícies de Bézier a partir do produto externo dos vetores tangentes ∂P/∂u e ∂P/∂v
- **Coordenadas de textura por primitiva** — mapeamento UV específico para cada geometria (ex.: ponto médio + raio para a base do cone, divisão altura/stacks e largura/slices na esfera, `(1-v, 1-u)` nas superfícies de Bézier)
- **Estruturas `Light`, `Color`, `ModelInfo` e `ModelSettings`** — novas structs em `config.h` para guardar luzes, materiais e os dados (vértices/normais/texCoords) de cada modelo
- **Iluminação em OpenGL** — `glEnable(GL_LIGHTING)` / `glEnable(GL_LIGHTi)`, posicionamento e orientação das luzes via `glLightfv`/`glLightf` (`GL_POSITION`, `GL_SPOT_DIRECTION`, `GL_SPOT_CUTOFF`, `GL_SPOT_EXPONENT`)
- **Materiais e texturas em OpenGL** — `glMaterialfv`/`glMaterialf` para as componentes de cor de cada modelo; buffers extra (`nBuffers`, `texBuffers`) e um array de `texIDs` para bind das texturas por modelo em `drawModelsVBO`
- **Cena completa do Sistema Solar** — Sol, planetas (com anel de Saturno) e respetivas órbitas/rotações animadas, com texturas e materiais realistas para cada corpo celeste

## Funcionalidades

- Tudo o que já existia nas fases anteriores (primitivas, hierarquia de grupos, câmaras Explorer/FPS, curvas de Catmull-Rom, superfícies de Bézier, VBOs)
- Geração de normais e coordenadas de textura para todas as primitivas
- Iluminação point, directional e spotlight, configurável via XML
- Materiais (diffuse, ambient, specular, emissive, shininess) por modelo
- Aplicação de texturas 2D aos modelos
- Cena de demonstração do Sistema Solar completo, texturado e animado

O relatório completo desta fase contém a explicação detalhada do cálculo de normais e coordenadas de textura para cada primitiva, da implementação da iluminação e das texturas no engine, e as capturas de ecrã de todos os testes.
