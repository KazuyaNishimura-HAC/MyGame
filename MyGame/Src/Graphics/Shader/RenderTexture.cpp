#include "RenderTexture.h"
#include <GSgame.h>
void RenderTexture::CreateRenderTarget(int id, GSvector2 size, GSboolean colorBuf, GSboolean depthBuf, GSboolean formatFloat)
{
	gsCreateRenderTarget(id,size.x,size.y,colorBuf,depthBuf,formatFloat);
}

void RenderTexture::BeginRender(int id)
{
	gsBeginRenderTarget(id);
}

void RenderTexture::EndRender()
{
	gsEndRenderTarget();
}

void RenderTexture::BindRenderTexture(int id, GSuint colorBuf)
{
	gsBindRenderTargetTexture(id,colorBuf);
}

void RenderTexture::UnBindRenderTexture(int id, GSuint colorBuf)
{
	gsUnbindRenderTargetTexture(id,colorBuf);
}

void RenderTexture::BindRenderTextureEx(int id, GSuint colorBuf, GSuint textureID)
{
	gsBindRenderTargetTextureEx(id, colorBuf,textureID);
}

void RenderTexture::UnBindRenderTextureEx(int id, GSuint colorBuf, GSuint textureID)
{
	gsUnbindRenderTargetTextureEx(id, colorBuf, textureID);
}

void RenderTexture::BindRenderDepth(int id)
{
	gsBindRenderTargetDepth(id);
}

void RenderTexture::UnBindRenderDepth(int id)
{
	gsUnbindRenderTargetDepth(id);
}

void RenderTexture::BindRenderDepthEx(int id, GSuint textureID)
{
	gsBindRenderTargetDepthEx(id, textureID);
}

void RenderTexture::UnBindRenderDepthEx(int id, GSuint textureID)
{
	gsUnbindRenderTargetDepthEx(id, textureID);
}

void RenderTexture::DrawRender(int id)
{
	gsDrawRenderTarget(id);
}

