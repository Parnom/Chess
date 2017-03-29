#pragma once

class Incrementbutton {
	float buttonSize1 = 20;
	float buttonSize2 = 4;
	int textSize = 20;

public:

	void createIncButton(sf::RenderWindow& window, sf::Text & text, float PosX, float PosY, float Value) {
		ostringstream stringButton;
		sf::RectangleShape buttonShapeX(sf::Vector2f(buttonSize1, buttonSize2));
		buttonShapeX.setPosition(PosX, PosY);
		buttonShapeX.setFillColor(sf::Color(0, 155, 0));
		window.draw(buttonShapeX);
		sf::RectangleShape buttonShapeY(sf::Vector2f(buttonSize2, buttonSize1));
		buttonShapeY.setPosition(PosX + (buttonSize1 / 2) - (buttonSize2 / 2), PosY - (buttonSize1 / 2) + (buttonSize2 / 2));
		buttonShapeY.setFillColor(sf::Color(0, 155, 0));
		window.draw(buttonShapeY);

		stringButton << Value;
		text.setString(stringButton.str());
		text.setCharacterSize(textSize);
		text.setPosition(PosX + buttonSize1 + 10, PosY - 12);
	//	text.setColor(sf::Color::Red);
		window.draw(text);
		sf::RectangleShape buttonShapeY2(sf::Vector2f(buttonSize1, buttonSize2));
		buttonShapeY2.setPosition(PosX + buttonSize1 + 50, PosY);
		buttonShapeY2.setFillColor(sf::Color(155, 0, 0));
		window.draw(buttonShapeY2);
	}

	int isMouseOnButtonClicked(sf::RenderWindow& window, sf::Text& text, int PosX, int PosY, float Value) {
		ostringstream stringButton;
		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;

		if (mouseX > PosX  && mouseX < (PosX + buttonSize1) && mouseY > PosY  && mouseY < (PosY + buttonSize1)) {
			ostringstream stringButton;
			sf::RectangleShape buttonShapeX(sf::Vector2f(buttonSize1, buttonSize2));
			buttonShapeX.setPosition(PosX, PosY);
			buttonShapeX.setFillColor(sf::Color(0, 255, 0));
			window.draw(buttonShapeX);
			sf::RectangleShape buttonShapeY(sf::Vector2f(buttonSize2, buttonSize1));
			buttonShapeY.setPosition(PosX + (buttonSize1 / 2) - (buttonSize2 / 2), PosY - (buttonSize1 / 2) + (buttonSize2 / 2));
			buttonShapeY.setFillColor(sf::Color(0, 255, 0));
			window.draw(buttonShapeY);

			stringButton << Value;
			text.setString(stringButton.str());
			text.setCharacterSize(textSize);
			text.setPosition(PosX + buttonSize1 + 10, PosY - 12);
		//	text.setColor(sf::Color(222, 222, 222));
			window.draw(text);
			sf::RectangleShape buttonShapeY2(sf::Vector2f(buttonSize1, buttonSize2));
			buttonShapeY2.setPosition(PosX + buttonSize1 + 50, PosY);
			buttonShapeY2.setFillColor(sf::Color(155, 0, 0));
			window.draw(buttonShapeY2);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return (1);
		}
		if (mouseX > (PosX + 70) && mouseX < PosX + buttonSize1 + 70 && mouseY > PosY - 10 && mouseY < PosY - 10 + buttonSize1) {
			ostringstream stringButton;
			sf::RectangleShape buttonShapeX(sf::Vector2f(buttonSize1, buttonSize2));
			buttonShapeX.setPosition(PosX, PosY);
			buttonShapeX.setFillColor(sf::Color(0, 155, 0));
			window.draw(buttonShapeX);
			sf::RectangleShape buttonShapeY(sf::Vector2f(buttonSize2, buttonSize1));
			buttonShapeY.setPosition(PosX + (buttonSize1 / 2) - (buttonSize2 / 2), PosY - (buttonSize1 / 2) + (buttonSize2 / 2));
			buttonShapeY.setFillColor(sf::Color(0, 155, 0));
			window.draw(buttonShapeY);

			stringButton << Value;
			text.setString(stringButton.str());
			text.setCharacterSize(textSize);
			text.setPosition(PosX + buttonSize1 + 10, PosY - 12);
		//	text.setColor(sf::Color(222, 222, 222));
			window.draw(text);
			sf::RectangleShape buttonShapeY2(sf::Vector2f(buttonSize1, buttonSize2));
			buttonShapeY2.setPosition(PosX + buttonSize1 + 50, PosY);
			buttonShapeY2.setFillColor(sf::Color(255, 0, 0));
			window.draw(buttonShapeY2);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return (2);
		}
		return (0);
	}

};

