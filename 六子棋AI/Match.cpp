#include <iostream>
#include <vector>
using namespace std;
#define M 80
#define ROWS 19
#define COLS 19
#define OWNCOLOR 1
#define OPPCOLOR 2
extern int chessBoard[ROWS][COLS];
extern vector<pair<int, int>> waitSele;
struct ChessType
{
	int type[8];
};
struct ChessType chessType1[M] =
{
	//己方存在可获胜的五子
	{0,1,1,1,1,1},	//0
	{1,0,1,1,1,1},
	{1,1,0,1,1,1},
	{1,1,1,0,1,1},
	{1,1,1,1,0,1},
	{1,1,1,1,1,0},
	//己方存在可获胜的四子
	{0,0,1,1,1,1},	//6
	{1,0,0,1,1,1},
	{1,1,0,0,1,1},
	{1,1,1,0,0,1},
	{1,1,1,1,0,0},
	{0,1,0,1,1,1},
	{0,1,1,0,1,1},
	{0,1,1,1,0,1},
	{0,1,1,1,1,0},
	{1,0,1,0,1,1},
	{1,0,1,1,0,1},
	{1,0,1,1,1,0},
	{1,1,0,1,0,1},
	{1,1,0,1,1,0},
	{1,1,1,0,1,0},
	//需堵两子才可阻止对方获胜
	{0,2,2,2,2,2,0},	//21
	{0,0,2,2,2,2,0,2},
	{0,0,2,2,2,2,0,0},
	{2,0,2,2,2,2,0,0},
	{2,0,2,2,2,2,0,2},
	//需堵一子即可阻止对方获胜
	{2,2,0,2,2,2},	//26
	{2,2,2,0,2,2},
	{2,2,0,0,2,2},
	{2,2,2,0,0,2},
	{2,0,0,2,2,2},
	{0,2,0,2,2,2},
	{0,2,2,0,2,2},
	{0,2,2,2,0,2},
	{2,0,2,0,2,2},
	{2,0,2,2,0,2},
	{2,0,2,2,2,0},
	{2,2,0,2,0,2},
	{2,2,0,2,2,0},
	{2,2,2,0,2,0},
	{1,2,2,2,2,2,0},//40
	{1,0,2,2,2,2,0},
	{1,2,2,2,2,0,0},
	{0,2,2,2,2,0,1},//43
	{0,2,2,2,2,2,1},
	{0,0,2,2,2,2,1},
	{0,2,2,2,2,0,1},
	//己方有获胜潜力的三子
	{0,0,0,1,1,1},	//47
	{1,1,1,0,0,0},
	{0,1,1,1,0,0},
	{0,0,1,1,1,0},
	{1,0,1,1,0,0},
	{1,1,0,1,0,0},
	{0,0,1,0,1,1},
	{0,0,1,1,0,1},
	{0,1,0,0,1,1},
	{0,1,1,0,0,1},
	{1,0,0,1,1,0},
	{1,1,0,0,1,0},
	{1,0,0,0,1,1},
	{1,1,0,0,0,1},
	{1,0,1,0,0,1},
	{1,0,0,1,0,1},
	{0,1,0,1,0,1},
	{1,0,1,0,1,0},
	//己方存在有获胜潜力的二子
	{0,0,0,0,1,1},//65
	{0,0,0,1,1,0},
	{0,0,1,1,0,0},
	{0,1,1,0,0,0},
	{1,1,0,0,0,0},
	{1,0,1,0,0,0},
	{0,1,0,1,0,0},
	{0,0,1,0,1,0},
	{0,0,0,1,0,1},
	{1,0,0,1,0,0},
	{0,1,0,0,1,0},
	{0,0,1,0,0,1},
	{1,0,0,0,1,0},
	{0,1,0,0,0,1},
	{1,0,0,0,0,1},	//79

};
struct ChessType boundary[6]=
{
	{2, 2, 2, 2, 2, 0},//起始位置位于棋盘边缘
	{ 0,2,2,2,2,0 },
	{ 2,2,2,2,0,0 },
	{ 0,2,2,2,2,0 },//终止位于棋盘边缘
	{ 0,2,2,2,2,2 },
	{ 0,0,2,2,2,2 },

};

pair<pair<int, int>, pair<int, int>> Attack(int row, int col, bool& existed)
{
	int start, end;
	int startR, startC, endR, endC;
	int row1, col1, row2, col2;
	int count = 0;
	//从右上角到左下角
	startR = row - 5, startC = col + 5, endR = row + 5, endC = col - 5;
	while (startR < 0 || startC > COLS - 1)
	{
		++startR;
		--startC;
	}
	while (endR > ROWS - 1 || endC < 0)
	{
		--endR;
		++endC;
	}
	for (int r = startR, c = startC; r <= endR && c >= endC; ++r, --c)
	{
		if (chessBoard[r][c] == OWNCOLOR)
			++count;

	}
	if (count >= 2)
	{
		for (int r = startR, c = startC; r <= endR - 5 && c >= endC - 5; ++r, --c)
		{
			for (int i = 47; i < 80; ++i)
			{
				int rr = r, cc = c;
				int amount1 = 0;
				int sele[6];
				for (int k = 0; k < 6; ++k, ++rr, --cc)
				{
					sele[k] = chessBoard[rr][cc];
					if (sele[k] == OWNCOLOR)
						++amount1;
				}
				if (amount1 >= 2)
				{
					int j = 0, count0 = 0;
					int rr = r, cc = c;
					for (; j < 6; ++j, ++rr,--cc)
					{
						if (sele[j] != chessType1[i].type[j])
							break;

						if (sele[j] != 1 && sele[j] != 2)
						{
							++count0;
							if (count0 == 1)
							{
								row1 = rr;
								col1 = cc;
							}
							if (count0 == 2)
							{
								row2 = rr;
								col2 = cc;
							}
						}
					}
					if (j == 6)
					{
						existed = true;
						return make_pair(make_pair(row1, col1), make_pair(row2, col2));
					}
				}
			}
		}
	}
	//从左上角到右下角
	startR = row - 5, startC = col - 5, endR = row + 5, endC = col + 5;
	while (startR < 0 || startC < 0)
	{
		++startR;
		++startC;
	}
	while (endR > ROWS - 1 || endC > COLS - 1)
	{
		--endR;
		--endC;
	}
	count = 0;
	for (int r = startR, c = startC; r <= endR && c <= endC; ++r, ++c)
	{
		if (chessBoard[r][c] == OWNCOLOR)
			++count;
	}
	if (count >= 2)
	{
		for (int r = startR, c = startC; r <= endR - 5 && c <= endC - 5; ++r, ++c)
		{
			for (int i = 47; i < 80; ++i)
			{
				int rr = r, cc = c;
				int amount1 = 0; 
				int sele[6];
				for (int k = 0; k < 6; ++k, ++rr, ++cc)
				{
					sele[k] = chessBoard[rr][cc];
					if (sele[k] == OWNCOLOR)
						++amount1;
				}
				if (amount1 >= 2)
				{
					int rr = r, cc = c;
					int j = 0, count0 = 0;
					for (; j < 6; ++j, ++rr,++cc)
					{
						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] != 1 && sele[j] != 2)
						{
							++count0;
							if (count0 == 1)
							{
								row1 = rr;
								col1 = cc;
							}
							if (count0 == 2)
							{
								row2 = rr;
								col2 = cc;
							}
						}
					}
					if (j == 6)
					{
						existed = true;
						return make_pair(make_pair(row1, col1), make_pair(row2, col2));
					}
				}
			}
		}
	}
	//横向
	start = col - 5, end = col + 5;
	while (start < 0 || end > COLS - 1)
	{
		++start;
		--end;
	}
	count = 0;
	for (int c = start; c <= end; ++c)
	{
		if (chessBoard[row][c] == OWNCOLOR)
			++count;
	}
	if (count >= 2)
	{
		for (int c = start; c <= end - 5; ++c)
		{
			int amount1 = 0;
			int sele[6];
			int cc = c;
			for (int k = 0; k < 6; ++k, ++cc)
			{
				sele[k] = chessBoard[row][cc];
				if (sele[k] == OWNCOLOR)
					++amount1;
			}
			if(amount1 >= 2)
			{
				for (int i = 47; i < 80; ++i)
				{
					int cc = c;
					int j = 0, count0 = 0;
					for (; j < 6; ++j, ++cc)
					{
						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == 0)
						{
							++count0;
							if (count0 == 1)
							{
								row1 = row;
								col1 = cc;
							}
							if (count0 == 2)
							{
								row2 = row;
								col2 = cc;
							}
						}
					}
					if (j == 6)
					{
						existed = true;
						return make_pair(make_pair(row1, col1), make_pair(row2, col2));
					}
				}
			}
		}
	}
	//纵向
	start = row - 5, end = row + 5;
	while (start < 0 || end > ROWS - 1)
	{
		++start;
		--end;
	}
	count = 0;
	for (int r = start; r <= end; ++r)
	{
		if (chessBoard[r][col] == OWNCOLOR)
			++count;
	}
	if (count >= 2)
	{
		for (int r = start; r <= end - 5; ++r)
		{
			int rr = r;
			int amount1 = 0;
			int sele[6];
			for (int k = 0; k < 6; ++k, ++rr)
			{
				sele[k] = chessBoard[rr][col];
				if (sele[k] == OWNCOLOR)
						++amount1;
			}
			if(amount1 >= 2)
			{
				for (int i = 47; i < 80; ++i)
				{
					int rr = r;
					int j = 0, count0 = 0;
					for (; j < 6; ++j, ++rr)
					{
						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == 0)
						{
							++count0;
							if (count0 == 1)
							{
								row1 = rr;
								col1 = col;
							}
							if (count0 == 2)
							{
								row2 = rr;
								col2 = col;
							}
						}
					}
					if (j == 6)
					{
						existed = true;
						return make_pair(make_pair(row1, col1), make_pair(row2, col2));
					}
				}
			}
		}
	}
	return make_pair(make_pair(-1, -1), make_pair(-1, -1));
}

