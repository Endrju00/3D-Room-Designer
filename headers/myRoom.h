#ifndef MYROOM_H_INCLUDED
#define MYROOM_H_INCLUDED

int myRoomVertexCount = 24;
float length = 9, width = 5, height = 3;


float myRoomVertices[] = {
	//            //�ciana 1
				//length, -height,-width,1.0f,
				//-length, height,-width,1.0f,
				//-length, -height,-width,1.0f,

				//length,-height,-width,1.0f,
				//length, height,-width,1.0f,
				//-length, height,-width,1.0f,

				//�ciana 2 tylnia
				-length,-height, width,1.0f,
				length, height, width,1.0f,
				length,-height, width,1.0f,

				-length,-height, width,1.0f,
				-length, height, width,1.0f,
				length, height, width,1.0f,


				//�ciana 3 dolna
			/*	-length,-height,-width,1.0f,
				length,-height, width,1.0f,
				length,-height,-width,1.0f,

				-length,-height,-width,1.0f,
				-length,-height, width,1.0f,
				length,-height, width,1.0f,*/

				////�ciana 4 g�rna
				//-length, height, width,1.0f,
				//length, height,-width,1.0f,
				//length, height, width,1.0f,

				//-length, height, width,1.0f,
				//-length, height,-width,1.0f,
				//length, height,-width,1.0f,

				//�ciana 5 prawa
				-length,-height,-width,1.0f,
				-length, height, width,1.0f,
				-length,-height, width,1.0f,

				-length,-height,-width,1.0f,
				-length, height,-width,1.0f,
				-length, height, width,1.0f,

				//�ciana 6 lewa
				length,-height, width,1.0f,
				length, height,-width,1.0f,
				length,-height,-width,1.0f,

				length,-height, width,1.0f,
				length, height, width,1.0f,
				length, height,-width,1.0f,
};


float myWallsVertices[] = {

				//�ciana 2 tylnia
				-length,-height, width,1.0f,
				length, height, width,1.0f,
				length,-height, width,1.0f,

				-length,-height, width,1.0f,
				-length, height, width,1.0f,
				length, height, width,1.0f,

				//�ciana 5 prawa
				-length,-height,-width,1.0f,
				-length, height, width,1.0f,
				-length,-height, width,1.0f,

				-length,-height,-width,1.0f,
				-length, height,-width,1.0f,
				-length, height, width,1.0f,

				//�ciana 6 lewa
				length,-height, width,1.0f,
				length, height,-width,1.0f,
				length,-height,-width,1.0f,

				length,-height, width,1.0f,
				length, height, width,1.0f,
				length, height,-width,1.0f,
};

float myFloorVertices[] = {

				//�ciana 3 dolna
				-length,-height,-width,1.0f,
				length,-height, width,1.0f,
				length,-height,-width,1.0f,

				-length,-height,-width,1.0f,
				-length,-height, width,1.0f,
				length,-height, width,1.0f,
};


float myRoomColors[] = {
	//�ciana tylnia
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,

	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,

	//pod�oga
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,

	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,

	//�ciana prawa
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,

	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,

	//�ciana lewa
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,

	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,

	////�ciana 5
	//0.0f,1.0f,1.0f,1.0f,
	//0.0f,1.0f,1.0f,1.0f,
	//0.0f,1.0f,1.0f,1.0f,

	//0.0f,1.0f,1.0f,1.0f,
	//0.0f,1.0f,1.0f,1.0f,
	//0.0f,1.0f,1.0f,1.0f,

	////�ciana 6
	//1.0f,1.0f,1.0f,1.0f,
	//1.0f,1.0f,1.0f,1.0f,
	//1.0f,1.0f,1.0f,1.0f,

	//1.0f,1.0f,1.0f,1.0f,
	//1.0f,1.0f,1.0f,1.0f,
	//1.0f,1.0f,1.0f,1.0f,
};


