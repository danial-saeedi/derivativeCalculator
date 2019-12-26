#include <iostream>
#include <queue>
using namespace std; 

int main()
{
	queue<int> s;   // creates an empty stack of integer s 
    
    s.push(2);   // pushes 2 in the stack  , now top =2
    s.push(3);   // pushes 3 in the stack  , now top =3

    cout << s.front();
    s.pop();
    cout << s.front();
}
