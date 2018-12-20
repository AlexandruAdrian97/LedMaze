/*
 Name:    LedMaze.ino
 Created: 18/12/2018
 Author:  Alexandru Adrian
*/


#include "LedControl.h" 
#include <LiquidCrystal.h>

LedControl lc = LedControl(8, 10, 9); // DIN, CLK, LOAD

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int ii = 8, jj = 8;


#define JOY_X A0
#define JOY_Y A1
#define button 13 
#define V0 6 

int xValue = 0;
int yValue = 0;

int presentX, presentY, previousX, previousY;

int i;
int j;

int level = 0;
int lives = 5;
int highScore = 1;
int scoreLives = 20;

bool mazeOne[ii][jj] = {
  {0,0,1,1,1,1,1,1},
  {0,0,0,0,0,1,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,1,0,0,0,1,1},
  {1,1,1,1,0,0,0,1},
  {1,1,1,1,0,0,0,1},
  {1,1,1,1,1,1,0,0},
  {1,1,1,1,1,1,0,0},
};

bool mazeTwo[ii][jj] = {
  {0,0,1,1,1,1,1,1},
  {1,0,0,0,0,0,1,1},
  {1,1,1,1,1,0,1,1},
  {1,1,0,0,0,0,1,1},
  {1,1,0,1,1,1,1,1},
  {1,1,0,0,0,0,0,1},
  {1,1,1,1,1,1,0,1},
  {1,1,1,1,1,1,0,0},
};


bool mazeThree[ii][jj] = {
  {0,0,0,0,1,0,0,0},
  {0,0,1,0,1,0,1,0},
  {1,1,1,0,0,0,1,0},
  {1,1,1,1,1,1,1,0},
  {0,0,0,0,1,0,0,0},
  {0,1,1,0,0,0,1,1},
  {0,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0},
};


bool mazeFour[ii][jj] = {
  {0,0,1,1,1,1,1,1},
  {0,0,1,1,1,0,0,0},
  {1,0,1,1,1,0,1,0},
  {1,0,1,0,0,0,1,0},
  {1,0,1,0,1,1,1,0},
  {1,0,1,0,1,0,0,0},
  {1,0,1,0,1,0,1,1},
  {1,0,0,0,1,0,0,0},
};

bool mazeFive[ii][jj] = {
  {0,1,1,0,0,0,0,1},
  {0,0,1,0,1,1,0,1},
  {1,0,0,0,1,1,0,1},
  {1,1,1,1,1,1,0,1},
  {0,0,0,0,0,1,0,1},
  {0,1,1,1,0,0,0,1},
  {0,1,1,0,1,1,1,1},
  {0,0,0,0,0,0,0,0},
};

bool mazeSix[ii][jj] = {
  {0,1,1,1,1,1,1,1},
  {0,1,0,0,0,0,0,0},
  {0,0,0,1,1,1,1,0},
  {1,1,1,1,0,0,0,0},
  {1,0,0,0,0,1,1,1},
  {1,0,1,1,1,1,1,1},
  {1,0,0,1,0,0,0,1},
  {1,1,0,0,0,1,0,0},
};

bool mazeSeven[ii][jj] = {
  {0,0,1,1,1,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,1,0,0,0,1,0,1},
  {1,1,1,1,1,0,0,1},
  {1,0,0,0,1,0,1,1},
  {0,0,1,0,0,0,1,1},
  {0,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0},
};

bool mazeEight[ii][jj] = {
  {0,1,1,0,0,0,0,0},
  {0,1,1,0,1,1,1,0},
  {0,0,0,0,1,0,0,0},
  {1,1,1,1,1,0,1,1},
  {0,0,0,1,0,0,1,1},
  {0,1,0,0,0,1,1,1},
  {0,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0},
};

bool mazeNine[ii][jj] = {
  {0,0,1,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,0,1,0,1,0},
  {1,1,1,1,1,0,1,0},
  {0,0,0,0,0,0,1,0},
  {0,1,1,1,1,1,1,0},
  {0,1,0,0,0,1,0,0},
  {0,0,0,1,0,0,0,0},
};

