# Fase 3 — Curvas, Superfícies Cúbicas e VBOs

Terceira fase do projeto de **Computação Gráfica**, com o objetivo de obter uma representação mais dinâmica e realista do Sistema Solar, através de curvas de animação, superfícies cúbicas de Bézier e renderização com VBOs.

## Descrição

Esta fase estende o motor gráfico das fases anteriores ([Fase 1](../TP_Fase1/README.md), [Fase 2](../TP_Fase2/README.md)) em três frentes:

- **generator** — passa a suportar a conversão de ficheiros `.patch` (superfícies de Bézier, ex: o clássico *teapot*) em ficheiros `.3d`, através de tesselação configurável;
- **engine** — passa a suportar transformações **animadas com tempo**: translações ao longo de curvas de Catmull-Rom (com alinhamento opcional do objeto à curva) e rotações contínuas de 360° em torno de um eixo;
- **engine** — o desenho das primitivas deixa de usar `glBegin`/`glEnd` e passa a ser feito através de **VBOs** (Vertex Buffer Objects), para maior eficiência de renderização.

## Tecnologias

- **C++**
- **OpenGL / GLUT / GLEW** — renderização e gestão de buffers na GPU
- **CMake**
- **tinyxml2**

## Novidades face à Fase 2

- **Superfícies de Bézier** — `loadPatch` lê um ficheiro `.patch` (número de patches, índices e pontos de controlo); `bezierSurfacePoint` calcula os pontos da superfície; `createPrimitive` gera o `.3d` correspondente, com nível de detalhe ajustável por tesselação
- **Transformações com tempo** — a estrutura `Transform` ganha os campos `time` (duração da animação) e `align` (se o objeto deve orientar-se com a curva), além de `points` (pontos de controlo da curva)
- **Curvas de Catmull-Rom** — `getGlobalCatmullRomPoint`/`getCatmullRomPoint` (em `utils/`) calculam a posição e a derivada num dado instante, permitindo animar translações ao longo de um percurso fechado
- **Rotações animadas** — quando definido um `time` em vez de um `angle`, o ângulo de rotação é recalculado em cada frame com base no tempo decorrido, completando uma volta a cada intervalo definido
- **VBOs** — os pontos de cada modelo são copiados para buffers na GPU (`modelsToBuffers`) e desenhados com `glDrawArrays`, substituindo o desenho imediato usado nas fases anteriores
- **Indicadores em tempo real** — o título da janela passa a mostrar FPS e o tempo decorrido da simulação

## Funcionalidades

- Tudo o que já existia nas fases anteriores (primitivas, hierarquia de grupos, câmaras Explorer/FPS)
- Geração de superfícies de Bézier a partir de ficheiros `.patch`
- Animações de translação ao longo de curvas de Catmull-Rom, com alinhamento opcional à trajetória
- Rotações contínuas com duração configurável (em vez de ângulo fixo)
- Renderização via VBOs
- Cena de demonstração do Sistema Solar com um cometa animado numa trajetória Catmull-Rom

O relatório completo desta fase contém a explicação das superfícies de Bézier, dos VBOs e das transformações animadas.
