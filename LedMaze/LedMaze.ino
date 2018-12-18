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
long score = 0;


int mazeOne[8][8] = {
  {0,0,1,1,1,1,1,1},
  {0,0,0,0,0,1,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,1,0,0,0,1,1},
  {1,1,1,1,0,0,0,1},
  {1,1,1,1,0,0,0,1},
  {1,1,1,1,1,1,0,0},
  {1,1,1,1,1,1,0,0},
};

int mazeTwo[8][8] = {
  {0,0,1,1,1,1,1,1},
  {1,0,0,0,0,0,1,1},
  {1,1,1,1,1,0,1,1},
  {1,1,0,0,0,0,1,1},
  {1,1,0,1,1,1,1,1},
  {1,1,0,0,0,0,0,1},
  {1,1,1,1,1,1,0,1},
  {1,1,1,1,1,1,0,0},
};

int mazeThree[8][8] = {
  {0,0,0,0,1,0,0,0},
  {0,0,1,0,1,0,1,0},
  {1,1,1,0,0,0,1,0},
  {1,1,1,1,1,1,1,0},
  {0,0,0,0,1,0,0,0},
  {0,1,1,0,0,0,1,1},
  {0,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0},
};

int gameOverM[8][8] = {
  {1,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,1,0},
  {0,0,1,0,0,1,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,1,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1},
};

int finishM[8][8] = {
  {0,0,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {1,1,1,1,1,0,0,0},
  {1,1,1,1,1,0,0,0},
  {1,1,1,1,1,0,0,1},
  {0,0,0,0,0,0,1,0},
  {0,0,0,1,0,1,0,0},
  {0,0,0,0,1,0,0,0},
};

int transitionLevelOne[8][8] = {
  {1,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,1,0,0},
};

int transitionLevelTwo[8][8] = {
  {1,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,1,0,1,0},
  {0,0,0,0,1,0,1,0},
  {0,0,0,0,1,0,1,0},
};

int transitionLevelThree[8][8] = {
  {1,0,0,0,0,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1,0},
  {1,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,1,0,1,0,1},
  {0,0,0,1,0,1,0,1},
  {0,0,0,1,0,1,0,1},
};

int standByM[8][8] = {
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

void scoreTime(long t)
{
	lcd.begin(16, 2);
	lcd.setCursor(4, 0);
	lcd.print("Scoretime: ");
	lcd.setCursor(5, 1);
	lcd.print(t / 1000);
	lcd.print(" sec")
}

void movement()
{
	xValue = analogRead(JOY_X);
	yValue = analogRead(JOY_Y);

	previousX = presentX;
	previousY = presentY;

	if (xValue > 600)
	{
		if (presentX == 7)
		{
			presentX = 7;
		}
		else
		{
			presentX++;
		}
	}
	else
		if (xValue < 400)
		{
			if (presentX == 0)
			{
				presentX = 0;
			}
			else presentX--;
		}
	if (yValue > 600)
	{
		if (presentY == 7)
		{
			presentY = 7;
		}
		else
		{
			presentY++;
		}
	}
	else
		if (yValue < 400)
		{
			if (presentY == 0)
			{
				presentY = 0;
			}
			else presentY--;
		}
	delay(100);
}

void levelOne()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			lc.setLed(0, i, j, mazeOne[i][j]);
}

void levelTwo()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			lc.setLed(0, i, j, mazeTwo[i][j]);
}

void levelThree()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			lc.setLed(0, i, j, mazeThree[i][j]);
}

void standBy()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			lc.setLed(0, i, j, standByM[i][j]);
}

void transitionOne()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			lc.setLed(0, i, j, transitionLevelOne[i][j]);
}

void transitionTwo()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			lc.setLed(0, i, j, transitionLevelTwo[i][j]);
}

void transitionThree()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			lc.setLed(0, i, j, transitionLevelThree[i][j]);
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
		transitionOne();
		delay(2000);
		level++;
		score = 0;
		score = millis();
		break;

	case 2:
		displayLives(lives);
		levelOne();

		if (mazeOne[presentY][presentX] == true)
		{
			lives = lives - 1;
			presentY = 0;
			presentX = 0;
		}

		lc.setLed(0, previousY, previousX, 0);
		lc.setLed(0, presentY, presentX, 1);

		if (lives == 0)
		{
			level = 8;
			break;
		}

		lc.setLed(0, previousY, previousX, 0);
		lc.setLed(0, presentY, presentX, 1);

		if (presentY == 7 && presentX == 7)
			level++;
		break;

	case 3:
		transitionTwo();
		delay(2000);
		level++;
		break;

	case 4:
		displayLives(lives);
		levelTwo();

		if (mazeTwo[presentY][presentX] == true)
		{
			lives = lives - 1;
			presentY = 7;
			presentX = 7;
		}

		lc.setLed(0, previousY, previousX, 0);
		lc.setLed(0, presentY, presentX, 1);

		if (lives == 0)
		{
			level = 8;
			break;
		}

		lc.setLed(0, previousY, previousX, 0);
		lc.setLed(0, presentY, presentX, 1);

		if (presentY == 0 && presentX == 0)
			level++;
		break;

	case 5:
		transitionThree();
		delay(2000);
		level++;
		break;

	case 6:
		displayLives(lives);
		levelThree();

		if (mazeThree[presentY][presentX] == true)
		{
			lives = lives - 1;
			presentY = 0;
			presentX = 0;
		}

		lc.setLed(0, previousY, previousX, 0);
		lc.setLed(0, presentY, presentX, 1);

		if (lives == 0)
		{
			level = 8;
			break;
		}

		lc.setLed(0, previousY, previousX, 0);
		lc.setLed(0, presentY, presentX, 1);

		if (presentY == 7 && presentX == 7)
			level++;
		break;

	case 7:
		lc.clearDisplay(0);
		finish();
		delay(1500);
		scoreTime(score);
		delay(1500);
		level = 0;
		lives = 5;
		presentX = 0;
		presentY = 0;
		break;

	case 8:
		lc.clearDisplay(0);
		gameOver();
		delay(1500);
		scoreTime(score);
		delay(1500);
		level = 0;
		lives = 5;
		presentX = 0;
		presentY = 0;
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
	pinMode(V0, OUTPUT); // PWM instead of POTENTIOMETRE
	analogWrite(V0, 100);
}

void loop()
{
	movement();
	levelSwitch();
}