//己方是否存在可获胜的棋型
pair<pair<int, int>, pair<int, int>> CanWin(int row, int col, bool& existed)	
{
	int start = col - 5, end = col + 5;	
	int row1, col1, row2, col2;
	int startR, startC, endR, endC;
	int count = 0;
	startR = row - 5, startC = col + 5, endR = row + 5, endC = col - 5;
	while (startR < 0 || startC > COLS - 1)
	{
		++startR;
		--startC;
	}
	while (endR > ROWS - 1 || endC < 0)
	{
		--endR;
		++endC;
	}
	for (int r = startR, c = startC; r <= endR && c >= endC; ++r, --c)
	{
		if (chessBoard[r][c] == OWNCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 5 && c >= endC - 5; ++r, --c)		//从右上角到左下角
		{
			int count0 = 0, count1 = 0;
			for (int rr = r, cc = c; rr < r + 6; ++rr, --cc)
			{
				if (chessBoard[rr][cc] == 1)
					++count1;
				if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)		//空位处的数字可能为0或者8
				{
					++count0;
					if (count0 == 1)
					{
						row1 = rr;
						col1 = cc;
					}
					if (count0 == 2)
					{
						row2 = rr;
						col2 = cc;
					}

				}
			}
			if (count1 == 5 && count0 == 1)
			{
				existed = true;
				for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
				{
					if ((*it) != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), *it);
				}
			}
			if (count1 == 4 && count0 == 2)
			{
				existed = true;
				return make_pair(make_pair(row1, col1), make_pair(row2, col2));
			}
		}
	}
	startC = col - 5;
	endC = col + 5;
	while (startC < 0 || endC > COLS - 1)
	{
		++startC;
		--endC;
	}
	//从左上角到右下角
	count = 0;
	for (int r = startR, c = startC; r <= endR && c <= endC; ++r, ++c)
	{
		if (chessBoard[r][c] == OWNCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 5 && c <= endC - 5; ++r, ++c)
		{
			int count0 = 0, count1 = 0;
			for (int rr = r, cc = c; rr < r + 6; ++rr, ++cc)
			{
				if (chessBoard[rr][cc] == 1)
					++count1;
				if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
				{
					++count0;
					if (count0 == 1)
					{
						row1 = rr;
						col1 = cc;
					}
					if (count0 == 2)
					{
						row2 = rr;
						col2 = cc;
					}

				}
			}
			if (count1 == 5 && count0 == 1)
			{
				existed = true;
				for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
				{
					if ((*it) != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), *it);
				}
			}
			if (count1 == 4 && count0 == 2)
			{
				existed = true;
				return make_pair(make_pair(row1, col1), make_pair(row2, col2));
			}
		}
	}
	while (start < 0 || end > COLS - 1)
	{
		++start;
		--end;
	}
	//横向
	count = 0;
	for (int i = start; i <= end; ++i)
	{
		if (chessBoard[row][i] == OWNCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int i = start; i <= end - 5; ++i)
		{
			int count0 = 0, count1 = 0;
			for (int c = i; c < i + 6; ++c)
			{
				if (chessBoard[row][c] == 1)
					++count1;
				if (chessBoard[row][c] != 1 && chessBoard[row][c] != 2)
				{
					++count0;
					if (count0 == 1)
					{
						row1 = row;
						col1 = c;
					}
					if (count0 == 2)
					{
						row2 = row;
						col2 = c;
					}

				}
			}
			if (count1 == 5 && count0 == 1)
			{
				existed = true;
				for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
				{
					if ((*it) != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), *it);
				}
			}
			if (count1 == 4 && count0 == 2)
			{
				existed = true;
				return make_pair(make_pair(row1, col1), make_pair(row2, col2));
			}
		}
	}

	start = row - 5, end = row + 5;
	while (start < 0 || end > ROWS - 1)
	{
		++start;
		--end;
	}
	//纵向
	count = 0;
	for (int i = start; i <= end; ++i)
	{
		if (chessBoard[i][col] == OWNCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int i = start; i <= end - 5; ++i)
		{
			int count0 = 0, count1 = 0;
			for (int r = i; r < i + 6; ++r)
			{
				if (chessBoard[r][col] == 1)
					++count1;
				if (chessBoard[r][col] != 1 && chessBoard[r][col] != 2)
				{
					++count0;
					if (count0 == 1)
					{
						row1 = r;
						col1 = col;
					}
					if (count0 == 2)
					{
						row2 = r;
						col2 = col;
					}

				}
			}
			if (count1 == 5 && count0 == 1)
			{
				existed = true;
				for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
				{
					if ((*it) != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), *it);
				}
			}
			if (count1 == 4 && count0 == 2)
			{
				existed = true;
				return make_pair(make_pair(row1, col1), make_pair(row2, col2));
			}
		}
	}

	return make_pair(make_pair(-1, -1), make_pair(-1, -1));
}

