# Fase 4 — Iluminação, Texturas e Sistema Solar

Esta é a última fase do projeto de Computação Gráfica. O objetivo foi tornar a representação das cenas mais realista e dinâmica através da adição de **normais**, **coordenadas de textura**, **iluminação** e da renderização completa do **Sistema Solar**.

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


Com esta fase o projeto ficou completo: o `generator` gera normais e coordenadas de textura para todas as primitivas, e o `engine` lê, ilumina e texture-mapeia os modelos, permitindo renderizar uma cena tão complexa como o Sistema Solar de forma realista e a bom desempenho, tudo isto encontra-se meticulosamente descrito no relatório.
