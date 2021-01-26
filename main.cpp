//kopia zapasowa
#include <iostream>
#include <fstream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Menu.h"
#include "EndGame.h"
#include "Personalize.h"

using namespace sf;
using namespace std;

template <class T1, class T2> bool isIntersecting(T1& A, T2& B) //sprawdza czy dane obiekty się zderzają
{
	return A.right() >= B.left() && A.left() <= B.right()
		&& A.bottom() >= B.top() && A.top() <= B.bottom();
}

bool collisionTest(Paddle& paddle, Ball& ball)    //funkcja sprawdzająca, czy piłeczka odbija się od platformy
{

	if (!isIntersecting(paddle, ball)) return false;
	ball.moveUp();

	if (ball.getPosition().x < paddle.getPosition().x)
	{
		ball.moveLeft();
	}
	else if (ball.getPosition().x > paddle.getPosition().x)
	{
		ball.moveRight();
	}


}

bool collisionTest(Block& block, Ball& ball)
{
	if (!isIntersecting(block, ball)) return false; //jezeli się nie przecinają (nie zachodzi kolizja między bloczkiem a kulką) to zwracamy false, nic się nie dzieje

	block.destroy(); //jesli się przecinają, niszczymy bloczek
	float overlapLeft{ ball.right() - block.left() }; //  zmienne oznaczają przesuniecie krawędzi kulki względem odpowiedniej krawędzi bloczka, 
	//^dzięki przesunięciom dowiemy się, z której strony kulka uderzyła w bloczek. w tym przypadku kulka uderzyła bloczek z lewej strony
	float overlapRight{ block.right() - ball.left() };//sprawdzamy prawą krawędź bloczka względem lewej krawędzi kulki
	float overlapTop{ ball.bottom() - block.top() }; //to samo dla krawędzi górnych oraz dolnych
	float overlapBottom{ block.bottom() - ball.top() };

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));//sprawdzamy z której strony kulka uderzyła w nasz bloczek, dlatego porównujemy wartości przesunięć w poziomie
	//^jeżeli nierówność będzie spełniona, to kulka uderzyła z lewej strony

	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));
	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
	{
		ballFromLeft ? ball.moveLeft() : ball.moveRight();
	}

	else {
		ballFromTop ? ball.moveUp() : ball.moveDown();
	}


}

bool LoseTest(const RenderWindow& window, Ball& ball)
{
	if (ball.bottom() > window.getSize().y) //TUTAJ!
	{
		return true;
	}
	return false;
}

