#include <iostream>
#include <string>
#include "TLStack.h"
#include "TLCalculator.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "russian");
    setlocale(LC_NUMERIC, "eng");

    TLStack<int> s;

    cout << "Console TLStack demo\n";
    cout << "=========================\n\n";

    cout << "Stack s:\n" << s << " (IsEmpty = " << s.IsEmpty() << ")\n\n";

    for (int i = 1; i <= 3; i++)
    {
        s.Push(i);
        cout << s << " (IsEmpty = " << s.IsEmpty() << ")\n\n";
    }

    cout << "Let's assign s to s2 and clear s. The result is:\n\n";
    TLStack<int> s2 = s;
    s.Clear();

    cout << "s: " << s << " (IsEmpty = " << s.IsEmpty() << ")\n";
    cout << "s2: " << s2 << " (IsEmpty = " << s2.IsEmpty() << ")\n\n";

    cout << "Then we can try to pop from an empty s:\n";
    try {
        s.Pop();
    }
    catch (TLStackException e)
    {
        cout << e << "\n";
    }

    cout << "Or just simply get the top element of s:\n";
    try {
        s.Top();
    }
    catch (TLStackException e)
    {
        cout << e << "\n";
    }

    cout << "So, let's continue with s2:\n";
    while(s2.IsNotEmpty())
    {
        cout << s2.Pop() << " popped\n";
        cout << s2 << " (IsEmpty = " << s2.IsEmpty() << ")\n\n";
    }

    cout << "Other tests:\n\n";

    TLStack<int> s3;
    for (int i = 1; i <= 5; i++)
        s3.Push(i);

    cout << "s3:\n" << s3 << " (IsEmpty = " << s3.IsEmpty() << ")\n\n";

    TLStack<int> s4(s3);
    cout << "s4(s3):\n" << s4 << " (IsEmpty = " << s4.IsEmpty() << ")\n\n";

    cout << "(s3 == s4) = " << (s3 == s4) << "\n\n";

    TLStack<int> s5;
    for (int i = 1; i <= 5; i++)
        s5.Push(i);
    cout << "s5:\n" << s5 << " (IsEmpty = " << s5.IsEmpty() << ")\n\n";

    cout << "(s5 == s3) = " << (s5 == s3) << "\n\n";
    cout << "(s5 == s4) = " << (s5 == s4) << "\n\n";


    TLCalculator calc;
    string str;

    cout << "Console TLCalculator\n";
    cout << "=========================\n\n";
    while (true)
    {
        cout << "Enter your expression:\n\n";
        getline(cin, str);
        cout << "========================\n\n";
        calc.SetExpr(str);
        cout << "Expression: " << calc.GetExpr() << "\n\n";

        bool bracesOk = calc.CheckExpr();
        if (bracesOk) {
            cout << "Braces are correct :)\n\n";
        }
        else {
            cout << "Braces are incorrect :(\n\n";
            continue;
        }

        cout << "Postfix: ";
        calc.PreparePostfix();
        cout << calc.GetPostfix() << "\n\n";

        cout << "Result (CalcPostfix):  ";
        try
        {
            cout << calc.CalcPostfix() << "\n";
        }
        catch (...)
        {
            cout << "Exception\n\n";
        }

        cout << "Result (Calc):         ";
        try
        {
            cout << calc.Calc() << "\n\n";
        }
        catch (...)
        {
            cout << "Exception\n\n";
        }
        cout << "==================================\n\n";
    }
}