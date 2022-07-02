#include<bits/stdc++.h>
using namespace std;
//creating a size of all the alphabets
const int size=26;
//creating  a  node

//creating a class for node
class trienode
{
    public:
    //unodered map is a standard template library which 
    //uses the concept of hash table which maps the keys to values
    //creating the node for storing the children node
    unordered_map<char,trienode *>children;
    bool endofword;

    trienode()
    {
        endofword=false;
    }
};

class trie
{
    public:
    int total_nodes;
    int total_words;
    //using the composition class
    trienode *root;
    trie()
    {
        //calling the constructor of the node class
        root=new trienode();
    }
    void insert(string str);
    void remove(string str);
    bool _remove(trienode *curr,string str,int index);
    trienode *search_exact(string str);
    vector<string> search_pre(string str);
};

//dfs for prefix search
void get_words_dfs(trienode *current, string pre, vector<string> &results)
{
    if (current == NULL)
    {
        return;
    }
    if (current->endofword)
    {
        results.push_back(pre);
    }

    for (auto i : current->children)
    {
        get_words_dfs(i.second, (pre + i.first), results);
    }
}

//prefix search function
vector<string> trie::search_pre(string str)
{
    auto start = std::chrono::high_resolution_clock::now();
    trienode *current = root;
    vector<string> results;

    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        if (current->children.find(ch) != current->children.end())
        {
            current = current->children[ch];
        }
        else
        {
            return results;
        }
    }

    get_words_dfs(current, str, results);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"<< results.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return results;
}

//insertion in tree
void trie::insert(string str)
{
    trienode *current=root;
    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        if (current->children.find(ch) != current->children.end())
        {
            current = current->children[ch];
        }
        else
        {
            //using the unordered map data structure ,insert function
            //which map the specific key to value
            current->children.insert(make_pair(ch,new trienode()));
            current = current->children[ch];
        }
    }

    current->endofword= true;
}
//removing an element from string
void trie::remove(string str)
{
    //calling the remove function which revursively calls itself
    _remove(root,str,0);
}

bool trie:: _remove(trienode *curr,string str,int index)
{
    if(index==str.length())
    {
        if(!curr->endofword)
        {
            return false;//word doesn't exist
        }
        curr->endofword=false;

        return curr->children.size()==0;
    }

    char i=str[index];

    if(!curr->children[i])
    {
        return false;//word don't exist
    }
    //calling the function recursively
    bool deletenode=_remove(curr->children[i],str, index + 1);

    if(deletenode)
    {
        if(!curr)
        {
            curr->children.erase(i);
            return curr->children.size()==0;
        }

    }

    return 0;
}
//exact search function,it tells whether the string exists or not
trienode *trie::search_exact(string str)
{
    trienode *current=root;
    auto start=std::chrono::high_resolution_clock::now();
    for(int i=0;i<str.size();i++)
    {
        char ch=str[i];
        if(current->children.find(ch)!=current->children.end())
        {
            current=current->children[ch];
        }
        else
        {
            return NULL;
        }
    }
    auto stop=std::chrono::high_resolution_clock::now();
    auto duration=std::chrono::duration_cast<chrono::nanoseconds>(stop-start);
    cerr<<"\033[32m\n"<<current->endofword<<"results in"<<double(duration.count()/double(1000000))<<"ms.\033[0m\n\n";

    return current->endofword ?current :NULL;
}

vector<string> get_array(string src)
{
    fstream file(src);
    string word;
    vector<string>words;

    if(!file)
    {
        cerr<<"\n Can't open file"<<src<<"\n";
        return words;
    }
    while(!file.eof())
    {
        getline(file,word);
        if(word.size())
            words.push_back(word);
        word='\0';
    }
    return words;
}
/*******
instead of using naive algorithm which have a worst case of O(mn),i used KMP algorithm which have worst case of 
O(m+n)

The KMP matching algorithm uses degenerating property (pattern having same sub-patterns appearing more than once in the pattern) 
of the pattern and improves the worst case complexity to O(n). 
KMP algorithm-knuth morris pratt algorithm
************/
void computeLPSArray(string pat, int M, int *lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0)
            {
                len = lps[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Prints occurrences of txt[] in pat[]
int KMPSearch(string pat, string txt)
{
    int M = pat.size();
    int N = txt.size();

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            // printf("Found pattern at index %d ", i - j);
            return i - j;
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return -1;
}

// universal Search function ,it gives all the occurrences if particular word or a letter is given

vector<string> search(vector<string> v, string pat)
{

    vector<string> results;

    auto start = std::chrono::high_resolution_clock::now();

    for (auto str : v)
    {
        if (KMPSearch(pat, str) != -1)
        {
            results.push_back(str);
        }
    }

    auto stop =std:: chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << results.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return results;
}