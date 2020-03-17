#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>

std::list<unsigned int> clip(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
{
    unsigned int dx, dy;
    float x, y, step, xinc, yinc;
    std::list<unsigned int> temp;
    dx = x1-x0;
    dy = y1-y0;
    if (dx>dy)
        step = dx;
    else
        step = dy;
    xinc = dx/step; yinc = dy/step;
    x = x0, y = y0;
    for(int i =0; i<step; i++)
    {
        x = x + xinc;
        y = y + yinc;
        temp.push_back(x);
        temp.push_back(y);
    }
    return temp;
}

int main()
{
    int x0, y0, x1, y1;
	std::cout<<"Enter co-ordinates of first point: ";
	std::cin>>x0>>y0;
 
	std::cout<<"Enter co-ordinates of second point: ";
	std::cin>>x1>>y1;

	std::list<unsigned int> l = clip(x0, y0, x1, y1);

    if(!glfwInit())
        return -1;

    GLFWwindow* window;

    window = glfwCreateWindow(640, 480, "Digital Differential Analyzer Algorithm", NULL, NULL);
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
