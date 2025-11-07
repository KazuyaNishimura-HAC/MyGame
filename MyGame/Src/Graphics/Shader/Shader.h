#ifndef SHADER_H_
#define	SHADER_H_
#include "ShaderID.h"
class Shader
{
public:
    static void BeginShader(int id = 0);
    static void BeginMeshShader(int id);
    static void BeginSkinMeshShader(int id);
    static void EndShader();
    static void EndMeshShader();
    static void EndSkinMeshShader();
};

#endif
