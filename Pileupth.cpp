#include "File.h"
#include <time.h>

int main()
{
    srand(time(NULL));

    RenderWindow window(VideoMode(400, 600), "PILE UP 2019                       Made by Datumi", Style::Close);
    window.setFramerateLimit(60);

    Texture backGround, playButton, ques, mark;
    backGround.loadFromFile("Images/1.png");
    playButton.loadFromFile("Images/PlayButton.png");
    ques.loadFromFile("Images/3.png");
    mark.loadFromFile("Images/Question.png");

    Sprite background(backGround), playbutton(playButton), Ques(ques), Mark(mark);
    playbutton.setPosition(148, 271);
    Mark.setPosition(183, 350);

    SoundBuffer play;
    play.loadFromFile("Musics/Play.wav");
    Sound Play(play);

    while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
        window.clear();
		window.draw(background);
		window.draw(playbutton);
		window.draw(Mark);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Mouse::getPosition(window).x >= 148 && Mouse::getPosition(window).x <= 252
				&& Mouse::getPosition(window).y >= 271 && Mouse::getPosition(window).y <= 329) playGame(window);
		}

        if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Mouse::getPosition(window).x >= 183 && Mouse::getPosition(window).x <= 223
				&& Mouse::getPosition(window).y >= 350 && Mouse::getPosition(window).y <= 390) Ans(window);
		}

		window.display();
	}

    return 0;
}
