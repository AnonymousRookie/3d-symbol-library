#ifndef BASE_STRING_UTILS_H
#define BASE_STRING_UTILS_H

#include <vector>
#include <string>
#include <sstream>
#include "Uncopyable.h"


class StringUtils : Base::Uncopyable 
{
public:
    // ��ָ���ָ������ַ�������split
    static std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    static std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

    // �ַ��� ת���� float ����
    static float stringToFloat(const std::string& str) {  
        std::istringstream iss(str);  
        float num;  
        iss >> num;  
        return num;      
    }
};



#endif  // BASE_STRING_UTILS_H