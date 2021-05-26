#ifndef MYROOM_H_INCLUDED
#define MYROOM_H_INCLUDED

int myRoomVertexCount = 24;
float length = 7, width = 5, height = 3;


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
				-length,-height,-width,1.0f,
				length,-height, width,1.0f,
				length,-height,-width,1.0f,

				-length,-height,-width,1.0f,
				-length,-height, width,1.0f,
				length,-height, width,1.0f,

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





#endif // MYCUBE_H_INCLUDED

