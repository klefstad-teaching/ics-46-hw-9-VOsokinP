#include "ladder.h"

int main()
{
    std::string s1 = "marty";
    std::string s2 = "curls";
    int d = 3;

    if(edit_distance_within(s1, s2, d))
        cout << s1 << " is within " << d << " edit(s) from " << s2 << endl;
    else
        cout << s1 << " is further than " << d << " edit(s) from " << s2 << endl;

    verify_word_ladder();

    return 0;
}