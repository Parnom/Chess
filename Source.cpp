#pragma once
#define _CRT_SECURE_NO_DEPRECATE
 //  #define _CRT_SECURE_NO_WARNINGS
//    #define _CRT_SECURE_NO_WARNINGS_GLOBALS


   #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")     // Blendet Console aus !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <iostream>
 // #include <string>
 // #include <fstream>
#include <sstream>
#include <thread>
#include <SFML/Graphics.hpp>


using namespace std;

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

int ScreenWidth = 1200;   // 1920
int ScreenHigh = 800;    // 1200

const float drawLineXPos = 230;
const float drawLineYPos = 97;
const float abstandX = 77.0;
const float abstandY = 76.5;
const float buttonPosX = 1050;
const float buttonPosY = 200;
const float incButtonPosX = 920;
const float incButtonPosY = 450;
const float buttonAbstand = 35;

sf::Color colorWhite(225, 225, 155);   // 255, 255, 155
sf::Color colorBlack(80, 0, 255);       // 0,0,255


bool drawCauseMoveRepeat = false;
bool drawBecause50Moves = false;
bool unsuficientMatereals = false;
bool draw = false;
bool whiteMates = false;
bool blackMates = false;

int thinkingTime = 0;

#include "ChessEngine.h"
#include "DrawBoard.h"

bool testcheck = 0;

