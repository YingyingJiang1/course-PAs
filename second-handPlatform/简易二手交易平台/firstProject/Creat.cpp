#include <sstream>
#include <iomanip>
using namespace std;
#include "map.h"
void _ForCreat(const char ch, int count)
{
	stringstream ss;
	ss << setw(5) << setfill('0') << count + 1;
	ss >> id;
	id = ch + id;
}