#include <iostream>
#include <ScopeExit/ScopeExit.h>

using namespace std;

int main()
{
    cout << "<html>" << endl;
    SCOPE_EXIT{ cout << "</html>" << endl; };

    {
        cout << "<head>" << endl;
        SCOPE_EXIT{ cout << "</head>" << endl; };

        cout << "<title>Hello</title>" << endl;
    }

    cout << "<body>" << endl;
    SCOPE_EXIT{ cout << "</body>" << endl; };

    cout << "<h1>Hello World!</h1>" << endl;

    return 0;
}