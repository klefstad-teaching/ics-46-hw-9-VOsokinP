#include "ladder.h"

void error(string word1, string word2, string msg)
{
    cerr << "Error: " << msg  << ". \nIn words: " << word1 << " and " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{

	int m = str1.size();
    int n = str2.size();

    if (abs(m - n) > d) return false;

    std::vector<int> prev(n+1);
    std::vector<int> curr(n+1);

    for(int j = 0; j <= n; ++j)
        prev[j] = j;

    for(int i = 1; i <= m; ++i)
    {
        curr[0] = i;
        for(int j = 1; j <= n; ++j)
        {
            if(str1[i - 1] == str2[j - 1])
                curr[j] = prev[j - 1];
            else
                curr[j] = 1 + std::min({prev[j], curr[j - 1], prev[j - 1]});
        }
        prev = curr;
    }
    return prev[n] <= d;
}

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if(begin_word == end_word)
    {
        error(begin_word, end_word, "same word as a start and as an end");
        return {};
    }
    queue<vector<string>> lq;
    lq.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while(!lq.empty())
    {
        vector<string> ladder = lq.front();
        lq.pop();
        string last_word = ladder.back();
        for(string word : word_list)
        {
            if(is_adjacent(last_word, word))
            {
                if(!visited.contains(word))
                {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if(word == end_word)
                        return new_ladder;
                    lq.push(new_ladder);
                }
            }
        }
    }
    error(begin_word, end_word, "no ladder found");
    return {};
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream f(file_name);
    if(!f.is_open())
    {
        cerr << "Input file missing" << endl;
        return;
    }

    string line;

    while(getline(f, line))
        word_list.insert(line);
    f.close();

}

void print_word_ladder(const vector<string>& ladder)
{
    for(int i = 0; i < ladder.size(); ++i)
    {
        cout << ladder[i];
        if(i < ladder.size() - 1)
            cout << " ";
    }
    cout << endl;
}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}