#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>

std::list<unsigned int> drawcircle(unsigned int x0, unsigned int y0, unsigned int radius)
{
    std::list<unsigned int> temp;
    unsigned int x = radius;
    unsigned int y = 0;
    int p;
 
    while (x >= y)
    {
        temp.push_back(x0 + x);
        temp.push_back(y0 + y);
        temp.push_back(x0 + y);
        temp.push_back(y0 + x);
        temp.push_back(x0 - y);
        temp.push_back(y0 + x);
        temp.push_back(x0 - x);
        temp.push_back(y0 + y);
        temp.push_back(x0 - x);
        temp.push_back(y0 - y);
        temp.push_back(x0 - y);
        temp.push_back(y0 - x);
        temp.push_back(x0 + y);
        temp.push_back(y0 - x);
        temp.push_back(x0 + x);
        temp.push_back(y0 - y);
        if (p <= 0)
        {
            y += 1;
            p += 2*y + 1;
        }
        else
        {
            x -= 1;
            p -= 2*x + 1;
        }
    }
    return temp;
}

int main()
{
    unsigned int x0, y0, r;
	std::cout<<"Enter the center: ";
	std::cin>>x0>>y0;
 
	std::cout<<"Enter the radius: ";
	std::cin>>r;

	std::list<unsigned int> l = drawcircle(x0, y0, r);

    if(!glfwInit())
        return -1;

    GLFWwindow* window;

    window = glfwCreateWindow(640, 480, "Mid-point Circle Algorithm", NULL, NULL);
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
