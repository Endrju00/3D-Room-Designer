#ifndef MYROOM_H_INCLUDED
#define MYROOM_H_INCLUDED

int myRoomVertexCount = 24;
float length = 8, width = 5, height = 2;


float myRoomVertices[] = {
	//            //œciana 1
				//length, -height,-width,1.0f,
				//-length, height,-width,1.0f,
				//-length, -height,-width,1.0f,

				//length,-height,-width,1.0f,
				//length, height,-width,1.0f,
				//-length, height,-width,1.0f,

				//œciana 2 tylnia
				-length,-height, width,1.0f,
				length, height, width,1.0f,
				length,-height, width,1.0f,

				-length,-height, width,1.0f,
				-length, height, width,1.0f,
				length, height, width,1.0f,


				//œciana 3 dolna
			/*	-length,-height,-width,1.0f,
				length,-height, width,1.0f,
				length,-height,-width,1.0f,

				-length,-height,-width,1.0f,
				-length,-height, width,1.0f,
				length,-height, width,1.0f,*/

				////œciana 4 górna
				//-length, height, width,1.0f,
				//length, height,-width,1.0f,
				//length, height, width,1.0f,

				//-length, height, width,1.0f,
				//-length, height,-width,1.0f,
				//length, height,-width,1.0f,

				//œciana 5 prawa
				-length,-height,-width,1.0f,
				-length, height, width,1.0f,
				-length,-height, width,1.0f,

				-length,-height,-width,1.0f,
				-length, height,-width,1.0f,
				-length, height, width,1.0f,

				//œciana 6 lewa
				length,-height, width,1.0f,
				length, height,-width,1.0f,
				length,-height,-width,1.0f,

				length,-height, width,1.0f,
				length, height, width,1.0f,
				length, height,-width,1.0f,
};


float myWallsVertices[] = {

				//œciana 2 tylnia
				-length,-height, width,1.0f,
				length, height, width,1.0f,
				length,-height, width,1.0f,

				-length,-height, width,1.0f,
				-length, height, width,1.0f,
				length, height, width,1.0f,

				//œciana 5 prawa
				-length,-height,-width,1.0f,
				-length, height, width,1.0f,
				-length,-height, width,1.0f,

				-length,-height,-width,1.0f,
				-length, height,-width,1.0f,
				-length, height, width,1.0f,

				//œciana 6 lewa
				length,-height, width,1.0f,
				length, height,-width,1.0f,
				length,-height,-width,1.0f,

				length,-height, width,1.0f,
				length, height, width,1.0f,
				length, height,-width,1.0f,
};

float myFloorVertices[] = {

				//œciana 3 dolna
				-length,-height,-width,1.0f,
				length,-height, width,1.0f,
				length,-height,-width,1.0f,

				-length,-height,-width,1.0f,
				-length,-height, width,1.0f,
				length,-height, width,1.0f,
};


float myRoomColors[] = {
	//œciana tylnia
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,

	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,

	//pod³oga
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,

	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,

	//œciana prawa
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,

	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,

	//œciana lewa
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,

	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,

	////œciana 5
	//0.0f,1.0f,1.0f,1.0f,
	//0.0f,1.0f,1.0f,1.0f,
	//0.0f,1.0f,1.0f,1.0f,

	//0.0f,1.0f,1.0f,1.0f,
	//0.0f,1.0f,1.0f,1.0f,
	//0.0f,1.0f,1.0f,1.0f,

	////œciana 6
	//1.0f,1.0f,1.0f,1.0f,
	//1.0f,1.0f,1.0f,1.0f,
	//1.0f,1.0f,1.0f,1.0f,

	//1.0f,1.0f,1.0f,1.0f,
	//1.0f,1.0f,1.0f,1.0f,
	//1.0f,1.0f,1.0f,1.0f,
};


float myRoomTexCoords[] = {
	//Œciana 1
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//Œciana 2
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//Œciana 3
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//Œciana 4
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//Œciana 5
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//Œciana 6
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
};

