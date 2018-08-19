#include <windows.h>
#include <conio.h>
#include "tenis.h"

int ballX, ballY, bincX, bincY;

void clearRacket( int x, int y );
void putRacket( int x, int y );
int newCoords( int ballX, int ballY, int incX, int incY, int leftY, int rightY );

void GotoXY(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HideCursor() {
  HANDLE hOut;
  CONSOLE_CURSOR_INFO ConCurInf;

  hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  ConCurInf.dwSize = 10;
  ConCurInf.bVisible = FALSE;

  SetConsoleCursorInfo(hOut, &ConCurInf);
}

void putChar( int x, int y, char ch ) {
  GotoXY(x, y);
  _putch(ch);
}

int moveRacket( int x, int y, int up, int down ) {
  if ( up && y > FIRST_ROW ) {
    clearRacket( x, y );
    y--;
    putRacket ( x, y );
  }
  if ( down && y <= (LAST_ROW - RACKET_LEN) ) {
    clearRacket( x, y );
    y++;
    putRacket ( x, y );
  }
  return y;
}

int moveBall( int leftY, int rightY ) {
  int retVal = NONE_POINT, oldX = ballX, oldY = ballY, code;

  code = newCoords( ballX, ballY, bincX, bincY, leftY, rightY );
  ballY = code & 0xFF;
  code >>= 8;
  ballX = code &0xFF;
  code >>= 8;
  bincY = (code & 3) - 1;
  code >>= 2;
  bincX = (code & 3) - 1;

  if ( ballX == FIRST_COL ) { // daca e pe prima coloana
      ballX = LAST_COL / 2;
      ballY = LAST_ROW / 2;
      bincX = -bincX;
      retVal = RIGHT_POINT;
  } else if ( ballX == LAST_COL ) { // daca e pe ultima coloana
    // testam daca avem paleta sa ne schimbe sensul
      ballX = LAST_COL / 2;
      ballY = LAST_ROW / 2;
      bincX = -bincX;
      retVal = LEFT_POINT;
  }

  GotoXY( oldX, oldY );
    _putch(' ');
  GotoXY( ballX, ballY );
    _putch('O');

  return retVal;
}

void clearBall() {
  GotoXY( ballX, ballY );
    _putch(' ');
}

void printScore( int x, int score ) {
  GotoXY(x, SCORE_Y);
  _putch(score + '0');
}

void printWinner(int scoreLeft, int scoreRight) {
  char *msg = scoreLeft < scoreRight ? RIGHT_MSG : scoreLeft == scoreRight ? NOBODY_MSG : LEFT_MSG;
  GotoXY(WIN_MSG_X, WIN_MSG_Y);
  _cprintf(WIN_MSG, msg );
}

int main()
{
  int quit, point, scoreLeft, scoreRight,
    leftUp, leftDown, leftY,
    rightUp, rightDown, rightY;
  char buff[1000];

  HideCursor();
  scoreLeft = scoreRight = quit = 0;
  printScore( LEFT_SCORE_X, scoreLeft);
  printScore( RIGHT_SCORE_X, scoreLeft);
  leftY = rightY = (LAST_ROW - RACKET_LEN) / 2;
  ballX = LAST_COL / 2;
  ballY = LAST_ROW / 2;
  bincX = bincY = 1;
  putRacket( FIRST_COL, leftY );
  putRacket( LAST_COL, rightY );
  _getch();
  while ( quit == 0 ) {
    Sleep(50);
    quit = 0;
    leftUp = GetAsyncKeyState('Q') & 0x8000;
    leftDown = GetAsyncKeyState('A') & 0x8000;
    rightUp = GetAsyncKeyState('O') & 0x8000;
    rightDown = GetAsyncKeyState('L') & 0x8000;
    quit = GetAsyncKeyState(VK_ESCAPE) & 0x8000;
    leftY = moveRacket(FIRST_COL, leftY, leftUp, leftDown);
    rightY = moveRacket(LAST_COL, rightY, rightUp, rightDown);
    point = moveBall(leftY, rightY);
    if ( point != NONE_POINT ) {
      if ( point == LEFT_POINT ) {
        scoreLeft++;
        printScore( LEFT_SCORE_X, scoreLeft);
        if ( scoreLeft >= MAX_SCORE )
          quit = 1;
      } else {
        scoreRight++;
        printScore( RIGHT_SCORE_X, scoreRight);
        if ( scoreRight >= MAX_SCORE )
          quit = 1;
      }
    }
  }

  printWinner(scoreLeft, scoreRight);
  clearBall();
  _cgets(buff);

  return 0;
}
