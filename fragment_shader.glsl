#version 330

uniform sampler2D textureMap0;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 ic; 

in vec4 n1;
in vec4 l1;
in vec4 v1;

in vec4 n2;
in vec4 l2;
in vec4 v2;

in vec2 iTexCoord0;

void main(void) {

	//Znormalizowane interpolowane wektory 1
	vec4 ml1 = normalize(l1);
	vec4 mn1 = normalize(n1);
	vec4 mv1 = normalize(v1);

	//Wektor odbity 1
	vec4 mr1 = reflect(-ml1, mn1);

	//Obliczenie modelu oœwietlenia 1
	float nl1 = clamp(dot(mn1, ml1), 0.2, 0.4);
	float rv1 = pow(clamp(dot(mr1, mv1), 0, 1), 2);

	//Znormalizowane interpolowane wektory 2
	vec4 ml2 = normalize(l2);
	vec4 mn2 = normalize(n2);
	vec4 mv2 = normalize(v2);

	//Wektor odbity 2
	vec4 mr2 = reflect(-ml2, mn2);

	//Obliczenie modelu oœwietlenia 2
	float nl2 = clamp(dot(mn2, ml2), 0.2, 0.4);
	float rv2 = pow(clamp(dot(mr2, mv2), 0, 1), 2);

	//Parametry powierzchni 
	vec4 kd = texture(textureMap0, iTexCoord0);
	vec4 ks = kd;

	//Suma dwoch zrodel
	pixelColor= vec4(kd.rgb * nl1, kd.a) + vec4(ks.rgb*rv1, 0) + vec4(kd.rgb * nl2, kd.a) + vec4(ks.rgb*rv2, 0);
}
