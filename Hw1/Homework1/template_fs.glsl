#version 430

uniform sampler2D diffuse_color;

out vec4 fragcolor;
in vec4 colour;//in variable for vertex shader
out vec3 normalO;

layout(location=4) in vec2 tex_coord;
layout(location=5) uniform float time;


in vec3 FragPos;  
in vec3 normal;  

void main(void)
{
   vec3 lightPos=vec3(10.0f, 10.0f, 5.0f);
   vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
   float ambientStrong = 0.1f;
   vec3 ambient = ambientStrong * lightColor;///need this

   vec3 norm = normalize(normal);
   vec3 lightDirection = normalize(lightPos - FragPos);
   float diff = max(dot(norm, lightDirection), 0.0f);

   vec3 diffuse = diff * lightColor;
   vec3 result = (diffuse + ambient) * vec3(colour);
   normalO = norm;

   fragcolor = vec4(result, 1.0f);

     //fragcolor=colour;
     //fragcolor.rg=tex_coord;
    
	//fragcolor = texture(diffuse_color, tex_coord);
    //fragcolor = vec4(1.0,0.0,0.0,1.0);
  
    
}




















