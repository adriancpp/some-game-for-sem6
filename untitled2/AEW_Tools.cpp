#include <sstream>

using namespace std;

class AEW_Tools
{
    public:
        static string IntToStr(int zmienna)
        {
            stringstream ss;
            string temp;
            ss << zmienna;
            ss >> temp;
            return temp;
        }
};
