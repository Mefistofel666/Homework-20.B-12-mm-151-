// #include <iostream>
// #include "Stack.h"
// #include <string>
// #include <ctype.h>

// int calculate(std::string str_in)
// {
//     Stack val_stack(NULL);
//     int n1, n2, res;
//     for (int i = 0; i < str_in.length(); ++i)
//     {
//         if (isdigit(str_in[i]))
//         {
//             val_stack.push(str_in[i]);
//         }
//         else
//         {
//             n2 = val_stack.pop();
//             n1 = val_stack.pop();
//             switch (str_in[i])
//             {
//             case '+':
//                 res = n1 + n2;
//                 break;
//             case '-':
//                 res = n1 - n2;
//                 break;
//             case '*':
//                 res = n1 * n2;
//                 break;
//             case '/':
//                 res = n1 / n2;
//                 break;
//             default:
//                 std::cout << "Ошибка !\n";
//             }
//             val_stack.push(res);
//         }
        
//     }
//     return val_stack.pop();
// }



// int prior(char a)
// {
//     switch (a)
//     {
//     case '*':
//         return 3;
//     case '/':
//         return 3;
//     case '+':
//         return 2;
//     case '-':
//         return 2;
//     case '(':
//         return 1;
//     }
//     return 0;
// }

// int main()
// {
//     std::string s;
//     getline(std::cin, s);
//     std::string res;
//     Stack op(NULL);

//     for (size_t i = 0; i < s.size(); i++)
//     {
//         if ((s[i] >= 'a') && (s[i] <= 'z'))
//         {
//             res += s[i];
//         }
//         if (s[i] == '(')
//         {
//             op.push(s[i]);
//         }
//         if (s[i] == ')')
//         {
//             while ((op.head->data) != '(')
//             {
//                 res += op.pop();
//             }
//             op.pop();
//         }
//         if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
//         {
//             while ((op.head != NULL) && (prior(op.head->data) >= prior(s[i])))
//             {
//                 res += op.pop();
//             }
//             op.push(s[i]);
//         }
//     }

//     while (op.head != NULL)
//     {
//         res += op.pop();
//     }
//     std::cout << "res: " << res << "\n";
//     std::cout << s << "\n";

//     std::string a = "56+78*";

//     std::cout << calculate(a);


//     Stack result(NULL);

//     return 0;
// }