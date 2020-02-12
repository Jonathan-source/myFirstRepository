#include <iostream>

int main()
{

std::cout << "This is my first piece of code written in Nano (Linux Ubuntu terminal) and transfered from Git to GitHub" << std::endl; 
int max = 10;
int nrOf = 0;
int*arr = new int[max];

for(int i = 0; i < max; i++){
arr[nrOf++] = i;
std::cout << arr[i] << " ";
}

std::cout << std::endl;

// Expand array
{
max = max * 10;
int*temp = new int[max];
for(int i = 0; i < nrOf; i++){
temp[i] = arr[i];
}
delete[] arr;
arr = temp;  
}

for(int i = 0; i < max; i++){
std::cout << arr[i] << " ";
}
return 0;
}
