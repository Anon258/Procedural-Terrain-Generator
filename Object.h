#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <iostream>

//Class to draw rectangle
class rectangle {
public:
	unsigned int length, breadth;

rectangle(unsigned int l, unsigned int b) {
    length = l;
    breadth = b;
}

//Make vertex and elementary buffer objects
void BufferObjects(float vertices[], unsigned int indices[]) {
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void DrawRectangle() {
    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };
    for (unsigned int i = 0; i < length; i++) {
        for (unsigned int j = 0; j < breadth; j++) {
            //Defining vertices of each 1*1 square
            float vertices[12] = {
                -length / 2 + i + 1, breadth / 2 - j, 0.0f,
                -length / 2 + i + 1, breadth / 2 - j - 1, 0.0f,
                -length / 2 + i, breadth / 2 - j - 1, 0.0f,
                -length / 2 + i, breadth / 2 - j, 0.0f
            };
            BufferObjects(vertices, indices);
        }
    }
}
};

class cube {
    unsigned int length, breadth, height, VBO, VAO;
    unsigned int ncubes;
    shader cshader("object.vs", "object.fs");
    cube(unsigned int l, unsigned int b, unsigned int h) {
        length = l;
        breadth = b;
        height = h;
        ncubes = length * breadth * height;
        BufferObjects();
    }
    glm::vec3* cubepos = new glm::vec3[ncubes];//Array containing centers of all 1*1*1 cubes

    void BufferObjects() {
        float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        };
        unsigned int x = 0;
        for (unsigned int i = 0; i < length; i++) {
            for (unsigned int j = 0; j < breadth;j++) {
                for (unsigned int k = 0; k < height;k++) {
                    cubepos[x] = glm::vec3(length / 2 - 0.5f - i, breadth / 2 - 0.5f - j, height/2-0.5f-k);
                    x++;
                }
            }
        }
        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void DrawCube() {
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubepos[i]);
            cshader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
};