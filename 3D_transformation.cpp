#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include <math.h>

std::list<int> translation(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int translation_factor)
{
    std::list<int> temp;
    temp.push_back(x1+translation_factor);
    temp.push_back(y1+translation_factor);
    temp.push_back(z1+translation_factor);
    temp.push_back(x2+translation_factor);
    temp.push_back(y2+translation_factor);
    temp.push_back(z2+translation_factor);
    temp.push_back(x3+translation_factor);
    temp.push_back(y3+translation_factor);
    temp.push_back(z3+translation_factor);
    return temp;
}

std::list<int> scaling(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int scaling_factor)
{
    std::list<int> temp;
    temp.push_back(x1*scaling_factor);
    temp.push_back(y1*scaling_factor);
    temp.push_back(z1*scaling_factor);
    temp.push_back(x2*scaling_factor);
    temp.push_back(y2*scaling_factor);
    temp.push_back(z2*scaling_factor);
    temp.push_back(x3*scaling_factor);
    temp.push_back(y3*scaling_factor);
    temp.push_back(z3*scaling_factor);
    return temp;
}

std::list<int> rotation(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, char axis, double angle)
{
    std::list<int> temp;
    if(axis == 'x')
    {
        temp.push_back(x1);
        temp.push_back(y1*cos(angle)-z1*sin(angle));
        temp.push_back(y1*sin(angle)+z1*cos(angle));
        temp.push_back(x2);
        temp.push_back(y2*cos(angle)-z2*sin(angle));
        temp.push_back(y2*sin(angle)+z2*cos(angle));
        temp.push_back(x3);
        temp.push_back(y3*cos(angle)-z3*sin(angle));
        temp.push_back(y3*sin(angle)+z3*cos(angle));
    }
    else if(axis == 'y')
    {
        temp.push_back(z1*sin(angle)+x1*cos(angle));
        temp.push_back(y1);
        temp.push_back(y1*cos(angle)-x1*sin(angle));
        temp.push_back(z2*sin(angle)+x2*cos(angle));
        temp.push_back(y2);
        temp.push_back(y2*cos(angle)-x2*sin(angle));
        temp.push_back(z3*sin(angle)+x3*cos(angle));
        temp.push_back(y3);
        temp.push_back(y3*cos(angle)-x3*sin(angle));
    }
    else
    {
        temp.push_back(x1*cos(angle)-y1*sin(angle));
        temp.push_back(x1*sin(angle)+y1*cos(angle));
        temp.push_back(z1);
        temp.push_back(x2*cos(angle)-y2*sin(angle));
        temp.push_back(x2*sin(angle)+y2*cos(angle));
        temp.push_back(z2);
        temp.push_back(x3*cos(angle)-y3*sin(angle));
        temp.push_back(x3*sin(angle)+y3*cos(angle));
        temp.push_back(z3);
    }
    return temp;
}

int main()
{
    int x1, y1, z1, x2, y2, z2, x3, y3, z3;
	std::cout<<"Enter the coordinates: ";
	std::cin>>x1>>y1>>z1>>x2>>y2>>z2>>x3>>y3>>z3;
	
    std::list<int> l;
    std::cout<<"Translation:1 Scaling:2 Rotation:3"<<std::endl;
    int inp;
    std::cin>>inp;

    if(inp == 1)
    {
        int factor;
        std::cout<<"Enter translation factor"<<std::endl;
        std::cin>>factor;
        l = translation(x1, y1, z1, x2, y2, z2, x3, y3, z3,factor);
    }
    else if(inp == 2)
    {
        int factor;
        std::cout<<"Enter scaling factor"<<std::endl;
        std::cin>>factor;
        l = scaling(x1, y1, z1, x2, y2, z2, x3, y3, z3,factor);
    }
    else if(inp == 3)
    {
        char axis;
        int angle;
        std::cout<<"Enter rotation axis and rotation angle"<<std::endl;
        std::cin>>axis>>angle;
        l = rotation(x1, y1, z1, x2, y2, z2, x3, y3, z3, axis, angle);
    }
    else
    {
        std::cout<<"Enter a valid input."<<std::endl;
    }
    
    if(!glfwInit())
        return -1;

    GLFWwindow* window;

    window = glfwCreateWindow(640, 480, "3D Transformation", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
        return -1;

    int vertex_positions[l.size()];
    std:: copy(l.begin(), l.end(), vertex_positions);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glPointSize(1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 320, -240, 240, -1, 1);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertex_positions)/3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
