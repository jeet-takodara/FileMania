#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

class Splitter {

public:
    void split_by_line();

};

class Merger {

public:
    void merge_files();

};

class Functionality {

public:
    void replace_word();
    void compare_files();
    void encrypt();
    void decrypt();
    void frequent();
    void rename_file();

};

void Merger::merge_files() {

    ifstream input_file;
    ofstream output_file;
    int number_of_files;
    char ch;

    cout<<"How many files do you want to merge?\n";
    cin>>number_of_files;

    char file_names[number_of_files][30];

    cout<<"\n\nEnter the file names with extensions:\n";
    for(int i=0;i<number_of_files;i++) {
        cin>>file_names[i];
    }

    char output_file_name[30];

    cout<<"\n\nEnter the output file name: ";
    cin>>output_file_name;

    output_file.open(output_file_name);

    for(int i=0;i<number_of_files;i++) {
        input_file.open(file_names[i]);

        if(input_file.fail()) {
            cout<<"\nFailed to open file "<<file_names[i];
            if(i!=number_of_files-1){
                cout<<"\n Skipping to next file!\n";
            }
        } else {

        while(!input_file.eof()) {
            input_file.get(ch);
            output_file.put(ch);
            ch = (char) 0;
        }

        output_file.put('\n');
        input_file.close();
        }
    }

    cout<<"\nFiles are merged!";
        output_file.close();

}

void Splitter::split_by_line() {

    system("cls");
    ifstream input_file;
    ofstream output_file;
    char input_file_name[30];
    int number_of_lines;
    char ch;
    int lines = 0,k=0;

    cout<<"Enter the file name: ";
    cin>>input_file_name;

    cout<<"\nEnter the number of lines\n";
    cin>>number_of_lines;

    input_file.open(input_file_name);

    if(input_file.fail()) {

        cout<<"\n\nCannot open the file!\n";

    } else {

        string f1 = to_string(k) + ".txt";
        cout<<f1<<"\n";
        output_file.open(f1);
        while(!input_file.eof()) {

            if(lines == number_of_lines) {
                ++k;
                output_file.close();
                string file = to_string(k) + ".txt";
                cout<<file<<"\n";
                output_file.open(file);
                lines=0;
            }

            input_file.get(ch);
            if(ch == '\n'){
                ++lines;
            }
            output_file.put(ch);

            ch = (char)0;
        }

        output_file.close();
        cout<<"\n\nFile Splitted";
    }

}

# define MAX_CHARS 26
# define MAX_WORD_SIZE 30

struct TrieNode
{
    bool isEnd;
    unsigned frequency;
    int indexMinHeap;
    TrieNode* child[MAX_CHARS];
};

struct MinHeapNode
{
    TrieNode* root;
    unsigned frequency;
    char* word;
};

struct MinHeap
{
    unsigned capacity;
    int count;
    MinHeapNode* array;
};

TrieNode* newTrieNode()
{
    TrieNode* trieNode = new TrieNode;

    trieNode->isEnd = 0;
    trieNode->frequency = 0;
    trieNode->indexMinHeap = -1;
    for( int i = 0; i < MAX_CHARS; ++i )
        trieNode->child[i] = NULL;

    return trieNode;
}

MinHeap* createMinHeap( int capacity )
{
    MinHeap* minHeap = new MinHeap;

    minHeap->capacity = capacity;
    minHeap->count  = 0;

    minHeap->array = new MinHeapNode [ minHeap->capacity ];

    return minHeap;
}

