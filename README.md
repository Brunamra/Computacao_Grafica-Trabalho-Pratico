# Computação Gráfica — Trabalho Prático

Trabalho prático desenvolvido no âmbito da Unidade Curricular de **Computação Gráfica** (Licenciatura em Ciências da Computação, Universidade do Minho, 2023/2024), ao longo de quatro fases. 
Consiste num motor gráfico 3D em OpenGL/GLUT capaz de ler a descrição de uma cena a partir de um ficheiro XML e renderizá-la, culminando numa recriação animada e texturada do Sistema Solar.

## Sobre o projeto

O objetivo do trabalho é construir, do zero e de forma incremental, um pequeno motor de renderização 3D — sem recorrer a bibliotecas de scene graph ou engines já existentes. Toda a lógica de descrição da cena, geometria, transformações, animações, iluminação e texturas é implementada pelo grupo, usando apenas OpenGL/GLUT como camada de desenho.
O projeto assenta na separação entre **geometria** e **cena**, seguindo uma filosofia semelhante à de motores de jogos reais:

- A **geometria** de cada objeto (um plano, uma esfera, um bule...) é calculada uma única vez e guardada em disco num ficheiro `.3d`, independente de onde ou como esse objeto vai ser usado;
- A **cena** é descrita separadamente, num ficheiro XML, como uma **árvore de grupos**: cada grupo pode ter transformações (estáticas ou animadas), modelos (referências a ficheiros `.3d`, com cor e textura) e outros grupos filhos. Isto permite, por exemplo, definir um planeta uma só vez e reutilizá-lo várias vezes na cena do Sistema Solar, cada instância com a sua própria órbita, escala e textura.

Esta separação dá origem ao pipeline usado ao longo de todas as fases:

```
generator  →  ficheiros .3d (geometria: pontos + normais + coordenadas de textura)
                      
cena.xml   →  descreve janela, câmara, luzes e a árvore de grupos
                      
engine     →  lê o XML, carrega os .3d referenciados e renderiza a cena
```

O projeto foi desenvolvido em quatro fases cumulativas — cada uma acrescenta funcionalidades novas ao `generator` e ao `engine` sem excluir o trabalho anterior — partindo de primitivas geométricas simples e transformações estáticas (Fase 1 e 2), passando por animações e superfícies curvas (Fase 3), até à iluminação e texturas que permitem a representação final e realista do Sistema Solar (Fase 4).

## Descrição

O projeto está organizado em dois programas:

- **`generator`** — gera ficheiros `.3d` com a geometria (pontos, normais e coordenadas de textura) de primitivas como planos, caixas, cones, esferas, anéis e superfícies de Bézier;
- **`engine`** — lê um ficheiro XML de configuração da cena, carrega os modelos `.3d` referenciados e renderiza a cena em OpenGL, com câmara navegável, hierarquia de transformações, animações, iluminação e texturas.

## Tecnologias

- **C++**
- **OpenGL / GLUT / GLEW** — renderização, VBOs e iluminação
- **DevIL** — carregamento de texturas
- **CMake**
- **tinyxml2**

## Fases do projeto

- [**Fase 1**](./TP_Fase1/README.md) — Geração de primitivas (plano, caixa, cone, esfera) e leitura de cenas XML simples
- [**Fase 2**](./TP_Fase2/README.md) — Motor gráfico, grupos e transformações estáticas (translate, rotate, scale) hierárquicas
- [**Fase 3**](./TP_Fase3/README.md) — Animações com curvas de Catmull-Rom, rotações dependentes do tempo, superfícies de Bézier e VBOs
- [**Fase 4**](./TP_Fase4/README.md) — Normais, coordenadas de textura, iluminação (point/directional/spot) e Sistema Solar completo

### Controlos

| Tecla | Ação |
|---|---|
| `w` / `s` | Aproximar/afastar (Explorer) ou avançar/recuar (FPS) |
| `a` / `d` | Strafe lateral (FPS) |
| Setas | Orientar a câmara |
| `e` | Câmara em modo Explorer (orbital) |
| `f` | Câmara em modo FPS |
| Botão direito do rato | Menu FILL / LINE / POINT |

**Elaborado por** 
- Bruna Micaela Rodrigues Araújo (a84914)
- Hugo Alexandre Peres Ferreira (a100082)
- Nuno Filipe Norberto Gonçalves de Oliveira (a53971)