pair<pair<int, int>, pair<int, int>> NeedDefense(int row, int col, bool& existed)
{
	int start = col - 5, end = col + 5;	
	int row1, col1, row2, col2;
	int startR, startC, endR, endC;
	int count = 0;
	bool judg = false;
//从右上角到左下角
	//堵两棋
	startR = row - 6, startC = col + 6, endR = row + 6, endC = col - 6;
	while (startR < 0 || startC > COLS - 1)
	{
		++startR;
		--startC;
	}
	while (endR > ROWS - 1 || endC < 0)
	{
		--endR;
		++endC;
	}
	for (int r = startR, c = startC; r <= endR && c >= endC ; ++r, --c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 6 && c >= endC - 6; ++r, --c)
		{
			int count0 = 0, count2 = 0;
			int rr = r, cc = c;
			//{0,2,2,2,2,2,0}
			if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2) {
				row1 = rr;
				col1 = cc;
				++rr, --cc;
				for (int i = 0; i < 5; ++i, ++rr, --cc)
				{
					if (chessBoard[rr][cc] == 2)
						++count2;
					if (chessBoard[rr][cc] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
				{
					row2 = rr;
					col2 = cc;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	startR = row - 7, startC = col + 7, endR = row + 7, endC = col - 7;
	while (startR < 0 || startC > COLS - 1)
	{
		++startR;
		--startC;
	}
	while (endR > ROWS - 1 || endC < 0)
	{
		--endR;
		++endC;
	}
	count = 0;
	for (int r = startR, c = startC; r <= endR  && c >= endC ; ++r, --c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 7 && c >= endC - 7; ++r, --c)
		{
			int rr = r, cc = c;
			int sele[8];
			rr = r; cc = c;
			for (int i = 0; i < 8; ++i, ++rr, --cc)
				sele[i] = chessBoard[rr][cc];
			for (int i = 22; i < 26; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = r + 1;
					col1 = c - 1;
					row2 = r + 6;
					col2 = c - 6;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	//堵一棋
	count = 0;
	for (int r = startR, c = startC; r <= endR && c >= endC; ++r, --c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 5 && c >= endC - 5; ++r, --c)
		{
			int rr = r, cc = c;
			int amount2 = 0;
			int sele[6];
			for (int k = 0; k < 6; ++k, ++rr, --cc)
			{
				sele[k] = chessBoard[rr][cc];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 4)
			{
				if (r == 0)
				{
					for (int i = 0; i < 3; ++i)
					{
						int j = 0;
						for (; j < 6; ++j)
						{
							if (sele[j] != boundary[i].type[j])
								break;
						}
						if (j == 6)
						{
							row1 = r + 5;
							col1 = c - 5;
							return make_pair(make_pair(row1, col1), make_pair(-1, -1));
						}
					}
				}
				if (r + 5 == ROWS - 1)
				{
					for (int i = 3; i < 6; ++i)
					{
						int j = 0;
						for (; j < 6; ++j)
						{
							if (sele[j] != boundary[i].type[j])
								break;
						}
						if (j == 6)
						{
							row1 = r;
							col1 = c;
							return make_pair(make_pair(row1, col1), make_pair(-1, -1));
						}
					}


				}
				for (int i = 26; i < 40; ++i)
				{
					int rr = r, cc = c;
					int j = 0;
					for (; j < 6; ++j, ++rr, --cc)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == OPPCOLOR && sele[j+1] == 0)
						{
							row1 = rr + 1;
							col1 = cc - 1;
						}
					}
					if (j == 6)
						return make_pair(make_pair(row1, col1), make_pair(-1, -1));
				}
			}
		}
		for (int r = startR, c = startC; r <= endR - 6 && c >= endC - 6; ++r, --c)
		{
			int rr = r, cc = c;
			int amount2 = 0;
			int sele[7];
			for (int k = 0; k < 7; ++k, ++rr, --cc)
			{
				sele[k] = chessBoard[rr][cc];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 4)
			{
				for (int i = 40; i < 47; ++i)
				{
					int rr = r, cc = c;
					int j = 0;
					for (; j < 7; ++j, ++rr, --cc)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
					}
					if (j == 7)
					{
						if (i < 43)
						{
							row1 = rr - 1;
							col1 = cc + 1;
						}
						else
						{
							row1 = r;
							col1 = c;
						}
						return make_pair(make_pair(row1, col1), make_pair(-1, -1));
					}
				}
			}
		}
		
	}

//纵向
	//堵两棋
	start = row - 6, end = row + 6;
	if (start < 0)
		start = 0;
	if (end > ROWS - 1)
		end = ROWS - 1;
	count = 0;
	for (int r = start; r <= end; ++r)
	{
		if (chessBoard[r][col] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = start; r <= end - 6; ++r)
		{
			int rr = r;
			int count0 = 0, count2 = 0;
			//{0,2,2,2,2,2,0}
			if (chessBoard[rr][col] == 0) {
				row1 = rr;
				col1 = col;
				++rr;
				for (int i = 0; i < 5; ++i, ++rr)
				{
					if (chessBoard[rr][col] == 2)
						++count2;
					if (chessBoard[rr][col] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[rr][col] == 0)
				{
					row2 = rr;
					col2 = col;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	start = row - 7, end = row + 7;
	if (start < 0)
		start = 0;
	if (end > ROWS - 1)
		end = ROWS - 1;
	count = 0;
	for (int r = start; r <= end; ++r)
	{
		if (chessBoard[r][col] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = start; r <= end - 7; ++r)
		{
			int sele[8];
			int rr = r;
			for (int i = 0; i < 8; ++i, ++rr)
				sele[i] = chessBoard[rr][col];
			for (int i = 22; i < 26; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = r + 1;		//此处是r,不是rr
					col1 = col;
					row2 = r + 6;
					col2 = col;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}

		//堵一棋
		for (int r = start; r <= end - 5; ++r)
		{
			int rr = r, amount2 = 0;
			int sele[6];
			for (int k = 0; k < 6; ++k, ++rr)
			{
				sele[k] = chessBoard[rr][col];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 4)
			{
				if (r == 0)
				{
					for (int i = 0; i < 3; ++i)
					{
						int j = 0;
						for (; j < 6; ++j)
						{
							if (sele[j] != boundary[i].type[j])
								break;
						}
						if (j == 6)
						{
							row1 = r + 5;
							col1 = col;
							return make_pair(make_pair(row1, col1), make_pair(-1, -1));
						}
					}
				}
				if (r + 5 == ROWS - 1)
				{
					for (int i = 3; i < 6; ++i)
					{
						int j = 0;
						for (; j < 6; ++j)
						{
							if (sele[j] != boundary[i].type[j])
								break;
						}
						if (j == 6)
						{
							row1 = r;
							col1 = col;
							return make_pair(make_pair(row1, col1), make_pair(-1, -1));
						}
					}


				}
				for (int i = 26; i < 40; ++i)
				{
					int j = 0;
					int rr = r;
					for (; j < 6; ++j, ++rr)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == OPPCOLOR && sele[j +1] == 0)
						{
							row1 = rr + 1;
							col1 = col;
						}
					}
					if (j == 6)
						return make_pair(make_pair(row1, col1), make_pair(-1, -1));
				}
			}
		}
		for (int r = start; r <= end - 6; ++r)
		{
			int rr = r, amount2 = 0;
			int sele[7];
			for (int k = 0; k < 7; ++k, ++rr)
			{
				sele[k] = chessBoard[rr][col];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 4)
			{
				for (int i = 40; i < 47; ++i)
				{
					int j = 0;
					int rr = r;
					for (; j < 7; ++j, ++rr)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
					}
					if (j == 7)
					{
						if (i < 43)
						{
							row1 = rr - 1;
							col1 = col;
						}
						else
						{
							row1 = r;
							col1 = col;
						}
						return make_pair(make_pair(row1, col1), make_pair(-1, -1));
					}
				}
			}
		}
	}
//横向
	//堵两棋
	start = col - 6, end = col + 6;
	if (start < 0)
		start = 0;
	if (end > COLS - 1)
		end = COLS - 1;
	count = 0;
	for (int c = start; c <= end; ++c)
	{
		if (chessBoard[row][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int c = start; c <= end - 6; ++c)
		{
			int count0 = 0, count2 = 0;
			int cc = c;
			//{0,2,2,2,2,2,0}
			if (chessBoard[row][cc] == 0) {
				row1 = row;
				col1 = cc;
				++cc;
				for (int i = 0; i < 5; ++i, ++cc)
				{
					if (chessBoard[row][cc] == 2)
						++count2;
					if (chessBoard[row][cc] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[row][cc] == 0)
				{
					row2 = row;
					col2 = cc;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	start = col - 7, end = col + 7;
	if (start < 0)
		start = 0;
	if (end > COLS - 1)
		end = COLS - 1;
	count = 0;
	for (int c = start; c <= end; ++c)
	{
		if (chessBoard[row][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int c = start; c <= end - 7; ++c)
		{
			int sele[8];
			int cc = c;
			for (int i = 0; i < 8; ++i, ++cc)
				sele[i] = chessBoard[row][cc];
			for (int i = 22; i < 26; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = row;
					col1 = c + 1;
					row2 = row;
					col2 = c + 6;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}

		//堵一棋
		for (int c = start; c <= end - 5; ++c)
		{
			int cc = c, amount2 = 0;
			int sele[6];
			for (int k = 0; k < 6; ++k, ++cc)
			{
				sele[k] = chessBoard[row][cc];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 4)
			{
				if (c == 0)
				{
					for (int i = 0; i < 3; ++i)
					{
						int j = 0;
						for (; j < 6; ++j)
						{
							if (sele[j] != boundary[i].type[j])
								break;
						}
						if (j == 6)
						{
							row1 = row;
							col1 = c + 5;
							return make_pair(make_pair(row1, col1), make_pair(-1, -1));
						}
					}
				}
				if (c + 5 == ROWS - 1)
				{
					for (int i = 3; i < 6; ++i)
					{
						int j = 0;
						for (; j < 6; ++j)
						{
							if (sele[j] != boundary[i].type[j])
								break;
						}
						if (j == 6)
						{
							row1 = row;
							col1 = c;
							return make_pair(make_pair(row1, col1), make_pair(-1, -1));
						}
					}


				}
				for (int i = 26; i < 40; ++i)
				{
					int j = 0;
					int cc = c;
					for (; j < 6; ++j, ++cc)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == OPPCOLOR && sele[j + 1] == 0)
						{
							row1 = row;
							col1 = cc + 1;
						}
					}
					if (j == 6)
						return make_pair(make_pair(row1, col1), make_pair(-1, -1));
				}
			}
		}
		for (int c = start; c <= end - 6; ++c)
		{
			int cc = c, amount2 = 0;
			int sele[7];
			for (int k = 0; k < 7; ++k, ++cc)
			{
				sele[k] = chessBoard[row][cc];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 4)
			{
				for (int i = 40; i < 47; ++i)
				{
					int j = 0;
					int cc = c;
					for (; j < 7; ++j, ++cc)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
					}
					if (j == 7)
					{
						if (i < 43)
						{
							row1 = row;
							col1 = cc - 1;
						}
						else
						{
							row1 = row;
							col1 = c;
						}
						return make_pair(make_pair(row1, col1), make_pair(-1, -1));
					}
				}
			}
		}
		
	}
//从左上角到右下角
	//堵两棋
	startR = row - 6, startC = col - 6, endR = row + 6, endC = col + 6;
	while (startR < 0 || startC < 0)
	{
		++startR;
		++startC;
	}
	while (endR > ROWS - 1 || endC > COLS - 1)
	{
		--endR;
		--endC;
	}
	count = 0;
	for (int r = startR, c = startC; r <= endR && c <= endC; ++r, ++c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 6 && c <= endC - 6; ++r, ++c)
		{
			int count0 = 0, count2 = 0;
			int rr = r, cc = c;
			if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2) {		//{0,2,2,2,2,2,0}
				row1 = rr;
				col1 = cc;
				++rr, ++cc;
				for (int i = 0; i < 5; ++i, ++rr, ++cc)
				{
					if (chessBoard[rr][cc] == 2)
						++count2;
					if (chessBoard[rr][cc] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
				{
					row2 = rr;
					col2 = cc;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	startR = row - 7, startC = col - 7, endR = row + 7, endC = col + 7;
	while (startR < 0 || startC < 0)
	{
		++startR;
		++startC;
	}
	while (endR > ROWS - 1 || endC > COLS - 1)
	{
		--endR;
		--endC;
	}
	count = 0;
	for (int r = startR, c = startC; r <= endR && c <= endC; ++r, ++c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 7 && c <= endC - 7; ++r, ++c)
		{
			int rr = r, cc = c;
			int sele[8];
			rr = r; cc = c;
			for (int i = 0; i < 8; ++i, ++rr, ++cc)
				sele[i] = chessBoard[rr][cc];
			for (int i = 22; i < 26; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = r + 1;
					col1 = c + 1;
					row2 = r + 6;
					col2 = c + 6;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
		//堵一棋
		for (int r = startR, c = startC; r <= endR - 5 && c <= endC - 5; ++r, ++c)
		{
			int rr = r, cc = c;
			int amount2 = 0;
			int sele[6];
			for (int k = 0; k < 6; ++k, ++rr, ++cc)
			{
				sele[k] = chessBoard[rr][cc];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 4)
			{
				if (r == 0)
				{
					for (int i = 0; i < 3; ++i)
					{
						int j = 0;
						for (; j < 6; ++j)
						{
							if (sele[j] != boundary[i].type[j])
								break;
						}
						if (j == 6)
						{
							row1 = r + 5;
							col1 = c + 5;
							return make_pair(make_pair(row1, col1), make_pair(-1, -1));
						}
					}
				}
				if (r + 5 == ROWS - 1)
				{
					for (int i = 3; i < 6; ++i)
					{
						int j = 0;
						for (; j < 6; ++j)
						{
							if (sele[j] != boundary[i].type[j])
								break;
						}
						if (j == 6)
						{
							row1 = r;
							col1 = c;
							return make_pair(make_pair(row1, col1), make_pair(-1, -1));
						}
					}


				}
				for (int i = 26; i < 40; ++i)
				{
					int rr = r, cc = c;
					int j = 0;
					for (; j < 6; ++j, ++rr, ++cc)
					{

						if( sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == OPPCOLOR && sele[j + 1] == 0)
						{
							row1 = rr + 1;
							col1 = cc + 1;
						}
					}
					if (j == 6)
						return make_pair(make_pair(row1, col1), make_pair(-1, -1));
				}
			}
		}
		for (int r = startR, c = startC; r <= endR - 6 && c <= endC - 6; ++r, ++c)
		{
			int rr = r, cc = c;
			int amount2 = 0;
			int sele[7];
			for (int k = 0; k < 7; ++k, ++rr, ++cc)
			{
				sele[k] = chessBoard[rr][cc];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 4)
			{
				for (int i = 40; i < 47; ++i)
				{
					for (int i = 40; i < 47; ++i)
					{
						int rr = r, cc = c;
						int j = 0;
						for (; j < 7; ++j, ++rr, ++cc)
						{

							if (sele[j] != chessType1[i].type[j])
								break;
						}
						if (j == 7)
						{
							if (i < 43)
							{
								row1 = rr - 1;
								col1 = cc - 1;
							}
							else
							{
								row1 = r;
								col1 = c;
							}
							return make_pair(make_pair(row1, col1), make_pair(-1, -1));
						}
					}
				}
			}
		}
		
	}

	return make_pair(make_pair(-1, -1), make_pair(-1, -1));
}


/*
pair<pair<int, int>, pair<int, int>> Attack(int row, int col, bool& existed)
{
	int start, end;
	int startR, startC, endR, endC;
	int row1, col1, row2, col2;
	int count = 0;
	//从右上角到左下角
	startR = row - 5, startC = col + 5, endR = row + 5, endC = col - 5;
	while (startR < 0 || startC > COLS - 1)
	{
		++startR;
		--startC;
	}
	while (endR > ROWS - 1 || endC < 0)
	{
		--endR;
		++endC;
	}
	for (int r = startR, c = startC; r <= endR && c >= endC; ++r, --c)
	{
		if (chessBoard[r][c] == OWNCOLOR)
			++count;

	}
	if (count >= 2)
	{
		for (int r = startR, c = startC; r <= endR - 5 && c >= endC - 5; ++r, --c)
		{
			for (int i = 46; i < 79; ++i)
			{
				int rr = r, cc = c;

				int j = 0, count0 = 0;
				for (; j < 6; ++j, ++rr, --cc)
				{
					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;

					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						++count0;
						if (count0 == 1)
						{
							row1 = rr;
							col1 = cc;
						}
						if (count0 == 2)
						{
							row2 = rr;
							col2 = cc;
						}
					}
				}
				if (j == 6)
				{
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	//从左上角到右下角
	startR = row - 5, startC = col - 5, endR = row + 5, endC = col + 5;
	while (startR < 0 || startC < 0)
	{
		++startR;
		++startC;
	}
	while (endR > ROWS - 1 || endC > COLS - 1)
	{
		--endR;
		--endC;
	}
	count = 0;
	for (int r = startR, c = startC; r <= endR && c <= endC; ++r, ++c)
	{
		if (chessBoard[r][c] == OWNCOLOR)
			++count;
	}
	if (count >= 2)
	{
		for (int r = startR, c = startC; r <= endR - 5 && c <= endC - 5; ++r, ++c)
		{
			for (int i = 46; i < 79; ++i)
			{
				int rr = r, cc = c;
				int j = 0, count0 = 0;
				for (; j < 6; ++j, ++rr, ++cc)
				{
					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						++count0;
						if (count0 == 1)
						{
							row1 = rr;
							col1 = cc;
						}
						if (count0 == 2)
						{
							row2 = rr;
							col2 = cc;
						}
					}
				}
				if (j == 6)
				{
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	//横向
	start = col - 5, end = col + 5;
	while (start < 0 || end > COLS - 1)
	{
		++start;
		--end;
	}
	count = 0;
	for (int c = start; c <= end; ++c)
	{
		if (chessBoard[row][c] == OWNCOLOR)
			++count;
	}
	if (count >= 2)
	{
		for (int c = start; c <= end - 5; ++c)
		{
			for (int i = 46; i < 79; ++i)
			{
				int j = 0, count0 = 0;
				for (; j < 6; ++j, ++c)
				{
					if (chessBoard[row][c] != chessType1[i].type[j])
						break;
					if (chessBoard[row][c] != 1 && chessBoard[row][c] != 2)
					{
						++count0;
						if (count0 == 1)
						{
							row1 = row;
							col1 = c;
						}
						if (count0 == 2)
						{
							row2 = row;
							col2 = c;
						}
					}
				}
				if (j == 6)
				{
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	//纵向
	start = row - 5, end = row + 5;
	while (start < 0 || end > ROWS - 1)
	{
		++start;
		--end;
	}
	count = 0;
	for (int r = start; r <= end; ++r)
	{
		if (chessBoard[r][col] == OWNCOLOR)
			++count;
	}
	if (count >= 2)
	{
		for (int r = start; r <= end - 5; ++r)
		{
			for (int i = 46; i < 79; ++i)
			{
				int j = 0, count0 = 0;
				for (; j < 6; ++j, ++r)
				{
					if (chessBoard[r][col] != chessType1[i].type[j])
						break;
					if (chessBoard[r][col] != 1 && chessBoard[r][col] != 2)
					{
						++count0;
						if (count0 == 1)
						{
							row1 = r;
							col1 = col;
						}
						if (count0 == 2)
						{
							row2 = r;
							col2 = col;
						}
					}
				}
				if (j == 6)
				{
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	return make_pair(make_pair(-1, -1), make_pair(-1, -1));
}

//己方是否存在可获胜的棋型
pair<pair<int, int>, pair<int, int>> CanWin(int row, int col, bool& existed)
{
	int start = col - 5, end = col + 5;
	int row1, col1, row2, col2;
	int startR, startC, endR, endC;
	int count = 0;
	startR = row - 5, startC = col + 5, endR = row + 5, endC = col - 5;
	while (startR < 0 || startC > COLS - 1)
	{
		++startR;
		--startC;
	}
	while (endR > ROWS - 1 || endC < 0)
	{
		--endR;
		++endC;
	}
	for (int r = startR, c = startC; r <= endR && c >= endC; ++r, --c)
	{
		if (chessBoard[r][c] == OWNCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 5 && c >= endC - 5; ++r, --c)		//从右上角到左下角
		{
			int count0 = 0, count1 = 0;
			for (int rr = r, cc = c; rr < r + 6; ++rr, --cc)
			{
				if (chessBoard[rr][cc] == 1)
					++count1;
				if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)		//空位处的数字可能为0或者8
				{
					++count0;
					if (count0 == 1)
					{
						row1 = rr;
						col1 = cc;
					}
					if (count0 == 2)
					{
						row2 = rr;
						col2 = cc;
					}

				}
			}
			if (count1 == 5 && count0 == 1)
			{
				existed = true;
				for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
				{
					if ((*it) != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), *it);
				}
			}
			if (count1 == 4 && count0 == 2)
			{
				existed = true;
				return make_pair(make_pair(row1, col1), make_pair(row2, col2));
			}
		}
	}
	startC = col - 5;
	endC = col + 5;
	while (startC < 0 || endC > COLS - 1)
	{
		++startC;
		--endC;
	}
	//从左上角到右下角
	count = 0;
	for (int r = startR, c = startC; r <= endR && c <= endC; ++r, ++c)
	{
		if (chessBoard[r][c] == OWNCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 5 && c <= endC - 5; ++r, ++c)
		{
			int count0 = 0, count1 = 0;
			for (int rr = r, cc = c; rr < r + 6; ++rr, ++cc)
			{
				if (chessBoard[rr][cc] == 1)
					++count1;
				if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
				{
					++count0;
					if (count0 == 1)
					{
						row1 = rr;
						col1 = cc;
					}
					if (count0 == 2)
					{
						row2 = rr;
						col2 = cc;
					}

				}
			}
			if (count1 == 5 && count0 == 1)
			{
				existed = true;
				for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
				{
					if ((*it) != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), *it);
				}
			}
			if (count1 == 4 && count0 == 2)
			{
				existed = true;
				return make_pair(make_pair(row1, col1), make_pair(row2, col2));
			}
		}
	}
	while (start < 0 || end > COLS - 1)
	{
		++start;
		--end;
	}
	//横向
	count = 0;
	for (int i = start; i <= end; ++i)
	{
		if (chessBoard[row][i] == OWNCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int i = start; i <= end - 5; ++i)
		{
			int count0 = 0, count1 = 0;
			for (int c = i; c < i + 6; ++c)
			{
				if (chessBoard[row][c] == 1)
					++count1;
				if (chessBoard[row][c] != 1 && chessBoard[row][c] != 2)
				{
					++count0;
					if (count0 == 1)
					{
						row1 = row;
						col1 = c;
					}
					if (count0 == 2)
					{
						row2 = row;
						col2 = c;
					}

				}
			}
			if (count1 == 5 && count0 == 1)
			{
				existed = true;
				for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
				{
					if ((*it) != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), *it);
				}
			}
			if (count1 == 4 && count0 == 2)
			{
				existed = true;
				return make_pair(make_pair(row1, col1), make_pair(row2, col2));
			}
		}
	}

	start = row - 5, end = row + 5;
	while (start < 0 || end > ROWS - 1)
	{
		++start;
		--end;
	}
	//纵向
	count = 0;
	for (int i = start; i <= end; ++i)
	{
		if (chessBoard[i][col] == OWNCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int i = start; i <= end - 5; ++i)
		{
			int count0 = 0, count1 = 0;
			for (int r = i; r < i + 6; ++r)
			{
				if (chessBoard[r][col] == 1)
					++count1;
				if (chessBoard[r][col] != 1 && chessBoard[r][col] != 2)
				{
					++count0;
					if (count0 == 1)
					{
						row1 = r;
						col1 = col;
					}
					if (count0 == 2)
					{
						row2 = r;
						col2 = col;
					}

				}
			}
			if (count1 == 5 && count0 == 1)
			{
				existed = true;
				for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
				{
					if ((*it) != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), *it);
				}
			}
			if (count1 == 4 && count0 == 2)
			{
				existed = true;
				return make_pair(make_pair(row1, col1), make_pair(row2, col2));
			}
		}
	}

	return make_pair(make_pair(-1, -1), make_pair(-1, -1));
}

pair<pair<int, int>, pair<int, int>> NeedDefense(int row, int col, bool& existed)
{
	int start = col - 5, end = col + 5;
	int row1, col1, row2, col2;
	int startR, startC, endR, endC;
	int count = 0;
	bool judg = false;
//从右上角到左下角
	//堵两棋
	startR = row - 6, startC = col + 6, endR = row + 6, endC = col - 6;
	while (startR < 0 || startC > COLS - 1)
	{
		++startR;
		--startC;
	}
	while (endR > ROWS - 1 || endC < 0)
	{
		--endR;
		++endC;
	}
	for (int r = startR, c = startC; r <= endR && c >= endC ; ++r, --c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 6 && c >= endC - 6; ++r, --c)
		{
			int count0 = 0, count2 = 0;
			int rr = r, cc = c;
			//{0,2,2,2,2,2,0}
			if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2) {
				row1 = rr;
				col1 = cc;
				++rr, --cc;
				for (int i = 0; i < 5; ++i, ++rr, --cc)
				{
					if (chessBoard[rr][cc] == 2)
						++count2;
					if (chessBoard[rr][cc] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
				{
					row2 = rr;
					col2 = cc;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	startR = row - 7, startC = col + 7, endR = row + 7, endC = col - 7;
	while (startR < 0 || startC > COLS - 1)
	{
		++startR;
		--startC;
	}
	while (endR > ROWS - 1 || endC < 0)
	{
		--endR;
		++endC;
	}
	count = 0;
	for (int r = startR, c = startC; r <= endR  && c >= endC ; ++r, --c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 7 && c >= endC - 7; ++r, --c)
		{
			int rr = r, cc = c;
			int sele[8];
			rr = r; cc = c;
			for (int i = 0; i < 8; ++i, ++rr, --cc)
				sele[i] = chessBoard[rr][cc];
			for (int i = 22; i < 25; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = r + 1;
					col1 = c - 1;
					row2 = r + 6;
					col2 = c - 6;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	//堵一棋
	count = 0;
	for (int r = startR, c = startC; r <= endR && c >= endC; ++r, --c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 5 && c >= endC - 5; ++r, --c)
		{
			for (int i = 25; i < 27; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 6; ++j, ++rr, --cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						row1 = rr;
						col1 = cc;
					}
				}
				if (j == 6)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = startR, c = startC; r <= endR - 6 && c >= endC - 6; ++r, --c)
		{
			for (int i = 27; i < 29; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 7; ++j, ++rr, --cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						row1 = rr;
						col1 = cc;
					}
				}
				if (j == 7)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = startR, c = startC; r <= endR - 7 && c >= endC - 7; ++r, --c)
		{
			for (int i = 29; i < 31; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 8; ++j, ++rr, --cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] == 2)
					{
						if (chessBoard[rr + 1][cc - 1] != 1 && chessBoard[rr + 1][cc - 1] != 2)
						{
							row1 = rr + 1;
							col1 = cc - 1;
						}
					}
				}
				if (j == 8)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
			for (int i = 31; i < 46; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 8; ++j, ++rr, --cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						row1 = rr;
						col1 = cc;
					}
				}
				if (j == 8)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
	}

//纵向
	//堵两棋
	start = row - 6, end = row + 6;
	while (start < 0 || end > ROWS - 1)
	{
		++start;
		--end;
	}
	count = 0;
	for (int r = start; r <= end; ++r)
	{
		if (chessBoard[r][col] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = start; r <= end - 6; ++r)
		{
			int count0 = 0, count2 = 0;
			//{0,2,2,2,2,2,0}
			if (chessBoard[r][col] != 1 && chessBoard[r][col] != 2) {
				row1 = r;
				col1 = col;
				++r;
				for (int i = 0; i < 5; ++i, ++r)
				{
					if (chessBoard[r][col] == 2)
						++count2;
					if (chessBoard[r][col] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[r][col] != 1 && chessBoard[r][col] != 2)
				{
					row2 = r;
					col2 = col;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	start = row - 7, end = row + 7;
	while (start < 0 || end > ROWS - 1)
	{
		++start;
		--end;
	}
	count = 0;
	for (int r = start; r <= end; ++r)
	{
		if (chessBoard[r][col] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = start; r <= end - 7; ++r)
		{
			int sele[8];
			for (int i = 0; i < 8; ++i, ++r)
				sele[i] = chessBoard[r][col];
			for (int i = 22; i < 25; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = r + 1;
					col1 = col - 1;
					row2 = r + 6;
					col2 = col - 6;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}

		//堵一棋
		for (int r = start; r <= end - 5; ++r)
		{
			for (int i = 25; i < 27; ++i)
			{
				int j = 0;
				for (; j < 6; ++j, ++r)
				{

					if (chessBoard[r][col] != chessType1[i].type[j])
						break;
					if (chessBoard[r][col] != 1 && chessBoard[r][col] != 2)
					{
						row1 = r;
						col1 = col;
					}
				}
				if (j == 6)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = start; r <= end - 6; ++r)
		{
			for (int i = 27; i < 29; ++i)
			{
				int j = 0;
				for (; j < 7; ++j, ++r)
				{

					if (chessBoard[r][col] != chessType1[i].type[j])
						break;
					if (chessBoard[r][col] != 1 && chessBoard[r][col] != 2)
					{
						row1 = r;
						col1 = col;
					}
				}
				if (j == 7)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = start; r <= end - 7; ++r)
		{
			for (int i = 29; i < 31; ++i)
			{
				int j = 0;
				for (; j < 8; ++j, ++r)
				{

					if (chessBoard[r][col] != chessType1[i].type[j])
						break;
					if (chessBoard[r][col] == 2)
					{
						if (chessBoard[r + 1][col - 1] != 1 && chessBoard[r + 1][col - 1] != 2)
						{
							row1 = r + 1;
							col1 = col - 1;
						}
					}
				}
				if (j == 8)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
			for (int i = 31; i < 46; ++i)
			{
				int j = 0;
				for (; j < 8; ++j, ++r)
				{

					if (chessBoard[r][col] != chessType1[i].type[j])
						break;
					if (chessBoard[r][col] != 1 && chessBoard[r][col] != 2)
					{
						row1 = r;
						col1 = col;
					}
				}
				if (j == 8)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
	}
//横向
	//堵两棋
	start = col - 6, end = col + 6;
	while (start < 0 || end > COLS - 1)
	{
		++start;
		--end;
	}
	count = 0;
	for (int c = start; c <= end; ++c)
	{
		if (chessBoard[row][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int c = start; c <= end - 6; ++c)
		{
			int count0 = 0, count2 = 0;
			//{0,2,2,2,2,2,0}
			if (chessBoard[row][c] != 1 && chessBoard[row][c] != 2) {
				row1 = row;
				col1 = c;
				++c;
				for (int i = 0; i < 5; ++i, ++c)
				{
					if (chessBoard[row][c] == 2)
						++count2;
					if (chessBoard[row][c] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[row][c] != 1 && chessBoard[row][c] != 2)
				{
					row2 = row;
					col2 = c;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	start = col - 7, end = col + 7;
	while (start < 0 || end > COLS - 1)
	{
		++start;
		--end;
	}
	count = 0;
	for (int c = start; c <= end; ++c)
	{
		if (chessBoard[row][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int c = start; c <= end - 7; ++c)
		{
			int sele[8];
			for (int i = 0; i < 8; ++i, ++c)
				sele[i] = chessBoard[row][c];
			for (int i = 22; i < 25; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = row + 1;
					col1 = c - 1;
					row2 = row + 6;
					col2 = c - 6;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}

		//堵一棋
		for (int c = start; c <= end - 5; ++c)
		{
			for (int i = 25; i < 27; ++i)
			{
				int j = 0;
				for (; j < 6; ++j, ++c)
				{

					if (chessBoard[row][c] != chessType1[i].type[j])
						break;
					if (chessBoard[row][c] != 1 && chessBoard[row][c] != 2)
					{
						row1 = row;
						col1 = c;
					}
				}
				if (j == 6)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int c = start; c <= end - 6; ++c)
		{
			for (int i = 27; i < 29; ++i)
			{
				int j = 0;
				for (; j < 7; ++j, ++c)
				{

					if (chessBoard[row][c] != chessType1[i].type[j])
						break;
					if (chessBoard[row][c] != 1 && chessBoard[row][c] != 2)
					{
						row1 = row;
						col1 = c;
					}
				}
				if (j == 7)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int c = start; c <= end - 7; ++c)
		{
			for (int i = 29; i < 31; ++i)
			{
				int j = 0;
				for (; j < 8; ++j, ++c)
				{

					if (chessBoard[row][c] != chessType1[i].type[j])
						break;
					if (chessBoard[row][c] == 2)
					{
						if (chessBoard[row][c + 1] != 1 && chessBoard[row][c + 1] != 2)
						{
							row1 = row;
							col1 = c + 1;
						}
					}
				}
				if (j == 8)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
			for (int i = 31; i < 46; ++i)
			{
				int j = 0;
				for (; j < 8; ++j, ++c)
				{

					if (chessBoard[row][c] != chessType1[i].type[j])
						break;
					if (chessBoard[row][c] != 1 && chessBoard[row][c] != 2)
					{
						row1 = row;
						col1 = c;
					}
				}
				if (j == 8)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
	}
//从左上角到右下角
	//堵两棋
	startR = row - 6, startC = col - 6, endR = row + 6, endC = col + 6;
	while (startR < 0 || startC < 0)
	{
		++startR;
		++startC;
	}
	while (endR > ROWS - 1 || endC > COLS - 1)
	{
		--endR;
		--endC;
	}
	count = 0;
	for (int r = startR, c = startC; r <= endR && c <= endC; ++r, ++c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 6 && c <= endC - 6; ++r, ++c)
		{
			int count0 = 0, count2 = 0;
			int rr = r, cc = c;
			if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2) {		//{0,2,2,2,2,2,0}
				row1 = rr;
				col1 = cc;
				++rr, ++cc;
				for (int i = 0; i < 5; ++i, ++rr, ++cc)
				{
					if (chessBoard[rr][cc] == 2)
						++count2;
					if (chessBoard[rr][cc] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
				{
					row2 = rr;
					col2 = cc;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	startR = row - 7, startC = col - 7, endR = row + 7, endC = col + 7;
	while (startR < 0 || startC < 0)
	{
		++startR;
		++startC;
	}
	while (endR > ROWS - 1 || endC > COLS - 1)
	{
		--endR;
		--endC;
	}
	count = 0;
	for (int r = startR, c = startC; r <= endR && c <= endC; ++r, ++c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 7 && c <= endC - 7; ++r, ++c)
		{
			int rr = r, cc = c;
			int sele[8];
			rr = r; cc = c;
			for (int i = 0; i < 8; ++i, ++rr, ++cc)
				sele[i] = chessBoard[rr][cc];
			for (int i = 22; i < 25; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = r + 1;
					col1 = c + 1;
					row2 = r + 6;
					col2 = c + 6;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
		//堵一棋
		for (int r = startR, c = startC; r <= endR - 5 && c <= endC - 5; ++r, ++c)
		{
			for (int i = 25; i < 27; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 6; ++j, ++rr, ++cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						row1 = rr;
						col1 = cc;
					}
				}
				if (j == 6)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = startR, c = startC; r <= endR - 6 && c <= endC - 6; ++r, ++c)
		{
			for (int i = 27; i < 29; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 7; ++j, ++rr, ++cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						row1 = rr;
						col1 = cc;
					}
				}
				if (j == 7)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = startR, c = startC; r <= endR - 7 && c <= endC - 7; ++r, ++c)
		{
			for (int i = 29; i < 31; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 8; ++j, ++rr, ++cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] == 2)
					{
						if (chessBoard[rr + 1][cc + 1] != 1 && chessBoard[rr + 1][cc + 1] != 2)
						{
							row1 = rr + 1;
							col1 = cc + 1;
						}
					}
				}
				if (j == 8)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
			for (int i = 31; i < 46; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 8; ++j, ++rr, ++cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						row1 = rr;
						col1 = cc;
					}
				}
				if (j == 8)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
	}

	return make_pair(make_pair(-1, -1), make_pair(-1, -1));
}

*/

/*
pair<pair<int, int>, pair<int, int>> NeedDefense(int row, int col, bool& existed)
{
	int start = col - 5, end = col + 5;
	int row1, col1, row2, col2;
	int startR, startC, endR, endC;
	int count = 0;
	bool judg = false;
//从右上角到左下角
	//堵两棋
	startR = row - 6, startC = col + 6, endR = row + 6, endC = col - 6;
	while (startR < 0 || startC > COLS - 1)
	{
		++startR;
		--startC;
	}
	while (endR > ROWS - 1 || endC < 0)
	{
		--endR;
		++endC;
	}
	for (int r = startR, c = startC; r <= endR && c >= endC ; ++r, --c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 6 && c >= endC - 6; ++r, --c)
		{
			int count0 = 0, count2 = 0;
			int rr = r, cc = c;
			//{0,2,2,2,2,2,0}
			if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2) {
				row1 = rr;
				col1 = cc;
				++rr, --cc;
				for (int i = 0; i < 5; ++i, ++rr, --cc)
				{
					if (chessBoard[rr][cc] == 2)
						++count2;
					if (chessBoard[rr][cc] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
				{
					row2 = rr;
					col2 = cc;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	startR = row - 7, startC = col + 7, endR = row + 7, endC = col - 7;
	while (startR < 0 || startC > COLS - 1)
	{
		++startR;
		--startC;
	}
	while (endR > ROWS - 1 || endC < 0)
	{
		--endR;
		++endC;
	}
	count = 0;
	for (int r = startR, c = startC; r <= endR  && c >= endC ; ++r, --c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 7 && c >= endC - 7; ++r, --c)
		{
			int rr = r, cc = c;
			int sele[8];
			rr = r; cc = c;
			for (int i = 0; i < 8; ++i, ++rr, --cc)
				sele[i] = chessBoard[rr][cc];
			for (int i = 22; i < 25; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = r + 1;
					col1 = c - 1;
					row2 = r + 6;
					col2 = c - 6;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	//堵一棋
	count = 0;
	for (int r = startR, c = startC; r <= endR && c >= endC; ++r, --c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 5 && c >= endC - 5; ++r, --c)
		{
			for (int i = 25; i < 27; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 6; ++j, ++rr, --cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						row1 = rr;
						col1 = cc;
					}
				}
				if (j == 6)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = startR, c = startC; r <= endR - 6 && c >= endC - 6; ++r, --c)
		{
			for (int i = 27; i < 29; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 7; ++j, ++rr, --cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						row1 = rr;
						col1 = cc;
					}
				}
				if (j == 7)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = startR, c = startC; r <= endR - 7 && c >= endC - 7; ++r, --c)
		{
			int rr = r, cc = c;
			int amount2 = 0;
			int sele[8];
			for (int k = 0; k < 8; ++k, ++rr,--cc)
			{
				sele[k] = chessBoard[rr][cc];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 4)
			{
				for (int i = 29; i < 31; ++i)
				{
					int j = 0;
					int rr = r, cc = c;
					for (; j < 8; ++j, ++rr, --cc)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == OPPCOLOR)
						{
							if (sele[j + 1] == 0)
							{
								row1 = rr + 1;
								col1 = cc - 1;
							}
						}
					}
					if (j == 8)
					{
						pair<pair<int, int>, pair<int, int>> step;
						existed = true;
						for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
							step = Attack((*it).first, (*it).second, existed);
						if (step.first != make_pair(row1, col1))
							return make_pair(make_pair(row1, col1), step.first);
						else
							return make_pair(make_pair(row1, col1), step.second);
					}
				}
				for (int i = 31; i < 46; ++i)
				{
					int rr = r, cc = c;
					int j = 0;
					for (; j < 8; ++j, ++rr, --cc)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == 0)
						{
							row1 = rr;
							col1 = cc;
						}
					}
					if (j == 8)
					{
						pair<pair<int, int>, pair<int, int>> step;
						existed = true;
						for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
							step = Attack((*it).first, (*it).second, existed);
						if (step.first != make_pair(row1, col1))
							return make_pair(make_pair(row1, col1), step.first);
						else
							return make_pair(make_pair(row1, col1), step.second);
					}
				}
			}
		}
	}

//纵向
	//堵两棋
	start = row - 6, end = row + 6;
	if (start < 0)
		start = 0;
	if (end > ROWS - 1)
		end = ROWS - 1;
	count = 0;
	for (int r = start; r <= end; ++r)
	{
		if (chessBoard[r][col] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = start; r <= end - 6; ++r)
		{
			int rr = r;
			int count0 = 0, count2 = 0;
			//{0,2,2,2,2,2,0}
			if (chessBoard[rr][col] == 0) {
				row1 = rr;
				col1 = col;
				++r;
				for (int i = 0; i < 5; ++i, ++rr)
				{
					if (chessBoard[rr][col] == 2)
						++count2;
					if (chessBoard[rr][col] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[rr][col] == 0)
				{
					row2 = rr;
					col2 = col;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	start = row - 7, end = row + 7;
	if (start < 0)
		start = 0;
	if (end > ROWS - 1)
		end = ROWS - 1;
	count = 0;
	for (int r = start; r <= end; ++r)
	{
		if (chessBoard[r][col] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = start; r <= end - 7; ++r)
		{
			int sele[8];
			int rr = r;
			for (int i = 0; i < 8; ++i, ++rr)
				sele[i] = chessBoard[rr][col];
			for (int i = 22; i < 25; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = r + 1;		//此处是r,不是rr
					col1 = col;
					row2 = r + 6;
					col2 = col;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}

		//堵一棋
		for (int r = start; r <= end - 5; ++r)
		{
			for (int i = 25; i < 27; ++i)
			{
				int j = 0;
				int rr = r;
				for (; j < 6; ++j, ++rr)
				{

					if (chessBoard[rr][col] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][col] == 0)
					{
						row1 = rr;
						col1 = col;
					}
				}
				if (j == 6)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = start; r <= end - 6; ++r)
		{
			for (int i = 27; i < 29; ++i)
			{
				int j = 0;
				int rr = r;
				for (; j < 7; ++j, ++rr)
				{

					if (chessBoard[rr][col] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][col] == 0)
					{
						row1 = rr;
						col1 = col;
					}
				}
				if (j == 7)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = start; r <= end - 7; ++r)
		{
			int rr = r, amount2 = 0;
			int sele[8];
			for (int k = 0; k < 8; ++k, ++rr)
			{
				sele[k] = chessBoard[rr][col];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 2)
			{
				int rr = r;
				for (int i = 29; i < 31; ++i)
				{
					int j = 0;
					for (; j < 8; ++j, ++rr)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == OPPCOLOR)
						{
							if (sele[j+1] == 0)
							{
								row1 = rr + 1;
								col1 = col - 1;
							}
						}
					}
					if (j == 8)
					{
						pair<pair<int, int>, pair<int, int>> step;
						existed = true;
						for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
							step = Attack((*it).first, (*it).second, existed);
						if (step.first != make_pair(row1, col1))
							return make_pair(make_pair(row1, col1), step.first);
						else
							return make_pair(make_pair(row1, col1), step.second);
					}
				}
				for (int i = 31; i < 46; ++i)
				{
					int rr = r;
					int j = 0;
					for (; j < 8; ++j, ++rr)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == 0)
						{
							row1 = rr;
							col1 = col;
						}
					}
					if (j == 8)
					{
						pair<pair<int, int>, pair<int, int>> step;
						existed = true;
						for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
							step = Attack((*it).first, (*it).second, existed);
						if (step.first != make_pair(row1, col1))
							return make_pair(make_pair(row1, col1), step.first);
						else
							return make_pair(make_pair(row1, col1), step.second);
					}
				}
			}
		}
	}
//横向
	//堵两棋
	start = col - 6, end = col + 6;
	if (start < 0)
		start = 0;
	if (end > COLS - 1)
		end = COLS - 1;
	count = 0;
	for (int c = start; c <= end; ++c)
	{
		if (chessBoard[row][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int c = start; c <= end - 6; ++c)
		{
			int count0 = 0, count2 = 0;
			int cc = c;
			//{0,2,2,2,2,2,0}
			if (chessBoard[row][cc] == 0) {
				row1 = row;
				col1 = cc;
				++cc;
				for (int i = 0; i < 5; ++i, ++cc)
				{
					if (chessBoard[row][cc] == 2)
						++count2;
					if (chessBoard[row][cc] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[row][cc] == 0)
				{
					row2 = row;
					col2 = cc;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	start = col - 7, end = col + 7;
	if (start < 0)
		start = 0;
	if (end > COLS - 1)
		end = COLS - 1;
	count = 0;
	for (int c = start; c <= end; ++c)
	{
		if (chessBoard[row][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int c = start; c <= end - 7; ++c)
		{
			int sele[8];
			int cc = c;
			for (int i = 0; i < 8; ++i, ++cc)
				sele[i] = chessBoard[row][cc];
			for (int i = 22; i < 25; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = row;
					col1 = c + 1;
					row2 = row;
					col2 = c + 6;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}

		//堵一棋
		for (int c = start; c <= end - 5; ++c)
		{
			for (int i = 25; i < 27; ++i)
			{
				int j = 0;
				int cc = c;
				for (; j < 6; ++j, ++cc)
				{

					if (chessBoard[row][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[row][cc] == 0)
					{
						row1 = row;
						col1 = cc;
					}
				}
				if (j == 6)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int c = start; c <= end - 6; ++c)
		{
			for (int i = 27; i < 29; ++i)
			{
				int j = 0;
				int cc = c;
				for (; j < 7; ++j, ++cc)
				{

					if (chessBoard[row][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[row][cc] != 1 && chessBoard[row][c] != 2)
					{
						row1 = row;
						col1 = cc;
					}
				}
				if (j == 7)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int c = start; c <= end - 7; ++c)
		{
			int cc = c, amount2 = 0;
			int sele[8];
			for (int k = 0; k < 8; ++k, ++cc)
			{
				sele[k] = chessBoard[row][cc];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 4)
			{
				for (int i = 29; i < 31; ++i)
				{
					int j = 0;
					int cc = c;
					for (; j < 8; ++j, ++cc)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == OPPCOLOR)
						{
							if (sele[j+1] == 0)
							{
								row1 = row;
								col1 = cc + 1;
							}
						}
					}
					if (j == 8)
					{
						pair<pair<int, int>, pair<int, int>> step;
						existed = true;
						for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
							step = Attack((*it).first, (*it).second, existed);
						if (step.first != make_pair(row1, col1))
							return make_pair(make_pair(row1, col1), step.first);
						else
							return make_pair(make_pair(row1, col1), step.second);
					}
				}
				for (int i = 31; i < 46; ++i)
				{
					int j = 0;
					int cc = c;
					for (; j < 8; ++j, ++cc)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == 0)
						{
							row1 = row;
							col1 = cc;
						}
					}
					if (j == 8)
					{
						pair<pair<int, int>, pair<int, int>> step;
						existed = true;
						for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
							step = Attack((*it).first, (*it).second, existed);
						if (step.first != make_pair(row1, col1))
							return make_pair(make_pair(row1, col1), step.first);
						else
							return make_pair(make_pair(row1, col1), step.second);
					}
				}
			}
		}
	}
//从左上角到右下角
	//堵两棋
	startR = row - 6, startC = col - 6, endR = row + 6, endC = col + 6;
	while (startR < 0 || startC < 0)
	{
		++startR;
		++startC;
	}
	while (endR > ROWS - 1 || endC > COLS - 1)
	{
		--endR;
		--endC;
	}
	count = 0;
	for (int r = startR, c = startC; r <= endR && c <= endC; ++r, ++c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 6 && c <= endC - 6; ++r, ++c)
		{
			int count0 = 0, count2 = 0;
			int rr = r, cc = c;
			if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2) {		//{0,2,2,2,2,2,0}
				row1 = rr;
				col1 = cc;
				++rr, ++cc;
				for (int i = 0; i < 5; ++i, ++rr, ++cc)
				{
					if (chessBoard[rr][cc] == 2)
						++count2;
					if (chessBoard[rr][cc] != 2)
						break;
				}
				if (count2 == 5 && chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
				{
					row2 = rr;
					col2 = cc;
					existed = true;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
	}
	startR = row - 7, startC = col - 7, endR = row + 7, endC = col + 7;
	while (startR < 0 || startC < 0)
	{
		++startR;
		++startC;
	}
	while (endR > ROWS - 1 || endC > COLS - 1)
	{
		--endR;
		--endC;
	}
	count = 0;
	for (int r = startR, c = startC; r <= endR && c <= endC; ++r, ++c)
	{
		if (chessBoard[r][c] == OPPCOLOR)
			++count;
	}
	if (count >= 4)
	{
		for (int r = startR, c = startC; r <= endR - 7 && c <= endC - 7; ++r, ++c)
		{
			int rr = r, cc = c;
			int sele[8];
			rr = r; cc = c;
			for (int i = 0; i < 8; ++i, ++rr, ++cc)
				sele[i] = chessBoard[rr][cc];
			for (int i = 22; i < 25; ++i)
			{
				int j = 0;
				for (; j < 8; ++j)
				{

					if (sele[j] != chessType1[i].type[j])
						break;
				}
				if (j == 8)
				{
					existed = true;
					row1 = r + 1;
					col1 = c + 1;
					row2 = r + 6;
					col2 = c + 6;
					return make_pair(make_pair(row1, col1), make_pair(row2, col2));
				}
			}
		}
		//堵一棋
		for (int r = startR, c = startC; r <= endR - 5 && c <= endC - 5; ++r, ++c)
		{
			for (int i = 25; i < 27; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 6; ++j, ++rr, ++cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						row1 = rr;
						col1 = cc;
					}
				}
				if (j == 6)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = startR, c = startC; r <= endR - 6 && c <= endC - 6; ++r, ++c)
		{
			for (int i = 27; i < 29; ++i)
			{
				int rr = r, cc = c;
				int j = 0;
				for (; j < 7; ++j, ++rr, ++cc)
				{

					if (chessBoard[rr][cc] != chessType1[i].type[j])
						break;
					if (chessBoard[rr][cc] != 1 && chessBoard[rr][cc] != 2)
					{
						row1 = rr;
						col1 = cc;
					}
				}
				if (j == 7)
				{
					pair<pair<int, int>, pair<int, int>> step;
					existed = true;
					for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
						step = Attack((*it).first, (*it).second, existed);
					if (step.first != make_pair(row1, col1))
						return make_pair(make_pair(row1, col1), step.first);
					else
						return make_pair(make_pair(row1, col1), step.second);
				}
			}
		}
		for (int r = startR, c = startC; r <= endR - 7 && c <= endC - 7; ++r, ++c)
		{
			int rr = r, cc = c;
			int amount2 = 0;
			int sele[8];
			for (int k = 0; k < 8; ++k, ++rr,++cc)
			{
				sele[k] = chessBoard[rr][cc];
				if (sele[k] == OPPCOLOR)
					++amount2;
			}
			if (amount2 >= 4)
			{
				for (int i = 29; i < 31; ++i)
				{
					int rr = r, cc = c;
					int j = 0;
					for (; j < 8; ++j, ++rr, ++cc)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j] == OPPCOLOR)
						{
							if (sele[j + 1] == 0)
							{
								row1 = rr + 1;
								col1 = cc + 1;
							}
						}
					}
					if (j == 8)
					{
						pair<pair<int, int>, pair<int, int>> step;
						existed = true;
						for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
							step = Attack((*it).first, (*it).second, existed);
						if (step.first != make_pair(row1, col1))
							return make_pair(make_pair(row1, col1), step.first);
						else
							return make_pair(make_pair(row1, col1), step.second);
					}
				}
				for (int i = 31; i < 46; ++i)
				{
					int rr = r, cc = c;
					int j = 0;
					for (; j < 8; ++j, ++rr, ++cc)
					{

						if (sele[j] != chessType1[i].type[j])
							break;
						if (sele[j+ 1] == 0)
						{
							row1 = rr;
							col1 = cc;
						}
					}
					if (j == 8)
					{
						pair<pair<int, int>, pair<int, int>> step;
						existed = true;
						for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
							step = Attack((*it).first, (*it).second, existed);
						if (step.first != make_pair(row1, col1))
							return make_pair(make_pair(row1, col1), step.first);
						else
							return make_pair(make_pair(row1, col1), step.second);
					}
				}
			}
		}
	}

	return make_pair(make_pair(-1, -1), make_pair(-1, -1));
}


*/

/*
struct ChessType chessType1[M] =
{
	//己方存在可获胜的五子
	{0,1,1,1,1,1},	//0
	{1,0,1,1,1,1},
	{1,1,0,1,1,1},
	{1,1,1,0,1,1},
	{1,1,1,1,0,1},
	{1,1,1,1,1,0},
	//己方存在可获胜的四子
	{0,0,1,1,1,1},	//6
	{1,0,0,1,1,1},
	{1,1,0,0,1,1},
	{1,1,1,0,0,1},
	{1,1,1,1,0,0},
	{0,1,0,1,1,1},
	{0,1,1,0,1,1},
	{0,1,1,1,0,1},
	{0,1,1,1,1,0},
	{1,0,1,0,1,1},
	{1,0,1,1,0,1},
	{1,0,1,1,1,0},
	{1,1,0,1,0,1},
	{1,1,0,1,1,0},
	{1,1,1,0,1,0},
	//需堵两子才可阻止对方获胜
	{0,2,2,2,2,2,0},	//21
	{2,0,2,2,2,2,0},
	{0,2,2,2,2,0,2},
	{0,2,2,2,2,0},
	//需堵一子即可阻止对方获胜
	{2,2,0,2,2,2},	//25
	{2,2,2,0,2,2},
	{2,2,0,0,2,2},
	{2,2,2,0,0,2},
	{2,0,0,2,2,2},
	{0,2,0,2,2,2},
	{0,2,2,0,2,2},
	{0,2,2,2,0,2},
	{2,0,2,0,2,2},
	{2,0,2,2,0,2},
	{2,0,2,2,2,0},
	{2,2,0,2,0,2},
	{2,2,0,2,2,0},
	{2,2,2,0,2,0},
	{1,2,2,2,2,2,0},
	{0,2,2,2,2,2,1},
	{0,0,2,2,2,2,1},
	{1,0,2,2,2,2,0},
	{0,2,2,2,2,0,1},
	{1,2,2,2,2,0,0},
	{2,0,2,2,2,2,0,1},
	{1,0,2,2,2,2,0,2},
	//己方有获胜潜力的三子
	{0,0,0,1,1,1},	//46
	{1,1,1,0,0,0},
	{0,1,1,1,0,0},
	{0,0,1,1,1,0},
	{1,0,1,1,0,0},
	{1,1,0,1,0,0},
	{0,0,1,0,1,1},
	{0,0,1,1,0,1},
	{0,1,0,0,1,1},
	{0,1,1,0,0,1},
	{1,0,0,1,1,0},
	{1,1,0,0,1,0},
	{1,0,0,0,1,1},
	{1,1,0,0,0,1},
	{1,0,1,0,0,1},
	{1,0,0,1,0,1},
	{0,1,0,1,0,1},
	{1,0,1,0,1,0},
	//己方存在有获胜潜力的二子
	{1,1,0,0,0,0},	//64
	{0,1,1,0,0,0},
	{0,0,1,1,0,0},
	{0,0,0,1,1,0},
	{0,0,0,0,1,1},
	{1,0,1,0,0,0},
	{0,1,0,1,0,0},
	{0,0,1,0,1,0},
	{0,0,0,1,0,1},
	{1,0,0,1,0,0},
	{0,1,0,0,1,0},
	{0,0,1,0,0,1},
	{1,0,0,0,1,0},
	{0,1,0,0,0,1},
	{1,0,0,0,0,1},	//78

};
*/