#ifndef FILE
#define FILE
#include <string>
using namespace std;
#include "extern.h"
void _FromFile(const string fname, struct Table* &head, struct Table *&tail);
void _IntoFile(const string fname, struct Table* head);
#endif




                        