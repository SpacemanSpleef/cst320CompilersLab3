//************************************** 
//
// parse.cpp 
// Starting point for top-down recursive-descent parser 
// Used in CST 320 Lab2 
// 
// Author: Phil Howard 
// phil.howard@oit.edu 

#include <iostream> 
#include "lex.h" 
#include "parse.h" 
#include "utils.h" 
#include "tokens.h" 
//******************************************* 
// // Find a PROG non-terminal /
// / NOTE: this code is not complete 
bool FindPROG() 
{ 
    if (!FindSTMTS()) 
    { Error("Program"); return false; } 
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
//******************************************* // Find a STMT non-terminal 
// // NOTE: this code is not complete
bool FindSTMT() 
{ 
    if (FindEXPR()) 
    { 
        int token = PeekToken(); 
        if(token != ';') 
        { 
            return false; 
        } 
        AdvanceToken(); 
        std::cout << "Found a statement\n";
        return true; 
    }
    else if(PeekToken() == IDENTIFIER)
    {
        AdvanceToken();
        if(PeekToken() == '=')
        {
            AdvanceToken();
            if(FindEXPR()) 
            {
                 //AdvanceToken();
                 if(PeekToken() != ';')
                { 
                    return false; 
                } 
                else 
                { 
                    std::cout << "Found a statement\n";
                    return true; 
                } 
            } 
        } 
    } 
    Error(";"); 
    return false; 
} 
bool FindSTMTS() 
{ 
    while(FindSTMT()) 
    {}
    return true; 
}
bool FindEXPR() 
{
    int token = PeekToken();
    if(token == '(')
    {
        AdvanceToken();
        if(FindEXPR()) 
        { 
            token = PeekToken();
            if(token ==')') 
            { 
                AdvanceToken();
                if(FindEXPR_P()) 
                { 
                    return true; 
                } 
            } 
        } 
    } 
    else if(FindTERM()) 
    { 
        return true; 
    } 
    return false; 
} 
bool FindEXPR_P() 
{ 
    if(FindPLUSOP())
     { 
        int token = PeekToken();
        if(token == '(') 
        { 
            AdvanceToken();
            if(FindEXPR())
            { 
                token = PeekToken();
                if(token ==')')
                { 
                    AdvanceToken();
                    if(FindEXPR_P()) 
                    { 
                        return true; 
                    } 
                } 
            }
        } 
    } 
    return true; 
} 
bool FindPLUSOP() 
{ 
    int token = PeekToken();
    if(token == '+' || token == '-') 
    { 
        AdvanceToken(); 
        return true; 
    }
    return false; 
} 
bool FindTERM() 
{ 
    int token = PeekToken();
    if(token == '[') 
    { 
        AdvanceToken();
        if(FindEXPR()) 
        { 
            token = PeekToken(); 
            if(token == ']') 
            { 
                AdvanceToken(); 
                if(FindTERM_P()) 
                { 
                    return true; 
                } 
            } 
        } 
    } 
    else if (token == NUM) 
    { 
        AdvanceToken(); 
        return true; 
    } else if(token == '{') 
    { 
        AdvanceToken(); 
        token = PeekToken(); 
        if(token == IDENTIFIER) 
        { 
            AdvanceToken(); 
            token = PeekToken(); 
            if(token == '}') 
            { 
                AdvanceToken(); 
                return true; 
            } 
        } 
    } 
    return false; 
} 
bool FindTERM_P() 
{ 
    if(FindTIMESOP()) 
    { 
        int token = PeekToken();
        if(token == '[') 
        { 
            AdvanceToken(); 
            if(FindEXPR()) 
            { 
                token = PeekToken(); 
                if(token ==']') 
                { 
                    AdvanceToken(); 
                    if(FindTERM_P()) 
                    { 
                        return true; 
                    } 
                } 
            } 
        } 
    } 
    return true; 
} 
bool FindTIMESOP() 
{ 
    int token;
    token = PeekToken(); 
    if(token == '*' || token == '/') 
    { 
        AdvanceToken(); 
        return true; 
    } 
    return false; 
} 
// /******************************************* bool FindExample() { if (!FindPART1()) return false; int token = PeekToken(); if (token != '+') return false; AdvanceToken(); // past '+' if (!FindPART2()) return false; return true; } */