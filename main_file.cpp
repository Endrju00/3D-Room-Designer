#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/types.h>

#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myRoom.h"
#include "models/myCube.h"
#include "models/myTeapot.h"

using namespace std;


//predkosc 
float speed_x = 0;//[radiany/s]
float speed_y = 0;//[radiany/s]
float speed_z = 0;
float aspectRatio = 1;

//pozycja kamery
int camera_set = 1;
float camera_coords[4][3] = {
	{20.0f, 10.0f, -8.0f},
	{0.0f, 10.0f, -20.0f},
	{-20.0f, 10.0f, -8.0f},
	{0.0f, 20.0f, -1.0f}
};

float camera_x = camera_coords[camera_set][0];
float camera_y = camera_coords[camera_set][1];
float camera_z = camera_coords[camera_set][2];

//Program cieniujący
ShaderProgram* sp;

//uchwyty tekstur
GLuint walls_tex;
GLuint floor_tex; 

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

// wyswietl zawartosc folderu
void list_dir(const char* path) {
	struct dirent* entry;
	DIR* dir = opendir(path);
	int i = -1;
	if (dir == NULL) {
		return;
	}
	while ((entry = readdir(dir)) != NULL) {
		if (i > 0) {
			cout << "    --> " << i << ". " << entry->d_name << endl;
		}
		i++;
	}
	closedir(dir);
}

//Wczytywanie tekstury
GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

// informacja odnosnie sterowania
void info() {

	cout << "\n--> Aby wyswietlic menu - uzyj klawisza M." << endl;						
	cout << "--> Aby obracac pokojem - uzyj strzalek." << endl;
	cout << "--> Aby przyblizac/oddalac kamere - uzyj odpowiednio klawiszy W oraz S." << endl;
	cout << "--> Aby zresetowac pozycje kamery - uzyj klawisza R." << endl;
	cout << "\n!!! Podpowiedz: uzywaj powyzszych klawiszy w oknie OpenGL. !!!" << endl;
}

//zmiana tekstur calego pomieszczenia
void changeRoomTexture() {
	string floor_path = "textures/floor/";
	string walls_path = "textures/walls/";
	string choice;
	
	cout << "\nWybierz teksture dla scian:" << endl;
	list_dir("textures/walls");

	cout << "\nWpisz nazwe tekstury: ";
	cin >> choice;
	walls_path += choice;	// stworzenie sciezki

	char* char_wall;
	string str_obj(walls_path);		// zamiana z string na char
	char_wall = &str_obj[0];

	cout << "\nWybierz teksture dla podlogi:" << endl;
	list_dir("textures/floor");

	cout << "\nWpisz nazwe tekstury: ";
	cin >> choice;
	floor_path += choice;	// stworzenie sciezki

	char* char_floor;
	string floor_obj(floor_path);	// zamiana z string na char
	char_floor = &floor_obj[0];

	walls_tex = readTexture(char_wall);  // wczytanie tekstury ściany
	floor_tex = readTexture(char_floor); // wczytanie tekstury podłogi

	cout << "\n>>Generowanie pokoju..." << endl;
	info();
}

//zmiana tekstury podlogi
void changeFloorTexture() {
	string floor_path = "textures/floor/";
	string choice;

	cout << "\nWybierz teksture dla podlogi:" << endl;
	list_dir("textures/floor");

	cout << "\nWpisz nazwe tekstury: ";
	cin >> choice;
	floor_path += choice;	// stworzenie sciezki

	char* char_floor;
	string floor_obj(floor_path);	// zamiana z string na char
	char_floor = &floor_obj[0];

	floor_tex = readTexture(char_floor); // wczytanie tekstury podłogi

	cout << "\n>>Wprowadzanie zmian..." << endl;
	info();
}

//zmiana tekstury scian
void changeWallsTexture() {
	string walls_path = "textures/walls/";
	string choice;

	cout << "\nWybierz teksture dla scian:" << endl;
	list_dir("textures/walls");

	cout << "\nWpisz nazwe tekstury: ";
	cin >> choice;
	walls_path += choice;	// stworzenie sciezki

	char* char_wall;
	string str_obj(walls_path);		// zamiana z string na char
	char_wall = &str_obj[0];

	walls_tex = readTexture(char_wall);  // wczytanie tekstury ściany

	cout << "\n>>Wprowadzanie zmian..." << endl;
	info();
}

