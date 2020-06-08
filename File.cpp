#include "File.h"

int highscore = 0;

void Ans(RenderWindow& window)
{
    Texture ques, mark, quit, left, right, attention, flat, play, instruction;
    ques.loadFromFile("Images/3.png");
    mark.loadFromFile("Images/Question.png");
    quit.loadFromFile("Images/Quit.png");
    left.loadFromFile("Images/Left.png");
    right.loadFromFile("Images/Right.png");
    attention.loadFromFile("Images/Attention.png");
    flat.loadFromFile("Images/Flat.png");
    play.loadFromFile("Images/2.png");
    instruction.loadFromFile("Images/Instruction.png");

    Sprite Ques(ques), Mark(mark), Quit(quit), Left(left), Right(right);
    Sprite Attention(attention), Flat(flat), Play(play), Instruction(instruction);
    Mark.setPosition(360, 0);
    Quit.setPosition(360, 0);
    Left.setPosition(70, 205);
    Right.setPosition(70, 240);
    Attention.setPosition(5, 300);
    Flat.setPosition(180, 275);
    Play.setPosition(163, 200);
    Instruction.setPosition(50, 125);

    string instructions = " Press       = Move          left; \n Press       = Move          right; \n Each time, touch                  SCORE += 1;\n      If you jump into black hole, you die.";

    Font font;
	font.loadFromFile("Images/Lobs.ttf");

	Text instruct;
	instruct.setFont(font);
	instruct.setFillColor(Color(36, 79, 95, 244));
	instruct.setPosition(0, 200);
	instruct.setCharacterSize(25);
	instruct.setString(instructions);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}

		window.clear();
		window.draw(Ques);
		window.draw(Instruction);
		window.draw(instruct);
		window.draw(Quit);
		window.draw(Play);
		window.draw(Left);
		window.draw(Right);
		window.draw(Flat);
		window.draw(Attention);
		window.display();
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Mouse::getPosition(window).x >= 360 && Mouse::getPosition(window).x <= 400
            && Mouse::getPosition(window).y >= 0 && Mouse::getPosition(window).y <= 40) return;
		}
	}

}

void playGame(RenderWindow& window)
{
    bool gameOver = false;

    Music music;
    music.openFromFile("Musics/BLACKPINK.wav");
    music.setVolume(100);
    music.play();

    SoundBuffer swin, slose, snote;
    swin.loadFromFile("Musics/Win.wav");
    slose.loadFromFile("Musics/Lose.wav");
    snote.loadFromFile("Musics/pianonote.wav");
    Sound Win(swin), Lose(slose), Note(snote);
    Win.setVolume(20);
    Lose.setVolume(100);
    Note.setVolume(100);

    Texture back, base, player, quit, tScore, lose, replay, hole, home;
    back.loadFromFile("Images/3.png");
    base.loadFromFile("Images/Base.png");
    player.loadFromFile("Images/2.png");
	quit.loadFromFile("Images/Quit.png");
	tScore.loadFromFile("Images/SCORE.png");
    lose.loadFromFile("Images/GameOver.png");
    replay.loadFromFile("Images/Replay.png");
    hole.loadFromFile("Images/Hole.png");
    home.loadFromFile("Images/Home.png");

    Sprite sBackground(back), sBase(base), sPlay(player), sQuit(quit), sScore(tScore);
    Sprite sLose(lose), sReplay(replay), sHole(hole), sHome(home);
    sQuit.setPosition(360, 0);
    sScore.setPosition(0, 0);

    Font font;
	font.loadFromFile("Images/zorque.ttf");

    int score = 0;
	Text Score, High;
	Score.setFont(font);
	High.setFont(font);
	Score.setFillColor(Color(36, 79, 95, 244));
	High.setFillColor(Color(36, 79, 95, 244));
	Score.setString(to_string(score));
	Score.setPosition(120, 12);

    // Set up randomly base's coordinates
    coordinate plat[11];
    for (int i = 0; i < 10; i++)
      {
       plat[i].x = rand() % 320 + rand() % 20;
       plat[i].y = rand() % 60 + rand() % 20 + 80 + i * 60 - rand() % 50;
       /*plat[i].x = rand() % 340;
       plat[i].y = rand() % 600;*/
      }
    // Black hole
    coordinate Hole;
    Hole.x = rand() % 400;
    Hole.y = rand() % 200;

	int x = 170, y = 220, h = 250, delay = -1;
    float dy = 0;

    while (window.isOpen() && gameOver != true)
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) x += 2;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 2;

        //Jump up/down
        dy += 0.2;
        y += dy;

        if (y >= 545)
        {
            gameOver = true;
            Lose.play();
            music.stop();
        }

        //Jump into base
        for (int i = 0; i < 10; i++)
        {
            if ((x > plat[i].x - 50) && (x < plat[i].x + 58)
            && (y > plat[i].y - 60) && (y + 60 < plat[i].y + 13) && (dy > 0))
            {
                dy = -10;
                if (i != delay)
                {
                    score ++;
                    Win.play();
                }
                delay = i;
                Score.setString(to_string(score));
            }
        }
        //Touch black hole
        if ((x > Hole.x - 50) && (x < Hole.x + 25) && (y > Hole.y - 50) && (y < Hole.y + 25))
        {
            gameOver = true;
            Lose.play();
            music.stop();
        }
        //Change coordinates
        if (y < h)
        {
            for (int i = 0; i < 10; i++)
            {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 600)
                {
                    plat[i].y = 0;
                    //plat[i].x = rand() % 340;
                    plat[i].x = rand() % 300 + rand()% 40 ;
                }
            }
            Hole.y = Hole.y - dy;
            if (Hole.y > 600)
            {
                Hole.y = 0;
                Hole.x = rand() % 400;
            }
        }

        if (x < 0) x = 340;
        if (x > 340) x = 0;

        sPlay.setPosition(x,y);

        window.draw(sBackground);
        window.draw(sPlay);
        window.draw(sQuit);
        window.draw(sScore);
        window.draw(Score);

        //Random base's coordinates
        for (int i = 0; i < 10; i++)
        {
            sBase.setPosition(plat[i].x, plat[i].y);
            window.draw(sBase);
        }
        sHole.setPosition(Hole.x, Hole.y);
        window.draw(sHole);
        music.setLoop(true);
        window.display();

        // Exit game
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Mouse::getPosition(window).x >= 360 && Mouse::getPosition(window).x <= 400 &&
				Mouse::getPosition(window).y >= 0 && Mouse::getPosition(window).y <= 40)
				return;
		}
    }
    // Replay game
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}

		if (highscore < score) highscore = score;
		Score.setCharacterSize(35);
        Score.setPosition(65, 280);
        High.setPosition(75, 250);
        High.setCharacterSize(35);
		Score.setString("YOUR SCORE: " + to_string(score));
		High.setString("HIGH SCORE: " + to_string(highscore));

		sReplay.setPosition(240, 480);
		sHome.setPosition(200, 480);

		window.clear();
		window.draw(sLose);
		window.draw(sReplay);
		window.draw(sHome);
		window.draw(Score);
		window.draw(High);
		window.display();
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Mouse::getPosition(window).x >= 240 && Mouse::getPosition(window).x <= 280
            && Mouse::getPosition(window).y >= 480 && Mouse::getPosition(window).y <= 520) return playGame(window);
            else if (Mouse::getPosition(window).x >= 200 && Mouse::getPosition(window).x <= 240 &&
                     Mouse::getPosition(window).y >= 480 && Mouse::getPosition(window).y <= 520) return;
		}
	}
}
