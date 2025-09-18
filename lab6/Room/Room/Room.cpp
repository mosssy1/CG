#include "Room.h"

Room::Room()
    :m_bed()
    ,m_rug()
    ,m_wall()
    ,m_bear()
    ,m_lamp()
    ,m_cat()
    ,m_firewood()
{
}

void Room::Draw()
{ 
    DrawBed();
    DrawRug();
    DrawWall();
    DrawBear();
    DrawLamp();
    DrawCat();
    DrawFirewood();
}

void Room::DrawBed()
{
    glPushMatrix();
    glRotatef(90.0f, 1, 0, 0);
    glTranslatef(0.0f, 0.0f, -2.0f);
    glScalef(1.5, 1.0, 1.0);
    m_bed.RenderModel();
    glPopMatrix();
}

void Room::DrawRug()
{
    glPushMatrix();
    glTranslatef(0.0f, 2.0, 0.0001f);
    glScalef(0.025, 0.025, 0.02);
    m_rug.RenderModel();
    glPopMatrix();

}

void Room::DrawWall()
{
    //стена
    glPushMatrix();
    glScalef(2.0, 0.5, 1.0);
    glRotatef(90.0f, 1, 0, 0);
    glTranslatef(-1.0f, 2.0f, -10.0f);
    m_wall.RenderModel();
    glPopMatrix();
    //пол
    glPushMatrix();
    glScalef(2.0, 2.0, 1.0);
    glTranslatef(-1.075f, 1.0f, 0.0f);
    m_wall.RenderModel();
    glPopMatrix();
    //слева
    glPushMatrix();
    glRotatef(90.0f, 0, 1, 0);
    glRotatef(90.0f, 0, 0, 1);
    glTranslatef(0.0f, 2.0f, -4.0f);
    glScalef(2.0, 1.0, 1.0);
    m_wall.RenderModel();
    glPopMatrix();
}

void Room::DrawBear()
{
    glPushMatrix();
    glTranslatef(0.0f, 4.5f, 2.0f);
    glScalef(0.03f, 0.03f, 0.03f);
    m_bear.RenderModel();
    glPopMatrix();

}

void Room::DrawLamp()
{
    //справа
    glPushMatrix();
    glTranslatef(2.5f, 4.0f, 0.0f);
    glScalef(0.02f, 0.02f, 0.02f);
    m_lamp.RenderModel();
    glPopMatrix();
    //слева
    glPushMatrix();
    glTranslatef(-2.5f, 4.0f, 0.0f);
    glScalef(0.02f, 0.02f, 0.02f);
    m_lamp.RenderModel();
    glPopMatrix();

}

void Room::DrawCat()
{
    glPushMatrix();
    glTranslatef(-1.2f, 1.2f, 0.0f);
    glRotatef(45.0f, 0, 0, 1);
    glScalef(0.03f, 0.03f, 0.03f);
    m_cat.RenderModel();
    glPopMatrix();
}

void Room::DrawFirewood()
{
    glPushMatrix();
    glTranslatef(3.0f, 2.3f, 0.0f);
    glScalef(0.01f, 0.01f, 0.01f);
    m_firewood.RenderModel();
    glPopMatrix();
}


void Room::LoadObjects()
{
    m_bed.LoadModel("./models/Bed.obj");
    m_rug.LoadModel("./models/rug.obj");
    m_wall.LoadModel("./models/wall.obj");
    m_bear.LoadModel("./models/bear (1).obj");
    m_lamp.LoadModel("./models/lamp/Lamp.obj");
    m_cat.LoadModel("./models/cat.obj");
    m_firewood.LoadModel("./models/firewood.obj");
}


