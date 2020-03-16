#include <vector>
#include <glm/glm.hpp>
#include "Surf.h"
#include "include\GL\Surf.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

static const int N = 50;
static const int NUM_VERTICES = N * N;

//The sinc surface
static glm::vec3 surf(int i, int j)
{
    const float center = 0.5f * N;
    const float xy_scale = 20.0f / N;
    const float z_scale = 10.0f;

    float x = xy_scale * (i - center);
    float y = xy_scale * (j - center);

    float r = sqrt(x * x + y * y);
    float z = 1.0f;

    if (r != 0.0f)
    {
        z = sin(r) / r;
    }
    z = z * z_scale;

    return 0.05f * glm::vec3(x, y, z);
}

//Sinc surface normals
static glm::vec3 normal(int i, int j)
{
    glm::vec3 du = surf(i + 1, j) - surf(i - 1, j);
    glm::vec3 dv = surf(i, j + 1) - surf(i, j - 1);
    return glm::normalize(glm::cross(du, dv));//these are normal vectors


}


GLuint create_surf_vbo()
{
    //Declare a vector to hold N*N vertices
    std::vector<glm::vec3> surf_verts;
    surf_verts.reserve(NUM_VERTICES);

    std::vector<glm::vec3> surf_norm;//normal vectors
    surf_norm.reserve(NUM_VERTICES);

    std::vector<glm::vec2> surf_tex;//normal vectors
    surf_tex.reserve(NUM_VERTICES);

    std::vector<glm::vec3> data;
   
       for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                
                //data.push_back(surf(i, j));//so these are position vectors
                //data.push_back(normal(i, j));//normal vectors

                data.push_back(surf(i, j));//so these are position vectors
                data.push_back(normal(i, j));//normal vectors

                //surf_tex.push_back(glm::vec2(float(i) / (N - 1), float(j) / (N - 1)));//texture

                //data.push_back(glm::vec3(float(i) / (N - 1), float(j) / (N - 1),float(0.0f)));//texture
                data.push_back(glm::vec3((glm::vec2(0.5f, 0.2f)), 0.0f));//texture
               
            }
        }

       GLuint vbo;
       glGenBuffers(1, &vbo); //Generate vbo to hold vertex attributes for triangle.
       glBindBuffer(GL_ARRAY_BUFFER, vbo); //Specify the buffer where vertex attribute data is stored.

       glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);


       //Upload from main memory to gpu memory.
       //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * surf_verts.size() + sizeof(glm::vec3) * surf_norm.size() + sizeof(glm::vec2) * surf_tex.size(),0, GL_STATIC_DRAW);//all


     /*  struct  pVertex {
           glm::vec3 surf_verts;
           glm::vec3 surf_norm;
           glm::vec2 surf_tex;

       };*/

    
    //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * surf_verts.size(), surf_verts.data());
    //glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * surf_verts.size(), sizeof(glm::vec3) * surf_norm.size(), surf_norm.data());
    //glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * surf_norm.size(), sizeof(glm::vec2) * surf_tex.size(),surf_tex.data());
    

    return vbo;
}

std::vector<glm::vec4> getColor() {
    std::vector<glm::vec4> colors;
    colors.push_back(glm::vec4(1, 0.1, 0, 1));
    colors.push_back(glm::vec4(0, 0.5, 0.2, 1));
    colors.push_back(glm::vec4(0.6, 0.5, 0, 1));
    colors.push_back(glm::vec4(0.8, 0.8, 0, 1));
    colors.push_back(glm::vec4(0.8, 0, 0.2, 1));
    colors.push_back(glm::vec4(0.1, 0, 0.9, 1));
    colors.push_back(glm::vec4(0, 0.5, 0, 1));
    colors.push_back(glm::vec4(0.3, 0, 0.1, 1));
    colors.push_back(glm::vec4(0.3, 0.9, 0.1, 1));
    return colors;
}


