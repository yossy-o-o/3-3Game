
//やること
//1, 適当に600 * 600のピクセルをwindowで開く
//2, windowを開き続ける
//3, いったん×押したら閉じるようにする
//4, window全体を白に塗りつぶす
//5, クリック処理を実装する
//6. クリックしたら〇を出す

#include <SFML/Graphics.hpp>

void graphics(sf::RenderWindow& window);
void placeCircleOnClick(sf::RenderWindow& window, int board[3][3]);


int board[3][3] = { 0 };

//ピクセルに表示する関数
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
		placeCircleOnClick(window, board);
		window.display();
	}

	return 0;
}

//3 * 3の線を出力する関数
void graphics(sf::RenderWindow& window)
{
	//横線の長さと厚み
	sf::RectangleShape line(sf::Vector2f(600, 5));
	line.setFillColor(sf::Color::Black);

	//iに200を乗算することで、200ピクセルごとに縦に線を引いている
	for (int i = 1; i <= 2; i++)
	{
		line.setSize(sf::Vector2f(600, 5));
		line.setPosition(0, i * 200);
		window.draw(line);
	}

	//同じく横線
	line.setSize(sf::Vector2f(5, 600));
	for (int i = 1; i <= 2; i++)
	{
		line.setPosition(i * 200, 0);
		window.draw(line);
	}


	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			if (board[row][col] == 1)
			{
				sf::CircleShape circle(60);
				circle.setFillColor(sf::Color::Transparent);
				circle.setOutlineColor(sf::Color::Red);
				circle.setOutlineThickness(5);
				circle.setPosition(col * 200 + 40, row * 200 + 40);
				window.draw(circle);
			}
		}
	}
}

//クリックで〇を表示
void placeCircleOnClick(sf::RenderWindow& window, int board[3][3])
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //左クリックしてたら
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		int col = mousePos.x / 200;
		int row = mousePos.y / 200;

		if (col >= 0 && col < 3 && row >= 0 && row < 3)
		{
			if (board[row][col] == 0)
			{
				board[row][col] = 1;
			}
		}

	}
}


