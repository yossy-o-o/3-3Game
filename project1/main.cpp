
//��邱��
//1, �K����600 * 600�̃s�N�Z����window�ŊJ��
//2, window���J��������
//3, ��������~�����������悤�ɂ���
//4, window�S�̂𔒂ɓh��Ԃ�

#include <SFML/Graphics.hpp>

void graphics(sf::RenderWindow& window);

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
		window.display();
	}

	return 0;
}

//3 * 3�̐����o�͂���֐�
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