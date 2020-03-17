#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include <math.h>

std::list<int> translation(int x1, int y1, int x2, int y2, int x3, int y3, int translation_factor)
{
    std::list<int> temp;
    temp.push_back(x1+translation_factor);
    temp.push_back(y1+translation_factor);
    temp.push_back(x2+translation_factor);
    temp.push_back(y2+translation_factor);
    temp.push_back(x3+translation_factor);
    temp.push_back(y3+translation_factor);
    return temp;
}

std::list<int> scaling(int x1, int y1, int x2, int y2, int x3, int y3, int scaling_factor)
{
    std::list<int> temp;
    temp.push_back(x1*scaling_factor);
    temp.push_back(y1*scaling_factor);
    temp.push_back(x2*scaling_factor);
    temp.push_back(y2*scaling_factor);
    temp.push_back(x3*scaling_factor);
    temp.push_back(y3*scaling_factor);
    return temp;
}

std::list<int> rotation(int x1, int y1, int x2, int y2, int x3, int y3, double angle)
{
    std::list<int> temp;
    temp.push_back(x1*cos(angle)-y1*sin(angle));
    temp.push_back(x1*sin(angle)+y1*cos(angle));
    temp.push_back(x2*cos(angle)-y2*sin(angle));
    temp.push_back(x2*sin(angle)+y2*cos(angle));
    temp.push_back(x3*cos(angle)-y3*sin(angle));
    temp.push_back(x3*sin(angle)+y3*cos(angle));
    return temp;
}

std::list<int> reflection(int x1, int y1, int x2, int y2, int x3, int y3, char axis)
{
    std::list<int> temp;
    if(axis == 'x')
    {
        temp.push_back(x1);
        temp.push_back(-y1);
        temp.push_back(x2);
        temp.push_back(-y2);
        temp.push_back(x3);
        temp.push_back(-y3);
    }
    else
    {
        temp.push_back(-x1);
        temp.push_back(y1);
        temp.push_back(-x2);
        temp.push_back(y2);
        temp.push_back(-x3);
        temp.push_back(y3);
    }
    return temp;
}

std::list<int> shearing(int x1, int y1, int x2, int y2, int x3, int y3, int shear, char axis)
{
    std::list<int> temp;
    if(axis == 'x')
    {
        temp.push_back(x1+shear*y1);
        temp.push_back(y1);
        temp.push_back(x2+shear*y2);
        temp.push_back(y2);
        temp.push_back(x3+shear*y3);
        temp.push_back(y3);
    }
    else
    {
        temp.push_back(x1);
        temp.push_back(y1+shear*x1);
        temp.push_back(x2);
        temp.push_back(y2+shear*x2);
        temp.push_back(x3);
        temp.push_back(y3+shear*x3);
    }
    return temp;
}

int main()
{
    int x1, y1, x2, y2, x3, y3;
	std::cout<<"Enter the coordinates: ";
	std::cin>>x1>>y1>>x2>>y2>>x3>>y3;
	
    std::list<int> l;
    std::cout<<"Translation:1 Scaling:2 Rotation:3 Reflection:4 Shearing:5"<<std::endl;
    int inp;
    std::cin>>inp;

    if(inp == 1)
    {
        int factor;
        std::cout<<"Enter translation factor"<<std::endl;
        std::cin>>factor;
        l = translation(x1,y1,x2,y2,x3,y3,factor);
    }
    else if(inp == 2)
    {
        int factor;
        std::cout<<"Enter scaling factor"<<std::endl;
        std::cin>>factor;
        l = scaling(x1,y1,x2,y2,x3,y3,factor);
    }
    else if(inp == 3)
    {
        int angle;
        std::cout<<"Enter rotation angle"<<std::endl;
        std::cin>>angle;
        l = rotation(x1,y1,x2,y2,x3,y3,angle);
    }
    else if(inp == 4)
    {
        char axis;
        std::cout<<"Enter axis of reflection"<<std::endl;
        std::cin>>axis;
        l = reflection(x1,y1,x2,y2,x3,y3,axis);
    }
    else
    {
        int factor;
        char axis;
        std::cout<<"Enter shearing factor and axis of shearing"<<std::endl;
        std::cin>>factor>>axis;
        l = shearing(x1,y1,x2,y2,x3,y3,factor,axis);
    }
    
    if(!glfwInit())
        return -1;

    GLFWwindow* window;

    window = glfwCreateWindow(640, 480, "2D Transformation", NULL, NULL);
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
    glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glPointSize(1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 320, -240, 240, -1, 1);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertex_positions)/2);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
