#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>

std::list<unsigned int> bla(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
{
    unsigned int dx, dy, x, y;
    int p;
    std::list<unsigned int> temp;
	dx= x1-x0;
	dy= y1-y0;
	x=x0;
	y=y0;
    temp.push_back(x);
    temp.push_back(y);
    if (dx>dy)
    {
        p=2*dy-dx;
        while(x<x1)
        {
            if(p>=0)
            {
                y++;
                p+=2*(dy-dx);
            }
            else
                p+=2*dy;
            x++;
            temp.push_back(x);
            temp.push_back(y);
        }
    }
    else
    {
        p=2*dx-dy;
        while(y<y1)
        {
            if(p>=0)
            {
                x++;
                p+=2*(dx-dy);
            }
            else
                p+=2*dx;
            y++;
            temp.push_back(x);
            temp.push_back(y);
        }
    }
    return temp;
}

std::list<unsigned int> dda(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
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

std::list<unsigned int> midpointcircle(unsigned int x0, unsigned int y0, unsigned int radius)
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

std::list<unsigned int> bresenhamcircle(unsigned int x0, unsigned int y0, unsigned int radius)
{
    std::list<unsigned int> temp;
    unsigned int x = 0;
    unsigned int y = radius;
    int p = 3-(2*radius);
 
    while (x <= y)
    {
        temp.push_back(x0 + x);
        temp.push_back(y0 + y);
        temp.push_back(x0 - x);
        temp.push_back(y0 + y);
        temp.push_back(x0 + x);
        temp.push_back(y0 - y);
        temp.push_back(x0 - x);
        temp.push_back(y0 - y);
        temp.push_back(x0 + y);
        temp.push_back(y0 + x);
        temp.push_back(x0 + y);
        temp.push_back(y0 - x);
        temp.push_back(x0 - y);
        temp.push_back(y0 + x);
        temp.push_back(x0 - y);
        temp.push_back(y0 - x);
        x+=1;
        if (p < 0)
        {
            p += 4*x + 6;
        }
        else
        {
            p += 4*(x-y) + 10;
            y -= 1;
        }
    }
    return temp;
}

std::list<unsigned int> midpointellipse(unsigned int xc, unsigned int yc, unsigned int rx, unsigned int ry)
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
    std::list<unsigned int> l;
    int inp;
    std::cout<<"dda:1 bla:2 midpointcircle:3 bresenhamcircle:4 midpointellipse:5"<<std::endl;
    std::cin>>inp;

    if(inp == 1)
    {
        int x0, y0, x1, y1;
        std::cout<<"Enter co-ordinates of first point: ";
        std::cin>>x0>>y0;
        std::cout<<"Enter co-ordinates of second point: ";
        std::cin>>x1>>y1;
        l = dda(x0, y0, x1, y1);
    }
    else if(inp == 2)
    {
        int x0, y0, x1, y1;
        std::cout<<"Enter co-ordinates of first point: ";
        std::cin>>x0>>y0;
        std::cout<<"Enter co-ordinates of second point: ";
        std::cin>>x1>>y1;
        l = bla(x0, y0, x1, y1);
    }
    else if(inp == 3)
    {
        unsigned int x0, y0, r;
	    std::cout<<"Enter the center: ";
	    std::cin>>x0>>y0;
	    std::cout<<"Enter the radius: ";
	    std::cin>>r;
	    l =  midpointcircle(x0, y0, r);  
    }
    else if(inp == 4)
    {
        unsigned int x0, y0, r;
	    std::cout<<"Enter the center: ";
	    std::cin>>x0>>y0;
	    std::cout<<"Enter the radius: ";
	    std::cin>>r;
	    l = bresenhamcircle(x0, y0, r);
    }
    else
    {
        unsigned int xc, yc, rx, ry;
	    std::cout<<"Enter the center: ";
	    std::cin>>xc>>yc;
	    std::cout<<"Enter the radii: ";
	    std::cin>>rx>>ry;
	    l = midpointellipse(xc, yc, rx, ry);
    }
    

    if(!glfwInit())
        return -1;

    GLFWwindow* window;

    window = glfwCreateWindow(640, 480, "Bresenham Line Drawing Algorithm", NULL, NULL);
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
