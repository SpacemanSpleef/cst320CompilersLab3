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

void synchronize(int syncToken) {
    while (PeekToken() != syncToken && PeekToken() != END) {
        AdvanceToken();
    }
    if (PeekToken() == syncToken) {
        AdvanceToken(); // skip the sync token
    }
}

//******************************************* 
// // Find a PROG non-terminal /
// / NOTE: this code is not complete 
bool FindPROG() 
{ 
    if (!FindSTMTS()) 
    { 
        Error("Program"); 
        return false; 
    } 
    else 
    { 
        if (PeekToken() != END) 
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
while (PeekToken() != IDENTIFIER &&
           PeekToken() != NUM &&
           PeekToken() != '[' &&
           PeekToken() != '(' &&
           PeekToken() != '{' &&
           PeekToken() != END) 
    {
        synchronize(';');
        if(PeekToken() == END)
        {break;}
        //AdvanceToken();
    }
    if(PeekToken() == IDENTIFIER)
    {
        AdvanceToken();
        if(PeekToken() == '=')
        {
            AdvanceToken();
            if(FindEXPR()) 
            {
                 //AdvanceToken();
                 if(PeekToken() == ';')
                { 
                    AdvanceToken();
                    std::cout << "Found a statement\n";
                    return true; 
                } 
                else 
                { 
                    Error(";");
                    synchronize(';');
                    return false;
                } 
            }
            else
            {
                Error("Expression");
                synchronize(';');
                return false;
            }
        } else
        {
            Error("=");
            synchronize(';');
            return false;
        }
    } 
    else if (FindEXPR()) 
    { 
        if(PeekToken() == ';') 
        { 
            AdvanceToken(); 
            std::cout << "Found a statement\n";
            return true;  
        } 
        else
        {
            Error(";");
            synchronize(';');
            return false;
        }
    } 
    return false; 
} 
bool FindSTMTS() 
{ 
    while(PeekToken() != END) 
    {
        FindSTMT();
    }
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
    while (FindPLUSOP())
    {
        if (PeekToken() == '(')
        {
            AdvanceToken();

            if (!FindEXPR())
            {
                Error("expression");
                synchronize(')');
                return false;
            }

            if (PeekToken() != ')')
            {
                Error(")");           
                synchronize(')');      
                return false;
            }

            AdvanceToken(); 
        }
        else
        {
            Error("(");                
            synchronize(';');          
            return false;
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
    
    while (PeekToken() == '*' || PeekToken() == '/')
    {
        AdvanceToken();

        if (PeekToken() != '[')
        {
            Error("[");
            synchronize(';'); 
            return false;
        }

        
        AdvanceToken();
        if (!FindEXPR())
        {
            Error("expression");
            synchronize(']');
            return false;
        }

        if (PeekToken() != ']')
        {
            Error("]");
            synchronize(';');
            return false;
        }

        AdvanceToken();
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