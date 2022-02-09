# Algoritmo Pintor
Arquivos referentes ao trabalho final da disciplina Computação Gráfica - DCA0114

### Alunos: 
#### Matheus Augusto do Amaral / Jefferson Estevo Feitosa / Elton Rafael Costa da Silva

**Para rodar o programa no ambiente Linux, basta seguir os passos descritos abaixo, utilizando o temrminal em um ambiente Linux, com o compilador gcc instalado:**

Compilar no Linux: 
* ``` g++ Pintor.cpp -o pintor -lm -lGL -lGLU -lglut ```

Executar no Linux: 
* ```./pintor ```

<p>O programa base irá desenhar 3 objetos, ordenados pela sua profundidade com relação ao eixo Z. Um trapézio vermelho mais a frente, um losango verde no meio, e por fim, um triangulo azul. Para fazer as rotações na cena devemos pressionar as teclas (AS LETRAS DEVEM SER MAÍUSCULAS):</p>

* Q: para fazer uma rotação de 10º positivos em torno do eixo X.
* A: para fazer uma rotação de 10º negativos em torno do eixo X.
* W: para fazer uma rotação de 10º positivos em torno do eixo Y.
* S: para fazer uma rotação de 10º negativos em torno do eixo Y.
* E: para fazer uma rotação de 10º positivos em torno do eixo Z.
* D: para fazer uma rotação de 10º negativos em torno do eixo Z.

<p>Para que seja possível desenhar outras figuras, devemos alterar os seguintes parâmetros:</p>

```c++
int num_objetos = 3, num_vertices = 12;

float Cena[3][15] = { { -3.0, -4.0, 4.0,  // X, Y e Z do primeiro ponto do primeiro objeto
                         4.0, -4.0, 4.0,  // X, Y e Z do segundo ponto primeiro do objeto
                         2.0, 3.0, 4.0,   // X, Y e Z do terceiro ponto do primeiro objeto
                         -3.0, 3.0, 4.0,  // X, Y e Z do quarto ponto do primeiro objeto
                         1.0, 0.0, 0.0},  // R, G e B do primeiro objeto (COR)

                       { -4.0, -2.0, 0.0,  // X, Y e Z do primeiro ponto do segundo objeto
                         -4.0, -2.0, 0.0,  // X, Y e Z do segundo ponto segundo do objeto
                          5.0, -2.0, 0.0,  // X, Y e Z do terceiro ponto do segundo objeto
                         -2.0, 1.5, 0.0,   // X, Y e Z do quarto ponto do segundo objeto
                          0.0, 0.0, 1.0},  // R, G e B do segundo objeto (COR)

                        {-1.0, -6.0, 2.0,   // X, Y e Z do primeiro ponto do terceiro objeto
                         1.0, -3.0, 2.0,    // X, Y e Z do segundo ponto terceiro do objeto
                         3.0, -6.0, 2.0,    // X, Y e Z do terceiro ponto do terceiro objeto
                         1.0, -9.0, 2.0,    // X, Y e Z do quarto ponto do terceiro objeto
                         0.0, 1.0, 0.0} };  // R, G e B do segundo vértice (COR)
```
<p>Onde, informamos inicalmente o número de objetos que desejamos pintar na cena. E o número de vértices que cada objeto da cena irá possuir.</p>

<p>No exemplo padrão do código, temos 3 objetos, cada um com 12 vértices e 3 valores finais referentes à sua cor.</p>

Alterando os valores mostrados acima, podemos: 
* Adicionar ou remover quantidade de objetos.
* Alterar o número de vértices(pontos) que os objetos terão.
* Alterar os valores de coordenadas e de cor para cada objeto.

Fazendo isso, podemos aproximar objetos desejados na renderização, aumentado o número de vértices.

