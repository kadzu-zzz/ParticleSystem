#version 330
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec3 vertexPosition;
in vec2 vertexUV;
in vec4 vertexColour;

out vec3 fragmentPosition;
out vec4 fragmentColour;
out vec2 fragmentUV;

uniform mat4 P;

void main() {
    //Set the x,y position on the screen
    gl_Position = (P * vec4(vertexPosition, 1.0));
   
    gl_Position.w = 1.0;
    //Indicate that the coordinates are normalized
    
    fragmentPosition = vertexPosition;
    
    fragmentColour = vertexColour;
    
    fragmentUV = vec2(vertexUV.x, vertexUV.y);
}