void drawObject(float* vertices, float* colors, float* normals, float* texCoords, int vertexCount, const char* texture = "textures/walls/bricks.png") {
	//GLuint tex = readTexture(texture);
	glm::mat4 M3 = glm::mat4(1.0f); // Rysowanie ścian
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M3));
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, vertices);

	glEnableVertexAttribArray(sp->a("color"));
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors);

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normals);

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords);

	glUniform1i(sp->u("textureMap0"), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, walls_tex);


	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("color"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));
}

// Menu uzytkownika
void menu() {
	cout << "\n>>Menu" << endl;
	cout << "1. Zmien wyglad podlogi." << endl;
	cout << "2. Zmien wyglad scian." << endl;
	cout << "3. Zmien wyglad calego pomieszczenia." << endl;
	cout << "4. Dodaj obiekt." << endl;
	cout << "5. Anuluj." << endl;

	int num;
	cout << "Wprowadz numer: ";
	cin >> num;

	switch (num) {
	case 1:
		changeFloorTexture(); break;
	case 2:
		changeWallsTexture(); break;
	case 3:
		changeRoomTexture(); break;
	case 4:
		cout << "Funkcja niedostepna." << endl; break;
	case 5:
		info(); break;
	default:
		cout << "Bledna opcja :(" << endl;
	}
}

void setCamera() {
	camera_x = camera_coords[camera_set][0];
	camera_y = camera_coords[camera_set][1];
	camera_z = camera_coords[camera_set][2];
}

//obsluga klawiszy
void key_callback(
	GLFWwindow* window,
	int key,
	int scancode,
	int action,
	int mod
) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_A) {
			if (camera_set == 0) camera_set = 3; else camera_set--;
		}
		if (key == GLFW_KEY_D) {
			if (camera_set > 2) camera_set = 0; else camera_set++;
		}
		if (key == GLFW_KEY_R) {
			camera_set = 1;
			
		}
		if (key == GLFW_KEY_M) {
			menu();
		}
	}
	if (action == GLFW_RELEASE) {
		
	}
}

// Skalowanie okna 
void windowResizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) return;
	aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    //initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(1, 1, 1, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, key_callback);
	sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
	walls_tex = readTexture("textures/walls/light_bricks.png");  // wczytanie domyslnej tekstury ściany
	floor_tex = readTexture("textures/floor/light_wood.png"); // wczytanie domyslnej tekstury podłogi
	cout << "\n************** Witaj w dekoratorze wnetrz! **************" << endl;
	info();
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    /*freeShaders();*/
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
	glDeleteTextures(1, &walls_tex);
	glDeleteTextures(1, &floor_tex);
	delete sp;
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyść bufor koloru i bufor głębokości

	glm::mat4 M = glm::mat4(1.0f); //Zainicjuj macierz modelu macierzą jednostkową
	glm::mat4 V = glm::lookAt(glm::vec3(camera_x, camera_y, camera_z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania

	
	sp->use();
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));


	glm::mat4 M1 = M; // Rysowanie ścian
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M1));
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myRoomVertices);

	glEnableVertexAttribArray(sp->a("color"));
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, myRoomColors);
	
	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, myWallsVertexNormals);
	
	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, myRoomTexCoords);

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, walls_tex);
	

	glDrawArrays(GL_TRIANGLES, 0, myRoomVertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("color"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));

	//myFloorVertices, myFloorTexCoords, myFloorVertexNormals


	glm::mat4 M2 = M; // Rysowanie podłogi
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M2));
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myFloorVertices);

	glEnableVertexAttribArray(sp->a("color"));
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, myRoomColors);

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, myFloorVertexNormals);

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, myRoomTexCoords);

	glUniform1i(sp->u("textureMap0"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, floor_tex);
	

	glDrawArrays(GL_TRIANGLES, 0, myRoomVertexCount);


	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("color"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));

	drawObject(myTeapotVertices, myTeapotColors, myTeapotNormals, myTeapotTexCoords, myTeapotVertexCount); //rysuj czajnik


	glfwSwapBuffers(window); //Skopiuj bufor tylny do bufora przedniego
}

int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	glfwSetTime(0); //Wyzeruj licznik czasu
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		setCamera();
		glfwSetTime(0); //Wyzeruj licznik czasu
		drawScene(window); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	glDeleteTextures(1, &walls_tex);
	glDeleteTextures(1, &floor_tex);

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
