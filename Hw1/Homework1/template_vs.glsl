#version 430            


//in vec3 pos_attrib;
//in vec2 tex_coord_attrib;
//in vec3 normal_attrib;


layout(location=0) in vec3 pos_attrib;//pos_loc
layout(location=1) in vec3 normal_attrib;//normal
layout(location=7) in vec2 tex_coord_attrib;//texture
layout(location=6) in vec4 color;//color 

layout(location=8) in mat4 model_matrix;
layout(location=3) uniform mat4 PVM;

out vec2 tex_coord;  //put out since it is going into the fragment shader
out vec4 colour;
out vec3 normal;
out vec3 FragPos;//put this here

void main(void)
{

   
   //gl_Position = PVM*vec4(pos_attrib, 1.0);
   gl_Position = PVM*model_matrix*vec4(pos_attrib, 1.0);// in the future

   tex_coord = tex_coord_attrib;////need this
   gl_PointSize=10.0;

   FragPos = vec3(model_matrix * vec4(pos_attrib, 1.0));

   colour=color;//take incoming attribute and assign it to outgoing attribute
   normal=normal_attrib;//light;
 
}