float myRoomTexCoords[] = {
	//�ciana 1
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//�ciana 2
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//�ciana 3
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//�ciana 4
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//�ciana 5
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//�ciana 6
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
};

float myWallsTexCoords[] = {

	////�ciana 2
	//1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	//1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	////�ciana 5
	//1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	//1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	////�ciana 6
	//1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	//1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
		  1.0f, 0.0f,	//A
	  0.0f, 1.0f,    //B
	  0.0f, 0.0f,    //C

	  1.0f, 0.0f,    //A
	  1.0f, 1.0f,    //D
	  0.0f, 1.0f,    //B

	  1.0f, 0.0f,	//A
	  0.0f, 1.0f,    //B
	  0.0f, 0.0f,    //C

	  1.0f, 0.0f,    //A
	  1.0f, 1.0f,    //D
	  0.0f, 1.0f,    //B

	  1.0f, 0.0f,	//A
	  0.0f, 1.0f,    //B
	  0.0f, 0.0f,    //C

	  1.0f, 0.0f,    //A
	  1.0f, 1.0f,    //D
	  0.0f, 1.0f,    //B

};

float myFloorTexCoords[] = {

	////�ciana 3
	//1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	//1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
		1.0f, 0.0f,	//A
	  0.0f, 1.0f,    //B
	  0.0f, 0.0f,    //C

	  1.0f, 0.0f,    //A
	  1.0f, 1.0f,    //D
	  0.0f, 1.0f,    //B

	
};

float myRoomVertexNormals[] = {
	//�ciana 1
		1.0f,-1.0f,-1.0f,0.0f,
		-1.0f, 1.0f,-1.0f,0.0f,
		-1.0f,-1.0f,-1.0f,0.0f,

			1.0f,-1.0f,-1.0f,0.0f,
		1.0f, 1.0f,-1.0f,0.0f,
		-1.0f, 1.0f,-1.0f,0.0f,

		//�ciana 2
		-1.0f,-1.0f, 1.0f,0.0f,
		1.0f, 1.0f, 1.0f,0.0f,
		1.0f,-1.0f, 1.0f,0.0f,

		-1.0f,-1.0f, 1.0f,0.0f,
		-1.0f, 1.0f, 1.0f,0.0f,
		1.0f, 1.0f, 1.0f,0.0f,

		//�ciana 3
		-1.0f,-1.0f,-1.0f,0.0f,
		1.0f,-1.0f, 1.0f,0.0f,
		1.0f,-1.0f,-1.0f,0.0f,

		-1.0f,-1.0f,-1.0f,0.0f,
		-1.0f,-1.0f, 1.0f,0.0f,
		1.0f,-1.0f, 1.0f,0.0f,

		//�ciana 4
	   -1.0f, 1.0f, 1.0f,0.0f,
	   1.0f, 1.0f,-1.0f,0.0f,
	   1.0f, 1.0f, 1.0f,0.0f,

	   -1.0f, 1.0f, 1.0f,0.0f,
	   -1.0f, 1.0f,-1.0f,0.0f,
	   1.0f, 1.0f,-1.0f,0.0f,

	   //�ciana 5
	  -1.0f,-1.0f,-1.0f,0.0f,
	  -1.0f, 1.0f, 1.0f,0.0f,
	  -1.0f,-1.0f, 1.0f,0.0f,

	  -1.0f,-1.0f,-1.0f,0.0f,
	  -1.0f, 1.0f,-1.0f,0.0f,
	  -1.0f, 1.0f, 1.0f,0.0f,

	  //�ciana 6
	 1.0f,-1.0f, 1.0f,0.0f,
	 1.0f, 1.0f,-1.0f,0.0f,
	 1.0f,-1.0f,-1.0f,0.0f,

	 1.0f,-1.0f, 1.0f,0.0f,
	 1.0f, 1.0f, 1.0f,0.0f,
	 1.0f, 1.0f,-1.0f,0.0f,
};

