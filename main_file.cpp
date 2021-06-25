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
#include "Mebel.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

//wspolrzedne swiatła
float l_x1 = 70;
float l_x2 = -70;
float l_y = 30;


float camera_x = camera_coords[camera_set][0];
float camera_y = camera_coords[camera_set][1];
float camera_z = camera_coords[camera_set][2];

//Program cieniujący
ShaderProgram* sp;

//uchwyty tekstur
GLuint walls_tex;
GLuint floor_tex;
GLuint table_tex;
GLuint chair_tex;
GLuint armchair_tex;
GLuint soundbar_tex;
GLuint carpet_tex;
GLuint vase_tex;
GLuint lamp_tex;
GLuint bed_tex;
GLuint cupboard_tex;


//assimp - wczytywanie modeli
vector<glm::vec4>verts;
vector<glm::vec4>norms;
vector<glm::vec2>texCoords;
vector<unsigned int> indices;

//assimp - wczytywanie modeli
vector<glm::vec4>verts2;
vector<glm::vec4>norms2;
vector<glm::vec2>texCoords2;
vector<unsigned int> indices2;

Mebel chair;
Mebel table;
Mebel armchair;
Mebel cupboard;
Mebel bed;
Mebel vase;
Mebel lamp;
Mebel lamp2;
Mebel carpet;

//Wskazniki na meble
vector<Mebel *> meble = { &chair, &table, &armchair, &cupboard, &bed, &vase, &carpet };
int p = 0;

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
	cout << "--> Aby zmieniac pozycje kamery - uzyj strzalek." << endl;
	cout << "--> Aby zresetowac pozycje kamery - uzyj klawisza R." << endl;
	cout << "--> Aby przesunac mebel - uzyj klawiszy W, S, A, D, Q oraz E." << endl;
	cout << "--> Aby obracac meblem względem osi X, Y, Z - uzyj klawiszy I, O oraz P." << endl;
	cout << "--> Aby zmienic przesuwany mebel - uzyj klawisza Tab." << endl;
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


// Menu uzytkownika
void menu() {
	cout << "\n>>Menu" << endl;
	cout << "1. Zmien wyglad podlogi." << endl;
	cout << "2. Zmien wyglad scian." << endl;
	cout << "3. Zmien wyglad calego pomieszczenia." << endl;
	cout << "4. Anuluj." << endl;

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
		if (key == GLFW_KEY_UP) {
			speed_z = 2 * PI;
		}
		if (key == GLFW_KEY_DOWN) {
			speed_z = -2 * PI;
		}
		if (key == GLFW_KEY_LEFT) {
			if (camera_set == 0) camera_set = 3; else camera_set--; setCamera();
		}
		if (key == GLFW_KEY_RIGHT) {
			if (camera_set > 2) camera_set = 0; else camera_set++; setCamera();
		}
		if (key == GLFW_KEY_R) {
			camera_set = 1; setCamera();
		}
		if (key == GLFW_KEY_M) {
			menu();
		}
		if (key == GLFW_KEY_I) {
			(*meble[p]).rotateModelX();
		}
		if (key == GLFW_KEY_O) {
			(*meble[p]).rotateModelY();
		}
		if (key == GLFW_KEY_P) {
			(*meble[p]).rotateModelZ();
		}
		if (key == GLFW_KEY_J) {
			l_x1 += 10;
			cout << "1: " << l_x1 << " 2: " << l_x2 << endl;
		}
		if (key == GLFW_KEY_K) {
			l_x2 -= 10;
			cout << "1: " << l_x1 << " 2: " << l_x2 << endl;
		}
		if (key == GLFW_KEY_Z) {
			l_y += 10;
			cout << "y: " << l_y << endl;
		}
		if (key == GLFW_KEY_X) {
			l_y -= 10;
			cout << "y: " << l_y << endl;
		}
		if (key == GLFW_KEY_D) {
			(*meble[p]).moveRight();
		}
		if (key == GLFW_KEY_A) {
			(*meble[p]).moveLeft();
		}
		if (key == GLFW_KEY_W) {
			(*meble[p]).moveForward();
		}
		if (key == GLFW_KEY_S) {
			(*meble[p]).moveBackward();
		}
		if (key == GLFW_KEY_Q) {
			(*meble[p]).moveUp();
		}
		if (key == GLFW_KEY_E) {
			(*meble[p]).moveDown();
		}
		if (key == GLFW_KEY_TAB) {
			if (p + 1 != meble.size()) p++;
			else p = 0;
		}

	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_UP) {
			speed_z = 0;
		}
		if (key == GLFW_KEY_DOWN) {
			speed_z = 0;
		}
	}
}

