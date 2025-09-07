#ifndef MESH_DRAWER_H_
#define MESH_DRAWER_H_

#include <gslib.h>

class MeshDrawer
{
public:
    MeshDrawer(GSuint id = 0);
    void MeshID(GSuint id);
    GSuint MeshID()const;
    void Draw()const;
    void Draw(const GSmatrix4& matrix)const;
private:
    GSuint meshID_;
};

#endif