int main()
{
	sf::Font font;
	sf::Thread startToFuck(&goFuckEngine);
	Controllbutton button;
	Incrementbutton incButton;
	
		
	if (!font.loadFromFile("comici.ttf"))
	{
		cout << "Kann Font nicht laden" << endl;
		return(0);
	}

	sf::Text text;
	text.setFont(font);

	sf::Text text2;
	text2.setFont(font);
	//     text2.setColor(sf::Color(120, 120, 120, 255));
	text2.setFillColor(sf::Color(120, 120, 120, 255));

	sf::Texture texture;
	sf::Sprite sprite;

	if (!texture.loadFromFile("Brett3.jpg")) {
		return(0);
	}
	sprite.setTexture(texture);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHigh, 32), "PARNOCHESS", sf::Style::Titlebar, settings);
	window.setFramerateLimit(60);
	
	
	startResetEngine();
	//   _readbook("olibook.pgn");
	saveValues();
	loadMstack("gamesavestack.txt");
	loadStellung("gamesavestell.txt");

	while (window.isOpen())
	{	
		window.clear();
		sf::Event event;
		ostringstream stringStr1;
		ostringstream stringStr2;
		ostringstream stringStr3;
		ostringstream stringStr4;
		ostringstream stringStr5;
		ostringstream stringStr6;

		static bool mouseLeftFlag1From = false;
		static bool mouseLeftFlag2From = false;		
		static bool mouseLeftFlagTo = false;
		static int fromFieldX = 0;
		static int fromFieldY = 0;
		static int toFieldX = 0;
		static int toFieldY = 0;
		
		stringStr1 << "Parnom´s Chess" << endl;
		text.setString(stringStr1.str());
		text.setPosition(370, 0);
		text.setFillColor(sf::Color(120, 120, 0, 255));				
		text.setCharacterSize(44);
		window.draw(text);		
		if ((engine == onmove) && (nodes + qnodes ) != 0) thinkingTime = (int)(getTime() - starttime);				
		stringStr2  << endl << "Halbzug: " << COUNT << endl;
		if (onmove == 0) stringStr2 << "Weiss am Zug " << endl;
		else stringStr2 << "Schwarz am Zug " << endl;

		text.setString(stringStr2.str());
		text.setPosition(ScreenWidth - 230, 50);
		text.setCharacterSize(26);
		if (onmove == 0)	text.setFillColor(sf::Color(225, 225, 155, 255));
		else text.setFillColor(sf::Color(80, 80, 255, 255));
		window.draw(text);

		stringStr6 << "Nodes:   " << (u32)(nodes + qnodes) << endl << "Q-Nodes: " << (u32)qnodes << endl << "Suchzeit in ms.: " << thinkingTime << endl <<
			"kNodes / Sec.:  " <<(u32)(nodes + qnodes) / (thinkingTime + 1) << endl << "Suchtiefe:  " << iter << endl << "Wert:  " << value[iter] << endl ;
		text.setString(stringStr6.str());
		text.setPosition(ScreenWidth - 250, 560);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color(255, 255, 255, 255));
		window.draw(text);
		text.setFillColor(sf::Color(225, 225, 0, 255));
		                                                                  //         ZUGLISTE 
		ostringstream zugString;
		for (int i = 0; i < countCopy; i++) {
			char t1 = 'a' + FROM(mstackCopy[i] >> 42L) % 8;
			char t2 = '1' + FROM(mstackCopy[i] >> 42L) / 8;
			char t3 = 'a' + TO(mstackCopy[i] >> 42L) % 8;
			char t4 = '1' + TO(mstackCopy[i] >> 42L) / 8;
			if (!(i % 2)) {
				zugString << "Zug: " << (i / 2) + 1 << " " << t1 << t2 << t3 << t4 << "  ";
			}
			else {
				zugString << t1 << t2 << t3 << t4 << endl;
			}
		}
		text.setString(zugString.str());

		text.setPosition(10, 0);            // POS    	
		text.setCharacterSize(10);
		text.setFillColor(sf::Color(225, 225, 255 ));
		window.draw(text);
		

	                                                                     	    // BUTTON CREATES
		button.createButton(window, text, "   GO    ", buttonPosX, buttonPosY + buttonAbstand * 0);
		button.createButton(window, text, "  TURN   ", buttonPosX, buttonPosY + buttonAbstand * 1);
		button.createButton(window, text, "  SAVE   ", buttonPosX, buttonPosY + buttonAbstand * 2);
		button.createButton(window, text, "  LOAD   ", buttonPosX, buttonPosY + buttonAbstand * 3);		
		button.createButton(window, text, "  EASY   ", buttonPosX, buttonPosY + buttonAbstand * 4);
		button.createButton(window, text, "  HARD   ", buttonPosX, buttonPosY + buttonAbstand * 5);
		button.createButton(window, text, "   NEW   ", buttonPosX, buttonPosY + buttonAbstand * 6);
		button.createButton(window, text, "  UNDO   ", buttonPosX, buttonPosY + buttonAbstand * 7);
		button.createButton(window, text, "  EXIT   ", buttonPosX, buttonPosY + buttonAbstand * 8);

		stringStr3 << "Rechenzeit in Sek." << endl << "0 = Automatik" << endl;
		text.setString(stringStr3.str());	
		text.setPosition(incButtonPosX, incButtonPosY - 50);
		text.setCharacterSize(12);
		text.setFillColor(sf::Color(225, 225, 100));
		window.draw(text);

		incButton.createIncButton(window, text, incButtonPosX, incButtonPosY , st);
		stringStr4 << "Max.Suchtiefe" << endl;
		text.setString(stringStr4.str());
	//	text.setPosition(920, 530);
		text.setPosition(incButtonPosX, incButtonPosY +20);
		text.setCharacterSize(12);
		window.draw(text);

		incButton.createIncButton(window, text, incButtonPosX, incButtonPosY + 50, sd);		

		                                                                      // Schachbrett
		if (turnB) {
			sprite.setRotation(0);
			sprite.setPosition(sf::Vector2f(182, 50));
			sprite.setScale(sf::Vector2f(0.7f, 0.7f));
			window.draw(sprite);
		}
		else {
			sprite.setRotation(180);
			sprite.setPosition(sf::Vector2f(895, 758));
			sprite.setScale(sf::Vector2f(0.7f, 0.7f));
			window.draw(sprite);
		}
		                                    //   Maus  ZUG

		int MouseX = sf::Mouse::getPosition(window).x;
		int MouseY = sf::Mouse::getPosition(window).y;

		if ((MouseX > drawLineXPos && MouseX < (drawLineXPos + (8 * abstandX))) && (MouseY > drawLineYPos && MouseY < (drawLineYPos + (8 * abstandY)))) {
			testcheck = true;
			int testX = (MouseX - drawLineXPos) / abstandX;
			int testY = (MouseY - drawLineYPos) / abstandY;
			// hier im spielfeld mit MAUS

			sf::RectangleShape shapex1(sf::Vector2f(abstandX + 2.f, 2.f));
			shapex1.setPosition(drawLineXPos + (testX * abstandX), drawLineYPos + (testY * abstandY));
			shapex1.setFillColor(sf::Color(255, 255, 55));
			window.draw(shapex1);
			sf::RectangleShape shapey1(sf::Vector2f(2.f, abstandY + 2.f));
			shapey1.setPosition(drawLineXPos + (testX * abstandX) + abstandX, drawLineYPos + (testY * abstandY));
			shapey1.setFillColor(sf::Color(255, 255, 55));
			window.draw(shapey1);
			sf::RectangleShape shapex2(sf::Vector2f(abstandX + 2.f, 2.f));
			shapex2.setPosition(drawLineXPos + (testX * abstandX), drawLineYPos + (testY * abstandY) + abstandY);
			shapex2.setFillColor(sf::Color(255, 255, 55));
			window.draw(shapex2);
			sf::RectangleShape shapey2(sf::Vector2f(2.f, abstandY + 2.f));
			shapey2.setPosition(drawLineXPos + (testX * abstandX), drawLineYPos + (testY * abstandY));
			shapey2.setFillColor(sf::Color(255, 255, 55));
			window.draw(shapey2);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseLeftFlag1From == 0) {
				fromFieldX = testX;
				fromFieldY = testY;				
				mouseLeftFlag1From = true;
			}


			if (mouseLeftFlag1From == true) {
				sf::RectangleShape shapex1(sf::Vector2f(abstandX + 2.f, 2.f));
				shapex1.setPosition(drawLineXPos + (fromFieldX * abstandX), drawLineYPos + (fromFieldY * abstandY));
				shapex1.setFillColor(sf::Color(0, 255, 0));
				window.draw(shapex1);
				sf::RectangleShape shapey1(sf::Vector2f(2.f, abstandY + 2.f));
				shapey1.setPosition(drawLineXPos + (fromFieldX * abstandX) + abstandX, drawLineYPos + (fromFieldY * abstandY));
				shapey1.setFillColor(sf::Color(0, 255, 0));
				window.draw(shapey1);
				sf::RectangleShape shapex2(sf::Vector2f(abstandX + 2.f, 2.f));
				shapex2.setPosition(drawLineXPos + (fromFieldX * abstandX), drawLineYPos + (fromFieldY * abstandY) + abstandY);
				shapex2.setFillColor(sf::Color(0, 255, 0));
				window.draw(shapex2);
				sf::RectangleShape shapey2(sf::Vector2f(2.f, abstandY + 2.f));
				shapey2.setPosition(drawLineXPos + (fromFieldX * abstandX), drawLineYPos + (fromFieldY * abstandY));
				shapey2.setFillColor(sf::Color(0, 255, 0));
				window.draw(shapey2);
			}
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) mouseLeftFlag2From = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseLeftFlag1From == true && (testX != fromFieldX || testY != fromFieldY) && mouseLeftFlag2From == true) {

				toFieldX = testX;
				toFieldY = testY;
				mouseLeftFlagTo = true;
			}
			if (mouseLeftFlagTo == true) {
				if (turnB) {
					irbuf[0] = ('a') + fromFieldX;
					irbuf[1] = ('8') - fromFieldY;
					irbuf[2] = ('a') + toFieldX;
					irbuf[3] = ('8') - toFieldY;
				}
				else {
					irbuf[0] = ('h') - fromFieldX; 
					irbuf[1] = ('1') + fromFieldY;
					irbuf[2] = ('h') - toFieldX;
					irbuf[3] = ('1') + toFieldY;
				}
				fromFieldX = 0;
				fromFieldY = 0;
				toFieldX = 0;
				toFieldY = 0;
			
				//	engine = pondering ? onmove ^ 1 : onmove;

//	goFuckEngine();
	///////////////////////////////////////
                            startToFuck.launch();   //        START THREAD !!!!!!!!!!!!!!!!!!
////////////////////////////////////////
                            startToFuck.launch();
//		startF.join();

mouseLeftFlagTo = false;
mouseLeftFlag1From = false;
mouseLeftFlag2From = false;

			}

			//   Hier weiter !!! :_))))))))))))

		}
		else {
			testcheck = false;
			mouseLeftFlag1From = false;
			mouseLeftFlagTo = false;

		}

		//      BUTTON  ABFRAGE

		static bool but4Flag = false;
		if (button.isMouseOnButtonClicked(window, text, "   GO", buttonPosX, buttonPosY + (buttonAbstand * 0)) && but4Flag == false) {
			if (!unsuficientMatereals && !whiteMates && !blackMates && !draw && !drawCauseMoveRepeat && !drawBecause50Moves) {
				engine = pondering ? onmove ^ 1 : onmove;
				startToFuck.launch();

			}
			but4Flag = true;
		}
		if (!button.isMouseOnButtonClicked(window, text, "   GO", buttonPosX, buttonPosY + (buttonAbstand * 0)))but4Flag = false;
		static bool but1Flag = false;
		if (button.isMouseOnButtonClicked(window, text, "  TURN", buttonPosX, buttonPosY + (buttonAbstand * 1)) && but1Flag == false) {
			turnB ^= 1;
			but1Flag = true;
		}
		if (!button.isMouseOnButtonClicked(window, text, "  TURN", buttonPosX, buttonPosY + (buttonAbstand * 1)))but1Flag = false;

		static bool but2Flag = false;
		if (button.isMouseOnButtonClicked(window, text, "  SAVE", buttonPosX, buttonPosY + (buttonAbstand * 2)) && but2Flag == false) {
			saveMstack("stackst.txt"); saveStellung("Stellung.txt");
			but2Flag = true;
		}
		if (!button.isMouseOnButtonClicked(window, text, "  SAVE", buttonPosX, buttonPosY + (buttonAbstand * 2)))but2Flag = false;

		static bool but3Flag = false;
		if (button.isMouseOnButtonClicked(window, text, "  LOAD", buttonPosX, buttonPosY + (buttonAbstand * 3)) && but3Flag == false) {
			startResetEngine(); loadMstack("stackst.txt"); loadStellung("Stellung.txt"); engine = -1;
			but3Flag = true;
		}
		if (!button.isMouseOnButtonClicked(window, text, "  LOAD", buttonPosX, buttonPosY + (buttonAbstand * 3)))but3Flag = false;



		static bool but5Flag = false;
		if (button.isMouseOnButtonClicked(window, text, "  EASY", buttonPosX, buttonPosY + (buttonAbstand * 4)) && but5Flag == false) {
		//	ponder = 0;
			but5Flag = true;
		}
		if (!button.isMouseOnButtonClicked(window, text, "  EASY", buttonPosX, buttonPosY + (buttonAbstand * 4)))but5Flag = false;

		static bool but6Flag = false;
		if (button.isMouseOnButtonClicked(window, text, "  HARD", buttonPosX, buttonPosY + (buttonAbstand * 5)) && but6Flag == false) {
		//	ponder = 1;
			but6Flag = true;
		}
		if (!button.isMouseOnButtonClicked(window, text, "  HARD", buttonPosX, buttonPosY + (buttonAbstand * 5)))but6Flag = false;

		static bool but7Flag = false;
		if (button.isMouseOnButtonClicked(window, text, "  NEW", buttonPosX, buttonPosY + (buttonAbstand * 6)) && but7Flag == false) {
			drawBecause50Moves = false;
			draw = false;
			drawCauseMoveRepeat = false;
			unsuficientMatereals = false;
			whiteMates = false;
			blackMates = false;
			_readbook("olibook.pgn");
			saveValues();
			but7Flag = true;
		}
		if (!button.isMouseOnButtonClicked(window, text, "   NEW", buttonPosX, buttonPosY + (buttonAbstand * 6)))but7Flag = false;

		static bool but8Flag = false;
		if (button.isMouseOnButtonClicked(window, text, "  UNDO", buttonPosX, buttonPosY + (buttonAbstand * 7)) && but8Flag == false) {
			undo(); engine = -1;
			saveValues();
			but8Flag = true;

			 drawCauseMoveRepeat = false;
			 drawBecause50Moves = false;
			 unsuficientMatereals = false;
			 draw = false;
			 whiteMates = false;
			 blackMates = false;
		}
		if (!button.isMouseOnButtonClicked(window, text, "  UNDO", buttonPosX, buttonPosY + (buttonAbstand * 7)))but8Flag = false;

		static bool but9Flag = false;
		if (button.isMouseOnButtonClicked(window, text, "  EXIT", buttonPosX, buttonPosY + (buttonAbstand * 8)) && but9Flag == false) {
			saveMstack("gamesavestack.txt");
			saveStellung("gamesavestell.txt");
			return(0);
			but9Flag = true;
		}
		if (!button.isMouseOnButtonClicked(window, text, "  EXIT", buttonPosX, buttonPosY + (buttonAbstand * 8)))but9Flag = false;

		static bool  incBut1Flag = false;
			if (incButton.isMouseOnButtonClicked(window, text, incButtonPosX, incButtonPosY, st) == 1 && incBut1Flag == false) {
				st += 1;
				incBut1Flag = true;
			}
			if (!incButton.isMouseOnButtonClicked(window, text, incButtonPosX, incButtonPosY, st) == 1)incBut1Flag = false;

			static bool  incBut2Flag = false;
			if (incButton.isMouseOnButtonClicked(window, text, incButtonPosX, incButtonPosY, st) == 2 && incBut2Flag == false) {

				if(st > 0)st -= 1;
				incBut2Flag = true;
			}
			if (!incButton.isMouseOnButtonClicked(window, text, incButtonPosX, incButtonPosY, st))incBut2Flag = false;

			static bool  incBut3Flag = false;
			if (incButton.isMouseOnButtonClicked(window, text, incButtonPosX, incButtonPosY +50, sd) == 1 && incBut3Flag == false) {
				sd += 1;
				incBut3Flag = true;
			}
			if (!incButton.isMouseOnButtonClicked(window, text, incButtonPosX, incButtonPosY +50, sd) == 1)incBut3Flag = false;

			static bool  incBut4Flag = false;
			if (incButton.isMouseOnButtonClicked(window, text, incButtonPosX, incButtonPosY +50, sd) == 2 && incBut4Flag == false) {
				if (sd > 0)	sd -= 1;
				incBut4Flag = true;
			}
			if (!incButton.isMouseOnButtonClicked(window, text, incButtonPosX, incButtonPosY +50, sd))incBut4Flag = false;
            


		//     FIGUREN AUSGABE 

			static int blinkColor = 100;
			static bool blinkFlag = 0;

			if (blinkColor >= 245)blinkFlag = 1;
			if (blinkColor <= 10) blinkFlag = 0;
			if (blinkFlag)blinkColor -=4;
			else blinkColor +=4;
			if (!((engine == onmove) && (nodes + qnodes) != 0)) {

				for (int i = 0; i < 64; i++) {
					ostringstream strstream;
					int xy;
					xy = turnB ? BOARDXY0(i) : BOARDXY1(i);

					if ((BIT[xy] & colorbCopy[0]) | (BIT[xy] & colorbCopy[1])) {

						if ((TO(mstackCopy[COUNT - 1] >> 42L) == xy) && (mstackCopy[COUNT - 1] >> 42L)) {
							strstream << "*";
							text.setString(strstream.str());
							text.setCharacterSize(30);
							text.setPosition(drawLineXPos + 10 + ((i % 8) * abstandX), drawLineYPos +   ((i / 8) * abstandY));
							text.setFillColor(sf::Color(255, blinkColor, blinkColor, 255));
							window.draw(text);
						}

					}
					else
						if (FROM(mstackCopy[COUNT - 1] >> 42L) == xy) {
							strstream << "  *";
							text.setString(strstream.str());
							text.setCharacterSize(30);
							text.setPosition(drawLineXPos + 10 + ((i % 8) * abstandX), drawLineYPos + 22 + ((i / 8) * abstandY));
							text.setFillColor(sf::Color(255, 255 - blinkColor, 255 - blinkColor, 255));
							window.draw(text);
						}

				}
			}

		for (int i = 0;i < 64;i++) {
			int xy;
			xy = turnB ? BOARDXY0(i) : BOARDXY1(i);
			if (BIT[xy] & colorbCopy[0] && BIT[xy] & piecebCopy[PAWN]) {
				drawBauer(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 62 + ((i / 8) * abstandY),1);
			}
			if (BIT[xy] & colorbCopy[1] && BIT[xy] & piecebCopy[PAWN]) {
				drawBauer(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 62 + ((i / 8) * abstandY), 0);
			}

			
			if (BIT[xy] & colorbCopy[0] && BIT[xy] & piecebCopy[ROOK]) {
				drawTurm(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 62 + ((i / 8) * abstandY), 1);
			}
			if (BIT[xy] & colorbCopy[1] && BIT[xy] & piecebCopy[ROOK]) {
				drawTurm(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 62 + ((i / 8) * abstandY), 0);
			}

			if (BIT[xy] & colorbCopy[0] && BIT[xy] & piecebCopy[BISHOP]) {
				drawLaufer(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 67 + ((i / 8) * abstandY), 1);
			}
			if (BIT[xy] & colorbCopy[1] && BIT[xy] & piecebCopy[BISHOP]) {
				drawLaufer(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 67 + ((i / 8) * abstandY), 0);
			}

			if (BIT[xy] & colorbCopy[0] && BIT[xy] & piecebCopy[KNIGHT]) {
				drawSpringer(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 67 + ((i / 8) * abstandY), 1);
			}
			if (BIT[xy] & colorbCopy[1] && BIT[xy] & piecebCopy[KNIGHT]) {
				drawSpringer(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 67 + ((i / 8) * abstandY), 0);
			}
			if (BIT[xy] & colorbCopy[0] && BIT[xy] & piecebCopy[KING]) {
				drawKing(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 67 + ((i / 8) * abstandY), 1);
			}
			if (BIT[xy] & colorbCopy[1] && BIT[xy] & piecebCopy[KING]) {
				drawKing(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 67 + ((i / 8) * abstandY), 0);
			}
			if (BIT[xy] & colorbCopy[0] && BIT[xy] & piecebCopy[QUEEN]) {
				drawQueen(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 67 + ((i / 8) * abstandY), 1);
			}
			if (BIT[xy] & colorbCopy[1] && BIT[xy] & piecebCopy[QUEEN]) {
				drawQueen(window, drawLineXPos + 25 + ((i % 8) * abstandX), drawLineYPos + 67 + ((i / 8) * abstandY), 0);
			}

			
		}

		if (unsuficientMatereals || whiteMates || blackMates || drawCauseMoveRepeat || drawBecause50Moves ) {
			if (unsuficientMatereals) stringStr5 << "LESS MATERIALS!" << endl;
			else if (whiteMates) stringStr5 << "WHITE MATES !!!" << endl;
			else if (blackMates) stringStr5 << "BLACK MATES !!!" << endl;
			else if (drawCauseMoveRepeat)stringStr5 << "DRAW REPEAT !!!" << endl;
			else if (drawBecause50Moves)stringStr5 << "DRAW 50 MOVES!!" << endl;		
			text2.setString(stringStr5.str());
			text2.setPosition(270, 370);
			text2.setCharacterSize(60);
			text2.setFillColor(sf::Color(255, 0, 0, 155));
			window.draw(text2);
		}

		//    RAUS AUF DEN SCHIRM ENDLICH :-)

		window.display();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 				
				window.close();			
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			saveMstack("gamesavestack.txt");
			saveStellung("gamesavestell.txt");
			return 0;
		}

	}
};
