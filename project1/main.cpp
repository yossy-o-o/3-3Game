
//やること
//1, 適当に600 * 600のピクセルをwindowで開く
//2, windowを開き続ける
//3, いったん×押したら閉じるようにする
//4, window全体を白に塗りつぶす

#include <SFML/Graphics.hpp>

void graphics(sf::RenderWindow& window);

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "〇×ゲーム");

	//イベント処理
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::White);
		graphics(window);
		window.display();
	}

	return 0;
}

//3 * 3の線を出力する関数
void graphics(sf::RenderWindow& window)
{
	sf::RectangleShape line(sf::Vector2f(600, 5));
	line.setFillColor(sf::Color::Black);

	for (int i = 1; i <= 2; i++)
	{
		line.setSize(sf::Vector2f(600, 5));
		line.setPosition(0, i * 200);
		window.draw(line);
	}

	line.setSize(sf::Vector2f(5, 600));
	for (int i = 1; i <=2; i++)
	{
		line.setPosition(i * 200, 0);
		window.draw(line);
	}
}