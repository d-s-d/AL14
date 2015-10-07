#include<iostream>
#include<vector>

int main()
{
	std::vector<int> v;

	v.push_back(1);
	v.push_back(2);
	std::swap( v[0], v[1] );
	std::cout << v[0] << v[1] << std::endl;
}