bool gameOverM[ii][jj] = {
  {1,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,1,0},
  {0,0,1,0,0,1,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,1,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1},
};

bool finishM[ii][jj] = {
  {0,0,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {1,1,1,1,1,0,0,0},
  {1,1,1,1,1,0,0,0},
  {1,1,1,1,1,0,0,1},
  {0,0,0,0,0,0,1,0},
  {0,0,0,1,0,1,0,0},
  {0,0,0,0,1,0,0,0},
};

bool transitionLevelOne[ii][jj] = {
  {1,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,1,0,0},
};

bool transitionLevelTwo[ii][jj] = {
  {1,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,1,0,1,0},
  {0,0,0,0,1,0,1,0},
  {0,0,0,0,1,0,1,0},
};

bool transitionLevelThree[ii][jj] = {
  {1,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,1,0,1,0,1},
  {0,0,0,1,0,1,0,1},
  {0,0,0,1,0,1,0,1},
};

bool transitionLevelFour[ii][jj] = {
  {1,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,1,0,1,0,0,0,1},
  {0,1,0,0,1,0,1,0},
  {0,1,0,0,0,1,0,0},
};

bool transitionLevelFive[ii][jj] = {
  {1,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,1,0,0,0,1},
  {0,0,0,0,1,0,1,0},
  {0,0,0,0,0,1,0,0},
};

bool transitionLevelSix[ii][jj] = {
  {1,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,1,0,1,0,1,0,0},
  {0,1,0,1,0,1,0,0},
  {0,0,1,0,0,1,0,0},
};

bool transitionLevelSeven[ii][jj] = {
  {1,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,1,0,1,0,1,1,0},
  {0,1,0,1,0,1,1,0},
  {0,0,1,0,0,1,1,0},
};

bool transitionLevelEight[ii][jj] = {
  {1,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {1,0,1,0,1,1,1,0},
  {1,0,1,0,1,1,1,0},
  {0,1,0,0,1,1,1,0},
};

bool standByM[ii][jj] = {
  {0,1,0,1,1,0,1,0},
  {1,0,1,0,0,1,0,1},
  {0,1,0,1,1,0,1,0},
  {1,0,1,0,0,1,0,1},
  {1,0,1,0,0,1,0,1},
  {0,1,0,1,1,0,1,0},
  {1,0,1,0,0,1,0,1},
  {0,1,0,1,1,0,1,0},
};



void displayLives(int dsplay)
{
	lcd.begin(16, 2);
	lcd.print("Number of lives: ");
	lcd.setCursor(6, 1);
	lcd.print(dsplay);
}

void score(int t, int v)
{
	lcd.begin(16, 2);
	lcd.setCursor(0, 0);
	lcd.print("Score: ");
	lcd.setCursor(7, 0);
	lcd.print(t * 6);
	lcd.print(" pts");
	lcd.setCursor(0, 1);
	lcd.print("H. Scr: ");
	lcd.setCursor(7, 1);
	lcd.print(v * 6);
	lcd.print(" pts");
}

void movement()
{
	xValue = analogRead(JOY_X);
	yValue = analogRead(JOY_Y);

	previousX = presentX;
	previousY = presentY;

	if (xValue > 600)
	{
		if (presentX != 7)
			presentX++;
	}
	else
		if (xValue < 300)
		{
			if (presentX != 0)
				presentX--;
		}
	if (yValue > 600)
	{
		if (presentY != 7)
			presentY++;
	}
	else
		if (yValue < 300)
		{
			if (presentY != 0)
				presentY--;
		}
	delay(30);
}

int levelOne()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, mazeOne[i][j]);
}

void levelTwo()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, mazeTwo[i][j]);
}

void levelThree()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, mazeThree[i][j]);
}

void levelFour()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, mazeFour[i][j]);
}

void levelFive()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, mazeFive[i][j]);
}

void levelSix()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, mazeSix[i][j]);
}

void levelSeven()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, mazeSeven[i][j]);
}

void levelEight()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, mazeEight[i][j]);
}

void standBy()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, standByM[i][j]);
}

void transitionOne()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, transitionLevelOne[i][j]);
}

