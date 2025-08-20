
#include <GL/freeglut.h>
#include <cstdio>

// 視窗尺寸
int winWidth = 800, winHeight = 600;

// 旋轉角度
float angle = 0.0f;

// 每幀旋轉增量
const float deltaAngle = 0.5f;

void display()
{
    glClearColor(0.06f, 0.06f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 旋轉整個場景
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    // 畫紅色三角形
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.6f);
    glVertex2f(-0.6f, -0.6f);
    glVertex2f(0.6f, -0.6f);
    glEnd();

    glutSwapBuffers();
}

// 更新旋轉角度的函式
void update(int value)
{
    angle += deltaAngle;
    if (angle >= 360.0f) angle -= 360.0f;

    glutPostRedisplay();            // 重新繪製
    glutTimerFunc(16, update, 0);  // 大約每16ms呼叫一次（60 FPS）
}

void reshape(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int, int)
{
    if (key == 27)
    {
        glutLeaveMainLoop();
    }
}

int main(int argc, char **argv)
{
    /*
    這是 FreeGLUT 的初始化函式。
    &argc, argv 是程式從命令列帶入的參數。
    FreeGLUT 可能會解析一些命令列參數，例如 -display 或 -geometry。
    必須在呼叫任何其他 GLUT 函式之前呼叫。
    簡單理解：告訴 GLUT “嘿，我要開始用 OpenGL 做視窗了”。
    */
    glutInit(&argc, argv);
    /*
    這是 FreeGLUT 專屬的函式，用來設定視窗關閉時的行為。
    GLUT_ACTION_ON_WINDOW_CLOSE 是要設定的選項（關閉視窗時的動作）。
    GLUT_ACTION_GLUTMAINLOOP_RETURNS 表示：
    當使用者關閉視窗時，glutMainLoop() 不會讓程式直接結束，而是會返回。
    這樣可以在視窗關閉後繼續執行其他程式碼。
    傳統 GLUT 不支援這種方式，FreeGLUT 才有這個功能。
    */
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    /*
    設定 顯示模式 (Display Mode)。
    GLUT_DOUBLE：
    啟用 雙緩衝 (double buffering)。
    意思是用兩個緩衝區輪流顯示畫面，一個顯示，一個渲染，減少閃爍。
    GLUT_RGBA：
    使用 RGBA 顏色模式（紅、綠、藍、透明度）。
    相對於 GLUT_INDEX（調色盤模式），RGBA 是現代 OpenGL 常用方式。
    簡單理解：告訴 GLUT 我要用雙緩衝、RGBA 顏色模式的視窗。
    */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    /*
    設定視窗 初始大小，單位是像素。
    winWidth 和 winHeight 是你程式裡定義的整數。
    例如 winWidth = 800, winHeight = 600 就會建立 800×600 的視窗。
    */
    glutInitWindowSize(winWidth, winHeight);
    /*
    創建一個 OpenGL 視窗，並設定視窗標題。
    這個呼叫後，OpenGL 的 context 會建立好，可以開始渲染。
    返回值通常是視窗 ID，可以用來操作多個視窗。
    例如 "Red Triangle - FreeGLUT" 就會顯示在視窗頂端的標題欄。
    */
    glutCreateWindow("Red Triangle - FreeGLUT");
    /*
    註冊 顯示回呼函式 (Display Callback)。
    display 是你自己寫的函式，用來畫畫面（渲染）。
    每當 GLUT 視窗需要重繪（例如剛開啟、被其他視窗遮住後再顯示、手動呼叫 glutPostRedisplay()），它就會呼叫 display()。
    簡單理解：這個函式就是你的「畫面更新程式」。
    */
    glutDisplayFunc(display);
    /*
    註冊 視窗大小改變回呼函式 (Reshape Callback)。
    reshape 是你自己寫的函式，用來處理視窗尺寸改變時的事情。
    例如：
    更新 OpenGL 投影矩陣 (glViewport、glOrtho、gluPerspective)。
    確保畫面比例正確。
    每當使用者調整視窗大小時，GLUT 會自動呼叫這個函式。
    */
    glutReshapeFunc(reshape);
    /*
    註冊 鍵盤事件回呼函式 (Keyboard Callback)。
    keyboard 是你自己寫的函式，用來處理使用者按鍵。
    每當使用者按下鍵盤按鍵，GLUT 會呼叫這個函式，並把按鍵字元和滑鼠位置傳給你。
    例如，你可以按 Esc 關閉視窗，或者按 R 改變顏色。
     */
    glutKeyboardFunc(keyboard);

    // 啟動定時器
    glutTimerFunc(0, update, 0);

    /*
    啟動 FreeGLUT 的主迴圈 (Main Loop)。
    它會：
    持續監控事件（視窗重繪、鍵盤、滑鼠）。
    呼叫你註冊的回呼函式（display、reshape、keyboard 等）。
    管理雙緩衝交換（如果你用 GLUT_DOUBLE）。
    這個呼叫通常會「阻塞程式」，直到你關閉視窗（或者使用 FreeGLUT 特定設定讓它返回）。
    簡單理解：這是一個「事件監聽迴圈」，負責把你的程式變成互動式應用程式。
    */
    glutMainLoop();

    printf("Main loop exited. Program will now terminate.\n");
    return 0;
}
