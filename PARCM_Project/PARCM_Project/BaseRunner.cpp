#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "BGObject.h"
#include "BackgroundImage.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"

#include <SFML/Audio.hpp>

#include "LaunchPadBase.h"
#include "AudioLooper.h"
#include "Button.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Entity Component", sf::Style::Close) {
	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	BackgroundImage* bg = new BackgroundImage("BG");
	GameObjectManager::getInstance()->addObject(bg);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

	//Launchpad
	LaunchPadBase* launchpadBase = new LaunchPadBase("LaunchPadBase");
	launchpadBase->setScale(0.8f, 0.8f);
	GameObjectManager::getInstance()->addObject(launchpadBase);


	//Audio Looper
	AudioLooper* looper = new AudioLooper("AudioLooper");
	GameObjectManager::getInstance()->addObject(looper);

	//Buttons
	int centerX = WINDOW_WIDTH / 2;
	int centerY = WINDOW_HEIGHT / 2;

	Button* button1 = new Button("Button1", looper, "Kick1");
	button1->setPosition(centerX - 500, centerY - 100);
	GameObjectManager::getInstance()->addObject(button1);

	Button* button2 = new Button("Button2", looper, "Kick2");
	button2->setPosition(centerX - 300, centerY - 100);
	GameObjectManager::getInstance()->addObject(button2);

	Button* button3 = new Button("Button3", looper, "Kick3");
	button3->setPosition(centerX - 500, centerY + 100);
	GameObjectManager::getInstance()->addObject(button3);

	Button* button4 = new Button("Button4", looper, "Kick4");
	button4->setPosition(centerX - 300, centerY + 100);
	GameObjectManager::getInstance()->addObject(button4);

	Button* button5 = new Button("Button5", looper, "Snare1");
	button5->setPosition(centerX - 100, centerY - 100);
	GameObjectManager::getInstance()->addObject(button5);

	Button* button6 = new Button("Button6", looper, "Snare2");
	button6->setPosition(centerX + 100, centerY - 100);
	GameObjectManager::getInstance()->addObject(button6);

	Button* button7 = new Button("button7", looper, "Snare3");
	button7->setPosition(centerX - 100, centerY + 100);
	GameObjectManager::getInstance()->addObject(button7);

	Button* button8 = new Button("button8", looper, "Snare4");
	button8->setPosition(centerX + 100, centerY + 100);
	GameObjectManager::getInstance()->addObject(button8);

	Button* button9 = new Button("button9", looper, "HH1");
	button9->setPosition(centerX + 300, centerY - 100);
	GameObjectManager::getInstance()->addObject(button9);

	Button* button10 = new Button("button10", looper, "HH2");
	button10->setPosition(centerX + 500, centerY - 100);
	GameObjectManager::getInstance()->addObject(button10);

	Button* button11 = new Button("button11", looper, "HH3");
	button11->setPosition(centerX + 300, centerY + 100);
	GameObjectManager::getInstance()->addObject(button11);

	Button* button12 = new Button("button12", looper, "HH4");
	button12->setPosition(centerX + 500, centerY + 100);
	GameObjectManager::getInstance()->addObject(button12);

	/*
	sf::Music* music = new sf::Music();
	if (!music->openFromFile("Media/Audio/Kick1.ogg")){
		std::cerr << "Failed to load music file" << std::endl;
	}

	music->play();
	*/
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	window.setFramerateLimit(60);

	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			processEvents();
			update(elapsedTime);
		}

		render();
	}
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if(window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			GameObjectManager::getInstance()->processInput(event);
			break;
		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}