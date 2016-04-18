#version 120

uniform float fade;

void main(void) {       
	gl_FragColor[0] = 0.6; 
	gl_FragColor[1] = 0.69; 
	gl_FragColor[2] = 1.0; 
	gl_FragColor[3] = fade;
}