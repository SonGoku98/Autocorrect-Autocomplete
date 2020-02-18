#include<bits/stdc++.h>
using namespace std;

class trienode
{
public:
    char data;
    trienode **children;
    bool isterminal;
    trienode(char d)
    {
        this->data=d;
        children =new trienode*[26];
        for(int i=0; i<26; i++)
        {
            children[i]=NULL;
        }
        this->isterminal=false;
    }
};

class trie
{
public:
    trienode *root;
    trie()
    {
        root=new trienode('\0');
    }
    void insertword(trienode *root,string word)
    {
        if(word.size()==0)
        {
            root->isterminal=true;
            return;
        }
        int index=word[0]-'a';
        trienode *child;
        if(root->children[index]!=NULL)
        {
            child=root->children[index];
        }
        else
        {
            child=new trienode(word[0]);
            root->children[index]=child;
        }
        return insertword(child,word.substr(1));
    }

    void insertword(string word)
    {
        return insertword(root,word);
    }

    bool searchword(trienode *root,string word)
    {
        if(word.size()==0)
        {
            if(root->isterminal==true)
            {
                return true;
            }
            return false;
        }
        int index=word[0]-'a';
        trienode *child;
        if(root->children[index]!=NULL)
        {
            child=root->children[index];
        }
        else
        {
            return false;
        }
        return searchword(child,word.substr(1));
    }

    bool searchword(string word)
    {
        return searchword(root,word);
    }

    void removeword(trienode *root,string word)
    {
        if(word.size()==0)
        {
            root->isterminal=false;
            return;
        }
        int index=word[0]-'a';
        trienode *child;
        if(root->children[index]!=NULL)
        {
            child=root->children[index];
        }
        else
        {
            return;
        }
        return removeword(child,word.substr(1));
        if(child->isterminal==false)
        {
            for(int i=0; i<26; i++)
            {
                if(child->children[i]!=NULL)
                {
                    return;
                }
            }
            delete child;
            root->children[index]=NULL;
        }
    }

    void removeword(string word)
    {
        return removeword(root,word);
    }

    int printAutoSuggestions(trienode* root,  string prefix, string tmp, vector<string> &v)
    {
        if(root->isterminal)
        {
            v.push_back(prefix+tmp);
        }
        for(int i=0; i<26; i++)
        {
            if(root->children[i] != NULL)
            {
                printAutoSuggestions(root->children[i], prefix, tmp + (char)(i+'a'), v);
            }
        }
    }

    void printAutoSuggestions(string prefix)
    {
        vector<string>v;
        string tmp = "";
        trienode* temp = root;
        int n = prefix.length();
        for (int level = 0; level < n; level++)
        {
            int index = prefix[level]-'a';
            if (!temp->children[index])
                return;
            temp = temp->children[index];
        }
        printAutoSuggestions(temp,prefix, tmp, v);
        sort(v.begin(), v.end());
        for(int i=0; i<v.size() && i<5; i++)
        {
            cout<<v[i]<<endl;
        }
    }

    string keyboardMisPrint(char ch)
    {
        switch(ch)
        {
        case 'a':
            return "qwsxz";
        case 'b':
            return "vfghn";
        case 'c':
            return "xsdfv";
        case 'd':
            return "xswerfvc";
        case 'e':
            return "swrfd";
        case 'f':
            return "cdertgbv";
        case 'g':
            return "vfrtyhnb";
        case 'h':
            return "bgtyujmn";
        case 'j':
            return "nhyuikm";
        case 'k':
            return "mjuiol";
        case 'l':
            return "kiopm";
        case 'm':
            return "nhjkl";
        case 'n':
            return "bghjkm";
        case 'o':
            return "kipl";
        case 'p':
            return "lo";
        case 'q':
            return "asw";
        case 'r':
            return "edfgt";
        case 's':
            return "qazxcdew";
        case 't':
            return "rfghy";
        case 'u':
            return "yhjki";
        case 'v':
            return "cdfgb";
        case 'w':
            return "qasde";
        case 'x':
            return "zasdc";
        case 'y':
            return "tghju";
        case 'z':
            return "asx";
        }
        return "";
    }

