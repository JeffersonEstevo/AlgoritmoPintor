#include <GL/glut.h>
#include <iostream>
#include <math.h>
#define PI 3.14159265
using namespace std;

// Variaveis que definem a quantidade em graus de rota��o nos eixos
int rot_x = 0, rot_y = 0, rot_z = 0;

// Variaveis de contagem do angulo de rota��o nos eixos
int sum_rot_x = 0, sum_rot_y = 0, sum_rot_z = 0;


// =========== CENAS ====================================================================

// 3 retangulos identicos
/*
int num_objetos = 3, num_vertices = 12;
float Cena[3][15] = { { -4.0, -2.0, 4.0,
                          4.0, -2.0, 4.0,
                          4.0, 1.5, 4.0,
                         -4.0, 1.5, 4.0,
                          1.0, 0.0, 0.0},

                       { -4.0, -2.0, 0.0,
                          4.0, -2.0, 0.0,
                          4.0, 1.5, 0.0,
                         -4.0, 1.5, 0.0,
                          0.0, 0.0, 1.0},

                        { -4.0, -2.0, 0.0,
                          4.0, -2.0, 0.0,
                          4.0, 1.5, 0.0,
                         -4.0, 1.5, 0.0,
                          0.0, 1.0, 0.0} };
*/

// 3 retangulos de altura e largura diferentes
/*
int num_objetos = 3, num_vertices = 12;

float Cena[3][15] = { { -3.0, -4.0, 4.0,
                         4.0, -4.0, 4.0,
                         4.0, 3.0, 4.0,
                         -3.0, 3.0, 4.0,
                         1.0, 0.0, 0.0},

                       { -4.0, -2.0, 0.0,
                          5.0, -2.0, 0.0,
                          5.0, 1.5, 0.0,
                         -4.0, 1.5, 0.0,
                          0.0, 0.0, 1.0},

                        {-1.0, -8.0, 2.0,
                         1.0, -8.0, 2.0,
                         1.0, 8.0, 2.0,
                         -1.0, 8.0, 2.0,
                         0.0, 1.0, 0.0} };
*/

// 1 losango, um triangulo e um trapezio
int num_objetos = 3, num_vertices = 12;

float Cena[3][15] = { { -3.0, -4.0, 4.0,
                         4.0, -4.0, 4.0,
                         2.0, 3.0, 4.0,
                         -3.0, 3.0, 4.0,
                         1.0, 0.0, 0.0},

                       { -4.0, -2.0, 0.0,
                         -4.0, -2.0, 0.0,
                          5.0, -2.0, 0.0,
                         -2.0, 1.5, 0.0,
                          0.0, 0.0, 1.0},

                        {-1.0, -6.0, 2.0,
                         1.0, -3.0, 2.0,
                         3.0, -6.0, 2.0,
                         1.0, -9.0, 2.0,
                         0.0, 1.0, 0.0} };

// =======================================================================================

// Retorna o minimo valor de "z' dos vertices de um poligono
float MinimoZ(float poligono[]) {
    
    float minimo = 999.999;
    for (int i = 2; i < num_vertices; i = i + 3) {
        if (poligono[i] < minimo) {
            minimo = poligono[i];
        }
    }
    cout << "Minimo z do objeto " << minimo << endl;;
    return minimo;

}

// Rotaciona os vertices da cena
void RotacionarCena(float cena[][15]) {

    float cx = cos(rot_x * PI / 180.0), sx = sin(rot_x * PI / 180.0);
    float cy = cos(rot_y * PI / 180.0), sy = sin(rot_y * PI / 180.0);
    float cz = cos(rot_z*PI/180.0), sz = sin(rot_z*PI / 180.0);

    float aux_x, aux_y, aux_z;
 
    for (int i = 0; i < num_objetos; i++) {

        for (int x = 0, y = 1, z = 2; x <= num_vertices-3 ; x += 3, y += 3, z += 3) {

            aux_x = cena[i][x];
            aux_y =  cena[i][y];
            aux_z = cena[i][z];

            cena[i][x] = (aux_x * cy * cz) + (aux_y * -1 * cy * sz) + (aux_z * -1 * sy);
            cena[i][y] = (aux_x * ((-1 * sx * sy * cz) + (cx * sz))) + (aux_y * ((cx * cz) + (sx * sy * sz))) + (aux_z * -1 * sx * cy);
            cena[i][z] = (aux_x * ((sx * sz) + (cx * sy * cz))) + (aux_y * ((-1 * cx * sy * sz) + (sx * cz))) + (aux_z * (cx * cy));
           
        }
    }
    
}

