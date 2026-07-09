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

## Primitivas Suportadas

- **Plano (Plane)** — quadrado no plano XZ, centrado na origem, subdividido em `divisions × divisions` células
- **Caixa (Box)** — junção de 6 planos, formando um cubo/paralelepípedo centrado na origem
- **Cone** — base circular no plano XZ, construída com `slices` fatias e `stacks` camadas
- **Esfera (Sphere)** — gerada por coordenadas esféricas, com `slices` fatias e `stacks` camadas
