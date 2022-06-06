#define _CRT_SECURE_NO_WARNINGS
#include "Reversi.h"
#include "Match.h"
#include <vector>
#include <iomanip>
using namespace std;
#define random(x) (rand()%x)
#define ROWS 19
#define COLS 19
#define ROUNDS 3
#define C 9
#define OWNCOLOR 1
#define OPPCOLOR 2

int chessBoard[ROWS][COLS];
vector< pair<int, int>>waitSele;	//存放可选点的坐标；
bool firstSteps = true;
void Init();
Reversi::Reversi(){
    client_socket = ClientSocket();
    oppositeColor = ownColor = -1;
}

Reversi::~Reversi(){}
void Reversi::setOwnColor(int color)
{
	if (color != 0 || color != 1)
		return;
	ownColor = color;
	oppositeColor = 1 - color;
}
;

/*
 send id and password to server by socket
 rtn != 0 represents socket transfer error
 */
void Reversi::authorize(const char *id , const char *pass)
{
    client_socket.connectServer();
    std::cout << "Authorize " << id << std::endl;
    char msgBuf[BUFSIZE];
    memset(msgBuf , 0 , BUFSIZE);
    msgBuf[0] = 'A';
    memcpy(&msgBuf[1] , id , 9);
    memcpy(&msgBuf[10] , pass , 6);
    int rtn = client_socket.sendMsg(msgBuf);
    if (rtn != 0) printf("Authorized Failed!\n");
}

// 用户id输入，服务器上需要有对应的账号密码：对应文件 players-0.txt
void Reversi::gameStart()
{
    char id[12] = {0}, passwd[10] = {0};
	strcpy(id, ID);
	strcpy(passwd, PASSWORD);
    authorize(id, passwd);
    
    printf("Game Start!\n");
    
    for (int round = 0 ; round < ROUNDS ; round++){
		for (int r = 0; r < ROWS; ++r)
			for (int c = 0; c < COLS; ++c)
				chessBoard[r][c] = 0;
		/*if (round != 1)
			chessBoard[C][C] = 2;
		else
			chessBoard[C][C] = 1;*/
		Init();
		roundStart(round);
		oneRound();
		roundOver(round);
		waitSele.clear();
		firstSteps = true;
    }
    gameOver();
    client_socket.close();
}

void Reversi::gameOver()
{
    printf("Game Over!\n");
}

//发一次消息，走哪一步，等两个消息，1.自己的步数行不行 2.对面走了哪一步 
void Reversi::roundStart(int round)
{
    printf("Round %d Ready Start!\n" , round);
    
    // first time receive msg from server
    int rtn = client_socket.recvMsg();
    if (rtn != 0) return ;
    if(strlen(client_socket.getRecvMsg()) < 2)
        printf("Authorize Failed!\n");
    else
        printf("Round start received msg %s\n", client_socket.getRecvMsg());
    switch (client_socket.getRecvMsg()[1]) {
            // this client : black chessman
        case 'B':
            ownColor = 0;
            oppositeColor = 1;
			chessBoard[C][C] = OPPCOLOR;
            rtn = client_socket.sendMsg("BB");
            printf("Send BB -> rtn: %d\n", rtn);
            if (rtn != 0) return ;
            break;
        case 'W':
            ownColor = 1;
            oppositeColor = 0;
			chessBoard[C][C] = OWNCOLOR;
            rtn = client_socket.sendMsg("BW");
            printf("Send BW -> rtn: %d\n", rtn);
            if (rtn != 0) return ;
            break;
        default:
            printf("Authorized Failed!\n");
            break;
    }
}

void Reversi::oneRound()
{
    int STEP = 1;
    switch (ownColor) {
        case 0:
            while (STEP < 10000) {
                
				pair<pair<int, int>, pair<int, int>> chess = step();                        // take action, send message
                
                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first.first, chess.first.second, chess.second.first, chess.second.second);
                
                
                if (observe() >= 1) break;     // receive RET Code
                
                if (observe() >= 1) break;    // see white move
                STEP++;
                // saveChessBoard();
            }
            printf("One Round End\n");
            break;
        case 1:
            while (STEP < 10000) {
                
                if (observe() >= 1) break;    // see black move
                
				pair<pair<int, int>, pair<int, int>> chess = step();                        // take action, send message
                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first.first,chess.first.second,chess.second.first, chess.second.second);
                
                
                if (observe() >= 1) break;     // receive RET Code
                // saveChessBoard();
                STEP++;
            }
            printf("One Round End\n");
            break;
            
        default:
            break;
    }
}

