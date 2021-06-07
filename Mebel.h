#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shaderprogram.h"
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

	void set(glm::mat4 matrix, glm::vec3 t, glm::vec3 s, glm::vec3 r=glm::vec3(1.0f, 0.0f, 0.0f), float angle=0.0f) {
		M = matrix;
		M = glm::translate(M, t);
		M = glm::rotate(M, glm::radians(angle), r);
		M = glm::scale(M, s);
	}

	void draw(int index, int gl_texture, GLuint tex, ShaderProgram* sp) {
		sp->use();
		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
		glEnableVertexAttribArray(sp->a("vertex"));
		glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts.data());

		glEnableVertexAttribArray(sp->a("normal"));
		glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, norms.data());

		glEnableVertexAttribArray(sp->a("texCoord0"));
		glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords.data());

		glUniform1i(sp->u("textureMap0"), index);
		glActiveTexture(gl_texture);
		glBindTexture(GL_TEXTURE_2D, tex);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

		glDisableVertexAttribArray(sp->a("vertex"));
		glDisableVertexAttribArray(sp->a("normal"));
		glDisableVertexAttribArray(sp->a("texCoord0"));
	}
};