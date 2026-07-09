# Fase 1 — Primitivas Gráficas

Primeira fase do projeto de **Computação Gráfica**, focada na construção de um mini motor gráfico 3D capaz de gerar e desenhar primitivas geométricas.

## Descrição

Esta fase é composta por duas aplicações:

- **generator** — calcula os vértices dos triângulos que compõem cada primitiva gráfica (plano, caixa, cone e esfera) e guarda-os num ficheiro `.3d`;
- **engine** — interpreta um ficheiro de configuração em XML (câmara, janela e modelos a carregar) e desenha as primitivas correspondentes em OpenGL.

Os ficheiros `.3d` gerados pelo `generator` são posteriormente lidos pelo `engine`, que os interpreta como listas de triângulos (cada 3 vértices consecutivos formam um triângulo).

## Tecnologias

- **C++**
- **OpenGL / GLUT** — renderização 3D e gestão de janela/input
- **CMake** — build system
- **tinyxml2** — parsing dos ficheiros de configuração XML

## Arquitetura

- **generator/** — cálculo geométrico das primitivas e escrita dos ficheiros `.3d`
- **engine/** — leitura da configuração XML, carregamento dos modelos e ciclo de renderização OpenGL
- **engine/config/** — estrutura `Config` e parsing do XML para memória
- **engine/tinyxml2/** — biblioteca de terceiros usada para parsing de XML

## Funcionalidades

- Geração de 4 primitivas gráficas via linha de comandos: **plano**, **caixa**, **cone** e **esfera**
- Leitura de ficheiro de configuração XML com definição de janela, câmara (posição, lookAt, up, projeção) e modelos a carregar
- Câmara orbital: desloca-se na superfície de uma esfera em torno da origem, sempre orientada para o centro
- Alternância entre modos de desenho **FILL**, **LINE** e **POINT** através de menu (botão direito do rato)
- Alteração da cor das primitivas em tempo real (teclas `0`–`7`)
- Controlo da câmara com as setas do teclado (rotação) e teclas `W`/`S` (aproximar/afastar)

## Estrutura do Projeto

```
fase1/
├── engine/
│   ├── engine.cpp        # Ciclo principal de renderização (OpenGL/GLUT)
│   ├── config/            # Estrutura Config e parsing do XML
│   │   ├── config.cpp
│   │   └── config.h
│   └── tinyxml2/          # Biblioteca de terceiros para parsing XML
│       ├── tinyxml2.cpp
│       └── tinyxml2.h
├── generator/
│   ├── generator.cpp      # Interpretação dos argumentos de linha de comandos
│   ├── primitives.cpp     # Cálculo dos vértices de cada primitiva
│   └── primitives.h
├── tests/                  # Ficheiros de configuração XML de exemplo
│   └── test_1_1.xml ... test_1_7.xml
├── scripts/
│   └── primitives_script.sh   # Script auxiliar para gerar todas as primitivas de teste
├── docs/
│   └── CG_TP_Fase1_Grupo12.pdf   # Relatório entregue nesta fase
└── CMakeLists.txt
```

## Como Executar

### Pré-requisitos

- Compilador C++ compatível com C++11 ou superior
- CMake ≥ 3.5
- OpenGL e GLUT instalados no sistema
  - Linux (Debian/Ubuntu): `sudo apt install freeglut3-dev`
  - macOS: GLUT já incluído via framework do sistema
  - Windows: necessário indicar a variável `TOOLKITS_FOLDER` com o GLUT (ver `CMakeLists.txt`)

### Compilar

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Isto gera dois executáveis: `generator` e `engine`.

### Gerar primitivas

```bash
./generator plane <lenght> <divisions> <filename>
./generator box <lenght> <divisions> <filename>
./generator cone <radius> <height> <slices> <stacks> <filename>
./generator sphere <radius> <slices> <stacks> <filename>
```

Também é possível gerar um conjunto de exemplos de uma só vez com o script incluído:

```bash
../scripts/primitives_script.sh
```

### Correr o motor gráfico

```bash
./engine ../tests/test_1_1.xml
```

**Controlos:**

| Ação | Tecla |
|---|---|
| Rodar câmara | Setas do teclado |
| Aproximar / Afastar | `W` / `S` |
| Mudar modo de desenho (FILL/LINE/POINT) | Botão direito do rato |
| Mudar cor da primitiva | Teclas `0`–`7` |

## Primitivas Suportadas

- **Plano (Plane)** — quadrado no plano XZ, centrado na origem, subdividido em `divisions × divisions` células
- **Caixa (Box)** — junção de 6 planos, formando um cubo/paralelepípedo centrado na origem
- **Cone** — base circular no plano XZ, construída com `slices` fatias e `stacks` camadas
- **Esfera (Sphere)** — gerada por coordenadas esféricas, com `slices` fatias e `stacks` camadas

O relatório completo desta fase, com detalhes de implementação e resultados visuais, está disponível em [`docs/CG_TP_Fase1_Grupo12.pdf`](docs/CG_TP_Fase1_Grupo12.pdf).
