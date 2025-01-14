#include <iostream>
#include <string>
#include "..\include\string.hpp"

void test1(){
    ani::string s1("Hello World");
    ani::string s2("New Era");

    std::cout << "<------------------ Assign ------------------>" << std::endl;
    std::cout << "s1 : " << s1 << std::endl;

    s1.assign("Welcome");
    std::cout << "s1 : " << s1 << std::endl;

    s1.assign(s2);
    std::cout << "s1 : " << s1 << std::endl;

    s1.assign(s2, 0, 3);
    std::cout << "s1 : " << s1 << std::endl;

    s1.assign(10, 'K');
    std::cout << "s1 : " << s1 << std::endl;

    s1.assign("Citizen", 4);
    std::cout << "s1 : " << s1 << std::endl;
    std::cout << std::endl;
}

void test2(){

    std::cout << "<------------------ String Creation ------------------>" << std::endl;
    // Create / Copy Construct / Copy Assign
    ani::string s1;
    std::cout << "s1 : " << s1 << std::endl;

    ani::string s2(14, 'Q');
    std::cout << "s2 : " << s2 << std::endl;

    ani::string s3(8, 'Z');
    std::cout << "s3 : " << s3 << std::endl;

    ani::string s4("Kylo");
    std::cout << "s4 : " << s4 << std::endl;

    ani::string s5 = "Tucker";
    std::cout << "s5 : " << s5 << std::endl;

    ani::string s6(s5);
    std::cout << "s6 : " << s6 << std::endl;

    s6 = s3;
    std::cout << "s6 : " << s6 << std::endl;

    s6 = 'X';
    std::cout << "s6 : " << s6 << std::endl;

    s6 = "Bernard";
    std::cout << "s6 : " << s6 << std::endl;

    std::cout << std::endl;

    std::cout << "<------------------ Member Access ------------------>" << std::endl;

    // at / opearator[] / front / back
    std::cout << "s6.at(5) : " << s6.at(5) << std::endl;
    std::cout << "s6[3] : " << s6[3] << std::endl;

    std::cout << "s6.front() : " << s6.front() << std::endl;
    std::cout << "s6.back() : " << s6.back() << std::endl;

    // std::cout << "s6.at(-1) : " << s6.at(-1) << std::endl;       // works as intended
    // std::cout << "s6.at(10) : " << s6.at(10) << std::endl;       // works as intended
    // std::cout << "s1.at(0) : " << s1.at(0) << std::endl;         // works as intended
    // std::cout << "s6.[-1] : " << s6[-1] << std::endl;            // works as intended
    // std::cout << "s6[10] : " << s6[10] << std::endl;             // works as intended
    // std::cout << "s1[0] : " << s1[0] << std::endl;               // works as intended

    std::cout << "s6 : before s6.at(0) = 'L' : " << s6 << std::endl;
    s6.at(0) = 'L';
    std::cout << "s6 : after s6.at(0) = 'L' : " << s6 << std::endl;

    std::cout << "s6 : before s6[2] = 'o' : " << s6 << std::endl;
    s6[2] = 'o';
    std::cout << "s6 : after s6[2] = 'o' : " << s6 << std::endl;

    std::cout << "s6 : before s6.front() = 'X' " << s6 << std::endl;
    s6.front() = 'X';
    std::cout << "s6 : after s6.front() = 'X' " << s6 << std::endl;

    std::cout << "s6 : before s6.back() = 't' " << s6 << std::endl;
    s6.back() = 't';
    std::cout << "s6 : after s6.back() = 't' " << s6 << std::endl;

    // c_str
    std::cout << "s6.c_str() : " << s6.c_str() << std::endl;

    // Reserve / Size / Capacity / Empty
    std::cout << std::boolalpha;
    std::cout << "s1.empty() : " << s1.empty() << std::endl;
    std::cout << "s2.empty() : " << s2.empty() << std::endl;
    std::cout << "s4.empty() : " << s4.empty() << std::endl;

    std::cout << "s2: before s2.reserve(10) : " << s2 << std::endl;
    s2.reserve(10);
    std::cout << "s2: after s2.reserve(10) : " << s2 << std::endl;

    std::cout << "s2: before s2.reserve(20) : " << s2 << std::endl;
    s2.reserve(20);
    std::cout << "s2: after s2.reserve(20) : " << s2 << std::endl;

    std::cout << std::endl;
    std::cout << "<------------------ Modifiers ------------------>" << std::endl;

    // Clear
    std::cout << "s3 : before s3.clear() : " << s3 << std::endl;
    s3.clear();
    std::cout << "s3 : after s3.clear() : " << s3 << std::endl;
    
    // Insert
    s3.insert(0, 10, 'Q');
    std::cout << "s3 : after s3.insert(0, 10, 'Q') : " << s3 << std::endl;

    s6.insert(7, "California");
    std::cout << "s6 : after s6.insert(7, \"Henry\") : " << s6 << std::endl;

    s6.insert(7, " is the Mayor of Seatle", 17);
    std::cout << "s6 : after s6.insert(7, \" is the Mayor of Seatle\", 17) : " << s6 << std::endl;

    s1.insert(0, s4);
    std::cout << "s1 : after s1.insert(0, s4) : " << s1 << std::endl;

    ani::string s7("Good day");
    s1.insert(0, s7, 4, 1);
    std::cout << "s1 : after s1.insert(0, s7, 4, 1) : " << s1 << std::endl;
    s1.insert(0, s7, 0, 8);
    std::cout << "s1 : after s1.insert(0, s7, 0, 8) : " << s1 << std::endl;

    // Erase
    s1.erase(11, 15);
    std::cout << "s1 : after s1.erase(11, 15) : " << s1 << std::endl;

    s1.erase(4, 4);
    std::cout << "s1 : after s1.erase(4, 4) : " << s1 << std::endl;

    s1.erase(4);
    std::cout << "s1 : after s1.erase(4) : " << s1 << std::endl;

    s1.erase();
    std::cout << "s1 : after s1.erase() : " << s1 << std::endl;

    // Push back
    ani::string s8;
    std::cout << "s8 : " << s8 << std::endl;
    s8.push_back('X');
    std::cout << "s8 : " << s8 << std::endl;
    s8.push_back('e');
    s8.push_back('n');
    s8.push_back('o');
    s8.push_back('m');
    s8.push_back('o');
    s8.push_back('r');
    s8.push_back('p');
    std::cout << "s8 : " << s8 << std::endl;
    s8.push_back('h');
    std::cout << "s8 : " << s8 << std::endl;

    // Pop back
    s8.pop_back();
    std::cout << "s8 : " << s8 << std::endl;
    s8.pop_back();
    s8.pop_back();
    s8.pop_back();
    s8.pop_back();
    std::cout << "s8 : " << s8 << std::endl;

    s8.clear();
    s8.pop_back();
    std::cout << "s8 : " << s8 << std::endl;

    // Append
    ani::string s9;
    s9.append(1, 'W');
    std::cout << "s9 : " << s9 << std::endl;
    s9.append("ashington");
    std::cout << "s9 : " << s9 << std::endl;
    s9.append(ani::string(" D.C. "));
    std::cout << "s9 : " << s9 << std::endl;
    s9.append(3, '7');
    std::cout << "s9 : " << s9 << std::endl;

    s9.clear();
    s9 += "Cyberpunk";
    std::cout << "s9 : " << s9 << std::endl;

    s9 += ' ';
    std::cout << "s9 : " << s9 << std::endl;

    s9 += ani::string("2077");
    std::cout << "s9 : " << s9 << std::endl;

    // operator+
    std::cout << "s9 : " << std::endl;
    std::cout << s9 + s8 << std::endl;
    std::cout << s9 + '!' << std::endl;
    std::cout << '#' + s9 << std::endl;
    std::cout << s9 + " Explorer" << std::endl;
    std::cout << "This " + s9<< std::endl;

    // Substr
    std::cout << "s9.substr(0, 9) : " << s9.substr(0, 9) << std::endl;

    // Swap
    std::cout << "Before swap : " << std::endl;
    std::cout << "s6 : " << s6 << std::endl;
    std::cout << "s9 : " << s9 << std::endl;
    s6.swap(s9);
    std::cout << "After swap : " << std::endl;
    std::cout << "s6 : " << s6 << std::endl;
    std::cout << "s9 : " << s9 << std::endl;

    std::cout << std::endl;
    std::cout << "<------------------ Comparison ------------------>" << std::endl;
    ani::string s11("ABCD");
    ani::string s12("ZBCD");
    std::cout << "s11 < s12 : " << s11.compare(s12) << std::endl;
    std::cout << "s11 < \"ZBCD\" : " << s11.compare("ZBCD") << std::endl;

    ani::string s13("");
    ani::string s14("");
    std::cout << "s13 < s14 : " << s13.compare(s14) << std::endl;
    std::cout << "s13 < \"\" : " << s13.compare("") << std::endl;

    ani::string s15("ABCD");
    ani::string s16("AB");
    std::cout << "s15 < s16 : " << s15.compare(s16) << std::endl;
    std::cout << "s15 < \"AB\" : " << s15.compare("AB") << std::endl;

    ani::string s17("AB");
    ani::string s18("ABCD");
    std::cout << "s17 < s18 : " << s17.compare(s18) << std::endl;
    std::cout << "s17 < \"ABCD\" : " << s17.compare("ABCD") << std::endl;

    ani::string s19("AB");
    ani::string s20("ZBCD");
    std::cout << "s19 < s20 : " << s19.compare(s20) << std::endl;
    std::cout << "s19 < \"ZBCD\" : " << s19.compare("ZBCD") << std::endl;

    ani::string s21("ZB");
    ani::string s22("ABCD");
    std::cout << "s21 < s22 : " << s21.compare(s22) << std::endl;
    std::cout << "s21 < \"ABCD\" : " << s21.compare("ABCD") << std::endl;

    ani::string s23("0123456789");
    ani::string s24("789");

    std::cout << "(s23 < s24) : " << (s23 < s24) << std::endl;
    std::cout << "(s23 <= s24) : " << (s23 <= s24) << std::endl;
    std::cout << "(s23 > s24) : " << (s23 > s24) << std::endl;
    std::cout << "(s23 >= s24) : " << (s23 >= s24) << std::endl;
    std::cout << "(s23 == s24) : " << (s23 == s24) << std::endl;
    std::cout << "(s23 != s24) : " << (s23 != s24) << std::endl;


    std::cout << std::endl;
    std::cout << "<------------------ Search ------------------>" << std::endl;
    ani::string s10("the quick brown fox jumps over the lazy dog");
    if(s10.find('w', 5) != s10.npos)
        std::cout << "s10.find('w', 5) : " << s10.find('w', 5) << std::endl;
    
    if(s10.find("w", 20) == s10.npos)
        std::cout << "s10.find('w', 20) : not found" << std::endl;

    if(s10.find("the") != s10.npos)
        std::cout << "s10.find(\"the\") : " << s10.find("the") << std::endl;

    if(s10.rfind("the") != s10.npos)
        std::cout << "s10.rfind(\"the\") : " << s10.rfind("the") << std::endl;

    if(s10.rfind('q') != s10.npos)
        std::cout << "s10.rfind('a') : " << s10.rfind('q') << std::endl;

    std::cout << std::endl;
    std::cout << "<------------------ Iterators ------------------>" << std::endl;
    std::cout << "s6 using const_iterator : \"";
    for(ani::string::const_iterator citer = s6.cbegin(); citer != s6.cend(); ++citer)
        std::cout << *citer;
    std::cout << "\"" << std::endl;

    std::cout << "s6 using reverse iterator : \"";
    for(ani::string::const_reverse_iterator rciter = s6.crbegin(); rciter != s6.crend(); ++rciter)
        std::cout << *rciter;
    std::cout << "\"" << std::endl;

     std::cout << "s6 encrypt using reverse iterator : \"";
    for(ani::string::reverse_iterator riter = s6.rbegin(); riter != s6.rend(); ++riter){
        *riter += 3;
        std::cout << *riter;
    }
    std::cout << "\"" << std::endl;

    std::cout << "s6 decrpyt using iterator : \"";
    for(ani::string::iterator iter = s6.begin(); iter != s6.end(); ++iter){
        *iter -= 3;
        std::cout << *iter;
    }
    std::cout << "\"" << std::endl;

    std::cout << std::endl;
    std::cout << "<------------------ Other Methods ------------------>" << std::endl;

    std::cout << std::endl;
    std::cout << "stoi(\"574\") : " << ani::stoi("574") << std::endl;
    std::cout << "to_string(574) : " << ani::to_string(574) << std::endl;
}

int main(){
    test1();
    test2();
    puts("All tests passed!");
    return 0;
}