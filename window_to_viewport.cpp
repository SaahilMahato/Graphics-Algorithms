#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>

std::list<int> convert(int x1_w, int y1_w, int x2_w, int y2_w, int x_wmax, 
                      int y_wmax, int x_wmin, int y_wmin, 
                      int x_vmax, int y_vmax, int x_vmin, 
                      int y_vmin)
{
    std::list<int> temp;
    int x1_v, y1_v, x2_v, y2_v;  
    double sx, sy;  
    sx = (double)(x_vmax - x_vmin) / (x_wmax - x_wmin); 
    sy = (double)(y_vmax - y_vmin) / (y_wmax - y_wmin); 
    x1_v = x_vmin + (double)((x1_w - x_wmin) * sx); 
    y1_v = y_vmin + (double)((y1_w - y_wmin) * sy);
    x2_v = x_vmin + (double)((x2_w - x_wmin) * sx); 
    y2_v = y_vmin + (double)((y2_w - y_wmin) * sy);
    temp.push_back(x1_v);
    temp.push_back(y1_v);
    temp.push_back(x2_v);
    temp.push_back(y2_v);
    return temp;
}

int main()
{
    int x_wmax=1366, y_wmax=768, x_wmin=0, y_wmin=0, x_vmax=640, y_vmax=480, x_vmin=0, y_vmin=0;

    int x1_w, y1_w, x2_w, y2_w;
	std::cout<<"Enter co-ordinates of first point: ";
	std::cin>>x1_w>>y1_w;
	std::cout<<"Enter co-ordinates of second point: ";
	std::cin>>x2_w>>y2_w;

	std::list<int> l = convert(x1_w, y1_w, x2_w, y2_w, x_wmax, y_wmax, x_wmin, y_wmin,
    x_vmax, y_vmax, x_vmin, y_vmin);

    if(!glfwInit())
        return -1;

    GLFWwindow* window;

    window = glfwCreateWindow(640, 480, "Viewport", NULL, NULL);
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
        glDrawArrays(GL_LINES, 0, sizeof(vertex_positions)/2);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
