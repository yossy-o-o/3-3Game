
//やること
//1, 適当に600 * 600のピクセルをwindowで開く
//2, windowを開き続ける
//3, いったん×押したら閉じるようにする
//4, window全体を白に塗りつぶす
//5, クリック処理を実装する
//6. クリックしたら〇を出す
//7. sfで左クリック取得
//8. クリックしたら、は入れるを受け取って、入ってるか入ってないかを確認
//9. 入っていたら、1、入ってなかったら0

#include <SFML/Graphics.hpp>

// ゲーム盤の状態：0 = 空、1 = 〇、2 = ×
int board[3][3] = { 0 };

// 今どちらの番か：true = 〇の番、false = ×の番
bool isCircleTurn = true;

// クリックされたとき、〇または×を盤に置く
void placeCircleOnClick(sf::RenderWindow& window, int board[3][3])
{
    static bool wasPressed = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!wasPressed)
        {
            wasPressed = true;

            // マウスの位置を取得
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int col = mousePos.x / 200;
            int row = mousePos.y / 200;

            // 範囲内かつ未使用マスなら配置
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
        wasPressed = false; // 離されたら次のクリックを受け付ける
    }
}

// 盤面とプレイヤー記号（〇×）の描画
void graphics(sf::RenderWindow& window)
{
    // グリッド線
    sf::RectangleShape line(sf::Vector2f(600, 5));
    line.setFillColor(sf::Color::Black);

    // 横線
    for (int i = 1; i <= 2; i++)
    {
        line.setSize(sf::Vector2f(600, 5));
        line.setPosition(0, i * 200);
        window.draw(line);
    }

    // 縦線
    line.setSize(sf::Vector2f(5, 600));
    for (int i = 1; i <= 2; i++)
    {
        line.setPosition(i * 200, 0);
        window.draw(line);
    }

    // マス内の〇×を描画
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if (board[row][col] == 1)
            {
                // ○を描画
                sf::CircleShape circle(60);
                circle.setFillColor(sf::Color::Transparent);
                circle.setOutlineColor(sf::Color::Red);
                circle.setOutlineThickness(5);
                circle.setPosition(col * 200 + 40, row * 200 + 40);
                window.draw(circle);
            }
            else if (board[row][col] == 2)
            {
                // ×を描画（交差する2本の線）
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
    // 横方向のチェック
    for (int row = 0; row < 3; ++row)
    {
        if (board[row][0] != 0 &&
            board[row][0] == board[row][1] &&
            board[row][1] == board[row][2])
        {
            return board[row][0];
        }
    }

    // 縦方向のチェック
    for (int col = 0; col < 3; ++col)
    {
        if (board[0][col] != 0 &&
            board[0][col] == board[1][col] &&
            board[1][col] == board[2][col])
        {
            return board[0][col];
        }
    }

    // 斜め（左上 → 右下）
    if (board[0][0] != 0 &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        return board[0][0];
    }

    // 斜め（右上 → 左下）
    if (board[0][2] != 0 &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        return board[0][2];
    }

    return 0; // 勝者なし
}

// メイン関数
int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "〇×ゲーム");

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

        // 勝者が出ていないときだけクリックを受け付ける
        int winner = checkWinner(board);
        if (winner == 0)
        {
            placeCircleOnClick(window, board);
        }

        graphics(window);

        // ウィンドウのタイトルで勝敗を表示
        if (winner == 1)
            window.setTitle("Player O Wins!");
        else if (winner == 2)
            window.setTitle("Player X Wins!");

        window.display();
    }

    return 0;
}
