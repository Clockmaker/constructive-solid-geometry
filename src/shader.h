/* shader.h */
#ifndef SHADER_H
#define SHADER_H

static  const char* File_toBuffer(const char *path);
static GLuint Shader_loadFromFile(const char *vertex_path,const char *fragment_path);

//#endif
//#ifdef SHADER_H_SOURCE

static  const char* File_toBuffer(const char *path){
    FILE *f;
    long size;
    char *buffer;

    f = fopen(path,"r");
    if(!f) {
        D_LOG("file not found : %s", path);
        return NULL;
    }
    fseek(f, 0,SEEK_END);
    size = ftell(f);
    buffer = (char *)malloc(size+1);
    fseek(f, 0,SEEK_SET);
    fread(buffer, size, 1, f);
    fclose(f);
    buffer[size]=0;
    //D_LOG("%s\n\n",buffer);

    return buffer;
}

static GLuint Shader_loadFromFile(const char *vertex_path, const char *fragment_path){

    // Create the shaders
    GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *vertex_source = File_toBuffer(vertex_path);
    const GLchar *fragment_source = File_toBuffer(fragment_path);


    //TODO: handle NULL ptr

    GLint valid = GL_FALSE;
    GLint log_length=0;

    // Compiling
    D_LOG("Compiling vertex shader: \"%s\"", vertex_path);
    //char const * VertexSourcePointer = vertex_shader.c_str();
    glShaderSource(vertex_id, 1, &vertex_source, 0);
    glCompileShader(vertex_id);

    glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &valid);
    if (GL_FALSE == valid){
        glGetShaderiv(vertex_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar log[log_length];
        glGetShaderInfoLog(vertex_id, log_length, &log_length, &log[0]);
        D_LOG("\n%s\n",log);
        glDeleteShader(vertex_id);
        return -1;
    }

    // Same
    D_LOG("Compiling fragment shader: \"%s\"", fragment_path);
    glShaderSource(fragment_id, 1, &fragment_source, 0);
    glCompileShader(fragment_id);

    glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &valid);
        glGetShaderiv(fragment_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar log[log_length];
        glGetShaderInfoLog(fragment_id, log_length, &log_length, &log[0]);
        D_LOG("\n%s",log);
    if (GL_FALSE == valid){
        glDeleteShader(fragment_id);
        return -1;
    }
    // Link the program
    GLuint shader = glCreateProgram();
    glAttachShader(shader, vertex_id);
    glAttachShader(shader, fragment_id);
    glLinkProgram(shader);

    // Check the program
    glGetProgramiv(shader, GL_LINK_STATUS, &valid);
    if (GL_FALSE == valid){
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        GLchar log[log_length];
        glGetProgramInfoLog(shader, log_length, &log_length, &log[0]);
        D_LOG("%s",log);
        glDeleteProgram(shader);
        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);
        return -1;
    }

    glValidateProgram(shader);
    //TODO: dev only (wrap in a macro)
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &valid);
    glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &log_length);
    GLchar log2[log_length];
    glGetProgramInfoLog(shader, log_length, &log_length, &log2[0]);
    D_LOG("\n%s",log2);

    glDetachShader(shader, vertex_id);
    glDetachShader(shader, fragment_id);
    //free()
    D_LOG("[%i] Shader compiled and linked successfully.", shader);

    return shader;
}

#endif
