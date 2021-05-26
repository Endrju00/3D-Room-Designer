#ifndef MYROOM_H_INCLUDED
#define MYROOM_H_INCLUDED

int myRoomVertexCount = 24;
float length = 7, width = 5, height = 3;


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
				-length,-height,-width,1.0f,
				length,-height, width,1.0f,
				length,-height,-width,1.0f,

				-length,-height,-width,1.0f,
				-length,-height, width,1.0f,
				length,-height, width,1.0f,

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





#endif // MYCUBE_H_INCLUDED

