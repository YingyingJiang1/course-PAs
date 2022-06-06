#ifndef BS
#define BS
#include "extern.h"
void _Creat(struct Table* &head, struct Table* &tail);
void _ShowTables(struct Table* &head, struct Table* &tail);
void _Drop(struct Table* &head, struct Table *&tail);
void _Insert(struct Table* &head);
void _Select(struct Table* &head);
void _Update(struct Table* &head);
void _Delete(struct Table* &head);
void _Alter(struct Table* &head, struct Table* &tail);
void _Count(struct Table*&head);
void _MyMax(struct Table*& head);
void _MyMin(struct Table*&head);
#endif