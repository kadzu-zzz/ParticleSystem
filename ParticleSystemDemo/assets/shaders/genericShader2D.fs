#version 330
//The fragment shader operates on each pixel in a given polygon

in vec3 fragmentPosition;
in vec4 fragmentColour;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

uniform bool lineMode;
uniform sampler2D sample;

void main() {
    vec4 textureColour = texture(sample, fragmentUV);
    
    color = fragmentColour * textureColour;
	
	if(lineMode)
		color = fragmentColour;
}