void transitionTwo()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, transitionLevelTwo[i][j]);
}

void transitionThree()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, transitionLevelThree[i][j]);
}

void transitionFour()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, transitionLevelFour[i][j]);
}

void transitionFive()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, transitionLevelFive[i][j]);
}

void transitionSix()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, transitionLevelSix[i][j]);
}

void transitionSeven()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, transitionLevelSeven[i][j]);
}
void transitionEight()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, transitionLevelEight[i][j]);
}

void gameOver()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, gameOverM[i][j]);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("  GAME OVER!:(");
}

void finish()
{
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			lc.setLed(0, i, j, finishM[i][j]);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("  You won !!!");
}

void levelSwitch()
{
	switch (level) {

	case 0:

		lc.clearDisplay(0);
		standBy();

		if (digitalRead(button) == 1)
		{
			lcd.setCursor(0, 0);
			lcd.print(" ***Led Maze*** ");
			lcd.setCursor(0, 1);
			lcd.print(" Press to start! ");
		}
		else
			level++;
		break;

	case 1:
		lc.clearDisplay(0);
		transitionOne();
		delay(500); // for the transition between the levels;
		level++;
		break;

	case 2:
		displayLives(lives);
		levelOne();

		if (mazeOne[presentY][presentX] == true)
		{
			lives = lives - 1;
			scoreLives = scoreLives - 2;
			presentY = 0;
			presentX = 0;
		}

		lc.setLed(0, previousY, previousX, 0);
		delay(45);
		lc.setLed(0, presentY, presentX, 1);

		if (lives == 0)
		{
			level = 18;
			scoreLives = scoreLives * 2;
			break;
		}

		if (presentY == 7 && presentX == 7)
		{
			level++;
			scoreLives = scoreLives * 3;
			presentX = 0;
			presentY = 0;
		}
		break;

	case 3:
		transitionTwo();
		delay(500);
		level++;
		break;

	case 4:
		displayLives(lives);
		levelTwo();

		if (mazeTwo[presentY][presentX] == true)
		{
			lives = lives - 1;
			scoreLives = scoreLives - 2;
			presentY = 0;
			presentX = 0;
		}

		lc.setLed(0, previousY, previousX, 0);
		delay(45);
		lc.setLed(0, presentY, presentX, 1);

		if (lives == 0)
		{
			level = 18;
			scoreLives = scoreLives * 4;
			break;
		}

		if (presentY == 7 && presentX == 7)
		{
			level++;
			scoreLives = scoreLives * 5;
			presentX = 0;
			presentY = 0;
		}
		break;

	case 5:
		transitionThree();
		delay(500);
		level++;
		break;

	case 6:
		displayLives(lives);
		levelThree();

		if (mazeThree[presentY][presentX] == true)
		{
			lives = lives - 1;
			scoreLives = scoreLives - 2;
			presentY = 0;
			presentX = 0;
		}

		lc.setLed(0, previousY, previousX, 0);
		delay(45);
		lc.setLed(0, presentY, presentX, 1);

		if (lives == 0)
		{
			level = 18;
			scoreLives = scoreLives * 6;
			break;
		}

		if (presentY == 7 && presentX == 7)
		{
			level++;
			scoreLives = scoreLives * 7;
			presentX = 0;
			presentY = 0;
		}
		break;

	case 7:
		transitionFour();
		delay(500);
		level++;
		break;

	case 8:
		displayLives(lives);
		levelFour();

		if (mazeFour[presentY][presentX] == true)
		{
			lives = lives - 1;
			scoreLives = scoreLives - 2;
			presentY = 0;
			presentX = 0;
		}

		lc.setLed(0, previousY, previousX, 0);
		delay(45);
		lc.setLed(0, presentY, presentX, 1);

		if (lives == 0)
		{
			level = 18;
			scoreLives = scoreLives * 8;
			break;
		}

		if (presentY == 7 && presentX == 7)
		{
			level++;
			scoreLives = scoreLives * 9;
			presentX = 0;
			presentY = 0;
		}
		break;

	case 9:
		transitionFive();
		delay(500);
		level++;
		break;

	case 10:
		displayLives(lives);
		levelFive();

		if (mazeFive[presentY][presentX] == true)
		{
			lives = lives - 1;
			scoreLives = scoreLives - 2;
			presentY = 0;
			presentX = 0;
		}

		lc.setLed(0, previousY, previousX, 0);
		delay(45);
		lc.setLed(0, presentY, presentX, 1);

		if (lives == 0)
		{
			level = 18;
			scoreLives = scoreLives * 10;
			break;
		}

		if (presentY == 7 && presentX == 7)
		{
			level++;
			scoreLives = scoreLives * 11;
			presentX = 0;
			presentY = 0;
		}
		break;

	case 11:
		lc.clearDisplay(0);
		transitionSix();
		delay(500); // for the transition between the levels;
		level++;
		break;

	case 12:
		displayLives(lives);
		levelSix();

		if (mazeSix[presentY][presentX] == true)
		{
			lives = lives - 1;
			scoreLives = scoreLives - 2;
			presentY = 0;
			presentX = 0;
		}

		lc.setLed(0, previousY, previousX, 0);
		delay(45);
		lc.setLed(0, presentY, presentX, 1);

		if (lives == 0)
		{
			level = 18;
			scoreLives = scoreLives * 12;
			break;
		}

		if (presentY == 7 && presentX == 7)

		{
			level++;
			scoreLives = scoreLives * 13;
			presentX = 0;
			presentY = 0;
		}
		break;

	case 13:
		transitionSeven();
		delay(500);
		level++;
		break;

	case 14:
		displayLives(lives);
		levelSeven();

		if (mazeSeven[presentY][presentX] == true)
		{
			lives = lives - 1;
			scoreLives = scoreLives - 2;
			presentY = 0;
			presentX = 0;
		}

		lc.setLed(0, previousY, previousX, 0);
		delay(45);
		lc.setLed(0, presentY, presentX, 1);

		if (lives == 0)
		{
			level = 18;
			scoreLives = scoreLives * 14;
			break;
		}

		if (presentY == 7 && presentX == 7)
		{
			level++;
			scoreLives = scoreLives * 15;
			presentX = 0;
			presentY = 0;
		}
		break;

	case 15:
		transitionEight();
		delay(500);
		level++;
		break;

	case 16:
		displayLives(lives);
		levelEight();

		if (mazeEight[presentY][presentX] == true)
		{
			lives = lives - 1;
			scoreLives = scoreLives - 2;
			presentY = 0;
			presentX = 0;
		}

		lc.setLed(0, previousY, previousX, 0);
		delay(45);
		lc.setLed(0, presentY, presentX, 1);

		if (lives == 0)
		{
			level = 18;
			scoreLives = scoreLives * 16;
			break;
		}

		if (presentY == 7 && presentX == 7)
		{
			level++;
			scoreLives = scoreLives * 17;
			presentX = 0;
			presentY = 0;
		}
		break;

	case 17:
		lc.clearDisplay(0);
		finish();
		if (scoreLives > highScore)
		{
			highScore = scoreLives;
		}
		delay(2000);
		score(scoreLives, highScore);
		delay(2000);
		level = 0;
		lives = 5;
		presentX = 0;
		presentY = 0;
		scoreLives = 20;
		break;

	case 18:
		lc.clearDisplay(0);
		gameOver();
		if (scoreLives > highScore)
		{
			highScore = scoreLives;
		}
		delay(2000);
		score(scoreLives, highScore);
		delay(2000);
		level = 0;
		lives = 5;
		presentX = 0;
		presentY = 0;
		scoreLives = 20;
		break;
	}
}

void setup()
{
	lcd.begin(16, 2);
	lc.shutdown(0, false); // Turn off power saving, enables display
	lc.setIntensity(0, 1); // 0~15 possible values
	lc.clearDisplay(0);

	pinMode(button, INPUT_PULLUP);
	pinMode(V0, OUTPUT); //PWM instead of POTENTIOMETRE
	analogWrite(V0, 100);
}

void loop()
{
	movement();
	levelSwitch();
}