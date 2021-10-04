//
// Created by Mark Minch  on 9/30/21.
//

#include "Shader.h"
namespace ShaderSystems {

    namespace UniformContext {
// utility uniform functions
// ------------------------------------------------------------------------
        void setBool(unsigned int ID, const std::string &name, bool value) {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
        }

// ------------------------------------------------------------------------
        void setInt(unsigned int ID, const std::string &name, int value) {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }

// ------------------------------------------------------------------------
        void setFloat(unsigned int ID, const std::string &name, float value) {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }

// ------------------------------------------------------------------------
        void setVec2(unsigned int ID, const std::string &name, const glm::vec2 &value) {
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }

        void setVec2(unsigned int ID, const std::string &name, float x, float y) {
            glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
        }

// ------------------------------------------------------------------------
        void setVec3(unsigned int ID, const std::string &name, const glm::vec3 &value) {
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }

        void setVec3(unsigned int ID, const std::string &name, float x, float y, float z) {
            glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
        }

// ------------------------------------------------------------------------
        void setVec4(unsigned int ID, const std::string &name, const glm::vec4 &value) {
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }

        void setVec4(unsigned int ID, const std::string &name, float x, float y, float z, float w) {
            glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
        }

// ------------------------------------------------------------------------
        void setMat2(unsigned int ID, const std::string &name, const glm::mat2 &mat) {
            glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

// ------------------------------------------------------------------------
        void setMat3(unsigned int ID, const std::string &name, const glm::mat3 &mat) {
            glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

// ------------------------------------------------------------------------
        void setMat4(unsigned int ID, const std::string &name, const glm::mat4 &mat) {
            unsigned int id = glGetUniformLocation(ID, name.c_str());
            glUniformMatrix4fv(id, 1, GL_FALSE, &mat[0][0]);
        }
    }


}