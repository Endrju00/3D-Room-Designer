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
		if (key == GLFW_KEY_W) {
			speed_z = 2 * PI;
		}
		if (key == GLFW_KEY_S) {
			speed_z = -2 * PI;
		}
		if (key == GLFW_KEY_A) {
			if (camera_set == 0) camera_set = 3; else camera_set--; setCamera();

		}
		if (key == GLFW_KEY_D) {
			if (camera_set > 2) camera_set = 0; else camera_set++; setCamera();
		}
		if (key == GLFW_KEY_R) {
			camera_set = 1; setCamera();
			
		}
		if (key == GLFW_KEY_M) {
			menu();
		}
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_W) {
			speed_z = 0;
		}
		if (key == GLFW_KEY_S) {
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

void loadModel(string plik, vector<glm::vec4> &v, vector<glm::vec4> &n, vector<glm::vec2> &t, vector<unsigned int> &ind) {
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
    //initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(1, 1, 1, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, key_callback);
	sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
	walls_tex = readTexture("textures/walls/light_bricks.png");  // wczytanie domyslnej tekstury ściany
	floor_tex = readTexture("textures/floor/light_wood.png"); // wczytanie domyslnej tekstury podłogi
	table_tex = readTexture("textures/dark_wood.png"); // wczytanie domyslnej tekstury sofy
	chair_tex = readTexture("textures/chair_tex.png"); // wczytanie domyslnej tekstury sofy
	cout << "\n************** Witaj w dekoratorze wnetrz! **************" << endl;
	info();

	//wczytywanie modeli
	loadModel(string("models/table.fbx"), verts, norms, texCoords, indices);
	loadModel(string("models/Chair.obj"), verts2, norms2, texCoords2, indices2);
	
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    /*freeShaders();*/
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
	glDeleteTextures(1, &walls_tex);
	glDeleteTextures(1, &floor_tex);
	glDeleteTextures(1, &table_tex);
	glDeleteTextures(1, &chair_tex);
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


	glm::mat4 M3 = M; // Rysowanie krzesła
	M3 = glm::translate(M3, glm::vec3(-3.0f, -1.0f, 0.0f));
	//M3 = glm::rotate(M3, glm::radians(-90.0f), glm::vec3(3.0f, 0.0f, 0.0f));
	M3 = glm::scale(M3, glm::vec3(0.06f, 0.06f, 0.06f));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M3));
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts2.data());

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, norms2.data());

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords2.data());

	glUniform1i(sp->u("textureMap0"), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, chair_tex);

	glDrawElements(GL_TRIANGLES, indices2.size(), GL_UNSIGNED_INT, indices2.data());

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));

	
	glm::mat4 M4 = M; // Rysowanie kostki
	M4 = glm::translate(M4, glm::vec3(-5.0f, 0.0f, 0.0f));
	M4 = glm::rotate(M4, glm::radians(-90.0f), glm::vec3(3.0f, 0.0f, 0.0f));
	M4 = glm::scale(M4, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M4));
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myCubeVertices);

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, myCubeNormals);

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, myCubeTexCoords);

	glUniform1i(sp->u("textureMap0"), 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, table_tex);

	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));

	glm::mat4 M5 = M; // Rysowanie stolika
	M5 = glm::translate(M5, glm::vec3(0.0f, -1.0f, 0.0f));
	M5 = glm::rotate(M5, glm::radians(-90.0f), glm::vec3(3.0f, 0.0f, 0.0f));
	M5 = glm::scale(M5, glm::vec3(2.0f, 2.0f, 2.0f));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M5));
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts.data());

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, norms.data());

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords.data());

	glUniform1i(sp->u("textureMap0"), 4);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, table_tex);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

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

	glDeleteTextures(1, &walls_tex);
	glDeleteTextures(1, &floor_tex);

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