//float myWallsVertexNormals[] = {
//
//	//�ciana 2
//		-1.0f,-1.0f, 1.0f,0.0f,
//		1.0f, 1.0f, 1.0f,0.0f,
//		1.0f,-1.0f, 1.0f,0.0f,
//
//		-1.0f,-1.0f, 1.0f,0.0f,
//		-1.0f, 1.0f, 1.0f,0.0f,
//		1.0f, 1.0f, 1.0f,0.0f,
//		
//		//�ciana 5
//	  -1.0f,-1.0f,-1.0f,0.0f,
//	  -1.0f, 1.0f, 1.0f,0.0f,
//	  -1.0f,-1.0f, 1.0f,0.0f,
//
//	  -1.0f,-1.0f,-1.0f,0.0f,
//	  -1.0f, 1.0f,-1.0f,0.0f,
//	  -1.0f, 1.0f, 1.0f,0.0f,
//
//	  //�ciana 6
//	 1.0f,-1.0f, 1.0f,0.0f,
//	 1.0f, 1.0f,-1.0f,0.0f,
//	 1.0f,-1.0f,-1.0f,0.0f,
//
//	 1.0f,-1.0f, 1.0f,0.0f,
//	 1.0f, 1.0f, 1.0f,0.0f,
//	 1.0f, 1.0f,-1.0f,0.0f,
//};

float myWallsVertexNormals[] = {

	//�ciana 2
		1.0f,1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,0.0f,
		-1.0f,1.0f, -1.0f,0.0f,

		1.0f,1.0f, -1.0f,0.0f,
		1.0f, -1.0f, -1.0f,0.0f,
		-1.0f, -1.0f, -1.0f,0.0f,

		//�ciana 5
	  1.0f,1.0f,1.0f,0.0f,
	  1.0f, -1.0f, -1.0f,0.0f,
	  1.0f,1.0f, -1.0f,0.0f,

	  1.0f,1.0f,1.0f,0.0f,
	  1.0f, -1.0f,1.0f,0.0f,
	  1.0f, -1.0f, -1.0f,0.0f,

	  //�ciana 6
	 -1.0f,1.0f, -1.0f,0.0f,
	 -1.0f, -1.0f,1.0f,0.0f,
	 -1.0f,1.0f,1.0f,0.0f,

	-1.0f,1.0f, -1.0f,0.0f,
	 -1.0f, -1.0f, -1.0f,0.0f,
	 -1.0f, -1.0f,1.0f,0.0f,
};

float myFloorVertexNormals[] = {

	//�ciana 3
	1.0f,1.0f,1.0f,0.0f,
	-1.0f,1.0f, -1.0f,0.0f,
	-1.0f,1.0f,1.0f,0.0f,

	1.0f,1.0f,1.0f,0.0f,
	1.0f,1.0f, -1.0f,0.0f,
	-1.0f,1.0f, -1.0f,0.0f,
};

void drawWalls(glm::mat4 matrix, int index, int gl_texture, GLuint tex, ShaderProgram* sp) {
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(matrix));
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myRoomVertices);

	glEnableVertexAttribArray(sp->a("color"));
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, myRoomColors);

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, myWallsVertexNormals);

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, myRoomTexCoords);

	glUniform1i(sp->u("textureMap0"), index);
	glActiveTexture(gl_texture);
	glBindTexture(GL_TEXTURE_2D, tex);


	glDrawArrays(GL_TRIANGLES, 0, myRoomVertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("color"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));
};

void drawFloor(glm::mat4 matrix, int index, int gl_texture, GLuint tex, ShaderProgram* sp) {
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(matrix));
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myFloorVertices);

	glEnableVertexAttribArray(sp->a("color"));
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, myRoomColors);

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, myFloorVertexNormals);

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, myRoomTexCoords);

	glUniform1i(sp->u("textureMap0"), index);
	glActiveTexture(gl_texture);
	glBindTexture(GL_TEXTURE_2D, tex);

	glDrawArrays(GL_TRIANGLES, 0, myRoomVertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("color"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));
};

#endif // MYCUBE_H_INCLUDED

