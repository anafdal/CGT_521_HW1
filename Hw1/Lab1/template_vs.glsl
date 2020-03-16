#version 430            


//in vec3 pos_attrib;
//in vec2 tex_coord_attrib;
//in vec3 normal_attrib;

layout(location=0) in vec3 pos_attrib;
layout(location=1) in vec2 tex_coord_attrib;
layout(location=2) in vec3 normal_attrib;
layout(location=3) uniform mat4 PVM;

out vec2 tex_coord;  

void main(void)
{

   gl_Position = PVM*vec4(pos_attrib, 1.0);
   tex_coord = tex_coord_attrib;

 
}