void Reversi::roundOver(int round)
{
    printf("Round %d Over!\n", round);
    // reset initializer

    ownColor = oppositeColor = -1;
}

int Reversi::observe()
{
	int rtn = 0;
	int recvrtn = client_socket.recvMsg();
	if (recvrtn != 0) return 1;
	printf("receive msg %s\n", client_socket.getRecvMsg());
	switch (client_socket.getRecvMsg()[0]) {
	case 'R':
	{
		switch (client_socket.getRecvMsg()[1]) {
		case 'Y':   // valid step
			switch (client_socket.getRecvMsg()[2]) {
			case 'P':   // update chessboard
			{
				int desRow1 = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol1 = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int desRow2 = (client_socket.getRecvMsg()[7] - '0') * 10 + client_socket.getRecvMsg()[8] - '0';
				int desCol2 = (client_socket.getRecvMsg()[9] - '0') * 10 + client_socket.getRecvMsg()[10] - '0';
				int color = (client_socket.getRecvMsg()[11] - '0');
				//你应该在这里处理desRow和desCol，推荐使用函数
				handleMessage(desRow1, desCol1, desRow2, desCol2, color);
				saveChessBoard();
				printf("a valid step of : (%d %d) (%d %d)\n", desRow1, desCol1, desRow2, desCol2);
				break;
			}
			case 'N':   // R0N: enemy wrong step
			{
				//
				printf("a true judgement of no step\n");
				break;
			}
			}

			break;
		case 'W':
			// invalid step
			switch (client_socket.getRecvMsg()[2]) {
			case 'P': {
				int desRow1 = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol1 = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int desRow2 = (client_socket.getRecvMsg()[7] - '0') * 10 + client_socket.getRecvMsg()[8] - '0';
				int desCol2 = (client_socket.getRecvMsg()[9] - '0') * 10 + client_socket.getRecvMsg()[10] - '0';
				int color = (client_socket.getRecvMsg()[11] - '0');
				printf("Invalid step , server random a true step of : (%d %d) (%d %d)\n", desRow1, desCol1, desRow2, desCol2);
				//你应该在这里处理desRow和desCol，推荐使用函数
				handleMessage(desRow1, desCol1, desRow2, desCol2, color);
				saveChessBoard();
				break;
			}
			case 'N': {
				printf("a wrong judgement of no step\n");
				break;
			}
			default:
				break;
			}
			break;
		case '1':

			printf("Error -1: Msg format error!\n");
			rtn = -1;
			break;
		case '2':

			printf("Error -2: Corrdinate error!\n");
			rtn = -2;
			break;
		case '4':

			printf("Error -4: Invalid step!\n");
			rtn = -4;
			break;
		default:

			printf("Error -5: Other error!\n");
			rtn = -5;
			break;
		}
		break;
	}
	case 'E':
	{
		switch (client_socket.getRecvMsg()[1]) {
		case '0':
			// game over
			rtn = 2;
			break;
		case '1':
			// round over
			rtn = 1;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return rtn;
}

void Reversi::generateOneStepMessage(int row1, int col1, int row2, int col2)
{
	char msg[BUFSIZE];
	memset(msg, 0, sizeof(msg));

	//put row and col in the message
	msg[0] = 'S';
	msg[1] = 'P';
	msg[2] = '0' + row1 / 10;
	msg[3] = '0' + row1 % 10;
	msg[4] = '0' + col1 / 10;
	msg[5] = '0' + col1 % 10;
	msg[6] = '0' + row2 / 10;
	msg[7] = '0' + row2 % 10;
	msg[8] = '0' + col2 / 10;
	msg[9] = '0' + col2 % 10;
	msg[10] = '\0';

	//print
	printf("generate one step at possition (%2d,%2d,%2d,%2d) : %s\n", row1, col1, row2, col2, msg);


	client_socket.sendMsg(msg);
}

/*-------------------------last three function--------------------------------
* step : find a good position to lazi your chess.
* saveChessBoard : save the chess board now.
* handleMessage: handle the message from server.
*/
void Init()
{
	waitSele.push_back(make_pair(C, C - 1));
	waitSele.push_back(make_pair(C, C + 1));
	waitSele.push_back( make_pair(C - 1, C));
	waitSele.push_back( make_pair(C + 1, C));
	waitSele.push_back(make_pair(C - 1, C - 1));
	waitSele.push_back(make_pair(C + 1, C - 1));
	waitSele.push_back(make_pair(C - 1, C + 1));
	waitSele.push_back( make_pair(C + 1, C + 1));
	
}
pair<pair<int, int>, pair<int, int>> Reversi::step()
{
	pair<pair<int, int>, pair<int,int>>step;
	int row, col;
	bool existed = false;	//判断是否存在有可获胜的棋
	if (firstSteps) {
		firstSteps = false;
		pair<int, int>step1,step2;
		int count = 0;
		if (chessBoard[10][10] == 0)
		{
			step1 = make_pair(10, 10);
			++count;
		}
		if (chessBoard[11][9] == 0)
		{
			step2 = make_pair(11, 9);
			++count;
		}
		if (count == 2)
			return make_pair(step1, step2);
		if (count == 0)
			return make_pair(make_pair(8, 10), make_pair(10, 8));
		if (step1 == make_pair(10, 10))
		{
			if(chessBoard[9][10] == 0)
				return make_pair(step1, make_pair(9, 10));
			return make_pair(step1, make_pair(10, 9));
		}			
		if (step2 == make_pair(11, 9))
		{
			if (chessBoard[10][9] == 0)
				return make_pair(step2, make_pair(10, 9));
			return make_pair(step2, make_pair(11, 10));
		}
	}
	if (waitSele.empty())
		return make_pair(make_pair(-1, -1), make_pair(-1, -1));
	for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
	{
		row = (*it).first;
		col = (*it).second;
		step = CanWin(row, col, existed);
		if (existed)
			return step;
	}
	for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
	{
		row = (*it).first;
		col = (*it).second;
		step = NeedDefense(row, col, existed);
		if (existed)
			return step;
		if (step.first != make_pair(-1, -1))
		{
			pair<pair<int, int>, pair<int, int>>step1;
			chessBoard[step.first.first][step.second.second] = OWNCOLOR;
			for (auto it1 = waitSele.begin(); it1 != waitSele.end(); ++it1)
			{
				if(*it1 != step.first)
					step1 = NeedDefense((*it1).first, (*it1).second, existed);
				if (step1.first != make_pair(-1, -1) && step1.first != step.first)
				{
					chessBoard[step.first.first][step.second.second] = 0;
					return make_pair(step.first, step1.first);
				}
			}
			for (auto it1 = waitSele.begin(); it1 != waitSele.end(); ++it1)
			{
				step1 = Attack((*it1).first, (*it1).second, existed);
				if (existed)
				{
					chessBoard[step.first.first][step.second.second] = 0;
					if (step1.first != step.first)
						return make_pair(step.first, step1.first);
					else
						return make_pair(step.first, step1.second);
				}
			}
			for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
			{
				chessBoard[step.first.first][step.second.second] = 0;
				if (*it != step.first)
					return make_pair(step.first, *it);
			}
				
		}
	}
	for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
	{
		row = (*it).first;
		col = (*it).second;
		step = Attack(row, col, existed);
		if (existed)
			return step;
	}
	for (auto it = waitSele.begin(); it != waitSele.end(); ++it)
		return make_pair(*it, *(++it));
}



void Reversi::saveChessBoard()
{

	cout << "     ";
	for (int i = 0; i < ROWS; ++i)
	{
		cout << left << setw(5) << i;
	}
	cout << endl;
	for (int i = 0; i < ROWS; ++i)
	{
		cout << left << setw(5) << i;
		for (int j = 0; j < COLS; ++j)
		{
			if (chessBoard[i][j] == 1 || chessBoard[i][j] == 2)
				cout << left << setw(5) << chessBoard[i][j];
			else
				cout << left << setw(5) << '-';
		}
		cout << endl;
	}
}


void Reversi::handleMessage(int row1, int col1, int row2, int col2, int color) {
	vector<pair<int, int>>posi;
	bool in = false;
	int cross = 0, len = 0, lefSlant = 0, rigSlant = 0, score = 0;
	if (color == ownColor) {
		chessBoard[row1][col1] = OWNCOLOR;
		chessBoard[row2][col2] = OWNCOLOR;
	}
	else {
		chessBoard[row1][col1] = OPPCOLOR;
		chessBoard[row2][col2] = OPPCOLOR;
	}
	for (auto it = waitSele.begin(); it != waitSele.end(); )
	{
		if ((*it) == make_pair(row1, col1) || (*it) == make_pair(row2, col2))
			it = waitSele.erase(it);
		else
			++it;
	}
	//将（row1,col1)附近的空位加入可选点
	if (row1 >= 1) {
		posi.push_back(make_pair(row1 - 1, col1));
		if (col1 >= 1)
			posi.push_back(make_pair(row1 - 1, col1 - 1));
		if (col1 < COLS - 1)
			posi.push_back(make_pair(row1 - 1, col1 + 1));
		if (row1 >= 2)
		{
			posi.push_back(make_pair(row1 - 2, col1));
			if (col1 >= 2)
				posi.push_back(make_pair(row1 - 2, col1 - 2));
			if (col1 < COLS - 2)
				posi.push_back(make_pair(row1 - 2, col1 + 2));
		}

	}
	if (row1 < ROWS - 1) {
		posi.push_back(make_pair(row1 + 1, col1));
		if (row1 < ROWS - 2)
		{
			posi.push_back(make_pair(row1 + 2, col1));
			if (col1 >= 2)
				posi.push_back(make_pair(row1 + 2, col1 - 2));
			if (col1 < COLS - 2)
				posi.push_back(make_pair(row1 + 2, col1 + 2));
		}
		if (col1 >= 1)
			posi.push_back(make_pair(row1 + 1, col1 - 1));
		if (col1 < COLS - 1)
			posi.push_back(make_pair(row1 + 1, col1 + 1));

	}
	if (col1 >= 1) {
		posi.push_back(make_pair(row1, col1 - 1));
		if (col1 >= 2)
			posi.push_back(make_pair(row1, col1 - 2));
	}
	if (col1 <= COLS - 1) {
		posi.push_back(make_pair(row1, col1 + 1));
		if (col1 <= COLS - 2)
			posi.push_back(make_pair(row1, col1 + 2));
	}

	if (row2 >= 1) {
		posi.push_back(make_pair(row2 - 1, col2));
		if (col2 >= 1)
			posi.push_back(make_pair(row2 - 1, col2 - 1));
		if (col2 < COLS - 1)
			posi.push_back(make_pair(row2 - 1, col2 + 1));
		if (row2 >= 2)
		{
			posi.push_back(make_pair(row2 - 2, col2));
			if (col2 >= 2)
				posi.push_back(make_pair(row2 - 2, col2 - 2));
			if (col2 < COLS - 2)
				posi.push_back(make_pair(row2 - 2, col2 + 2));
		}

	}
	if (row2 < ROWS - 1) {
		posi.push_back(make_pair(row2 + 1, col2));
		if (row2 < ROWS - 2)
		{
			posi.push_back(make_pair(row2 + 2, col2));
			if (col2 >= 2)
				posi.push_back(make_pair(row2 + 2, col2 - 2));
			if (col2 < COLS - 2)
				posi.push_back(make_pair(row2 + 2, col2 + 2));
		}
		if (col2 >= 1)
			posi.push_back(make_pair(row2 + 1, col2 - 1));
		if (col2 < COLS - 1)
			posi.push_back(make_pair(row2 + 1, col2 + 1));

	}
	if (col2 >= 1) {
		posi.push_back(make_pair(row2, col2 - 1));
		if (col2 >= 2)
			posi.push_back(make_pair(row2, col2 - 2));
	}
	if (col2 <= COLS - 1) {
		posi.push_back(make_pair(row2, col2 + 1));
		if (col2 <= COLS - 2)
			posi.push_back(make_pair(row2, col2 + 2));
	}
	
	for (auto it = posi.begin(); it != posi.end(); ++it)
	{
		bool exist = false;
		for (auto it1 = waitSele.begin(); it1 != waitSele.end(); ++it1)
		{
			if (*it == *it1)
			{
				exist = true;
				break;
			}
		}
		if (!exist && chessBoard[(*it).first][(*it).second] == 0)
		{
			waitSele.push_back((*it));
		}
	}
}

