#include <iostream>
#include "Stack.h"
#include <string>
#include <ctype.h>
#include <vector>

bool IsNumber(std::string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!isdigit(s[i]))
            return false;
    }
    return true;
}

std::vector<std::string> to_vector(std::string s)
{
    s += " ";
    std::vector<std::string> vec;
    std::string temp = "";
    std::string tmp;

    //преобразование
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            if (temp != "")
            {
                vec.push_back(temp);
                temp.clear();
            }
        }
        else if (i == s.length() - 1)
        {
            vec.push_back(tmp);
            tmp.clear();
        }
        else if (s[i] == ')' || s[i] == '(' || s[i] == '*' || s[i] == '+')
        {
            tmp += s[i];
            vec.push_back(tmp);
            tmp.clear();
        }
        else
        {
            tmp += s[i];
            temp += tmp;
            tmp.clear();
        }
    }
    return vec;
}

int calculate(std::vector<std::string> vec)
{
    Stack val_stack("");
    int n1, n2, res;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (IsNumber(vec[i]))
        {
            val_stack.push(vec[i]);
        }
        else
        {
            n2 = stoi(val_stack.pop());
            n1 = stoi(val_stack.pop());
            // std::cout<<"n1 = " << n1 << ", n2= " << n2 << "\n";

            if (vec[i] == "+")
                res = n1 + n2;
            if (vec[i] == "-")
                res = n1 - n2;
            if (vec[i] == "*")
                res = n1 * n2;
            if (vec[i] == "/")
                res = n1 / n2;

            // std::cout << "res = " << res<< "\n";

            val_stack.push(std::to_string(res));
        }
    }

    return res;
}

int prior(std::string a)
{

    if (a == "*" || a == "/")
        return 3;
    if (a == "+" || a == "-")
        return 2;
    if (a == "(")
        return 1;
    return 0;
}

int main()
{
    std::string s = "15 + 2 * ( 3 + 5 )";


    // getline(std::cin, s);

    std::vector<std::string> vec_s = to_vector(s);



    std::vector<std::string> res;

    Stack op("");

    for (size_t i = 0; i < vec_s.size(); i++)
    {
        if (IsNumber(vec_s[i]))
        {
            res.push_back(vec_s[i]);
        }

        if (vec_s[i] == "(")
        {
            op.push(vec_s[i]);
        }
        if (vec_s[i] == ")")
        {
            while ((op.head->data) != "(")
            {
                res.push_back(op.pop());
            }
            op.pop();
        }
        if (vec_s[i] == "+" || vec_s[i] == "-" || vec_s[i] == "*" || vec_s[i] == "/")
        {
            while ((op.head != NULL) && (prior(op.head->data) >= prior(vec_s[i])))
            {
                res.push_back(op.pop());
            }
            op.push(vec_s[i]);
        }
    }

    while (op.head != NULL)
    {
        res.push_back(op.pop());
    }

    for (int i = 0; i < res.size(); i++)
        std::cout << res[i] << " ";
    std::cout << "\n";
    std::cout << "calc: " << calculate(res);

    return 0;
}