float myWallsTexCoords[] = {

	////Œciana 2
	//1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	//1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	////Œciana 5
	//1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	//1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	////Œciana 6
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

	////Œciana 3
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
	//Œciana 1
		1.0f,-1.0f,-1.0f,0.0f,
		-1.0f, 1.0f,-1.0f,0.0f,
		-1.0f,-1.0f,-1.0f,0.0f,

			1.0f,-1.0f,-1.0f,0.0f,
		1.0f, 1.0f,-1.0f,0.0f,
		-1.0f, 1.0f,-1.0f,0.0f,

		//Œciana 2
		-1.0f,-1.0f, 1.0f,0.0f,
		1.0f, 1.0f, 1.0f,0.0f,
		1.0f,-1.0f, 1.0f,0.0f,

		-1.0f,-1.0f, 1.0f,0.0f,
		-1.0f, 1.0f, 1.0f,0.0f,
		1.0f, 1.0f, 1.0f,0.0f,

		//Œciana 3
		-1.0f,-1.0f,-1.0f,0.0f,
		1.0f,-1.0f, 1.0f,0.0f,
		1.0f,-1.0f,-1.0f,0.0f,

		-1.0f,-1.0f,-1.0f,0.0f,
		-1.0f,-1.0f, 1.0f,0.0f,
		1.0f,-1.0f, 1.0f,0.0f,

		//Œciana 4
	   -1.0f, 1.0f, 1.0f,0.0f,
	   1.0f, 1.0f,-1.0f,0.0f,
	   1.0f, 1.0f, 1.0f,0.0f,

	   -1.0f, 1.0f, 1.0f,0.0f,
	   -1.0f, 1.0f,-1.0f,0.0f,
	   1.0f, 1.0f,-1.0f,0.0f,

	   //Œciana 5
	  -1.0f,-1.0f,-1.0f,0.0f,
	  -1.0f, 1.0f, 1.0f,0.0f,
	  -1.0f,-1.0f, 1.0f,0.0f,

	  -1.0f,-1.0f,-1.0f,0.0f,
	  -1.0f, 1.0f,-1.0f,0.0f,
	  -1.0f, 1.0f, 1.0f,0.0f,

	  //Œciana 6
	 1.0f,-1.0f, 1.0f,0.0f,
	 1.0f, 1.0f,-1.0f,0.0f,
	 1.0f,-1.0f,-1.0f,0.0f,

	 1.0f,-1.0f, 1.0f,0.0f,
	 1.0f, 1.0f, 1.0f,0.0f,
	 1.0f, 1.0f,-1.0f,0.0f,
};

//float myWallsVertexNormals[] = {
//
//	//Œciana 2
//		-1.0f,-1.0f, 1.0f,0.0f,
//		1.0f, 1.0f, 1.0f,0.0f,
//		1.0f,-1.0f, 1.0f,0.0f,
//
//		-1.0f,-1.0f, 1.0f,0.0f,
//		-1.0f, 1.0f, 1.0f,0.0f,
//		1.0f, 1.0f, 1.0f,0.0f,
//		
//		//Œciana 5
//	  -1.0f,-1.0f,-1.0f,0.0f,
//	  -1.0f, 1.0f, 1.0f,0.0f,
//	  -1.0f,-1.0f, 1.0f,0.0f,
//
//	  -1.0f,-1.0f,-1.0f,0.0f,
//	  -1.0f, 1.0f,-1.0f,0.0f,
//	  -1.0f, 1.0f, 1.0f,0.0f,
//
//	  //Œciana 6
//	 1.0f,-1.0f, 1.0f,0.0f,
//	 1.0f, 1.0f,-1.0f,0.0f,
//	 1.0f,-1.0f,-1.0f,0.0f,
//
//	 1.0f,-1.0f, 1.0f,0.0f,
//	 1.0f, 1.0f, 1.0f,0.0f,
//	 1.0f, 1.0f,-1.0f,0.0f,
//};

float myWallsVertexNormals[] = {

	//Œciana 2
		1.0f,1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,0.0f,
		-1.0f,1.0f, -1.0f,0.0f,

		1.0f,1.0f, -1.0f,0.0f,
		1.0f, -1.0f, -1.0f,0.0f,
		-1.0f, -1.0f, -1.0f,0.0f,

		//Œciana 5
	  1.0f,1.0f,1.0f,0.0f,
	  1.0f, -1.0f, -1.0f,0.0f,
	  1.0f,1.0f, -1.0f,0.0f,

	  1.0f,1.0f,1.0f,0.0f,
	  1.0f, -1.0f,1.0f,0.0f,
	  1.0f, -1.0f, -1.0f,0.0f,

	  //Œciana 6
	 -1.0f,1.0f, -1.0f,0.0f,
	 -1.0f, -1.0f,1.0f,0.0f,
	 -1.0f,1.0f,1.0f,0.0f,

	-1.0f,1.0f, -1.0f,0.0f,
	 -1.0f, -1.0f, -1.0f,0.0f,
	 -1.0f, -1.0f,1.0f,0.0f,
};

float myFloorVertexNormals[] = {

	//Œciana 3
	1.0f,1.0f,1.0f,0.0f,
	-1.0f,1.0f, -1.0f,0.0f,
	-1.0f,1.0f,1.0f,0.0f,

	1.0f,1.0f,1.0f,0.0f,
	1.0f,1.0f, -1.0f,0.0f,
	-1.0f,1.0f, -1.0f,0.0f,
};

#endif // MYCUBE_H_INCLUDED