GLuint create_instance_vbo() {
    //put position here and read it as an attribute and move stuff around in the shader
    //Declare a vector to hold 9 colors
    //can do smth similar to ps and norm
    //4 vertx atrrb calls
    //in shader mattrix attribute

    std::vector<glm::vec4> surf_col=getColor();
    //std::vector<glm::vec4> surf_col;
    //surf_col.reserve(9);//9 colors


    /*for (int i = 0; i <9; i++)
    {
        surf_col.push_back(glm::vec4((i / 9.0f),(0.1 * i),(0.1*i),(0.1 * i)));//loop through colors
       // surf_col.push_back(glm::vec4(1.0f,1.0f,1.0f,1.0f));//red
    }*/


    GLuint vbo;
    glGenBuffers(1, &vbo); //Generate vbo to hold vertex attributes for triangle.
    glBindBuffer(GL_ARRAY_BUFFER, vbo); //Specify the buffer where vertex attribute data is stored.



    //Upload from main memory to gpu memory.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * surf_col.size(), surf_col.data(), GL_STATIC_DRAW);//all
    //specify per instance



    //Tell opengl how to get the attribute values out of the vbo (stride and offset).
    //In this case, the vertices are at the beginning of the VBO and are tightly packed.
    int col_loc = 6;
    glEnableVertexAttribArray(col_loc);//color
    glVertexAttribPointer(col_loc, 4, GL_FLOAT, false, 4 * sizeof(float), 0);////interleaved check stride+pointer
    glVertexAttribDivisor(col_loc, 1);

    return vbo;
}

std::vector<glm::mat4> getCoordinates() {
    std::vector<glm::mat4> coordinates;

    //column one
   coordinates.push_back(glm::translate(glm::vec3(-1.0f, 1.0f, 0.0f)));
    coordinates.push_back(glm::translate(glm::vec3(-1.0f, 0.0f, 0.0f)));
    coordinates.push_back(glm::translate(glm::vec3(-1.0f, -1.0f, 0.0f)));

    //column two
    coordinates.push_back(glm::translate(glm::vec3(0.0f, 1.0f, 0.0f)));
    coordinates.push_back(glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)));
    coordinates.push_back(glm::translate(glm::vec3(0.0f, -1.0f, 0.0f)));

    //column three
    coordinates.push_back(glm::translate(glm::vec3(1.0f, 1.0f, 0.0f)));
    coordinates.push_back(glm::translate(glm::vec3(1.0f, 0.0f, 0.0f)));
    coordinates.push_back(glm::translate(glm::vec3(1.0f, -1.0f, 0.0f)));



    return coordinates;
}

GLuint create_transform_vbo() {

    std::vector<glm::mat4> mat_surf = getCoordinates();

    GLuint vbo;
    glGenBuffers(1, &vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

                                        
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * mat_surf.size(), mat_surf.data(), GL_STATIC_DRAW);

    int mat_loc = 8;//location


    int mat_loc1 = mat_loc + 0;
    int mat_loc2 = mat_loc + 1;
    int mat_loc3 = mat_loc + 2;
    int mat_loc4 = mat_loc + 3;

    glEnableVertexAttribArray(mat_loc1);
    glEnableVertexAttribArray(mat_loc2);
    glEnableVertexAttribArray(mat_loc3);
    glEnableVertexAttribArray(mat_loc4);

    // Loop over each column of the matrix...
 /*for (int i = 0; i < 4; i++) {

     // Set up the vertex attribute/////////////////////////////////////////////////////////////////////////////////////////
     glVertexAttribPointer(mat_loc + i, 3, GL_FLOAT, GL_FALSE, sizeof(mat_loc), (void*)(sizeof(mat_loc) * i)); // Start offset

     glEnableVertexAttribArray(mat_loc + i);
     // Make it instanced
     glVertexAttribDivisor(mat_loc + i, 1);

 }*/
 

    glVertexAttribPointer(mat_loc1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 0));
    glVertexAttribPointer(mat_loc2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 1));
    glVertexAttribPointer(mat_loc3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 2));
    glVertexAttribPointer(mat_loc4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * 3));

    glVertexAttribDivisor(mat_loc1, 1);
    glVertexAttribDivisor(mat_loc2, 1);
    glVertexAttribDivisor(mat_loc3, 1);
    glVertexAttribDivisor(mat_loc4, 1);
   


    return vbo;
}




