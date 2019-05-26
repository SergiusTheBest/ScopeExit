#include <iostream>
#include <stdexcept>
#include <ScopeExit/ScopeExit.h>
#include <ScopeExit/ScopeFailure.h>
#include <ScopeExit/ScopeSuccess.h>

using namespace std;

void doSuccess()
{
    cout << "--- doSuccess() ---" << endl;

    SCOPE_EXIT{ cout << "scope exit 1" << endl; }; // always called
    SCOPE_EXIT{ cout << "scope exit 2" << endl; }; // always called
    SCOPE_FAILURE{ cout << "scope failure" << endl; }; // not called as there are no exceptions
    SCOPE_SUCCESS{ cout << "scope success" << endl; }; // called as there are no exceptions
}

void doFailure()
{
    cout << "--- doFailure() ---" << endl;

    try
    {
        SCOPE_EXIT{ cout << "scope exit 1" << endl; }; // always called
        SCOPE_EXIT{ cout << "scope exit 2" << endl; }; // always called
        SCOPE_FAILURE{ cout << "scope failure" << endl; }; // called as there are no exceptions
        SCOPE_SUCCESS{ cout << "scope success" << endl; }; // not called as there are no exceptions

        throw runtime_error("error");
    }
    catch (const exception&)
    {
        cout << "caught an exception" << endl;
    }
}

int main()
{
    doSuccess();
    doFailure();

    return 0;
}