// Skalowanie okna 
void windowResizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) return;
	aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}

void loadModel(string plik, vector<glm::vec4>& v, vector<glm::vec4>& n, vector<glm::vec2>& t, vector<unsigned int>& ind) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(plik, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
	cout << importer.GetErrorString() << endl;

	aiMesh* mesh = scene->mMeshes[0];

	for (int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D vertex = mesh->mVertices[i];
		v.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

		aiVector3D normal = mesh->mNormals[i];
		n.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

		aiVector3D texCoord = mesh->mTextureCoords[0][i];
		t.push_back(glm::vec2(texCoord.x, texCoord.y));
	}

	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace& face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; j++) {
			ind.push_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
}


//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	glClearColor(1, 1, 1, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, key_callback);

	//Deklaracja i przypisanie shaderu oraz tekstur
	sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
	walls_tex = readTexture("textures/walls/light_bricks.png");					// wczytanie domyslnych tekstur
	floor_tex = readTexture("textures/floor/light_wood.png"); 
	table_tex = readTexture("textures/floor/dark_wood.png"); 
	bed_tex = readTexture("textures/dark_wood1.png");
	cupboard_tex = readTexture("textures/floor/dark_wood.png");
	chair_tex = readTexture("textures/chair_tex.png"); 
	armchair_tex = readTexture("textures/sofa_tex.png");
	soundbar_tex = readTexture("textures/soundbar.png");
	carpet_tex = readTexture("textures/zebra.png");
	vase_tex = readTexture("textures/bronze.png");
	lamp_tex = readTexture("textures/gold.png");
	
	//Macierz jednostkowa
	glm::mat4 M = glm::mat4(1.0f);
	
	//Ustawienie krzesła
	chair = Mebel("models/Chair.obj", M, 1.0);
	chair.set(M,// macierz jednostkowa
		glm::vec3(-2.5f, -3.0f, 0.7f), // wektor przesuniecia
		glm::vec3(0.08f, 0.08f, 0.08f), //  wektor skalowania,
		glm::vec3(0.0f, 1.0f, 0.0f), // wektor rotacji jesli brak obrotu nie trzeba podawac
		-180.0f // kąt obrotu domyslnie 0.0f
	); 

	//Ustawienie stolika
	table = Mebel("models/table.fbx", M, 50.0);
	table.set(M, glm::vec3(-2.5f, -3.0f, 3.1f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);

	//Ustawienie fotela
	armchair = Mebel("models/armchair.obj", M, 0.05);
	armchair.M = M;
	armchair.M = glm::translate(armchair.M, glm::vec3(1.0f, -3.0f, 3.3f));
	armchair.M = glm::rotate(armchair.M, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	armchair.M = glm::rotate(armchair.M, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	armchair.M = glm::scale(armchair.M, glm::vec3(0.007f, 0.007f, 0.007f));

	//Ustawienie szafki
	cupboard = Mebel("models/szuflada.obj", M, 50.0);
	cupboard.set(M, glm::vec3(-8.0f, -2.0f, -2.0f), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);

	//Ustawienie lozka
	bed = Mebel("models/sofa.obj", M, 0.05);
	bed.set(M, glm::vec3(7.0f, -3.0f, 1.0f), glm::vec3(0.007f, 0.007f, 0.007f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);

	//Ustawienie wazy
	vase = Mebel("models/vase.obj", M, 0.2);
	vase.set(M, glm::vec3(8.0f, -3.0f, -4.0f), glm::vec3(0.025f, 0.025f, 0.025f));

	//Ustawienie lampy1
	lamp = Mebel("models/lamp1.obj", M, 50.0);
	lamp.set(M, glm::vec3(5.0f, 3.0f, 0.0f), glm::vec3(0.003f, 0.003f, 0.003f));
	
	//Ustawienie lampy2
	lamp2 = Mebel("models/lamp1.obj", M, 50.0);
	lamp2.set(M, glm::vec3(-5.0f, 3.0f, 0.0f), glm::vec3(0.003f, 0.003f, 0.003f));

	//Ustawienie dywanu
	carpet = Mebel("models/carpet1.3ds", M, 0.05);
	carpet.set(M, glm::vec3(1.0f, -3.0f, -0.5f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);

	//Wyswietl informacje w konsoli
	cout << "\n************** Witaj w dekoratorze wnetrz! **************" << endl;
	info();
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	glDeleteTextures(1, &walls_tex);
	glDeleteTextures(1, &floor_tex);
	glDeleteTextures(1, &table_tex);
	glDeleteTextures(1, &chair_tex);
	glDeleteTextures(1, &armchair_tex);
	glDeleteTextures(1, &soundbar_tex);
	glDeleteTextures(1, &carpet_tex);
	delete sp;
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyść bufor koloru i bufor głębokości

	glm::mat4 M = glm::mat4(1.0f); //Zainicjuj macierz modelu macierzą jednostkową
	glm::mat4 V = glm::lookAt(glm::vec3(camera_x, camera_y, camera_z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania

	//Shader
	sp->use();
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	//Przekazanie zmiennej reprezentującej wspołrzędne źródła światła 1 i 2
	glUniform4f(sp->u("lp1"), l_x1, l_y, 0, 1);
	glUniform4f(sp->u("lp2"), l_x2, l_y, 0, 1);

	//Rysowanie ścian
	glm::mat4 M1 = M; 
	drawWalls(M1, 0, GL_TEXTURE0, walls_tex, sp);

	//Rysowanie podłogi
	glm::mat4 M2 = M; 
	drawFloor(M2, 1, GL_TEXTURE1, floor_tex, sp);

	//Rysowanie mebli
	chair.draw(2, GL_TEXTURE2, chair_tex, sp);
	table.draw(3, GL_TEXTURE3, table_tex, sp);
	armchair.draw(4, GL_TEXTURE4, armchair_tex, sp);
	cupboard.draw(5, GL_TEXTURE5, cupboard_tex, sp);
	bed.draw(6, GL_TEXTURE6, bed_tex, sp);
	vase.draw(7, GL_TEXTURE7, vase_tex, sp);
	lamp.draw(8, GL_TEXTURE8, lamp_tex, sp);
	lamp2.draw(9, GL_TEXTURE9, lamp_tex, sp);
	carpet.draw(10, GL_TEXTURE10, carpet_tex, sp);

	//Rysowanie kostki (głosnika)
	glm::mat4 M4 = M; 
	M4 = glm::translate(M4, glm::vec3(-7.6f, -1.0f, 3.8f));
	M4 = glm::rotate(M4, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	M4 = glm::rotate(M4, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	M4 = glm::scale(M4, glm::vec3(0.75f, 0.75f, 2.0f));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M4));
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myCubeVertices);

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, myCubeNormals);

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, myCubeTexCoords);

	glUniform1i(sp->u("textureMap0"), 11);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, soundbar_tex);

	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));

	//Rysowanie czajnika
	glm::mat4 M6 = table.M; 
	M6 = glm::translate(M6, glm::vec3(0.0f, 0.0f, 0.4f));
	M6 = glm::rotate(M6, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	M6 = glm::scale(M6, glm::vec3(0.15f, .15f, .15f));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M6));
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myTeapotVertices);

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, myTeapotNormals);

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, myTeapotTexCoords);

	glUniform1i(sp->u("textureMap0"), 12);
	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_2D, walls_tex);

	glDrawArrays(GL_TRIANGLES, 0, myTeapotVertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));

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

	window = glfwCreateWindow(1000, 1000, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

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
		//setCamera();
		camera_z += speed_z * glfwGetTime();
		glfwSetTime(0); //Wyzeruj licznik czasu
		drawScene(window); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