class Controllbutton {

	int lengthX = 90;
	int lengthY = 30;
	int textSize = 20;
	int rot = 50;
	int grün = 55;
	int blau = 50;
	int rotB = 90;
	int grünB = 95;
	int blauB = 90;


public:

	void createButton(sf::RenderWindow& window, sf::Text& text, char buttonName[], int PosX, int PosY) {
		ostringstream stringButton;
		sf::RectangleShape buttonShape(sf::Vector2f(lengthX, lengthY));         // Button 
		buttonShape.setPosition(PosX, PosY);
		buttonShape.setFillColor(sf::Color(rot, grün, blau));
		buttonShape.setOutlineThickness(-4);
		buttonShape.setOutlineColor(sf::Color(blau, grün, rot));
		window.draw(buttonShape);
		stringButton << buttonName;
		text.setString(stringButton.str());
		text.setCharacterSize(textSize);
		text.setPosition(PosX, PosY);
	//	text.setColor(sf::Color(20, 20, 20));
		window.draw(text);

	}

	bool isMouseOnButtonClicked(sf::RenderWindow& window, sf::Text& text, char buttonName[], int PosX, int PosY) {
		ostringstream stringButton;
		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;

		if (mouseX > PosX && mouseX < (PosX + lengthX) && mouseY > PosY && mouseY < (PosY + lengthY)) {

			sf::RectangleShape buttonShape(sf::Vector2f(lengthX, lengthY));         // Button 
			buttonShape.setPosition(PosX, PosY);
			buttonShape.setFillColor(sf::Color(rotB, grünB, blauB));
			buttonShape.setOutlineThickness(-4);
			buttonShape.setOutlineColor(sf::Color(blauB, grünB, rotB));
			window.draw(buttonShape);
			stringButton << buttonName;
			text.setString(stringButton.str());
			text.setCharacterSize(textSize);
			text.setPosition(PosX, PosY);
		//	text.setColor(sf::Color(20, 20, 20));
			window.draw(text);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return(true);
			else return(false);
		}
		return(false);
	}
};




