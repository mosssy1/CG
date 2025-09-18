#pragma once
#include "include.h"
#include "Model.h"

class Room
{
public:
    Room();
    void Draw();
    void LoadObjects();

private:
    void DrawBed();
    void DrawRug();
    void DrawWall();
    void DrawBear();
    void DrawLamp();
    void DrawCat();
    void DrawFirewood();

    Model m_rug;
    Model m_wall;
    Model m_bear;
    Model m_lamp;
    Model m_cat;
    Model m_pawn;
    Model m_bed;
    Model m_firewood;

};