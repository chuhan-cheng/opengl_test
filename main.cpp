
#include <GL/freeglut.h>

// 視窗尺寸
int winWidth = 800, winHeight = 600;

void display() {
    glClearColor(0.06f, 0.06f, 0.08f, 1.0f); // 深色背景
    glClear(GL_COLOR_BUFFER_BIT);

    // 設定投影與座標（簡單 2D 正交座標）
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 畫紅色三角形
    glColor3f(1.0f, 0.0f, 0.0f); // 紅
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f,  0.6f);
        glVertex2f(-0.6f, -0.6f);
        glVertex2f(0.6f, -0.6f);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winWidth = w; winHeight = h;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int, int) {
    if (key == 27) { // ESC 離開
        glutLeaveMainLoop();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Red Triangle - FreeGLUT");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
