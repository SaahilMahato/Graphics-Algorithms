#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>

std::list<unsigned int> drawellipse(unsigned int xc, unsigned int yc, unsigned int rx, unsigned int ry)
{
    std::list<unsigned int> temp;
    int p;
    unsigned int x, y;
    p = ry*ry-rx*rx*ry+rx*rx/4;
    x=0; y=ry;

    while(2.0*ry*ry*x <= 2.0*rx*rx*y)
    {
        if(p < 0)
        {
            x++;
            p += 2*ry*ry*x+ry*ry;
        }
        else
        {
            x++; y--;
            p += 2*ry*ry*x-2*rx*rx*y-ry*ry;
        }

        temp.push_back(xc+x);
        temp.push_back(yc+y);
        temp.push_back(xc+x);
        temp.push_back(yc-y);
        temp.push_back(xc-x);
        temp.push_back(yc+y);
        temp.push_back(xc-x);
        temp.push_back(yc-y);
    }

    p = ry*ry*(x+0.5)*(x+0.5)+rx*rx*(y-1)*(y-1)-rx*rx*ry*ry;
    while(y > 0)
    {
        if(p <= 0)
        {
            x++; y--;
            p += 2*ry*ry*x-2*rx*rx*y+rx*rx;
        }
        else
        {
            y--;
            p -= 2*rx*rx*y+rx*rx;
        }
        
        temp.push_back(xc+x);
        temp.push_back(yc+y);
        temp.push_back(xc+x);
        temp.push_back(yc-y);
        temp.push_back(xc-x);
        temp.push_back(yc+y);
        temp.push_back(xc-x);
        temp.push_back(yc-y);
    }
    return temp;
}

int main()
{
    unsigned int xc, yc, rx, ry;
	std::cout<<"Enter the center: ";
	std::cin>>xc>>yc;
 
	std::cout<<"Enter the radius: ";
	std::cin>>rx>>ry;

	std::list<unsigned int> l = drawellipse(xc, yc, rx, ry);

    if(!glfwInit())
        return -1;

    GLFWwindow* window;

    window = glfwCreateWindow(640, 480, "Mid-point Ellipse Algorithm", NULL, NULL);
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
    glOrtho(0, 640, 0, 480, -1, 1);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, sizeof(vertex_positions)/2);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
