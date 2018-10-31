#version 330

in vec3 colour;

in vec3 normal;
in vec3 WordNormal;
in vec3 lightPos;
in vec3 cameraPos;

in vec3 worldPos;

out vec4 frag_colour;

void main () {
	
	vec3 vecToLight = normalize(lightPos - worldPos);
	vec3 vecToCamera = normalize(cameraPos - worldPos);


    frag_colour = vec4 (0.1,0.1,0.1,1);
	
	float dif = max(dot(normalize(vecToLight),normalize(WordNormal)),0) ;
	float spec = pow(max(dot(vecToCamera,reflect(-vecToLight,WordNormal)),0),20); 
	
	frag_colour += vec4 (1,0,0,1) * ( dif );
	frag_colour += vec4 (1,1,1,1) * ( spec );
	
}
