#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>

static void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void customPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
  GLdouble top = zNear * std::tan(fovy * 0.5 * std::acos(-1.0) / 180.0);
  GLdouble bottom = -top;
  GLdouble left = bottom * aspect;
  GLdouble right = top * aspect;
  glFrustum(left, right, bottom, top, zNear, zFar);
}

int main(void) {
  GLFWwindow* window;
  float angle = 0.0f;

  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    customPerspective(45.0f, (GLdouble)width / (GLdouble)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f); // 카메라를 뒤로 이동
    glRotatef(angle, 1.0f, 1.0f, 1.0f); // 회전

    glBegin(GL_QUADS);
    // 앞면
    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
    glNormal3f(0.0f, 0.0f, 1.0f); // 법선 벡터 설정
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // 뒷면
    glColor3f(0.0f, 1.0f, 0.0f); // 초록색
    glNormal3f(0.0f, 0.0f, -1.0f); // 법선 벡터 설정
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // 왼쪽면
    glColor3f(0.0f, 0.0f, 1.0f); // 파란색
    glNormal3f(-1.0f, 0.0f, 0.0f); // 법선 벡터 설정
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    // 오른쪽면
    glColor3f(1.0f, 1.0f, 0.0f); // 노란색
    glNormal3f(1.0f, 0.0f, 0.0f); // 법선 벡터 설정
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // 아래면
    glColor3f(1.0f, 0.0f, 1.0f); // 자홍색
    glNormal3f(0.0f, -1.0f, 0.0f); // 법선 벡터 설정
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // 위면
    glColor3f(0.0f, 1.0f, 1.0f); // 청록색
    glNormal3f(0.0f, 1.0f, 0.0f); // 법선 벡터 설정
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();

    angle += 0.3f;

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
