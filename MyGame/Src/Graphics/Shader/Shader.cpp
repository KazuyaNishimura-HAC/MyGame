#include "Shader.h"
#include <gslib.h>

void Shader::BeginShader(int id)
{
    gsBeginShader(id);
}

void Shader::BeginMeshShader(int id)
{
    gsBeginDefaultShader(id);
    gsBindDefaultMeshShader(id);
}

void Shader::BeginSkinMeshShader(int id)
{
    gsBeginDefaultShader(id);
    gsBindDefaultSkinMeshShader(id);
}

void Shader::EndShader()
{
    gsEndShader();
}

void Shader::EndMeshShader()
{
    gsEndShader();
    gsBindDefaultMeshShader(1019);
}

void Shader::EndSkinMeshShader()
{
    gsEndShader();
    gsBindDefaultSkinMeshShader(1020);
}
