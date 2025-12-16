#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARR_SIZE 14282

int rnd(int min, int max) {
    return rand() % (max - min) + min;
}

void padNumberWithZeros(int num, int desiredLength, char *buffer) {
    sprintf(buffer, "%0*d", desiredLength, num);
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(1, 1, "Compute Shader", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("GLEW init failed\n");
        return -1;
    }

    GLuint ssboNumbers, ssboCount;

    int numbers[MAX_ARR_SIZE] = {0};
    int count = 0;

    glGenBuffers(1, &ssboNumbers);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboNumbers);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(int) * MAX_ARR_SIZE, NULL, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssboNumbers);

    glGenBuffers(1, &ssboCount);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboCount);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(int), &count, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssboCount);

    const char *shaderSource = "#version 430\n"
        "layout(local_size_x=256) in;\n"
        "layout(std430, binding=0) buffer Numbers { int data[]; };\n"
        "layout(std430, binding=1) buffer Count { int count; };\n"
        "void main() {\n"
        "uint idx = gl_GlobalInvocationID.x;\n"
        "if (idx >= 100000) return;\n"
        "int n = int(idx); int sum = 0;\n"
        "for (int i = 0; i < 5; i++) { sum += n % 10; n /= 10; }\n"
        "if (sum % 7 == 0) { int pos = atomicAdd(count,1); data[pos]=int(idx); }\n"
        "}";
    GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(cs, 1, &shaderSource, NULL);
    glCompileShader(cs);

    GLuint program = glCreateProgram();
    glAttachShader(program, cs);
    glLinkProgram(program);
    glUseProgram(program);

    glDispatchCompute((100000 + 255) / 256, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_BUFFER_UPDATE_BARRIER_BIT);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboCount);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(int), &count);

    if (count == 0) {
        printf("No valid numbers found!\n");
        return -1;
    }

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboNumbers);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(int) * count, numbers);

    srand((unsigned int)time(NULL));

    char one[4], two[3], three[6], four[6];
    padNumberWithZeros(rnd(1, 366), 3, one);
    padNumberWithZeros(rnd(95, 99), 2, two);
    padNumberWithZeros(numbers[rnd(0, count)], 5, three);
    padNumberWithZeros(numbers[rnd(0, count)], 5, four);

    char key[50];
    sprintf(key, "%s%s-OEM-00%s-%s", one, two, three, four);
    printf("%s\n", key);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