GLuint create_surf_ebo() {
    //ebo stotes indixes
    GLuint ebo;//buffer for this one//////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<unsigned short int>indices;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); //Specify
    


    for (int i = 0; i < N-1; i++) {////////////////////////////////////////////////////////////////////////////////////////////////////////
        for (int j = 0; j < N; j++) {
            indices.push_back(j+i*N);
            indices.push_back(j+N+i*N);
         
        }
        indices.push_back(0xFFFF);
    }


    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short int)*indices.size(), indices.data(), GL_STATIC_DRAW);


    return ebo;
}


GLuint create_surf_vao()
{
    GLuint vao;

    //Generate vao id to hold the mapping from attrib variables in shader to memory locations in vbo
    glGenVertexArrays(1, &vao);

    //Binding vao means that bindbuffer, enablevertexattribarray and vertexattribpointer state will be remembered by vao
    glBindVertexArray(vao);

    GLuint ebo = create_surf_ebo();////////////////////////////////////////////////////////////////////////////////////////////////////////ebo&VBO

    GLuint vbo = create_surf_vbo();
    
  
    int pos_loc = 0;//pos_loc is at 0
    int norm_loc = 1;//morm_attrib is at 1
    int tex_loc = 7;//tex is at 7
   

    //glEnableVertexAttribArray(mat_loc);//mattrix instance

  
    glEnableVertexAttribArray(pos_loc); //Enable the position attribute.
    glEnableVertexAttribArray(norm_loc); //Enable normal
    glEnableVertexAttribArray(tex_loc);//texture
    

    //Tell opengl how to get the attribute values out of the vbo (stride and offset).
    //In this case, the vertices are at the beginning of the VBO and are tightly packed.

    //const float stride = 3 * sizeof(float)+3 * sizeof(float) + 2 * sizeof(float);

     //glVertexAttribPointer(pos_loc, 3, GL_FLOAT, false, 3 * sizeof(float), 0);
    //glVertexAttribPointer(norm_loc, 3, GL_FLOAT, false, 3 * sizeof(float), 0);
    //glVertexAttribPointer(tex_loc, 2, GL_FLOAT, false, 2 * sizeof(float), 0);

    const float stride = 3 * sizeof(float) + 3 * sizeof(float) + 3 * sizeof(float);
    glVertexAttribPointer(pos_loc, 3, GL_FLOAT, false, stride, (void*)0);////interleaved
    glVertexAttribPointer(norm_loc, 3, GL_FLOAT, false, stride,(void*) (3 * sizeof(float)));
    glVertexAttribPointer(tex_loc, 3, GL_FLOAT, false, stride, (void*)(2 * 3 * sizeof(float)));



    GLuint vbo3= create_transform_vbo();//matrix
    GLuint vbo4 = create_instance_vbo();///colors

    glBindVertexArray(0); //unbind the vao
    return vao;  
}

//Draw the set of points on the surface
void draw_surf(GLuint vao)
{
     glBindVertexArray(vao);
    //glDrawArrays(GL_POINTS, 0, NUM_VERTICES);
     glEnable(GL_PRIMITIVE_RESTART);///primituve restart
     glPrimitiveRestartIndex(0xFFFF);

     
    //glDrawElements(GL_TRIANGLE_STRIP, 49*50*2+50, GL_UNSIGNED_SHORT, 0);////////////////////firx this
      glDrawElementsInstanced(GL_TRIANGLE_STRIP, 49 * 50 * 2 + 50, GL_UNSIGNED_SHORT, 0,9);////////////////////firx this
     //glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 49 * 50 * 2 + 50, 9);

}