void Highscore(int score, sf::RenderWindow &window) {
	/* Funkcja wypisuje na ekranie końcowym wynik oraz najwyższy wynik odczytany z pliku, ale obsługa plików na razie nie działa */
	ifstream highscore;
	int prevHighscore = 0;
	highscore.open("highscore.txt");
	highscore >> prevHighscore;
	highscore.close();
	if (score > prevHighscore) {
		prevHighscore = score;
	}
	ofstream _highscore;
	_highscore.open("highscore.txt");
	_highscore << prevHighscore;
	_highscore.close();
	string _score = to_string(score);
	string _prevHighscore = to_string(prevHighscore);
	sf::Font hscore_font;
	sf::Text Score, HighScore;
	if (!hscore_font.loadFromFile("arial.ttf")) {
		std::cout << "Blad wczytwywania fontu!" << std::endl;
	}
	Score.setString(_score);
	Score.setFont(hscore_font);
	Score.setFillColor(Color::Black);
	Score.setPosition(395, 145);

	HighScore.setString(_prevHighscore);
	HighScore.setFont(hscore_font);
	HighScore.setFillColor(Color::Black);
	HighScore.setPosition(395, 255);

	window.draw(Score);
	window.draw(HighScore);

}
int main()
{
	RenderWindow window(VideoMode(800, 600), "Arkanoid");
	Ball ball(400, 300, sf::Color::Green);
	Paddle paddle(400, 550);
StartGame:	//flaga z goto
	ball.setPosition(400,300);
	window.setFramerateLimit(60);
	Event event;
	unsigned blockWidth{ 63 }, blockHeight{ 20 };
	vector<Block> blocks; //tworzymy kontener bloczków
	vector<Block> kostki;
	Menu menu(window.getSize().x, window.getSize().y);	//tworzenie menu
	Personalize opcje(window.getSize().x, window.getSize().y);
	EndGame endgame(window.getSize().x, window.getSize().y);
	sf::Texture gameBackground;
	if (!gameBackground.loadFromFile("GameBackground.png"))
	{
		std::cout << "Nie mozna zaladowac tla gry!" << std::endl;
	}
	sf::Sprite bck(gameBackground);
	int GameScore = 0;
	int level = 1;

	SoundBuffer bounce1Buff, bounce2Buff, winBuff, lostBuff;
	if ((!bounce1Buff.loadFromFile("bounce1.wav"))||(!bounce2Buff.loadFromFile("bounce2.wav")) || (!winBuff.loadFromFile("win.wav")) || (!lostBuff.loadFromFile("lost.wav"))) {
		std::cout << "Nie mozna zaladowac dzwiekow!" << std::endl;
	}

	Sound bounce1, bounce2, lost, win;
	bounce1.setBuffer(bounce1Buff);
	bounce2.setBuffer(bounce2Buff);
	win.setBuffer(winBuff);
	lost.setBuffer(lostBuff);

	Music mainTheme;
	if (!mainTheme.openFromFile("main_theme.wav")) {
		cout << "Nie mozna zaladowac muzyki!" << endl;
	}


	//intensywny pomaranczowy
	int color1_R = 167;
	int color1_G = 45;
	int color1_B = 45;

	//ciemnoniebieski turkus
	int color3_R = 5;
	int color3_G = 73;
	int color3_B = 89;

	//brudny blekit
	int color4_R = 7;
	int color4_G = 101;
	int color4_B = 141;

	//bialy
	int color9_R = 242;
	int color9_G = 241;
	int color9_B = 240;

	//motyw 1
	int pilka_color1_R = 95;
	int pilka_color1_G = 64;
	int pilka_color1_B = 146;

	int platforma_color1_R = 143;
	int platforma_color1_G = 146;
	int platforma_color1_B = 0;

	//motyw 2
	int pilka_color2_R = 54;
	int pilka_color2_G = 169;
	int pilka_color2_B = 225;

	int platforma_color2_R = 255;
	int platforma_color2_G = 237;
	int platforma_color2_B = 0;

	//motyw3
	int pilka_color3_R = 231;
	int pilka_color3_G = 29;
	int pilka_color3_B = 115;

	int platforma_color3_R = 83;
	int platforma_color3_G = 175;
	int platforma_color3_B = 50;


Poziomy:
	// poziom pierwszy
	if (level == 1)
	{

		for (int i = 0; i < 1; i++)
		{
			for (int m = 0; m < 2; m++) //do zbicia 2 razy
			{
				for (int j = 2; j < 8; j++)
				{
					blocks.emplace_back((j + 1)*(blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color4_R, color4_G, color4_B);
				}
			}
		}
		for (int i = 1; i < 4; i++)
		{
			if (i == 1)
			{
				for (int j = 1; j < 9; j++) //do zbicia 1 raz
				{
					blocks.emplace_back((j + 1)*(blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color3_R, color3_G, color3_B);
				}
			}
			else
			{
				for (int j = 0; j < 10; j++) //do zbicia 1 raz
				{
					blocks.emplace_back((j + 1)*(blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color3_R, color3_G, color3_B);
				}
			}
		}
		for (int i = 4; i < 7; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (j == 0 || j == 4 || j == 5 || j == 9)
				{
					for (int m = 0; m < 3; m++)
					{
						blocks.emplace_back((j + 1)*(blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color1_R, color1_G, color1_B);
					}
				}
			}
		}
		for (int i = 4; i < 6; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (j == 1 || j == 3 || j == 6 || j == 8)
				{
					for (int m = 0; m < 2; m++) //te trzeba zbic 3 razy
					{
						blocks.emplace_back((j + 1)*(blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color1_R, color1_G, color1_B);
					}
				}
			}
		}
		for (int i = 0; i < 2; i++) //bloczki nie do zbicia
		{
			if (i == 0)
			{
				for (int j = 0; j < 10; j++)
				{
					{
						if (j < 2 || j>7)
						{
							kostki.emplace_back((j + 1)*(blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
						}
					}
				}
			}
			else
			{
				kostki.emplace_back(blockWidth + 10, 3 * (blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
				kostki.emplace_back(10 * (blockWidth + 10), 3 * (blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
			}
		}


	}

	//poziom drugi
	if (level == 2)
	{
		ball.actual_velocity(5.0f);
		for (int i = 0; i < 10; i++) //do zbicia raz
		{
			if (i == 0 || i == 9)
			{
				for (int j = 0; j < 10; j++)
				{
					blocks.emplace_back((j + 1)*(blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color4_R, color4_G, color4_B);
				}
			}
			else
			{
				blocks.emplace_back((blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color4_R, color4_G, color4_B);

				blocks.emplace_back(10 * (blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color4_R, color4_G, color4_B);
			}
		}
		for (int m = 0; m < 2; m++) //dwa razy
		{
			for (int i = 1; i < 9; i++)
			{
				if (i == 1 || i == 8)
				{
					for (int j = 1; j < 9; j++)
					{
						blocks.emplace_back((j + 1)*(blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color3_R, color3_G, color3_B);
					}
				}
				else
				{
					blocks.emplace_back(2 * (blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color3_R, color3_G, color3_B);
					blocks.emplace_back(9 * (blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color3_R, color3_G, color3_B);
				}
			}
		}
		for (int i = 2; i < 8; i++)
		{
			if (i == 2 || i == 7)
			{
				for (int j = 2; j < 8; j++)
				{
					blocks.emplace_back((j + 1)*(blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color1_R, color1_G, color1_B);
				}
			}
			else
			{
				blocks.emplace_back(3 * (blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color1_R, color1_G, color1_B);
				blocks.emplace_back(8 * (blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color1_R, color1_G, color1_B);
			}

		}
		for (int i = 4; i < 6; i++) //nie do zbicia
		{
			kostki.emplace_back(5 * (blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
			kostki.emplace_back(6 * (blockWidth + 10), (i + 2)*(blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
		}
		kostki.emplace_back(4 * (blockWidth + 10), 5 * (blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
		kostki.emplace_back(4 * (blockWidth + 10), 8 * (blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
		kostki.emplace_back(7 * (blockWidth + 10), 5 * (blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
		kostki.emplace_back(7 * (blockWidth + 10), 8 * (blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
	}

	//poziom trzeci
	if (level == 3)
	{

		ball.actual_velocity(7.0f);

		for (int i = 0; i < 2; i++) //dwa razy do zbicia
		{
			for (int j = 0; j < 10; j++)
			{
				if (j % 2 == 0)
				{
					blocks.emplace_back((j + 1)*(blockWidth + 10), 2 * (blockHeight + 5), blockWidth, blockHeight, color4_R, color4_G, color4_B);
				}
				else
				{
					blocks.emplace_back((j + 1)*(blockWidth + 10), 3 * (blockHeight + 5), blockWidth, blockHeight, color4_R, color4_G, color4_B);
				}
			}
		}

		for (int j = 0; j < 10; j++) //kostki
		{
			if (j % 2 == 1)
			{
				kostki.emplace_back((j + 1)*(blockWidth + 10), 2 * (blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
			}
		}
		for (int j = 0; j < 5; j++)
		{
			blocks.emplace_back((j + 3.5)*(blockWidth + 10), 4 * (blockHeight + 5), blockWidth, blockHeight, color1_R, color1_G, color1_B);
		}
		for (int j = 0; j < 3; j++)
		{
			blocks.emplace_back((j + 4.5)*(blockWidth + 10), 5 * (blockHeight + 5), blockWidth, blockHeight, color1_R, color1_G, color1_B);
		}
		for (int i = 0; i < 10; i++) //dodanie kostek
		{
			if (i % 2 == 0)
			{
				kostki.emplace_back((i + 1)*(blockWidth + 10), 6 * (blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
			}
		}
		for (int j = 0; j < 3; j++)
		{
			blocks.emplace_back((j + 4.5)*(blockWidth + 10), 7 * (blockHeight + 5), blockWidth, blockHeight, color1_R, color1_G, color1_B);
		}
		for (int j = 0; j < 5; j++)
		{
			blocks.emplace_back((j + 3.5)*(blockWidth + 10), 8 * (blockHeight + 5), blockWidth, blockHeight, color1_R, color1_G, color1_B);
		}
		for (int j = 0; j < 10; j++)
		{
			if (j % 2 == 0)
			{
				blocks.emplace_back((j + 1)*(blockWidth + 10), 9 * (blockHeight + 5), blockWidth, blockHeight, color3_R, color3_G, color3_B);
			}
			else
			{
				blocks.emplace_back((j + 1)*(blockWidth + 10), 10 * (blockHeight + 5), blockWidth, blockHeight, color3_R, color3_G, color3_B);
			}
		}
		for (int j = 0; j < 10; j++) //kostki
		{
			if (j % 2 == 0)
			{
				kostki.emplace_back((j + 1)*(blockWidth + 10), 10 * (blockHeight + 5), blockWidth, blockHeight, color9_R, color9_G, color9_B);
			}
		}

	}

	mainTheme.setLoop(true);
	mainTheme.play();

	while (true)
	{
		window.clear(Color::Black);
		Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::KeyReleased:		//nasluchuje klawiszy w menu, sluzy do scrollowania i wybierania opcji
				switch (event.key.code) {
				case Keyboard::Up:
					menu.MoveUp();
					break;
				case Keyboard::Down:
					menu.MoveDown();
					break;
				case Keyboard::Return:
					switch (menu.GetPressedItem()) {		//sprawdza po nacisnieciu entera ktory element wybrano
					case 0:									//jezeli jest to element "0", czyli "START" to gra sie rozpoczyna
						mainTheme.stop();
						while (true) {
							window.pollEvent(event);
							if (event.type == Event::Closed)
							{
								window.close();
								break;
							}
							window.clear();


							if (Keyboard::isKeyPressed(Keyboard::Key::Space))			//po wcisnieciu spacji odpala sie pauza
							{
								while (true) {
									sleep(milliseconds(100));
									if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {	//po ponownej spacji wracamy do gry. Dziala w 85% przypadkow xD
										sleep(milliseconds(100));
										goto Resume;
									}
								}
							}
							Resume:
							ball.update(); //rysuje pileczke i platforme
							paddle.update();


							collisionTest(paddle, ball);

							for (auto& block : blocks) if (collisionTest(block, ball))
							{
								bounce1.play();
								GameScore++;
								break; //sprawdzamy kolizję pomiędzy bloczkiem a kulką
							}
							if (collisionTest(paddle, ball)) {
								bounce2.play();
							}

							//usuwamy z kontenera bloczki:

							auto  iterator = remove_if(begin(blocks), end(blocks), [](Block& block) {return  block.isDestroyed(); });
							blocks.erase(iterator, end(blocks)); //usuwamy z kontenera bloczki

							for (auto& block : kostki) if (collisionTest(block, ball)) //po to, aby pileczka odbijala sie od kostek
							{
								break;
							}

							//gdy pileczka spadnie:
							if (LoseTest(window, ball) == true)
							{
								lost.play();
								while (true) {
									window.clear(Color::Black);
									endgame.draw(window);
									Highscore(GameScore, window);
									window.display();
									while (window.pollEvent(event)) {
										switch (event.type) {
										case Event::Closed:
											window.close();
											break;
										case Event::KeyReleased:		//nasłuchuje klawiszy w menu, sluzy do scrollowania i wybierania opcji
											switch (event.key.code) {
											case Keyboard::Up:
												endgame.MoveUp();
												break;
											case Keyboard::Down:
												endgame.MoveDown();
												break;
											case Keyboard::Return:
												switch (endgame.GetPressedItem()) {		//sprawdza po naciśnięciu entera który element wybrano
												case 0:
													goto StartGame;
												case 1:
													window.close();
													return 0;
													break;
												}
											}
										}
									}
								}
							}




							if (blocks.empty() == 1) //pokazanie nowej planszy po zbiciu bloczkow, ekran koncowy po zakonczeniu 3ciego poziomu
							{
								win.play();
								GameScore = GameScore + 50; //dodanie punktow za ukończenie poziomu
								level = level + 1;
								if (level < 4)
								{
									goto Poziomy;
								}
								{
									while (true) {
										window.clear(Color::Black);
										endgame.draw(window);
										Highscore(GameScore, window);
										window.display();
										while (window.pollEvent(event)) {
											switch (event.type) {
											case Event::Closed:
												window.close();
												break;
											case Event::KeyReleased:		//nasłuchuje klawiszy w menu, sluzy do scrollowania i wybierania opcji
												switch (event.key.code) {
												case Keyboard::Up:
													endgame.MoveUp();
													break;
												case Keyboard::Down:
													endgame.MoveDown();
													break;
												case Keyboard::Return:
													switch (endgame.GetPressedItem()) {		//sprawdza po naciśnięciu entera który element wybrano
													case 0://przycisk "zagraj ponownie"
														goto StartGame;
													case 1://przycisk "zakoncz gre"
														window.close();
														return 0;
														break;
													}
												}
											}
										}
									}
								}
							}

							window.draw(bck);
							window.draw(ball);
							window.draw(paddle);

							for (auto& block : blocks) //iterujemy w ten sposób wszystkie bloki z kontenera i rysujemy je na ekranie
								window.draw(block);

							for (auto& block : kostki)
								window.draw(block);

							window.display();
						}
					case 1:									//Personalizacja wygladu
						while (true) {
							opcje.draw(window);
							window.display();
							while (window.pollEvent(event)) {
								switch (event.type) {
								case Event::Closed:
									window.close();
									break;
								case Event::KeyReleased:
									switch (event.key.code) {
									case Keyboard::Up:
										opcje.MoveUp();
										break;
									case Keyboard::Down:
										opcje.MoveDown();
										break;
									case Keyboard::Return:
										switch (opcje.GetPressedItem()) {
										case 0:
											//motyw 1
											paddle.kolorek = Color(platforma_color1_R, platforma_color1_G, platforma_color1_B);
											ball.kolorek = Color(pilka_color1_R, pilka_color1_G, pilka_color1_B);
											goto StartGame;
										case 1:
											//motyw 2
											paddle.kolorek = Color(platforma_color2_R, platforma_color2_G, platforma_color2_B);
											ball.kolorek = Color(pilka_color2_R, pilka_color2_G, pilka_color2_B);
											goto StartGame;
										case 2:
											//motyw 3
											paddle.kolorek = Color(platforma_color3_R, platforma_color3_G, platforma_color3_B);
											ball.kolorek = Color(pilka_color3_R, pilka_color3_G, pilka_color3_B);
											goto StartGame;
										case 3:
											goto StartGame;
											break;
										}
									}
								}
							}
						}
						
						break;
					case 2:
						window.close();		//zamyka okno i kończy program
						return 0;
						break;
					default:
						break;
					}

				}
				break;
			}

		}

		menu.draw(window);
		window.display();


	}
	return 0;
}
