#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Wspolrzedne swiatla 1 i 2 
uniform vec4 lp1;
uniform vec4 lp2;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color; //kolor zwi¹zany z wierzcho³kiem
in vec4 normal; //wektor normalny w przestrzeni modelu
in vec2 texCoord0; 

//Zmienne interpolowane
out vec4 ic;

out vec4 l1;
out vec4 n1;
out vec4 v1;

out vec4 l2;
out vec4 n2;
out vec4 v2;

out vec2 iTexCoord0;


void main(void) {
    //1
    l1 = normalize(V * lp1 - V*M*vertex); //wektor do œwiat³a w przestrzeni oka
    v1 = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //wektor do obserwatora w przestrzeni oka
    n1 = normalize(V * M * normal); //wektor normalny w przestrzeni oka

    //2
    l2 = normalize(V * lp2 - V*M*vertex); //wektor do œwiat³a w przestrzeni oka
    v2 = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //wektor do obserwatora w przestrzeni oka
    n2 = normalize(V * M * normal); //wektor normalny w przestrzeni oka

    iTexCoord0=texCoord0;
    ic = color;
    
    gl_Position=P*V*M*vertex;
}
