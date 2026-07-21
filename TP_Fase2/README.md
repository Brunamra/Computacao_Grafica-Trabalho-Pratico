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
- Cena de demonstração de um **Sistema Solar** com sol, planetas, lua e anel de Saturno
- 

O relatório completo desta fase, contém a explicação das novas estruturas de dados e os resultados visuais do Sistema Solar.
