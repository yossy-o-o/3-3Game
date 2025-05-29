
//��邱��
//1, �K����600 * 600�̃s�N�Z����window�ŊJ��
//2, window���J��������
//3, ��������~�����������悤�ɂ���
//4, window�S�̂𔒂ɓh��Ԃ�
//5, �N���b�N��������������
//6. �N���b�N������Z���o��

#include <SFML/Graphics.hpp>

void graphics(sf::RenderWindow& window);
void placeCircleOnClick(sf::RenderWindow& window, int board[3][3]);


int board[3][3] = { 0 };

//�s�N�Z���ɕ\������֐�
int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "�Z�~�Q�[��");

	//�C�x���g����
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

//3 * 3�̐����o�͂���֐�
void graphics(sf::RenderWindow& window)
{
	//�����̒����ƌ���
	sf::RectangleShape line(sf::Vector2f(600, 5));
	line.setFillColor(sf::Color::Black);

	//i��200����Z���邱�ƂŁA200�s�N�Z�����Ƃɏc�ɐ��������Ă���
	for (int i = 1; i <= 2; i++)
	{
		line.setSize(sf::Vector2f(600, 5));
		line.setPosition(0, i * 200);
		window.draw(line);
	}

	//����������
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

//�N���b�N�ŁZ��\��
void placeCircleOnClick(sf::RenderWindow& window, int board[3][3])
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //���N���b�N���Ă���
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


