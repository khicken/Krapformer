#ifndef OBJECT_H
#define OBJECT_H

#include "Main.h"
   
class Object {
public:
    const char* src;
    float borderColor[4];
    float *vertices;
    unsigned int VBO, VAO;
    unsigned int texture;

    Object(float *v, const char* s) {
        vertices = v;
        src = s;
    }

    void init() {
        loadBuffers();
        loadTexture();
    }

    void bind() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
    }

    void destroy() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        // glDeleteBuffers(1, &EBO);
    }
private:
    
    void loadBuffers() {
        // create and load buffer and array objects to shade
        glGenVertexArrays(1, &VAO); // only generating 1 VAO
        glGenBuffers(1, &VBO); // generate 1 VBO
        // glGenBuffers(1, &EBO); // generate 1 EBO

        glBindVertexArray(VAO); // bind the vao first
        glBindBuffer(GL_ARRAY_BUFFER, VBO); // then load to the just binded array(vbo -> vao)
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // setup draw for whatever vbo has to vao

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // glBindBuffers() is stored in element array buffers as it is required; so vao should be unbinded first later
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // setup draw for whatever ebo has to vao

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0); // using 3's for (x, y, z); sets how the vertices should be handled
        glEnableVertexAttribArray(0); // disable vao
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float))); // map color coords from array
        // glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float))); // map texture coords from array
        glEnableVertexAttribArray(1);

        // glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO, but KEEPING ebo binded, as vao is still using ebo
        // glBindVertexArray(0); // unbind vao
    }

    void loadTexture() {
        glGenTextures(1, &texture);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(src, &width, &height, &nrChannels, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // just in case if width and height return segmentation fault
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

        if(data != nullptr) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "image broke" << std::endl;
        }
        
        stbi_image_free(data);
    }
};

#endif