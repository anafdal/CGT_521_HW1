#version 430

uniform sampler2D diffuse_color;

out vec4 fragcolor;

layout(location=0) in vec2 tex_coord;
layout(location=1) uniform float time;
      
void main(void)
{
    
    
    //fragcolor.r=sin(time);

	//fragcolor = texture(diffuse_color, tex_coord);

    fragcolor = vec4(1.0,0.0,0.0,1.0);

   // if(gl_FragCoord.x>600.0)
   // {
   //  fragcolor = vec4(1.0,0.0,0.0,1.0);
   // }
    
}




















