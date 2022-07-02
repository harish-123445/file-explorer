#include <bits/stdc++.h>
#include "trie_implementation.cpp"
#include "phone.cpp"
#include<windows.h>
using namespace std;


int main()
{

    string contacts[] = {"Harish","Hari","Henry","Harper","Hudson","Hazel","Hannah","Hunter","Hayden","Hailey","Haarsh",
"Haina","Haripriya","Harry","hansa","sai","singam","stella","scarlett","siruthai","siva","sathvik","sabeesh","sabeer",
"sarkarai","sofia","santhosh","santi","saahi","sidhu","James","Jack","Jackson","Jacob","John","Joseph","Julian",
"Jayden","Jagadeesh","Jarvis","Jaggama","Jaxon","Jeshwin","Julis","Jupiter","jaggamama"};

	// Size of the Contact List
	int n = sizeof(contacts)/sizeof(string);
// Insert all the Contacts into Trie
insertIntoTrie(contacts, n);

    string filename;
    string query;
    trie T;
    int c;
    int type;
    /*Vectors are the same as dynamic arrays with the ability to resize itself 
    automatically when an element is inserted or deleted, with their storage being handled
     automatically by the container.*/
    vector<string> data;
    cout<<"Enter which type you want to search !!\n";
    cout<<" 1.phone directory search\n ";
    cout<<"2.file words search \n";
    cout<<" enter your choice :";
    cin>>type;
    if(type==1)
    {
        while(1)
        {
            cout<<"\nEnter 1 to query ";
            cout<<"\nEnter 0 to exit ";
            cin>>c;
            if(c==0)
            {
                cout<<"\n\n\n\t\t\tThank you !!\n\n\n\t\t\t";
                exit(0);
            }
            else 
            {
                cout<<"\nenter the search query :";
                cin>>query;
                displayContacts(query);
            }
        
        }

    }
    else if (type==2)
    {
        cout << "Enter File name to load data from. ( music | movies | words ) :\n";
        cin >> filename;
        cerr << "loading ...";
        data = get_array("../data/" + filename + ".txt");
        cerr << "Done.\n";
        //range based for loop is used
        for (string word : data)
        {
            T.insert(word);
        }

        int choice;
        do
        {

            Sleep(1000);              
            system("cls");

            cout << endl << endl;
            cout<<"\n\t\t\t    *********************** ||   Welcome user !  || ***********************  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                          1. Exact Search                            *  ";
            cout<<"\n\t\t\t    *                          2. Prefix Search                           *  ";
            cout<<"\n\t\t\t    *                          3. Universal Seach                         *  ";
            cout<<"\n\t\t\t    *                          0. Exit                                    *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    *                                                                     *  ";
            cout<<"\n\t\t\t    **************************  ||  -------  ||  **************************  ";
            cout<<"\n\t\t\t Enter your choice !!!";
            cin >> choice;
            getchar(); 

            string pattern;

            if (choice)
            {
                cout << "Enter Search Text  : ";
                getline(cin, pattern);
            }

            switch (choice)
            {
                case 1:
                    if (T.search_exact(pattern))
                    {
                        cout << "String Exists.\n";
                    }
                    else
                    {
                        cout << "NOT Found.\n";
                    }
                    break;

                case 2:
                    for (string w : T.search_pre(pattern))
                    {
                        cout << w << "\n";
                    }
                    break;
                case 3:
                    for (string w : search(data, pattern))
                    {
                        cout << w << "\n";
                    }
                    break;

                default:
                    break;
                }

                cout << "\n\npress any key to continue.";
                getchar();
                system("cls");

        } while (choice==1 || choice ==2 || choice ==3);
    }
    return 0;
}

