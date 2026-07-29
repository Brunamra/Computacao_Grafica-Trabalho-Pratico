# Fase 4 — Iluminação, Texturas e Sistema Solar

> Trabalho prático da Unidade Curricular de Computação Gráfica — Universidade do Minho (2023/2024)
> Grupo 12 — Bruna Micaela Rodrigues Araújo (a84914), Hugo Alexandre Peres Ferreira (a100082), Nuno Filipe Norberto Gonçalves de Oliveira (a53971)

Esta é a última fase do projeto de Computação Gráfica. O objetivo foi tornar a representação das cenas mais realista e dinâmica através da adição de **normais**, **coordenadas de textura**, **iluminação** e da renderização completa do **Sistema Solar**.

📄 Relatório completo desta fase: [`CG_TP_Fase4_Grupo12.pdf`](./CG_TP_Fase4_Grupo12.pdf)

---

## O que mudou em relação à Fase 3

- O ficheiro `.3d` gerado pelo `generator` passou a guardar, para cada vértice, três blocos de informação em vez de um só:
  1. Coordenadas do ponto
  2. Coordenadas do vetor normal
  3. Coordenadas de textura
- Todas as primitivas (`plane`, `box`, `cone`, `sphere`, `ring`, `patch`) foram atualizadas para calcular normais e mapear texturas.
- O `engine` passou a suportar:
  - Iluminação (point, directional e spotlight);
  - Aplicação de texturas via **DevIL**;
  - Cores por modelo (difusa, ambiente, especular, emissiva, shininess);
  - Leitura e renderização de uma cena completa do Sistema Solar animado.

## Estruturas de dados principais

```cpp
struct Light {
    int type;             // 0 - point | 1 - directional | 2 - spot
    float pos[4];
    float dir[4];
    float cuttOff;
};

struct Color {
    float diffuse[3];
    float ambient[3];
    float specular[3];
    float emissive[3];
    float shininess;
};

struct ModelInfo {
    vector<Point> vertices;
    vector<Point> normals;
    vector<TexCoord> texCoords;
};

struct ModelSettings {
    string modelFile;
    string textureFile;
    Color color;
};

struct Config {
    int window[2];
    float position[3], lookAt[3], up[3], projection[3];
    vector<Light> lights;
    map<string, ModelInfo> models;
    Group group;
};
```

Detalhes de todos os cálculos de normais e coordenadas de textura (plano, box, cone, esfera, ring e superfícies de Bezier) estão descritos e ilustrados no relatório em PDF.

## Como compilar

```bash
mkdir build && cd build
cmake ..
make
```

Dependências: OpenGL, GLUT, GLEW (Linux, exceto macOS) e DevIL.

## Como gerar as primitivas

```bash
./generator <primitiva> <parâmetros...> <ficheiro_destino.3d>
```

Exemplos:

```bash
./generator plane 2 3 plane_2_3.3d
./generator box 2 3 box_2_3.3d
./generator sphere 1 20 20 planet.3d
./generator cone 1 2 4 3 cone_1_2_4_3.3d
./generator ring 6.5 8 100 ring.3d
./generator patch teapot.patch 10 bezier_10.3d
```

O script [`primitives_script.sh`](./primitives_script.sh) automatiza a geração de todos os modelos usados nos testes de cada fase:

```bash
./primitives_script.sh phase_4
```

## Como correr o engine

```bash
./engine <ficheiro.xml>
```

Exemplo:

```bash
./engine solar_system.xml
```

### Ficheiros de teste incluídos

| Ficheiro | Descrição |
|---|---|
| `test_4_1.xml`, `test_4_2.xml`, `test_4_3.xml` | Testes base fornecidos pela UC para esta fase |
| `solar_system.xml` | Cena completa do Sistema Solar, com texturas, cores e animação |
| `solar_system_static_no_textures.xml` | Versão estática e sem texturas do Sistema Solar, para debug |
| `teapot.patch` | Patch de controlo (Utah teapot) para gerar a superfície de Bezier |

### Controlos

| Tecla | Ação |
|---|---|
| `w` / `s` | Mover para a frente / trás (modo Explorer: aproxima/afasta câmara; modo FPS: avança/recua) |
| `a` / `d` | Mover lateralmente (strafe, modo FPS) |
| Setas ↑ ↓ ← → | Orientar a câmara |
| `e` | Mudar para modo de câmara Explorer (orbital) |
| `f` | Mudar para modo de câmara FPS |
| Botão direito do rato | Menu para alternar entre modo FILL / LINE / POINT |

## Sistema Solar

A cena [`solar_system.xml`](./solar_system.xml) recria o Sistema Solar com o Sol, os planetas (incluindo anéis de Saturno) e as respetivas órbitas e rotações animadas, com texturas e materiais aplicados a cada corpo celeste. Ver secção 4 e 5 do relatório para capturas de ecrã.

## Estrutura de pastas

```
engine/
├── engine.cpp
├── config/
│   ├── config.cpp
│   └── config.h
├── utils/
│   ├── utils.cpp
│   └── utils.h
└── tinyxml2/
    ├── tinyxml2.cpp
    └── tinyxml2.h

generator/
├── generator.cpp
├── primitives.cpp
└── primitives.h

CMakeLists.txt
primitives_script.sh
```

## Conclusão

Com esta fase o projeto ficou completo: o `generator` gera normais e coordenadas de textura para todas as primitivas, e o `engine` lê, ilumina e texture-mapeia os modelos, permitindo renderizar uma cena tão complexa como o Sistema Solar de forma realista e a bom desempenho (>80 FPS nos testes realizados).
