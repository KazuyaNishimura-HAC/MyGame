#ifndef LINE_H_
#define LINE_H_

#include <gslib.h>
#include <GStransform.h>
// �����N���X
class Line {
public:
    // �f�t�H���g�R���X�g���N�^
    Line() = default;
    // �R���X�g���N�^
    Line(const GSvector3& start, const GSvector3& end) :
        start{ start }, end{ end } {
    };
    //�����̕����擾
    GSvector3 DirectionVec() { return (end - start).normalized(); };
    //���������擾
    float DirectionLength() { (end - start).magnitude(); };
public:
    // �n�_
    GSvector3 start{ 0.0f, 0.0f, 0.0f };
    // �I�_
    GSvector3 end{ 0.0f, 0.0f, 0.0f };
};

#endif