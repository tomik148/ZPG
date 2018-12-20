#version 330

in vec3 colour;

in vec3 normal;
in vec3 WordNormal;
in vec3 lightPos;
in vec3 cameraPos;
in vec2 txC;

in vec3 worldPos;

uniform sampler2D texture_diffuse0;

out vec4 frag_colour;

void main () {
	

	vec3 vecToLight = normalize(lightPos - worldPos);
	vec3 vecToCamera = normalize(cameraPos - worldPos);


    frag_colour = 0.05 * texture(texture_diffuse0,txC);
	
	float dif = max(dot(normalize(vecToLight),normalize(WordNormal)),0) ;
	float spec = pow(max(dot(vecToCamera,reflect(-vecToLight,WordNormal)),0),10); 
	
	frag_colour += texture(texture_diffuse0,txC) * ( dif );
	frag_colour += vec4 (1,1,1,1) * ( spec );
	
}
