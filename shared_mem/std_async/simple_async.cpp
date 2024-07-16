#include <iostream>
#include <future>

int square(int x) { return x*x; }

int main()
{
    // async function is a 'future'
    // type = std::future<int>
    auto asyncFunction = std::async(&square,12);
    // ... some time passes
    int result = asyncFunction.get();   // We are blocked here if
                                        // our value has not been computed
                                        // Otherwise, the value from get()
                                        // (which is wrapped in a promise)
                                        // is returned
    std::cout << "Thew async thread has returned! " << result << std::endl;

    return 0;
}