# Fase 2 — Transformações Geométricas

Segunda fase do projeto de **Computação Gráfica**, focada na organização hierárquica de cenas 3D através de transformações geométricas, culminando na construção de um modelo do Sistema Solar.

## Descrição

Esta fase estende o motor gráfico da [Fase 1](../fase1/README.md) com suporte a **cenas hierárquicas**: grupos que contêm transformações (translação, rotação, escala), modelos a desenhar e outros grupos "filho", que herdam as transformações do grupo "pai".

Foi ainda adicionada uma nova primitiva gráfica — o **anel (ring)** — usada para representar o anel de Saturno, e uma **câmara em modo FPS**, alternativa à câmara orbital da fase anterior, para melhor explorar a cena.

## Tecnologias

- **C++**
- **OpenGL / GLUT**
- **CMake**
- **tinyxml2**

## Novidades face à Fase 1

- **Estrutura `Transform`** — guarda o tipo de transformação (translação, rotação ou escala), o ângulo (quando aplicável) e as coordenadas
- **Estrutura `Group`** — guarda transformações, modelos e subgrupos, permitindo hierarquia entre grupos "pai" e "filho"
- **`addGroup`** — leitura recursiva de grupos a partir do XML, respeitando a ordem das transformações
- **`drawModels`** — desenho recursivo dos grupos, usando `glPushMatrix`/`glPopMatrix` para acumular e restaurar transformações
- **Primitiva `ring`** — nova primitiva no `generator`, usada para o anel de Saturno
- **Câmara FPS** — modo de câmara alternativo (tecla `F`), navegável com `W`/`A`/`S`/`D` e setas

## Funcionalidades

- Tudo o que já existia na Fase 1 (geração de primitivas, leitura de configuração XML, modos FILL/LINE/POINT, mudança de cor)
- Construção de cenas hierárquicas com grupos aninhados
- Geração da primitiva **ring** (anel), com raio interior, raio exterior e número de fatias
- Alternância entre câmara orbital (Explorer) e câmara FPS (tecla `E` / `F`)
- Cena de demonstração de um **Sistema Solar** com Sol, planetas, Lua e anel de Saturno

## Estrutura do Projeto

```
fase2/
├── engine/
│   ├── engine.cpp        # Renderização, câmaras (orbital e FPS), input
│   ├── config/
│   │   ├── config.cpp     # Parsing XML, incluindo grupos e transformações
│   │   └── config.h
│   └── tinyxml2/
├── generator/
│   ├── generator.cpp
│   ├── primitives.cpp     # Inclui agora a primitiva ring
│   └── primitives.h
├── tests/                  # Ficheiros de configuração XML de exemplo
│   ├── test_2_1.xml ... test_2_5.xml
│   ├── solar_system.xml
│   └── solar_system_2.xml
├── scripts/
│   └── primitives_script.sh   # Suporta "phase_1" e "phase_2" como argumento
├── docs/
│   └── CG_TP_Fase2_Grupo12.pdf   # Relatório entregue nesta fase
└── CMakeLists.txt
```

## Como Executar

### Pré-requisitos

- Compilador C++ compatível com C++11 ou superior
- CMake ≥ 3.5
- OpenGL e GLUT instalados no sistema

### Compilar

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Gerar primitivas (incluindo o anel)

```bash
./generator ring <innerRadius> <outerRadius> <slices> <filename>
```

Ou gerar o conjunto de primitivas usado nesta fase:

```bash
../scripts/primitives_script.sh phase_2
```

### Correr o motor gráfico

```bash
./engine ../tests/solar_system.xml
```

**Controlos:**

| Ação | Tecla |
|---|---|
| Alternar para câmara FPS | `F` |
| Voltar à câmara Explorer | `E` |
| Mover câmara (FPS) / Aproximar-afastar (Explorer) | `W` / `S` |
| Deslocar lateralmente (FPS) | `A` / `D` |
| Rodar câmara (Explorer) / Olhar em volta (FPS) | Setas do teclado |
| Mudar modo de desenho (FILL/LINE/POINT) | Botão direito do rato |
| Mudar cor da primitiva | Teclas `0`–`7` |

O relatório completo desta fase, com a explicação das novas estruturas de dados e os resultados visuais do Sistema Solar, está disponível em [`docs/CG_TP_Fase2_Grupo12.pdf`](docs/CG_TP_Fase2_Grupo12.pdf).