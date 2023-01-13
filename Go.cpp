#include "Go.h"

Go::Go(int index, const string& name) : Slot(index), m_name(name) {}


inline bool Go::play(Player* p)
{
    return true;
}

Go::~Go()
{
}

inline string Go::get_name() const
{
    return "Go: get 350$!";
}

//void Go::print_slot() const
//{
//    cout << 
//}

