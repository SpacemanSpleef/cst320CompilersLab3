//**************************************
// parse.cpp
//
// Starting point for top-down recursive-descent parser
// Used in CST 320 Lab2
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <iostream>
#include "lex.h"
#include "parse.h"
#include "utils.h"
#include "tokens.h"

//*******************************************
// Find a PROG non-terminal
// NOTE: this code is not complete
bool FindPROG()
{
    if (!FindSTMTS())
    {
        Error("Program");
        return false;
    }
    else
    {
        int token = PeekToken();
        if (token != END)
        {
            Error("END");
            return false;
        }
        AdvanceToken();
        return true;
    }

}
//*******************************************
// Find a STMT non-terminal
// NOTE: this code is not complete
bool FindSTMT()
{
    if (!FindEXPR())
    {
        Error("Expression");
        return false;
    }
    else
    {
        int token = PeekToken();
        if(token != ';')
        {
            return false;
        }
        std::cout << "Found a statement\n";
        return true;
    }

}
bool FindSTMTS()
{
    while(FindSTMT())
    {}

    return true;
}
bool FindEXPR()
{
    return false;
}
bool FindEXPR_P()
{
    return false;
}
bool FindPLUSOP()
{
    return false;
}
bool FindTERM()
{
    return false;
}
bool FindTERM_P()
{
    return false;
}
bool FindTIMESOP()
{
    return false;
}

/*******************************************
bool FindExample()
{
    if (!FindPART1()) return false;
    
    int token = PeekToken();
    if (token != '+') return false;
    AdvanceToken();         // past '+'

    if (!FindPART2()) return false;

    return true;
}
*/

