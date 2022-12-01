#include <iostream>
#include <sstream>

using namespace std;

std::string decodeEscape(const std::string &input)
{
    std::ostringstream s{};
    for (auto iter = input.begin(); iter != input.end(); iter++) {
        // Print current character
        const auto currentChar = *iter;
        const auto nextChar = (iter + 1 == input.end()) ? '\0' : *(iter + 1);

        /*
            An escape backslash found
            To prevent Json is failed to parsing, need to handle for the "\'" (= '\\' + '\'') and "\?" (= '\\' + '\?') only.
            Other Escape Sequence are not needed.
        */
        if (currentChar == '\\') {
            switch (nextChar) {
            case '\'': s << "\'"; break;
            case '?': s << "\?"; break;
            default:
                s << currentChar;
                continue;
            }
            // nextChar is concatenated, skip it in the next loop
            iter++;
        } else {
            s << currentChar;
        }
    }
    return s.str();
}

int main()
{
    string str = "\\\?\\\?!"; // this data correct from media
    string str2 = "??!";      // this incorrect from media
    

    cout << "Str Without processing: " << str << endl;
    cout << "Str Decode escape: " << decodeEscape(str) << endl;
    
    cout << "Str2 without decode: " << str2 << endl;
    cout << "Str2 decoded: " << decodeEscape(str2) << endl;
        
    string str3 = "\\\'I am between single quote\\\'"; // this from media
    cout << "str3 without processing: " << str3 << endl;
    cout << "str3 decode escape: " << decodeEscape(str3) << endl;
    
    return 0;
}