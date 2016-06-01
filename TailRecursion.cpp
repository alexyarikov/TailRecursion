#include <iostream>
#include <conio.h>

#define LIST_SIZE 25600000 // list items count

// recursive type enumeration
enum EnRecursionType { rtUnknown = '-1', rtSimple = '0', rtTail = '1' };

// simple list structure
struct lst
{
    lst* _next;
    lst(): _next(nullptr) {};
};

// initialization: allocates memory for list
// @return - Allocated list
lst* initialize()
{
    lst* li_head = new lst();
    lst* li = li_head;

    for (int i = 1; i < LIST_SIZE; i++)
    {
        li->_next = new lst();
        li = li->_next;
    }

    return li_head;
}

// shutdown: free'es list memory
// @head - head of list
void shutdown(const lst* head)
{
    const lst* li = head;
    while (li)
    {
        const lst* next = li->_next;
        delete li;
        li = next;
    }
}

// get recursion type from stdin
// @return - recursion type
EnRecursionType getRecursionType()
{
    printf("To launch simple resursion press 0, to launch tail recursion press 1: ");

    char recursion_type = _getch();
    printf("\r\n");

    if (recursion_type != EnRecursionType::rtSimple && recursion_type != EnRecursionType::rtTail)
        return EnRecursionType::rtUnknown;
    else
        return (EnRecursionType)recursion_type;
}

// calculates list items number as simple recursion
// @li - list item
// @count - list items number
int simple_recursion(const lst* li, int& count)
{
    return li ? simple_recursion(li->_next, ++count) + 1 : 0;
}

// calculates list items number as tail recursion
// @li - list item
// @count - list items number
int tail_recursion(const lst* li, int& count)
{
    return li ? tail_recursion(li->_next, ++count) : 0;
}

// launches list items number calculation as recursion of specified type
// @message - message to print
// recursion_func - recursion function
void launch(const EnRecursionType recursion_type)
{
    if (recursion_type == rtUnknown)
        return;

    printf("Initializing...\r\n");
    lst* head = initialize();

    int count = 0;

    switch (recursion_type)
    {
        case rtSimple:
            printf("Launching simple recursion, expecting stack overflow...\r\n");
            simple_recursion(head, count);
            break;
        case rtTail:
            printf("Launching tail recursion, expecting successful function call...\r\n");
            tail_recursion(head, count);
            break;
    }

    printf("Result: OK [%d]\r\n", count);
    printf("Shutting down...\r\n");
    shutdown(head);
}

// main function
int main(int argc, char* argv[])
{
    launch(getRecursionType());

    printf("Press any key to quit...");
    _getch();
    return 0;
}