// Algoritmo do pintor
void Pintor(float cena[][15]) {

    // Vetor com ordem dos objetos para desenhar
    // Para cada objeto na cena cria um vetor como este : [0, 1, 2, ...]
    // Cada valor do vetor � referente ao objeto, e a posi��o no vetor indica a ordem que eles ser�o
    // desenhados...Exemplo, se o vetor for : [2, 0, 1] quer dizer que o terceiro objeto sera desenhado
    // primeiro, o primeiro objeto sera desenhado em seguida e por fim o segundo objeto sera desenhado
    int* OrdemDesenho = (int*)malloc(num_objetos * sizeof(int));
    for (int i = 0; i < num_objetos; i++) {
        *(OrdemDesenho + i) = i;
    }

    // Variaveis de controle para ordena��o
    int distancia_obj_atual;
    int distancia_prox_obj;
    int obj_atual;
    int prox_obj;
    int aux;

    // Ordena o vetor com base na distancia de cada objeto na cena  
    for (int i = 1; i < num_objetos; i++) {
        obj_atual = *(OrdemDesenho + i);
        int j;
        for (j = i; j > 0 && MinimoZ(cena[*(OrdemDesenho + j - 1)]) > MinimoZ(cena[obj_atual]); j--) {
            *(OrdemDesenho + j) = *(OrdemDesenho + j  - 1);;
        }
        *(OrdemDesenho + j) = obj_atual;
    }
    

    cout << "Ordem dos objetos para desenhar : ";
    for (int i = 0; i < num_objetos; i++) {
        cout << *(OrdemDesenho + i) << " ";
    }
    cout << endl;

    // Desenha os objetos ordenados
    for (int i = 0; i < num_objetos; i++) {

        /*
        cout << "Vertices do poligono que vou desenhar : ";
        for (int j = 0; j < num_vertices; j++) {
            cout << cena[OrdemDesenho[i]][j] << " ";
        }
        cout << endl;
        */

        cout << "Z dos objetos : ";
        for (int j = 2; j < num_vertices; j=j+3) {
            cout << cena[i][j] << " ";
        }
        cout << endl;

        glColor3f(cena[OrdemDesenho[i]][num_vertices], cena[OrdemDesenho[i]][num_vertices + 1], cena[OrdemDesenho[i]][num_vertices + 2]);
        glBegin(GL_POLYGON);
        for (int j = 0; j < num_vertices - 2; j = j + 3) {
            glVertex3f(cena[OrdemDesenho[i]][j], cena[OrdemDesenho[i]][j + 1], cena[OrdemDesenho[i]][j + 2]);
        }
        glEnd();
    }
}

void init(void)
{
    // Especifica os valores de vermelho, verde, azul e transparencia usados quando o buffer de cor �
    // limpo. Basicamente � a cor de fundo.
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

}

void display(void)
{
    // Limpa o buffer de cores setando em seguida o definido em glClearColor
    // Basicamente limpa toda a tela e deixa a cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);
  
    cout << "Cena esta rotacionada em : " << endl;
    cout << sum_rot_x << " graus no eixo x" << endl;
    cout << sum_rot_y << " graus no eixo y" << endl;
    cout << sum_rot_z << " graus no eixo z" << endl;

    Pintor(Cena);
    
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'Q':
            rot_x = 10;
            rot_y = 0;
            rot_z = 0;
            sum_rot_x = (sum_rot_x + rot_x) % 360;
            RotacionarCena(Cena);
            glutPostRedisplay();
            break;
        case 'W':
            rot_x = 0;
            rot_y = 10;
            rot_z = 0;
            sum_rot_y = (sum_rot_y + rot_y) % 360;
            RotacionarCena(Cena);
            glutPostRedisplay();
            break;
        case 'E':
            rot_x = 0;
            rot_y = 0;
            rot_z = 10;
            sum_rot_z = (sum_rot_z + rot_z) % 360;
            RotacionarCena(Cena);
            glutPostRedisplay();
            break;
        case 'A':
            rot_x = -10;
            rot_y = 0;
            rot_z = 0;
            sum_rot_x = (sum_rot_x + rot_x) % 360;
            RotacionarCena(Cena);
            glutPostRedisplay();
            break;
        case 'S':
            rot_x = 0;
            rot_y = -10;
            rot_z = 0;
            sum_rot_y = (sum_rot_y + rot_y) % 360;
            RotacionarCena(Cena);
            glutPostRedisplay();
            break;
        case 'D':
            rot_x = 0;
            rot_y = 0;
            rot_z = -10;
            sum_rot_z = (sum_rot_z + rot_z) % 360;
            RotacionarCena(Cena);
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }

}

void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
 
}

int main(int argc, char** argv)
{
    // Inicia a biblioteca do GLUT
    glutInit(&argc, argv);

    // Configura o modo de display inicial
    // GLUT_SINGLE configura a janela para ter um unico buffer
    // GLUT_RGB configura a janela para o padr�o de cor RGB
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Tamanho inicial da janela
    glutInitWindowSize(250, 250);

    // Posi��o inicial da janela a partir da extremida superior esquerda do monitor
    glutInitWindowPosition(100, 100);

    // Nome da janela
    glutCreateWindow("hello");

    // Invoca a fun��o "Init"
    init();

    // Invoca a fun�ao "display" na janela
    glutDisplayFunc(display);

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // Faz com que as fun��es do glut fiquem em loop
    glutMainLoop();

    return 0;
}

