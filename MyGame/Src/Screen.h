#ifndef SCREEN_H_
#define SCREEN_H_

#include <gslib.h>

class Screen
{
public:
#if !_DEBUG
    static const bool fullScreen = true;
	static const int ScreenWidth = 1920, ScreenHeight = 1080;
#else
    static const bool fullScreen = false;
    static const int ScreenWidth = 1920, ScreenHeight = 1080;
#endif
    static const int HalfWidth{ ScreenWidth / 2 }, HalfHeight{ ScreenHeight / 2 };
    //ビューポート変換
	static void CalculateScreenPosition(GSvector3* screenPos, const GSvector3* worldPos)
	{
		GSmatrix4	matViewProjScreen;
        GSmatrix4	matProj;
        GSmatrix4	matView;
		GSmatrix4   matScreen;
        GLint		Viewport[4];
        //ビューポートの取得
		glGetIntegerv(GL_VIEWPORT, Viewport);
		// スクリーン座標変換行列を作成
		gsMatrix4Screen(&matScreen, Viewport[2], Viewport[3]);
		// 透視変換行列の取得
		glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&matProj);
		// 視点変換行列の取得
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&matView);
		// 座標変換を行う
		gsMatrix4Multiply(&matViewProjScreen, &matView, &matProj);
		gsMatrix4Multiply(&matViewProjScreen, &matViewProjScreen, &matScreen);
		gsVector3TransformCoord(screenPos, worldPos, &matViewProjScreen);

	}
    static GSvector2 WindowsScreen()
    {
        // ウィンドウハンドラを取得
        HWND hDWnd = GetActiveWindow();
        RECT rect;
        // 画面サイズ取得
        GetClientRect(hDWnd, &rect);
        GetClientRect(hDWnd, &rect);

        // 縦横サイズ取得
        LONG get_ww = rect.right - rect.left;
        LONG get_wh = rect.bottom - rect.top;
        return GSvector2((float)get_ww, (float)get_wh);
    }
};

#endif
