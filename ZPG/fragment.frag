#version 330

in vec3 colour;

in vec3 normal;
in vec3 lightPos;
in vec3 cameraPos;

in vec3 worldPos;

out vec4 frag_colour;

void main () {
	
	vec3 vecToLight = normalize(lightPos - worldPos);
	vec3 vecToCamera = normalize(cameraPos - worldPos);


    frag_colour = vec4 (0,0,0,0);
	
	frag_colour += max(dot(normalize(lightPos),normalize(normal)),0) ;

	//frag_colour += pow(max(dot(vecToCamera,reflect(-vecToLight,normal)),0),10); 
	frag_colour *= vec4 (1,0,0,1) ;
	
}
