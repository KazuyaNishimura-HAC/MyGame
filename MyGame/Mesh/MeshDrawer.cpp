#include "MeshDrawer.h"

MeshDrawer::MeshDrawer(GSuint id)
{
    MeshID(id);
}

void MeshDrawer::MeshID(GSuint id)
{
    meshID_ = id;
}

GSuint MeshDrawer::MeshID() const
{
    return meshID_;
}

void MeshDrawer::Draw() const
{
    glPushMatrix();
    gsDrawMesh(meshID_);
    glPopMatrix();
}

void MeshDrawer::Draw(const GSmatrix4& matrix) const
{
    glPushMatrix();
    glMultMatrixf(matrix);
    gsDrawMesh(meshID_);
    glPopMatrix();
}
