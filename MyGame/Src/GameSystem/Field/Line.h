#ifndef LINE_H_
#define LINE_H_

#include <gslib.h>
#include <GStransform.h>
// 線分クラス
class Line {
public:
    // デフォルトコンストラクタ
    Line() = default;
    // コンストラクタ
    Line(const GSvector3& start, const GSvector3& end) :
        start{ start }, end{ end } {
    };
    //線分の方向取得
    GSvector3 DirectionVec() { return (end - start).normalized(); };
    //線分長さ取得
    float DirectionLength() { (end - start).magnitude(); };
public:
    // 始点
    GSvector3 start{ 0.0f, 0.0f, 0.0f };
    // 終点
    GSvector3 end{ 0.0f, 0.0f, 0.0f };
};

#endif
