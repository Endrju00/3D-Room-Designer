#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using namespace std;

class Mebel {
public: 
	string name;
	vector<glm::vec4> verts;
	vector<glm::vec4> norms;
	vector<glm::vec2> texCoords;
	vector<unsigned int> indices;
	glm::mat4 M = glm::mat4(1.0f);
	float factor;

	void loadModel() {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(name, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
		cout << importer.GetErrorString() << endl;

		aiMesh* mesh = scene->mMeshes[0];

		for (int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D vertex = mesh->mVertices[i];
			verts.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

			aiVector3D normal = mesh->mNormals[i];
			norms.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

			aiVector3D texCoord = mesh->mTextureCoords[0][i];
			texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));
		}

		for (int i = 0; i < mesh->mNumFaces; i++) {
			aiFace& face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	}

	Mebel(string path, glm::mat4 matrice, float f) {
		name = path;
		this->loadModel();
		M = matrice;
		factor = f;
	}

	Mebel() {}
	
	void rotateModel() {
		M = glm::rotate(M, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void moveLeft() {
		M = glm::translate(M, glm::vec3(-1.0f/factor, 0.0f, 0.0f));
	}
	void moveRight() {
		M = glm::translate(M, glm::vec3(1.0f/factor, 0.0f, 0.0f));
	}
	void moveForward() {
		M = glm::translate(M, glm::vec3(0.0f, 0.0f, -1.0f/factor));
	}
	void moveBackward() {
		M = glm::translate(M, glm::vec3(0.0f, 0.0f, 1.0f/factor));
	}
};