void drawBauer(sf::RenderWindow& window, int PosX, int PosY,bool Color) {

	PosY = PosY - 3;

	sf::RectangleShape shape1(sf::Vector2f(30, 5));

	if (Color) {
		shape1.setFillColor(colorWhite);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		shape1.setFillColor(colorBlack);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	shape1.setPosition(PosX, PosY);
	window.draw(shape1);

	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(PosX, PosY));
	convex.setPoint(1, sf::Vector2f(PosX + 5, PosY - 6));
	convex.setPoint(2, sf::Vector2f(PosX + 25, PosY - 6));
	convex.setPoint(3, sf::Vector2f(PosX + 30, PosY));

	if (Color) {
		convex.setFillColor(colorWhite);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex.setFillColor(colorBlack);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex);

	sf::ConvexShape convex2;
	convex2.setPointCount(4);
	convex2.setPoint(0, sf::Vector2f(PosX + 5, PosY - 6));
	convex2.setPoint(1, sf::Vector2f(PosX + 14, PosY - 36));
	convex2.setPoint(2, sf::Vector2f(PosX + 16, PosY - 36));
	convex2.setPoint(3, sf::Vector2f(PosX + 25, PosY - 6));

	if (Color) {
		convex2.setFillColor(colorWhite);
		convex2.setOutlineThickness(-1);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex2.setFillColor(colorBlack);
		convex2.setOutlineThickness(-1);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex2);


	sf::CircleShape ball;
	ball.setPosition(PosX + 4 , PosY - 45 );
	ball.setRadius(11);
	if (Color) {
		ball.setFillColor(colorWhite);
		ball.setOutlineThickness(-2);
		ball.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		ball.setFillColor(colorBlack);
		ball.setOutlineThickness(-2);
		ball.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(ball);

};
void drawTurm(sf::RenderWindow& window, int PosX, int PosY, bool Color) {
	PosY = PosY - 0;

	sf::RectangleShape shape1(sf::Vector2f(30, 5));

	if (Color) {
		shape1.setFillColor(colorWhite);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		shape1.setFillColor(colorBlack);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	shape1.setPosition(PosX,PosY);
	window.draw(shape1);
	
	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(PosX, PosY ));
	convex.setPoint(1, sf::Vector2f(PosX + 5, PosY - 6));
	convex.setPoint(2, sf::Vector2f(PosX + 25, PosY - 6));
	convex.setPoint(3, sf::Vector2f(PosX + 30, PosY ));
			
	if (Color) {
		convex.setFillColor(colorWhite);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex.setFillColor(colorBlack);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex);

	sf::ConvexShape convex2;
	convex2.setPointCount(4);
	convex2.setPoint(0, sf::Vector2f(PosX + 5, PosY -6));
	convex2.setPoint(1, sf::Vector2f(PosX + 10, PosY - 36));
	convex2.setPoint(2, sf::Vector2f(PosX + 20, PosY - 36));
	convex2.setPoint(3, sf::Vector2f(PosX + 25, PosY - 6));

	if (Color) {
		convex2.setFillColor(colorWhite);
		convex2.setOutlineThickness(-1);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex2.setFillColor(colorBlack);
		convex2.setOutlineThickness(-1);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex2);


	sf::RectangleShape shape2(sf::Vector2f(30, 10));

	if (Color) {
		shape2.setFillColor(colorWhite);
		shape2.setOutlineThickness(-1);
		shape2.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		shape2.setFillColor(colorBlack);
		shape2.setOutlineThickness(-1);
		shape2.setOutlineColor(sf::Color(0, 0, 0));
	}
	shape2.setPosition(PosX , PosY -43);
	window.draw(shape2);




	sf::RectangleShape stone(sf::Vector2f(8, 8));
	if (Color) {
		stone.setFillColor(colorWhite);
		stone.setOutlineThickness(-1);
		stone.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		stone.setFillColor(colorBlack);
		stone.setOutlineThickness(-1);
		stone.setOutlineColor(sf::Color(0, 0, 0));
	}
	
		stone.setPosition(PosX  , PosY - 50);
		window.draw(stone);
		stone.setPosition(PosX + 22, PosY - 50);
		window.draw(stone);
		stone.setPosition(PosX + 11, PosY - 50);
		window.draw(stone);


		sf::CircleShape ball(4);

		if (Color) {
			ball.setFillColor(colorBlack);
		}
		else {
			ball.setFillColor(colorWhite);

		}
		ball.setPosition(PosX + 11, PosY - 30);
		window.draw(ball);


};

void drawLaufer(sf::RenderWindow& window, int PosX, int PosY, bool Color) {
	

	sf::RectangleShape shape1(sf::Vector2f(30, 5));

	if (Color) {
		shape1.setFillColor(colorWhite);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		shape1.setFillColor(colorBlack);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	shape1.setPosition(PosX, PosY);
	window.draw(shape1);

	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(PosX, PosY));
	convex.setPoint(1, sf::Vector2f(PosX + 5, PosY - 6));
	convex.setPoint(2, sf::Vector2f(PosX + 25, PosY - 6));
	convex.setPoint(3, sf::Vector2f(PosX + 30, PosY));

	if (Color) {
		convex.setFillColor(colorWhite);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex.setFillColor(colorBlack);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex);

	sf::ConvexShape convex2;
	convex2.setPointCount(4);
	convex2.setPoint(0, sf::Vector2f(PosX + 5, PosY - 6));
	convex2.setPoint(1, sf::Vector2f(PosX + 14, PosY - 36));
	convex2.setPoint(2, sf::Vector2f(PosX + 16, PosY - 36));
	convex2.setPoint(3, sf::Vector2f(PosX + 25, PosY - 6));

	if (Color) {
		convex2.setFillColor(colorWhite);
		convex2.setOutlineThickness(-1);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex2.setFillColor(colorBlack);
		convex2.setOutlineThickness(-1);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex2);


	sf::CircleShape ball;
	ball.setPosition(PosX + 5, PosY - 50);
	ball.setRadius(10);
	if (Color) {
		ball.setFillColor(colorWhite);
		ball.setOutlineThickness(-2);
		ball.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		ball.setFillColor(colorBlack);
		ball.setOutlineThickness(-2);
		ball.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(ball);
	sf::CircleShape ball2;
	ball2.setPosition(PosX + 7, PosY - 60);
	ball2.setRadius(8);
	if (Color) {
		ball2.setFillColor(colorBlack);
		ball2.setOutlineThickness(-2);
		ball2.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		ball2.setFillColor(colorWhite);
		ball2.setOutlineThickness(-2);
		ball2.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(ball2);
};

void drawSpringer(sf::RenderWindow& window, int PosX, int PosY, bool Color) {
	PosX = PosX + 5;
	
	sf::RectangleShape shape1(sf::Vector2f(30, 5));

	if (Color) {
		shape1.setFillColor(colorWhite);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		shape1.setFillColor(colorBlack);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	shape1.setPosition(PosX, PosY);
	window.draw(shape1);

	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(PosX, PosY));
	convex.setPoint(1, sf::Vector2f(PosX + 5, PosY - 6));
	convex.setPoint(2, sf::Vector2f(PosX + 25, PosY - 6));
	convex.setPoint(3, sf::Vector2f(PosX + 30, PosY));

	if (Color) {
		convex.setFillColor(colorWhite);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex.setFillColor(colorBlack);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex);

	sf::ConvexShape convex2;
	convex2.setPointCount(4);
	convex2.setPoint(0, sf::Vector2f(PosX + 5, PosY - 6));
	convex2.setPoint(1, sf::Vector2f(PosX + 8, PosY - 36));
	convex2.setPoint(2, sf::Vector2f(PosX + 22, PosY - 36));
	convex2.setPoint(3, sf::Vector2f(PosX + 25, PosY - 6));

	if (Color) {
		convex2.setFillColor(colorWhite);
		convex2.setOutlineThickness(-1);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex2.setFillColor(colorBlack);
		convex2.setOutlineThickness(-1);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex2);


	sf::ConvexShape convex3;
	convex3.setPointCount(4);
	convex3.setPoint(0, sf::Vector2f(PosX - 8, PosY -15));
	convex3.setPoint(1, sf::Vector2f(PosX - 12, PosY - 23));
	convex3.setPoint(2, sf::Vector2f(PosX + 22, PosY - 60));
	convex3.setPoint(3, sf::Vector2f(PosX + 35, PosY - 35));	
	if (Color) {
		convex3.setFillColor(colorWhite);
		convex3.setOutlineThickness(-2);
		convex3.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex3.setFillColor(colorBlack);
		convex3.setOutlineThickness(-2);
		convex3.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex3);

	sf::CircleShape augeShape;
	
		augeShape.setPosition(PosX +15, PosY - 45);
	    augeShape.setRadius(3);
	if (Color) {
		augeShape.setFillColor(colorBlack);		
	}
	else {
		augeShape.setFillColor(colorWhite);		
	}
	window.draw(augeShape);

};
void drawKing(sf::RenderWindow& window, int PosX, int PosY, bool Color) {
	PosY = PosY + 5;

	sf::RectangleShape shape1(sf::Vector2f(30, 5));

	if (Color) {
		shape1.setFillColor(colorWhite);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		shape1.setFillColor(colorBlack);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	shape1.setPosition(PosX, PosY);
	window.draw(shape1);

	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(PosX, PosY));
	convex.setPoint(1, sf::Vector2f(PosX + 5, PosY - 6));
	convex.setPoint(2, sf::Vector2f(PosX + 25, PosY - 6));
	convex.setPoint(3, sf::Vector2f(PosX + 30, PosY));

	if (Color) {
		convex.setFillColor(colorWhite);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex.setFillColor(colorBlack);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex);

	sf::RectangleShape shupi(sf::Vector2f(20,30));

	shupi.setPosition(PosX +5, PosY - 35);

	if (Color) {
		shupi.setFillColor(colorWhite);
		shupi.setOutlineThickness(-2);
		shupi.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		shupi.setFillColor(colorBlack);
		shupi.setOutlineThickness(-2);
		shupi.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(shupi);

	
	sf::ConvexShape convex2;
	convex2.setPointCount(4);
	convex2.setPoint(0, sf::Vector2f(PosX, PosY - 50));
	convex2.setPoint(1, sf::Vector2f(PosX + 30, PosY - 50));
	convex2.setPoint(2, sf::Vector2f(PosX + 25, PosY - 15));
	convex2.setPoint(3, sf::Vector2f(PosX + 5, PosY - 15));

	if (Color) {
		convex2.setFillColor(colorWhite);
		convex2.setOutlineThickness(-2);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex2.setFillColor(colorBlack);
		convex2.setOutlineThickness(-2);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex2);


	sf::RectangleShape xshape(sf::Vector2f(15,5));
	xshape.setPosition(sf::Vector2f(PosX +7, PosY - 62));
	if (Color) {
		xshape.setFillColor(colorBlack);
		convex2.setOutlineThickness(-2);
		convex2.setOutlineColor(sf::Color(0, 0, 0));

	}
	else {
		xshape.setFillColor(colorWhite);
		convex2.setOutlineThickness(-2);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(xshape);

	sf::RectangleShape yshape(sf::Vector2f(5, 15));
	yshape.setPosition(sf::Vector2f(PosX + 12, PosY - 66));
	if (Color) {
		yshape.setFillColor(colorBlack);
		convex2.setOutlineThickness(-2);
		convex2.setOutlineColor(sf::Color(0, 0, 0));

	}
	else {
		yshape.setFillColor(colorWhite);
		convex2.setOutlineThickness(-2);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(yshape);
};

void drawQueen(sf::RenderWindow& window, int PosX, int PosY, bool Color) {
	PosY = PosY ;
	sf::RectangleShape shape1(sf::Vector2f(30, 5));

	if (Color) {
		shape1.setFillColor(colorWhite);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		shape1.setFillColor(colorBlack);
		shape1.setOutlineThickness(-1);
		shape1.setOutlineColor(sf::Color(0, 0, 0));
	}
	shape1.setPosition(PosX, PosY);
	window.draw(shape1);

	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(PosX, PosY));
	convex.setPoint(1, sf::Vector2f(PosX + 5, PosY - 6));
	convex.setPoint(2, sf::Vector2f(PosX + 25, PosY - 6));
	convex.setPoint(3, sf::Vector2f(PosX + 30, PosY));

	if (Color) {
		convex.setFillColor(colorWhite);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex.setFillColor(colorBlack);
		convex.setOutlineThickness(-1);
		convex.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex);

	sf::ConvexShape convex2;
	convex2.setPointCount(4);
	convex2.setPoint(0, sf::Vector2f(PosX + 5, PosY - 6));
	convex2.setPoint(1, sf::Vector2f(PosX + 10, PosY - 36));
	convex2.setPoint(2, sf::Vector2f(PosX + 20, PosY - 36));
	convex2.setPoint(3, sf::Vector2f(PosX + 25, PosY - 6));

	if (Color) {
		convex2.setFillColor(colorWhite);
		convex2.setOutlineThickness(-1);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex2.setFillColor(colorBlack);
		convex2.setOutlineThickness(-1);
		convex2.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex2);

	sf::ConvexShape convex3;
	convex3.setPointCount(7);
	PosX = PosX + 1;
	convex3.setPoint(0, sf::Vector2f(PosX, PosY - 55));
	convex3.setPoint(1, sf::Vector2f(PosX + 7, PosY - 40));
	convex3.setPoint(2, sf::Vector2f(PosX + 14, PosY - 55));
	convex3.setPoint(3, sf::Vector2f(PosX + 21, PosY - 40));
	convex3.setPoint(4, sf::Vector2f(PosX + 28, PosY - 55));
	convex3.setPoint(5, sf::Vector2f(PosX + 21, PosY - 15));
	convex3.setPoint(6, sf::Vector2f(PosX + 7, PosY - 15));

	if (Color) {
		convex3.setFillColor(colorWhite);
		convex3.setOutlineThickness(-2);
		convex3.setOutlineColor(sf::Color(0, 0, 0));
	}
	else {
		convex3.setFillColor(colorBlack);
		convex3.setOutlineThickness(-2);
		convex3.setOutlineColor(sf::Color(0, 0, 0));
	}
	window.draw(convex3);

	sf::CircleShape augeShape;

	augeShape.setPosition(PosX + 10, PosY - 62);
	augeShape.setRadius(4);
	if (Color) {
		augeShape.setFillColor(colorBlack);

	}
	else {
		augeShape.setFillColor(colorWhite);

	}
	window.draw(augeShape);


};




// Nummerierung     Schachbrett
/*

for (int i = 0; i < 8; i++) {
int xy;
xy = turnB ? i : 7 - i;
ostringstream nummstring;
char testc = 'a' + xy;
nummstring << testc;

text.setString(nummstring.str());
text.setColor(sf::Color(0, 0, 0));
text.setCharacterSize(22);
text.setPosition(drawLineXPos + 20 + (i * abstand) + 20, drawLineYPos + (8 * abstand) );
window.draw(text);

for (int i = 0; i < 8; i++) {
int xy;
xy = turnB ? i : 7 - i;
ostringstream nummstring;
nummstring << 8 - xy;
text.setString(nummstring.str());
text.setColor(sf::Color(0, 0, 0));
text.setCharacterSize(20);
text.setPosition(drawLineXPos - 30, drawLineYPos + 10 + (i * abstand) + 20);
window.draw(text);
}

}
*/
