#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

int main()
{

    std::vector<std::string> tests{"tests/test1_in.txt", "tests/test2_in.txt", "tests/test3_in.txt", "tests/test4_in.txt", "tests/test5_in.txt"};

    for (size_t i = 0; i < tests.size(); i++)
    {

        std::string tmp = "myprog.exe < " + tests[i];
        const char *c = tmp.c_str();
        system(c);

        std::string line;

        std::ifstream in("test1_out.txt");

        getline(in, line);

        std::string ans;
        std::ostringstream stream;
        stream << "out/out" << (i + 1) << ".txt";

        std::string str = stream.str();

        std::ifstream in_ans(str);

        getline(in_ans, ans);

        if (ans == line)
            std::cout << "OK"
                      << " ";
        else
            std::cout << "Error"
                      << " ";
    }

    return 0;
}