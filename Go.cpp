#include "Go.h"

Go::Go(int index, const string& name) : Slot(index), m_name(name) {}


bool Go::play(Player* p)
{
    return true;
}

Go::~Go()
{
}

string Go::get_name() const
{
    return "Go: get 350$!";
}

