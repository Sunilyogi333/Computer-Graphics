#include <GL/glut.h>
#include <stdio.h>

// Function to plot a point
void plot(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y); // First quadrant
    glVertex2i(xc - x, yc + y); // Second quadrant
    glVertex2i(xc + x, yc - y); // Fourth quadrant
    glVertex2i(xc - x, yc - y); // Third quadrant
    glVertex2i(xc + y, yc + x); // Symmetry
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

// Midpoint Circle Algorithm
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r; // Initial decision parameter

    while (x <= y) {
        plot(xc, yc, x, y);
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * x - 2 * y + 1;
        }
    }
    glFlush();
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc = 250, yc = 250, radius = 100; // Center and radius
    drawCircle(xc, yc, radius);

    glFlush();
}

// OpenGL Initialization
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glColor3f(1.0, 1.0, 1.0);         // White color
    glPointSize(2.0);                // Point size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);      // Coordinate system
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
