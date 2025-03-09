#include "ladder.h"

void error(string word1, string word2, string msg)
{
    cerr << "Error: " << msg  << ". \nWords: " << word1 << " and " << word2 << endl;
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

vector<string> generate_neighbors(const string& word, const set<string>& word_list)
{
    vector<string> neighbors;
    string potential_word;

    for(size_t i = 0; i < word.size(); ++i)
    {
        potential_word = word;
        for(char chr = 'a'; chr <= 'z'; chr++)
        {
            if(potential_word[i] == chr)
                continue;
            potential_word[i] = chr;
            if(word_list.find(potential_word) != word_list.end())
                neighbors.push_back(potential_word);
        }
    }

    for(size_t i = 0; i < word.size(); ++i)
    {
        potential_word = word.substr(0, i) + word.substr(i + 1);
        if(!potential_word.empty() && word_list.find(potential_word) != word_list.end())
            neighbors.push_back(potential_word);
    }

    for(size_t i = 0; i <= word.size(); ++i)
    {
        for(char chr = 'a'; chr <= 'z'; ++chr)
        {
            potential_word = word.substr(0, i) + chr + word.substr(i);
            if(word_list.find(potential_word) != word_list.end())
                neighbors.push_back(potential_word);
        }
    }
    sort(neighbors.begin(), neighbors.end());
    return neighbors;
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

        vector<string> neighbors = generate_neighbors(last_word, word_list);
        for(const string &neighbor : neighbors)
        {
            if(visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(neighbor);
                if(neighbor == end_word)
                    return new_ladder;
                lq.push(new_ladder);
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
    {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        word_list.insert(line);
    }
    f.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    if(ladder.size() == 0)
        cout << "No word ladder found.";
    else
    {
        cout << "Word ladder found: ";
        for(int i = 0; i < ladder.size(); ++i)
        {
            cout << ladder[i] << " ";
        }
    }
    cout << endl;
}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");
    print_word_ladder(generate_word_ladder("awake", "sleep", word_list));
    // my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    // my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    // my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    // my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    // my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    // my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}