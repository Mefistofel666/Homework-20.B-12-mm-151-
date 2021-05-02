#include <iostream>
#include <map>
#include <vector>

int predict(st)
    std::map<uint8_t, int> class_freq;
    for(int i = 0; i < neighbours->size(); i++)
    {
        if(class_freq.find(neighbours->at(i)->get_label()) == class_freq.end())
        {
            class_freq[neighbours->at(i)->get_label()] = 1;
        }else
        {
            class_freq[neighbours->at(i)->get_label()]++;
        }
    }
}
