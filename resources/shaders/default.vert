#version 330 core

layout(location = 0) in vec4 vertex; // vec2 position and vec2 texCoords combined 

out vec2 TexCoords;

uniform mat4 model; 
uniform mat4 projection;

void main() 
{
    // pass the last 2 of the vec4
    TexCoords = vertex.zw; 
    gl_Position = projection * model * vec4(vertex.xy, 0, 1.0);
}