#ifndef RENDER_TEXTURE_H_
#define RENDER_TEXTURE_H_
#include <GStransform.h>
class RenderTexture
{
public:
	static void CreateRenderTarget(int id,GSvector2 size,GSboolean colorBuf, GSboolean depthBuf, GSboolean formatFloat);
	
	static void BeginRender(int id);
	static void EndRender();

	static void BindRenderTexture(int id,GSuint colorBuf);
	static void UnBindRenderTexture(int id, GSuint colorBuf);
	static void BindRenderTextureEx(int id, GSuint colorBuf,GSuint textureID);
	static void UnBindRenderTextureEx(int id, GSuint colorBuf, GSuint textureID);
	
	static void BindRenderDepth(int id);
	static void UnBindRenderDepth(int id);
	static void BindRenderDepthEx(int id, GSuint textureID);
	static void UnBindRenderDepthEx(int id, GSuint textureID);

	static void DrawRender(int id);
};

#endif
