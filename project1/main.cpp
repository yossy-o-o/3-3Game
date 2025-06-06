
//��邱��
//1, �K����600 * 600�̃s�N�Z����window�ŊJ��
//2, window���J��������
//3, ��������~�����������悤�ɂ���
//4, window�S�̂𔒂ɓh��Ԃ�
//5, �N���b�N��������������
//6. �N���b�N������Z���o��
//7. sf�ō��N���b�N�擾
//8. �N���b�N������A�͓������󂯎���āA�����Ă邩�����ĂȂ������m�F
//9. �����Ă�����A1�A�����ĂȂ�������0

#include <SFML/Graphics.hpp>

// �Q�[���Ղ̏�ԁF0 = ��A1 = �Z�A2 = �~
int board[3][3] = { 0 };

// ���ǂ���̔Ԃ��Ftrue = �Z�̔ԁAfalse = �~�̔�
bool isCircleTurn = true;

// �N���b�N���ꂽ�Ƃ��A�Z�܂��́~��Ղɒu��
void placeCircleOnClick(sf::RenderWindow& window, int board[3][3])
{
    static bool wasPressed = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!wasPressed)
        {
            wasPressed = true;

            // �}�E�X�̈ʒu���擾
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int col = mousePos.x / 200;
            int row = mousePos.y / 200;

            // �͈͓������g�p�}�X�Ȃ�z�u
            if (col >= 0 && col < 3 && row >= 0 && row < 3)
            {
                if (board[row][col] == 0)
                {
                    board[row][col] = isCircleTurn ? 1 : 2;
                    isCircleTurn = !isCircleTurn;
                }
            }
        }
    }
    else
    {
        wasPressed = false; // �����ꂽ�玟�̃N���b�N���󂯕t����
    }
}

// �Ֆʂƃv���C���[�L���i�Z�~�j�̕`��
void graphics(sf::RenderWindow& window)
{
    // �O���b�h��
    sf::RectangleShape line(sf::Vector2f(600, 5));
    line.setFillColor(sf::Color::Black);

    // ����
    for (int i = 1; i <= 2; i++)
    {
        line.setSize(sf::Vector2f(600, 5));
        line.setPosition(0, i * 200);
        window.draw(line);
    }

    // �c��
    line.setSize(sf::Vector2f(5, 600));
    for (int i = 1; i <= 2; i++)
    {
        line.setPosition(i * 200, 0);
        window.draw(line);
    }

    // �}�X���́Z�~��`��
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if (board[row][col] == 1)
            {
                // ����`��
                sf::CircleShape circle(60);
                circle.setFillColor(sf::Color::Transparent);
                circle.setOutlineColor(sf::Color::Red);
                circle.setOutlineThickness(5);
                circle.setPosition(col * 200 + 40, row * 200 + 40);
                window.draw(circle);
            }
            else if (board[row][col] == 2)
            {
                // �~��`��i��������2�{�̐��j
                sf::RectangleShape line1(sf::Vector2f(120, 5));
                sf::RectangleShape line2(sf::Vector2f(120, 5));
                line1.setFillColor(sf::Color::Blue);
                line2.setFillColor(sf::Color::Blue);

                line1.setOrigin(60, 2.5f);
                line2.setOrigin(60, 2.5f);

                float centerX = col * 200 + 100;
                float centerY = row * 200 + 100;

                line1.setPosition(centerX, centerY);
                line2.setPosition(centerX, centerY);

                line1.setRotation(45);
                line2.setRotation(-45);

                window.draw(line1);
                window.draw(line2);
            }
        }
    }
}

int checkWinner(int board[3][3])
{
    // �������̃`�F�b�N
    for (int row = 0; row < 3; ++row)
    {
        if (board[row][0] != 0 &&
            board[row][0] == board[row][1] &&
            board[row][1] == board[row][2])
        {
            return board[row][0];
        }
    }

    // �c�����̃`�F�b�N
    for (int col = 0; col < 3; ++col)
    {
        if (board[0][col] != 0 &&
            board[0][col] == board[1][col] &&
            board[1][col] == board[2][col])
        {
            return board[0][col];
        }
    }

    // �΂߁i���� �� �E���j
    if (board[0][0] != 0 &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        return board[0][0];
    }

    // �΂߁i�E�� �� �����j
    if (board[0][2] != 0 &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        return board[0][2];
    }

    return 0; // ���҂Ȃ�
}

// ���C���֐�
int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "�Z�~�Q�[��");

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

        // ���҂��o�Ă��Ȃ��Ƃ������N���b�N���󂯕t����
        int winner = checkWinner(board);
        if (winner == 0)
        {
            placeCircleOnClick(window, board);
        }

        graphics(window);

        // �E�B���h�E�̃^�C�g���ŏ��s��\��
        if (winner == 1)
            window.setTitle("Player O Wins!");
        else if (winner == 2)
            window.setTitle("Player X Wins!");

        window.display();
    }

    return 0;
}
