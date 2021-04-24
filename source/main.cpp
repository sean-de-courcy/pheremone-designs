#include "Image.h"
#include "glad.h"
#include <GLFW/glfw3.h>
// #include <ft2build.h>
// #include FT_FREETYPE_H
#include <math.h>
#include <string>
#include <chrono>
#include <unistd.h>
#include <streambuf>
#include <sstream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

bool INWARD = false;
bool BOXED = false;
unsigned short int TYPES = 2; // max = 3
bool RECORD = false;

int main() {
    srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    int WIDTH = 1280;
    int HEIGHT = 720;

    Image image(WIDTH, HEIGHT);

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            image.SetColor(Color(0,0,0,1), x, y);
        }
    }

    int SQRT_NUMPIX = 1000;

    Image particleImage(SQRT_NUMPIX, SQRT_NUMPIX);

    for (int x = 0; x < SQRT_NUMPIX; x++) {
        for (int y = 0; y < SQRT_NUMPIX; y++) {
            float posX, posY;
            if (BOXED) {
                posX = (rand()%WIDTH)/2.0 + WIDTH/4.0;
                posY = (rand()%HEIGHT)/2.0 + HEIGHT/4.0;
            } else {
                posX = rand()%WIDTH;
                posY = rand()%HEIGHT;
            }
            float angle = 0.0;
            if (INWARD) {
                float diffX = WIDTH/2.0 - posX;
                float diffY = posY - HEIGHT/2.0;
                if (diffX != 0) {
                    angle = atan(abs(diffY/diffX));
                } else {
                    (diffY > 0 ? angle = 3*M_PI/2.0 : angle = M_PI/2.0);
                }
                if (diffX < 0 && diffY < 0) {
                    angle = M_PI - angle;
                } else if (diffX < 0 && diffY > 0) {
                    angle = M_PI + angle;
                } else if (diffX > 0 && diffY > 0) {
                    angle = 2*M_PI - angle;
                }
                angle = angle / (2*M_PI);
                if (angle < 0 || angle > 1) {
                    std::cout << angle << std::endl;
                }
            } else {
                angle = rand()/(float)RAND_MAX;
            }
            float color = (float)(rand()%TYPES);
            if (TYPES > 2) {
                color = color/(TYPES-1);
            }
            particleImage.SetColor(Color(posX/WIDTH, posY/HEIGHT, angle, color), x, y);
        }
    }

    GLFWwindow* window;
    if(!glfwInit()) {
        std::cout << "Couldn't init GLFW.\n";
    }

    window = glfwCreateWindow(WIDTH*2, HEIGHT*2, "Hello Pheremones", NULL, NULL);
    if (!window) {
        std::cout << "Couldn't open window.\n";
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    unsigned char* image1Char = image.toChar();
    GLuint tex_handler1;
    glGenTextures(1, &tex_handler1);
    glBindTexture(GL_TEXTURE_2D, tex_handler1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image1Char);
    glBindImageTexture(0, tex_handler1, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
    delete[] image1Char;

    unsigned char* image2Char = image.toChar();
    GLuint tex_handler2;
    glGenTextures(1, &tex_handler2);
    glBindTexture(GL_TEXTURE_2D, tex_handler2);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image2Char);
    glBindImageTexture(1, tex_handler2, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
    delete[] image2Char;

    unsigned char* particleImageChar = particleImage.toChar();
    GLuint tex_handler3;
    glGenTextures(1, &tex_handler3);
    glBindTexture(GL_TEXTURE_2D, tex_handler3);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, particleImage.getWidth(), particleImage.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, particleImageChar);
    glBindImageTexture(2, tex_handler3, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
    delete[] particleImageChar;

    std::ifstream t1("pheremoneShader.comp");
    std::stringstream buffer1;
    buffer1 << t1.rdbuf();
    std::string str1 = buffer1.str();

    const GLchar* the_pheremone_shader_string = str1.c_str();

    GLuint pheremone_shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(pheremone_shader, 1, &the_pheremone_shader_string, NULL);
    glCompileShader(pheremone_shader);
    GLint isCompiled = 0;
    glGetShaderiv(pheremone_shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(pheremone_shader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(pheremone_shader, maxLength, &maxLength, &errorLog[0]);

        // Provide the infolog in whatever manor you deem best.
        std::cout << "Compute shader failed to compile.\n";
        for (auto c : errorLog) {
            std::cout << c;
        }
        // Exit with failure.
        glDeleteShader(pheremone_shader); // Don't leak the shader.
        return -1;
    }
    
    GLuint pheremone_program = glCreateProgram();
    glAttachShader(pheremone_program, pheremone_shader);
    glLinkProgram(pheremone_program);
    GLint isLinked = 0;
    glGetProgramiv(pheremone_program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(pheremone_program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(pheremone_program, maxLength, &maxLength, &infoLog[0]);

        // The program is useless now. So delete it.
        glDeleteProgram(pheremone_program);

        // Provide the infolog in whatever manner you deem best.
        std::cout << "The compute shader failed to link.\n";
        for (auto c : infoLog) {
            std::cout << c;
        }
        // Exit with failure.
        return -1;
    }

    std::ifstream t2("blurShader.comp");
    std::stringstream buffer2;
    buffer2 << t2.rdbuf();
    std::string str2 = buffer2.str();

    const GLchar* the_blur_shader_string = str2.c_str();

    GLuint blur_shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(blur_shader, 1, &the_blur_shader_string, NULL);
    glCompileShader(blur_shader);
    isCompiled = 0;
    glGetShaderiv(blur_shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(blur_shader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(blur_shader, maxLength, &maxLength, &errorLog[0]);

        // Provide the infolog in whatever manor you deem best.
        std::cout << "Compute shader failed to compile.\n";
        for (auto c : errorLog) {
            std::cout << c;
        }
        // Exit with failure.
        glDeleteShader(blur_shader); // Don't leak the shader.
        return -1;
    }
    
    GLuint blur_program = glCreateProgram();
    glAttachShader(blur_program, blur_shader);
    glLinkProgram(blur_program);
    isLinked = 0;
    glGetProgramiv(blur_program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(blur_program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(blur_program, maxLength, &maxLength, &infoLog[0]);

        // The program is useless now. So delete it.
        glDeleteProgram(blur_program);

        // Provide the infolog in whatever manner you deem best.
        std::cout << "The compute shader failed to link.\n";
        for (auto c : infoLog) {
            std::cout << c;
        }
        // Exit with failure.
        return -1;
    }

    const std::string fileName = "output0.avi";
    cv::VideoWriter outputVideo;
    cv::Mat img(HEIGHT*2, WIDTH*2, CV_8UC3);
    cv::Mat flipped(WIDTH*2, HEIGHT*2, CV_8UC3);

    if (RECORD) {
        outputVideo.open(fileName, cv::VideoWriter::fourcc('M','J','P','G'), 20.0, cv::Size(WIDTH*2, HEIGHT*2));
        if (!outputVideo.isOpened()) {
            std::cout << "Could not open the output video for write.";
            return -1;
        }
    }

    unsigned short int i = 0;
    int f = 0;
    while(!glfwWindowShouldClose(window)){
        glUseProgram(pheremone_program);
        glDispatchCompute((GLuint)particleImage.getWidth(), (GLuint)particleImage.getHeight(), 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up orthographic projection
        int window_width, window_height;
        glfwGetFramebufferSize(window, &window_width, &window_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, window_width, 0, window_height, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        glEnable(GL_TEXTURE_2D);
        (i == 0 ? glBindTexture(GL_TEXTURE_2D, tex_handler1) : glBindTexture(GL_TEXTURE_2D, tex_handler2));
        glBegin(GL_QUADS);
            glTexCoord2d(0,0); glVertex2i(0,0);
            glTexCoord2d(1,0); glVertex2i(image.getWidth()*2, 0);
            glTexCoord2d(1,1); glVertex2i(image.getWidth()*2, image.getHeight()*2);
            glTexCoord2d(0,1); glVertex2i(0, image.getHeight()*2);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        glBindImageTexture((i+1)%2, tex_handler1, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(i, tex_handler2, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

        i = (i+1)%2;

        glfwPollEvents();
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
        glfwSwapBuffers(window);

        // Making Video
        if (RECORD) {
            glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3) ? 1 : 4);
            glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
            glReadPixels(0,0, img.cols, img.rows, GL_BGR, GL_UNSIGNED_BYTE, img.data);
            
            cv::flip(img, flipped, 0);

            outputVideo.write(flipped);
        }

        glUseProgram(blur_program);
        glDispatchCompute((GLuint)image.getWidth(), (GLuint)image.getHeight(), 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
        f++;
        f *= (int)(RECORD);
    }
    if (RECORD) {
        outputVideo.release();
    }
    glfwDestroyWindow(window);
}