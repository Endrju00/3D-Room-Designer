//#version 330
//
//
//uniform sampler2D tex;
//
//out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela
//
////Zmienne interpolowane
//in vec2 i_tc;
//
//void main(void) {
//	pixelColor=texture(tex,i_tc);
//}
//
#version 330

uniform sampler2D textureMap0;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 ic; 
in vec4 n;
in vec4 l;
in vec4 v;
in vec2 iTexCoord0;

void main(void) {

	//Znormalizowane interpolowane wektory
	vec4 ml = normalize(l);
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);
	//Wektor odbity
	vec4 mr = reflect(-ml, mn);

	//Parametry powierzchni
	vec4 kd = texture(textureMap0, iTexCoord0);
	vec4 ks = kd;

	//Obliczenie modelu oświetlenia
	float nl = clamp(dot(mn, ml), 0.2, 0.4);
	float rv = pow(clamp(dot(mr, mv), 0, 1), 2);
	pixelColor= vec4(kd.rgb * nl, kd.a) + vec4(ks.rgb*rv, 0);
}