    void levenshtein(const string &toCorrect, int dist, vector<string>v[], int ind, trienode *root, string tmp)
    {
        //All inputString is traversed
        if(ind == toCorrect.size())
        {
            if(root->isterminal)
            {
                v[2-dist].push_back(tmp);
            }
            return;
        }

        //If this word is correct
        int index = toCorrect[ind]-'a';
        if(root->children[index] != NULL)
        {
            levenshtein(toCorrect, dist, v, ind+1, root->children[index], tmp + toCorrect[ind]);
        }
        //If edit-distance not equal to zero
        if(dist >0)
        {
            //Case 1: Missed a letter at index = ind
            for(int i=0; i<26; i++)
            {
                if(root->children[i] != NULL)
                {
                    levenshtein(toCorrect, dist-1, v, ind, root->children[i], tmp + (char)(i+'a'));
                }
            }

            //Case 2: Typed a letter extra at index = ind
            levenshtein(toCorrect, dist-1, v, ind+1, root, tmp);

            //Case 3: Wrong letter typed at index = ind
            string alternateWord = keyboardMisPrint(toCorrect[ind]);
            for(auto ch : alternateWord)
            {
                int index = ch -'a';
                if(root->children[index] != NULL)
                {
                    levenshtein(toCorrect, dist - 1, v, ind+1, root->children[index], tmp + ch);
                }
            }
        }
    }

    void autoCorrect(string input)
    {
        vector<string>v[3];
        string tmp="";
        int startIndex=0;
        levenshtein(input, 2, v, startIndex, root, tmp);
        int count=0;
        for(auto x : v)
        {
            for(auto yi: x)
            {
                cout<<yi<<"\n";
                count++;
                if(count==5) break;
            }
            if(count==5) break;
        }
    }

    void whiteSpaceMistake(vector<vector<string>> &whiteSpace, const string &inputString, int ind, trienode *root,vector<string> current, string word, trienode *rootHead)
    {
        if(ind == inputString.size())
        {
            if(root->isterminal)
            {
                current.push_back(word);
                whiteSpace.push_back(current);
            }
            return;
        }
        // Case 1: not to break at index ind
        int index = inputString[ind]-'a';
        if(root->children[index] != NULL)
        {
            whiteSpaceMistake(whiteSpace, inputString, ind+1, root->children[index], current, word+ inputString[ind], rootHead);
        }

        // Case 2: to break at this index
        if(root->isterminal)
        {
            current.push_back(word);
            trienode *troot = rootHead;
            whiteSpaceMistake(whiteSpace, inputString, ind, troot, current, "", rootHead);
        }
    }

    void spaceComplete(string input)
    {
        vector<vector<string>>whiteSpace;
        vector<string>current;
        string word="";
        int count=0;
        whiteSpaceMistake(whiteSpace, input, 0, root, current, word, root);
        for(auto str : whiteSpace)
        {
            for(auto wrd: str)
            {
                cout<<wrd<<" ";
            }
            count++;
            cout<<endl;
            if(count==5) break;
        }
    }
};


int main()
{
    fstream file;
    string word, q, filename;
    file.open("dictionary.txt");
    //Inserting all words from file into trie
    trie t;
    while (file >> word)
    {
        t.insertword(word);
    }
    file.close();

    cout<<"Enter string to search: ";
    string inputString;
    cin>>inputString;

    cout<<"\n_____________________\n";
    cout<<"Auto-Suggested Words:";
    cout<<"\n_____________________\n";
    t.printAutoSuggestions(inputString);

    cout<<"\n_______________________________________________\n";
    cout<<"AutoCorrect Results (allowing upto 2 mistakes):";
    cout<<"\n_______________________________________________\n";
    t.autoCorrect(inputString);

    cout<<"\n_____________________________________________________________\n";
    cout<<"Results obtained assuming that user has forgot to give space:";
    cout<<"\n_____________________________________________________________\n";
    t.spaceComplete(inputString);
    return 0;
}
