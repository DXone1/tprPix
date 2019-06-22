/*
 * ========================= VAOVBO.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2018.12.24
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *   本游戏只有一份 VAO，VBO。
 *   所有的 mesh/goMesh 都应该包含 本文件，直接使用里面的 VAO,VBO
 * ----------------------------
 */
#ifndef TPR_VAO_VBO_H_
#define TPR_VAO_VBO_H_
//=== *** glad FIRST, glfw SECEND *** ===
#include <glad/glad.h>  

inline GLuint VAO  {0}; //- obj id
inline GLuint VBO  {0}; //- obj id

void init_VAOVBO();    //- 创建 VAO, VBO
void delete_VAOVBO();  //- 删除 VAO, VBO

#endif