void swapMinHeapNodes ( MinHeapNode* a, MinHeapNode* b )
{
    MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify( MinHeap* minHeap, int idx )
{
    int left, right, smallest;

    left = 2 * idx + 1;
    right = 2 * idx + 2;
    smallest = idx;
    if ( left < minHeap->count &&
         minHeap->array[ left ]. frequency <
         minHeap->array[ smallest ]. frequency
       )
        smallest = left;

    if ( right < minHeap->count &&
         minHeap->array[ right ]. frequency <
         minHeap->array[ smallest ]. frequency
       )
        smallest = right;

    if( smallest != idx )
    {

        minHeap->array[ smallest ]. root->indexMinHeap = idx;
        minHeap->array[ idx ]. root->indexMinHeap = smallest;


        swapMinHeapNodes (&minHeap->array[ smallest ], &minHeap->array[ idx ]);

        minHeapify( minHeap, smallest );
    }
}

void buildMinHeap( MinHeap* minHeap )
{
    int n, i;
    n = minHeap->count - 1;

    for( i = ( n - 1 ) / 2; i >= 0; --i )
        minHeapify( minHeap, i );
}

void insertInMinHeap( MinHeap* minHeap, TrieNode** root, const char* word )
{
    if( (*root)->indexMinHeap != -1 )
    {
        ++( minHeap->array[ (*root)->indexMinHeap ]. frequency );

        minHeapify( minHeap, (*root)->indexMinHeap );
    }

    else if( minHeap->count < minHeap->capacity )
    {
        int count = minHeap->count;
        minHeap->array[ count ]. frequency = (*root)->frequency;
        minHeap->array[ count ]. word = new char [strlen( word ) + 1];
        strcpy( minHeap->array[ count ]. word, word );

        minHeap->array[ count ]. root = *root;
        (*root)->indexMinHeap = minHeap->count;

        ++( minHeap->count );
        buildMinHeap( minHeap );
    }

    else if ( (*root)->frequency > minHeap->array[0]. frequency )
    {

        minHeap->array[ 0 ]. root->indexMinHeap = -1;
        minHeap->array[ 0 ]. root = *root;
        minHeap->array[ 0 ]. root->indexMinHeap = 0;
        minHeap->array[ 0 ]. frequency = (*root)->frequency;

        delete [] minHeap->array[ 0 ]. word;
        minHeap->array[ 0 ]. word = new char [strlen( word ) + 1];
        strcpy( minHeap->array[ 0 ]. word, word );

        minHeapify ( minHeap, 0 );
    }
}

void insertUtil ( TrieNode** root, MinHeap* minHeap,
                        const char* word, const char* dupWord )
{
    if ( *root == NULL )
        *root = newTrieNode();

    if ( *word != '\0' )
        insertUtil ( &((*root)->child[ tolower( *word ) - 97 ]),
                         minHeap, word + 1, dupWord );
    else
    {
        if ( (*root)->isEnd )
            ++( (*root)->frequency );
        else
        {
            (*root)->isEnd = 1;
            (*root)->frequency = 1;
        }

        insertInMinHeap( minHeap, root, dupWord );
    }
}

void insertTrieAndHeap(const char *word, TrieNode** root, MinHeap* minHeap)
{
    insertUtil( root, minHeap, word, word );
}

void displayMinHeap( MinHeap* minHeap )
{
    int i;

    for( i = 0; i < minHeap->count; ++i )
    {
        printf( "%s : %d\n", minHeap->array[i].word,
                            minHeap->array[i].frequency );
    }
}

void printKMostFreq( FILE* fp, int k )
{
    MinHeap* minHeap = createMinHeap( k );

    TrieNode* root = NULL;

    char buffer[MAX_WORD_SIZE];

    while( fscanf( fp, "%s", buffer ) != EOF )
        insertTrieAndHeap(buffer, &root, minHeap);

    displayMinHeap( minHeap );
}


void Functionality::frequent() {

    int words;
    char file_name[30];

    cout<<"Enter the file name: ";
    cin>>file_name;

    cout<<"Enter the number of words: ";
    cin>>words;

    FILE *fp = fopen(file_name,"r");

    if(fp == NULL) {
        cout<<"\n\nInvalid file name!";
    }
    else {
        printKMostFreq(fp,words);
    }
    fclose(fp);
}


void Functionality::compare_files() {

    ifstream f1,f2;
    char file1[30],file2[30];

    cout<<"Enter the name of first file: \n";
    cin>>file1;

    cout<<"\n\nEnter the name of second file: \n";
    cin>>file2;

    f1.open(file1);
    f2.open(file2);

    if(f1.fail() || f2.fail()) {
        cout<<"\n\nInvalid file names!";
    }
    else {

        char ch1,ch2;

        int error = 0, pos = 0, line = 1;

        while(!f1.eof() && !f2.eof()) {
            pos++;

            f1.get(ch1);
            f2.get(ch2);

            if (ch1 == '\n' && ch2 == '\n')
            {
                line++;
                pos = 0;
            }

            if (ch1 != ch2)
            {
                error++;
                cout<<"Line Number : "<<line<<" \tError"
                " Position : "<<pos<<"\n";
            }

        }
        if(error == 0) {
            cout<<"\n\nFiles are identical!";
        }
        else {
        cout<<"\n\nTotal Errors: "<<error;
        }

        f1.close();
        f2.close();

    }

}

std::string replace_substrings( std::string str, const std::string& original_substring, const std::string& new_substring )
{
    auto pos = str.find( original_substring ) ;
    while( pos != std::string::npos )
    {
        str.replace( pos, original_substring.size(), new_substring ) ;
        pos = str.find( original_substring, pos + new_substring.size() ) ;
    }
    return str ;
}


void Functionality::replace_word() {

ifstream fin;
ofstream fout;
char file_name[30];
string find_word,replace_word;
cout<<"Enter the file name: \n";
cin>>file_name;

fin.open(file_name);

if(fin.fail()) {
    cout<<"\n\nCannot open file!";
}else {

cout<<"\n\nEnter the word to be replaced: \n";
cin>>find_word;
cout<<"\n\nEnter the word to be replaced with: \n";
cin>>replace_word;

string str;
   if(fin) {
      ostringstream ss;
      ss << fin.rdbuf(); // reading data
      str = ss.str();
   }

   fout.open(file_name);

    fout<<replace_substrings(str,find_word,replace_word);

}
cout<<"\n\nTask Completed!";

}

void Functionality::rename_file() {

    char old_name[30],new_name[30];
    cout<<"Enter the file name to be changed: \n";
    cin>>old_name;
    cout<<"\n\nEnter the new file name: \n";
    cin>>new_name;

    int value = rename(old_name,new_name);

    if(!value){
        cout<<"\n\nFile name changed successfully!";
    } else {
        cout<<"\n\nFile doesn't exists!";
    }

}

string encoder(string key)
{
    string encoded = "";
    bool arr[26] = {0};

    for (int i=0; i<key.size(); i++)
    {
        if(key[i] >= 'A' && key[i] <= 'Z')
        {
            if (arr[key[i]-65] == 0)
            {
                encoded += key[i];
                arr[key[i]-65] = 1;
            }
        }
        else if (key[i] >= 'a' && key[i] <= 'z')
        {
            if (arr[key[i]-97] == 0)
            {
                encoded += key[i] - 32;
                arr[key[i]-97] = 1;
            }
        }
    }

    for (int i=0; i<26; i++)
    {
        if(arr[i] == 0)
        {
            arr[i]=1;
            encoded += char(i + 65);
        }
    }
    return encoded;
}


string cipheredIt(string msg, string encoded)
{
    string cipher="";

    for (int i=0; i<msg.size(); i++)
    {
        if (msg[i] >='a' && msg[i] <='z')
        {
            int pos = msg[i] - 97;
            cipher += encoded[pos];
        }
        else if (msg[i] >='A' && msg[i] <='Z')
        {
            int pos = msg[i] - 65;
            cipher += encoded[pos];
        }
        else
        {
            cipher += msg[i];
        }
    }
    return cipher;
}


void Functionality::encrypt(){

char file_name[30];
string key,content;

cout<<"Enter the file name whose data is to be encrypted: \n";
cin>>file_name;

cout<<"\n\nEnter the key value: \n";
cin>>key;

ifstream fin;
ofstream fout;

fin.open(file_name);

if(fin.fail()) {
    cout<<"\n\nFile cannot be opened!";
}
else {

   string str;
   ostringstream ss;
   ss << fin.rdbuf();
   str = ss.str();

   fout.open(file_name);

   string encoded = encoder(key);

   fout<<cipheredIt(str,encoded);

   cout<<"\n\nFile Contents Encrypted!";
}
}

string plaintext = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string encoder1(string key)
{
    string encoded = "";
    bool arr[26] = {0};

    for (int i=0; i<key.size(); i++)
    {
        if(key[i] >= 'A' && key[i] <= 'Z')
        {

            if (arr[key[i]-65] == 0)
            {
                encoded += key[i];
                arr[key[i]-65] = 1;
            }
        }
        else if (key[i] >= 'a' && key[i] <= 'z')
        {
            if (arr[key[i]-97] == 0)
            {
                encoded += key[i] - 32;
                arr[key[i]-97] = 1;
            }
        }
    }

    for (int i=0; i<26; i++)
    {
        if(arr[i] == 0)
        {
            arr[i]=1;
            encoded += char(i + 65);
        }
    }
    return encoded;
}


string decipheredIt(string msg, string encoded)
{
    map <char,int> enc;
    for(int i=0; i<encoded.size(); i++)
    {
        enc[encoded[i]]=i;
    }

    string decipher="";

    for (int i=0; i<msg.size(); i++)
    {
        if (msg[i] >='a' && msg[i] <='z')
        {
            int pos = enc[msg[i]-32];
            decipher += plaintext[pos];
        }
        else if(msg[i] >='A' && msg[i] <='Z')
        {
            int pos = enc[msg[i]];
            decipher += plaintext[pos];
        }
        else
        {
            decipher += msg[i];
        }
    }
    return decipher;
}


void Functionality::decrypt(){

char file_name[30];
string key;

cout<<"Enter the file name whose contents are to be decrypted: \n";
cin>>file_name;

cout<<"\n\nEnter the key: \n";
cin>>key;

string encoded = encoder1(key);

ifstream fin;
fin.open(file_name);

if(fin.fail()){
    cout<<"\n\nFile cannot be opened!";
} else {

string str;
ostringstream ss;
ss << fin.rdbuf();
str = ss.str();

cout<<"Deciphered text: \n"<<decipheredIt(str,encoded);

}
}

int main() {

    int choice;
    Splitter s;
    Merger m;
    Functionality f;

    while(true) {
            system("cls");
    cout<<"                                                                       File Mania\n\n";
    cout<<"                                                                          MENU\n\n\n";
    cout<<"1. SPLIT FILE\n\n";
    cout<<"2. MERGE FILES\n\n";
    cout<<"3. REPLACE WORD\n\n";
    cout<<"4. COMPARE FILES\n\n";
    cout<<"5. RENAME FILE\n\n";
    cout<<"6. ENCRYPT FILE CONTENTS\n\n";
    cout<<"7. DECRYPT FILE CONTENTS\n\n";
    cout<<"8. FREQUENT WORDS\n\n";
    cout<<"9. EXIT\n\n";

    cout<<"Your Preference please: ";
    cin>>choice;

    switch(choice) {

        case 1:{
            s.split_by_line();
            cout<<"\n\n";
            system("pause");
            break;
        }

        case 2:{
            system("cls");
            m.merge_files();
            cout<<"\n\n";
            system("pause");
            break;
        }

        case 3:{
            system("cls");
            f.replace_word();
            cout<<"\n\n";
            system("pause");
            break;
        }

        case 4:{
            system("cls");
            f.compare_files();
            cout<<"\n\n";
            system("pause");
            break;
        }

        case 5:{
            system("cls");
            f.rename_file();
            cout<<"\n\n";
            system("pause");
            break;
        }

        case 6:{
            system("cls");
            f.encrypt();
            cout<<"\n\n";
            system("pause");
            break;
        }

        case 7:{
            system("cls");
            f.decrypt();
            cout<<"\n\n";
            system("pause");
            break;
        }

        case 8:{
            system("cls");
            f.frequent();
            cout<<"\n\n";
            system("pause");
            break;
        }

        default:
            exit(0);

    }
    }
    return 0;
}
