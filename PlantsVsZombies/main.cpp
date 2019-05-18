#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;
using namespace std;

//����������� �������� �� �����
class FlowerImage {
public:
	//����������� �������� (������)
	string currentPicture;
	//C������ (������ �� ��������)
	string weapon;
	int posWeaponX;
	int posWeaponY;
	//���������� ��������
	string doing;
	//�������� ������ ������
	double dx;
	//���������������� (���������)
	bool reprinting = false;
	//������ ��������
	virtual void setModel() = 0;
	//������� ������ �������
	virtual void weaponFrom() = 0;
	//�������� ������ �������
	virtual void setSpeedDx(double) = 0;
	//��������� ����������� ��������
	virtual void setDoing() = 0;
	//���������� ����������� ����
	virtual void updateBullet(RenderWindow& window, double time) = 0;
};


//��������� ��� ����������
class SunflowerImage : public FlowerImage {
	void setDoing() {
		doing = "������";
	}
	void weaponFrom() {};
	void setSpeedDx(double a) {
		dx = a;
	}
	void setModel() {
		currentPicture = "model���������.png";
	}
	void updateBullet(RenderWindow& window, double time) {};
};

//��������� ��� �������
class PeaImage : public FlowerImage {
	void weaponFrom() {
		weapon = "�������������.png";
			//������� ������ ������� �� ��������
			posWeaponX = 100;
			posWeaponY = 28;
	}

	void setSpeedDx(double speed) {
		dx = speed;
	}

	void setDoing() {
		doing = "������";
	}
	void setModel() {
		currentPicture = "model�������.png";
	}
	void updateBullet(RenderWindow& window, double time) {
		posWeaponX += dx * time;
		//�������� ����� ��������

		Image bulletRender;
		bulletRender.loadFromFile("�������������.png");
		Texture texture;
		texture.loadFromImage(bulletRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		//�������� ����� ��������� ��� ����
		newSprite.setTextureRect(IntRect(0, 0, 40, 40));
		newSprite.setPosition(posWeaponX, posWeaponY);
		//dx = 0;
		//���������� ��� ����������
		window.draw(newSprite);
	}
};


//��������� ��� �������
class CabbageImage : public FlowerImage {
	void weaponFrom() {
		weapon = "�������������.png";
			//������� ������ ������� �� ��������
			posWeaponX = 13;
			posWeaponY = 20;
	}


	void setSpeedDx(double speed = 0.03) {
		dx = speed;
	}
	void setDoing() {
		doing = "������";
	}
	void setModel() {
		currentPicture = "model�������.png";
	}
	void updateBullet(RenderWindow& window, double time) {
		posWeaponX += dx * time;
		//�������� ����� ��������

		Image bulletRender;
		bulletRender.loadFromFile("�������������.png");
		Texture texture;
		texture.loadFromImage(bulletRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		//�������� ����� ��������� ��� ����
		newSprite.setTextureRect(IntRect(0, 0, 80, 80));
		newSprite.setPosition(posWeaponX, posWeaponY);
		//dx = 0;
		//���������� ��� ����������
		window.draw(newSprite);
	}
};

//��������� ��� �����
class NutImage : public FlowerImage {
	void setDoing() {
		doing = "������";
	}
	void weaponFrom() {};
	void setSpeedDx(double a) {};
	void setModel() {
		currentPicture = "model����.png";
	}
	void updateBullet(RenderWindow& window, double time) {};
};

//��������� ��� �������
class ActiniaImage : public FlowerImage {
	void weaponFrom() {
		weapon = "�������1.png";
			//������� ������ ������� �� ��������
			posWeaponX = 103;
			posWeaponY = 28;
	}

	void setSpeedDx(double speed = 0.03) {
		//dx = speed;
	}
	void setDoing() {
		doing = "������";
	}
	void setModel() {
		currentPicture = "model�������.png";
	}
	void updateBullet(RenderWindow& window, double time) {
		posWeaponX += dx * time;
		//�������� ����� ��������

		Image bulletRender;
		if (posWeaponX % 2 == 0)
		    bulletRender.loadFromFile("�������1.png");
		else
			bulletRender.loadFromFile("�������2.png");
		Texture texture;
		texture.loadFromImage(bulletRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		//�������� ����� ��������� ��� ����
		newSprite.setTextureRect(IntRect(0, 0, 40, 40));
		newSprite.setPosition(posWeaponX, posWeaponY);
		//���������� ��� ����������
		window.draw(newSprite);
	}

};

//��������� ��� �����
class BombImage : public FlowerImage {
	void setDoing() {
		doing = "������";
	}
	void weaponFrom() {};
	void setSpeedDx(double a) {};
	void setModel() {
		currentPicture = "model�����.png";
	}
	void updateBullet(RenderWindow& window, double time) {};
};



//��������� "������ ������" � 5 ���������� ��� ����
class FlowerPhysic {
public:
	int health;
	int damage;
	//true, ���� ����� (���������)
	bool zombieInWay;
	bool isAvialiable;
	int weaponX;
	Clock timeToCooldaun;
public:
	//���������� ��������, ����, ������
	virtual void setHealthPoint(int) = 0;
	virtual void setDamagePoint(int) = 0;
	virtual int getHealthPoint() = 0;
	virtual int getDamage() = 0;
	// ������������� ��������������
	virtual bool needToActivate(int) = 0;
	

	void ripFlower() {
		isAvialiable = false;
	}

	bool isOnMap() {
		return isAvialiable;
	}

	virtual ~FlowerPhysic() {}
};

//���������� ��� ������� �� �������

//��������� ������� �� ��������
class SunflowerPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 100) {
		health = point;
	}
	void setDamagePoint(int point = 0) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int i = 1) {
		zombieInWay = true;
		return zombieInWay;
	}

	virtual ~SunflowerPhysic() {}
};

//������� ����� ���������� (������) 
class PeaPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 150) {
		health = point;
	}
	void setDamagePoint(int point = 20) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		//x1 - ���������� �������
		//x2 - ���������� �����
		//���� ����� ������ ����, �� ��������������
		if (x2 > weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}
	virtual ~PeaPhysic() {}
};

//���� - ������� ����, ��� ������ ���������!
class NutPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 150) {
		health = point;
	}
	void setDamagePoint(int point = 0) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		//x1 - ���������� �������
		//x2 - ���������� �����
		//���� ����� ������ ����, �� ��������������
		if (x2 > weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}

	virtual ~NutPhysic() {}
};

//������� - �� ������������� �����������!
class CabbagePhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 100) {
		health = point;
	}
	void setDamagePoint(int point = 30) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		//x1 - ���������� �����
		//x2 - ���������� �����
		//���� ����� ������ , �� ��������������
		if (x2 < weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}
	virtual ~CabbagePhysic() {}
};

//������� ����� ��������, �����!
class ActiniaPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 120) {
		health = point;
	}
	void setDamagePoint(int point = 10) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		//x1 - ���������� �����
		//x2 - ���������� �����
		//���� ����� ����� �����, �� ��������������
		if (x2 < weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}
	virtual ~ActiniaPhysic() {}
};

//����� - �� � �������!
class BombPhysic : public FlowerPhysic
{
public:
	void setHealthPoint(int point = 0) {
		health = point;
	}
	void setDamagePoint(int point = 0) {
		damage = point;
	}
	int getDamage() {
		return damage;
	}
	int getHealthPoint() {
		return health;
	}
	bool needToActivate(int x2) {
		//x1 - ���������� ��������
		//x2 - ���������� �����
		//���� ����� ������ ��������, �� ��������������
		if (x2 > weaponX) {
			zombieInWay = true;
		}
		return zombieInWay;
	}

	virtual ~BombPhysic() {}
};

//����������� ������� ��������
class FlowerFactory {
public:
	virtual FlowerImage* makeFlower() = 0;
	virtual FlowerPhysic* makePhysic() = 0;
};

//������� ����������� ���������� ��������� � ��� ������
//����������, ��� ��������� ��������
class SunflowersFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new SunflowerImage();
	}
	FlowerPhysic* makePhysic() {
		return new SunflowerPhysic();
	}
};

class PeaFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new PeaImage();
	}
	FlowerPhysic* makePhysic() {
		return new PeaPhysic();
	}
};

class CabbageFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new CabbageImage();
	}
	FlowerPhysic* makePhysic() {
		return new CabbagePhysic();
	}
};

class NutFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new NutImage();
	}
	FlowerPhysic* makePhysic() {
		return new NutPhysic();
	}
};

class ActiniaFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new ActiniaImage();
	}
	FlowerPhysic* makePhysic() {
		return new ActiniaPhysic();
	}
};

class BombFactory : public FlowerFactory {
	FlowerImage* makeFlower() {
		return new BombImage();
	}
	FlowerPhysic* makePhysic() {
		return new BombPhysic();
	}
};

//�����, � ������� ���� (�����������, ������)
class FlowerPair
{
public:
	FlowerImage* image;
	FlowerPhysic* physic;
};

//����� � ����������� ����� (����������� � ������)
class Flower {
public:
	FlowerPair* createFlower(FlowerFactory& factory) {
		FlowerPair* p = new FlowerPair;
		p->image = factory.makeFlower();
		p->physic = factory.makePhysic();
		return p;
	}
};


/////////////////////////////////////////////////////////

//����� "�����"
class Zombie {
public:
	//��������� �� ��� x
	//��� ����� ������ ������ ���
	float dx;
	float dy;
	string fileName;
	//��������� ��������
	float x;
	float y;
	Sprite sprite;
	//�����������
	bool statusAviliable;
	//���������� ������ � ����
	int health;
	int damage;
	//������� ��������� �����
	bool isLive;
	//������ - ������
	bool isEaten;


	//����������� 
	Zombie(RenderWindow &window, int posLine) {
		//����� �������� ��� ������� ������
		statusAviliable = true;
		isLive = false;
		isEaten = false;
		Image ZombieRender;
		//��������� ���� ��� �����
		fileName = "zombieOnPlace.png";
		ZombieRender.loadFromFile(fileName);
		Texture texture;
		texture.loadFromImage(ZombieRender);
		sprite.setTexture(texture);
		//��������� ������� �� ����� �� ��������� (�� 5)
		srand(time(0));
		x = 1100;
		//����������� "������"
		y = 125 + (posLine - 1) * 110;
		dx = -0.01;
		sprite.setTextureRect(IntRect(0, 0, 140, 140));
		sprite.setPosition(x, y);
		health = 150;
		damage = 10;
	}

	//�������� �����
	void update(RenderWindow &window, float time) {
		x += dx * time;
		//�������� ����� ��������
		if (fileName.find("On") != -1)
			fileName = "zombieInRun.png";
		else
			fileName = "zombieOnPlace.png";

		Image ZombieRender;
		ZombieRender.loadFromFile(fileName);
		Texture texture;
		texture.loadFromImage(ZombieRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		//�������� ����� ��������� ��� �����
		newSprite.setTextureRect(IntRect(0, 0, 140, 140));
		newSprite.setPosition(x, y);
		dx = 0;
		//���������� ��� ����������
		window.draw(newSprite);

	}

	double myDamage() {
		return damage;
	}

	//������� ����������� ��� ���������� ������
	void setUnvialible() {
		statusAviliable = false;
	}

	//�������� �� �����������
	bool isAvialible() {
		return statusAviliable;
	}

	//��������� ����� (�� ������)
	void getDamage(FlowerPhysic* someFlower) {
		health -= someFlower->getDamage();
		if (health <= 0)
			ripZombie();
	}

	//������ �������� ����
	void setDamage(FlowerPhysic* someFlower) {
		someFlower->health -= damage;
		if (someFlower->health <= 0) {
			someFlower->ripFlower();
			this->isEaten = false;
		}
	}

	//����� ����
	void ripZombie() {
		statusAviliable = false;
	}

	bool isZombieRip() {
		return statusAviliable;
	}

	//����� �������� ��� ���
	void setNextPictureEating(RenderWindow& window) {
		//�������� ����� ��������
		if (fileName.find("���") == -1)
			fileName = "��������.png";
		else
			fileName = "zombieOnPlace.png";

		Image ZombieRender;
		ZombieRender.loadFromFile(fileName);
		Texture texture;
		texture.loadFromImage(ZombieRender);
		Sprite newSprite;
		newSprite.setTexture(texture);
		//�������� ����� ��������� ��� �����
		newSprite.setTextureRect(IntRect(0, 0, 140, 140));
		newSprite.setPosition(x, y);
		dx = 0;
		//���������� ��� ����������
		window.draw(newSprite);
	}
};

///////////////////////////////////////////
// ����� "�������"
class Car {
public:
	//��������� �� ��� x
	//��� ������ ������ �� ���
	float dx;
	string fileName;
	//��������� ��������
	float x;
	float y;
	Sprite sprite;
	bool isRunningStatus;

	//����������� 
	Car(RenderWindow &window, int numberCar) {
		Image car;
		//��������� ���� ��� �����
		car.loadFromFile("model�����.png");
		Texture texture;
		texture.loadFromImage(car);
		sprite.setTexture(texture);
		//���������� ������ �������� ����, ������ � ������
		sprite.setTextureRect(IntRect(0, 0, 120, 120));
		//� ������������ ���������
		auto i = numberCar;
		sprite.setPosition(190, 140 + i * 110);
		x = 190;
		y = 140 + i * 110;
		dx = 0.1;
		isRunningStatus = false;
		window.draw(sprite);
	}
	//�������� ������ (�������� ������)
	void update(RenderWindow &window, float time, int num) {
		x += dx * time;

		Image car;
		//��������� ���� ��� �����
		car.loadFromFile("model�����.png");
		Texture texture;
		texture.loadFromImage(car);
		sprite.setTexture(texture);
		//���������� ������ �������� ����, ������ � ������
		sprite.setTextureRect(IntRect(0, 0, 120, 120));

		//�������� ����� ��������� ��� ������
		sprite.setPosition(x, y);
		dx = 0;
		//���������� ��� ����������
		window.draw(sprite);
	}

	bool isRun() {
		return isRunningStatus;
	}

	//�������� ������
	void carIsRunning(RenderWindow& window, int x1, vector<Zombie> &listZombies, vector<int> zombiesInLine, double time) {
		for (auto i = 0; i < zombiesInLine.size(); i++) {
			int x2 = listZombies[zombiesInLine[i]].x;
			if ((x1 > x2)&&(x1 < 1100)) {
				dx = 0.02;
				update(window, time, 0);
				listZombies[zombiesInLine[i]].isLive = false;
				listZombies[zombiesInLine[i]].health = -1;
				isRunningStatus = true;
			}
		}
	}

	void getDamage(Zombie* zombie) {
		zombie->health -= 200;
		if (zombie <= 0)
			zombie->ripZombie();
	}

};



//�������� �������� � ���� "�����"
void createMenuPause(RenderWindow &window) {
	Image pauseButtonRender;
	//��������� ���� ��� �����
	pauseButtonRender.loadFromFile("�����������.png");
	Texture texture;
	texture.loadFromImage(pauseButtonRender);
	Sprite buttonPause;
	buttonPause.setTexture(texture);
	//���������� ������ �������� ����, ������ � ������
	buttonPause.setTextureRect(IntRect(0, 0, 140, 140));
	//� ������������ �������
	buttonPause.setPosition(1000, 10);
	window.draw(buttonPause);
}

//�������� ���� � ������
void createPoints(RenderWindow &window) {
	Image pauseButtonRender;
	//��������� ���� ��� �����
	pauseButtonRender.loadFromFile("model������.png");
	Texture texture;
	texture.loadFromImage(pauseButtonRender);
	Sprite buttonPause;
	buttonPause.setTexture(texture);
	//���������� ������ �������� ����, ������ � ������
	buttonPause.setTextureRect(IntRect(0, 0, 140, 140));
	//� ������������ �������
	buttonPause.setPosition(500, 23);
	window.draw(buttonPause);
}


struct coordinats {
	int x;
	int y;
};


void heroToField(RenderWindow &window, std::string path, coordinats temp) {
	//�������� �������, ��� ������ �� ������ ���� ������
	//��������� �����
	Image hero_image;
	//��������� ���� ��� �����
	hero_image.loadFromFile(path);
	Texture texture;
	texture.loadFromImage(hero_image);
	Sprite hero;
	hero.setTexture(texture);
	//���������� ������ �������� ����, ������ � ������
	hero.setTextureRect(IntRect(0, 0, 120, 120));
	//� ������������ �������
	hero.setPosition(temp.x,temp.y);
	window.draw(hero);
}


//��������� �������� �����
void createHeroCard(RenderWindow &window, std::string path, int number_hero, vector<coordinats> &list) {
	//��������� ��������
	Image map_image;
	//��������� ���� ��� �����
	map_image.loadFromFile(path);
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(0, 95+number_hero*68);
	coordinats temp;
	temp.x = 0;
	temp.y = 95 + number_hero * 68;
	list.push_back(temp);
	window.draw(s_map);
}

//��������� ������� ����
void createBack(RenderWindow &window) {
	//��������� ����
	Image map_image;
	map_image.loadFromFile("������ ���.jpg");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(0, 0);
	window.draw(s_map);
}

//��������� �����
void createMap(RenderWindow &window) {
	//��������� �����
	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("������������.png");//��������� ���� ��� �����
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(300, 160);

	window.draw(s_map);
}


//������ �� �������� � ����� �����
bool isHitCard(coordinats temp, Vector2f click) {
    auto clickX = click.x;
    auto clickY = click.y;
	auto a = temp.y + 62 - clickY;
	return ((clickX < 106) && (temp.y + 62 - clickY > 0) && (clickY > temp.y));
}

//������� ������� "������" �� ��� ��������
FlowerPair* callObjectSunflower(Flower play, SunflowersFactory sun_factory) {
	FlowerPair* sunflower = play.createFlower(sun_factory);
	sunflower->physic->setHealthPoint(100);
	sunflower->physic->setDamagePoint(0);
	sunflower->image->setSpeedDx(0);
	sunflower->image->setModel();
	sunflower->image->reprinting = false;
	return sunflower;
}

FlowerPair* callObjectPea(Flower play, PeaFactory pea_factory) {
	FlowerPair* pea = play.createFlower(pea_factory);
	pea->physic->setHealthPoint(150);
	pea->physic->setDamagePoint(5);
	pea->image->setSpeedDx(0.1);
	pea->image->setModel();
	pea->image->weaponFrom();
	pea->image->reprinting = false;
	return pea;
}

FlowerPair* callObjectCabbage(Flower play, CabbageFactory cab_factory) {
	FlowerPair* cabbage = play.createFlower(cab_factory);
	cabbage->physic->setHealthPoint(100);
	cabbage->physic->setDamagePoint(30);
	cabbage->image->setSpeedDx(0.05);
	cabbage->image->setModel();
	cabbage->image->weaponFrom();
	cabbage->image->reprinting = false;
	return cabbage;
}

FlowerPair* callObjectNut(Flower play, NutFactory nut_factory) {
	FlowerPair* nut = play.createFlower(nut_factory);
	nut->physic->setHealthPoint(100);
	nut->physic->setDamagePoint(0);
	nut->image->setSpeedDx(0);
	nut->image->setModel();
	nut->image->reprinting = false;
	return nut;
}

FlowerPair* callObjectActinia(Flower play, ActiniaFactory act_factory) {
	FlowerPair* actinia = play.createFlower(act_factory);
	actinia->physic->setHealthPoint(100);
	actinia->physic->setDamagePoint(30);
	actinia->image->setSpeedDx(0.06);
	actinia->image->setModel();
	actinia->image->weaponFrom();
	actinia->image->reprinting = false;
	return actinia;
}

FlowerPair* callObjectBomb(Flower play, BombFactory bom_factory) {
	FlowerPair* bomb = play.createFlower(bom_factory);
	bomb->physic->setHealthPoint(1);
	bomb->physic->setDamagePoint(0);
	bomb->image->setSpeedDx(0);
	bomb->image->setModel();
	bomb->image->reprinting = false;
	return bomb;
}



int main()
{
	//�������� ����, n*n
	RenderWindow window(VideoMode(1200, 700), "Plants Vs Zombies");
	//������ ����
	Image icon;
	if (!icon.loadFromFile("icon.png"))
	{
		return 1;
	}
	window.setIcon(32, 32, icon.getPixelsPtr());
	
	///////////////////////////////////////
	//���� ���� (5*9)
	//����� 137*79 - ������� ����� �����
	//����� 41; ������ 53
	vector < vector<bool> > FIELD_GAME_STATUS;
	for (auto i = 0; i < 5; i++) {
		vector <bool> tempVector;
		for (auto j = 0; j < 9; j++) {
			tempVector.push_back(true);
		}
		FIELD_GAME_STATUS.push_back(tempVector);
	}
	bool heroIsReadyToBeStandToFeld = false;
	string heroPath;
	///////////////////////////////////////



	//����� � ������ ������� ����, ����� ��������� � ���� �����
	Clock timerStart;
	vector <int> timingsToGoZombie = { 4, 3, 2, 1, 5, 1, 1, 3, 4, 68};
	vector <int> numberWays = {1,2,2,4,1,3,2,5,4,1};
	double cooldaunShoot = 2;
	Clock timeToCooldaun;
	Clock timeMoney;
	int balance = 0;
	

	Clock clock;

	//������
	Car carOne = Car(window, 0);
	Car carTwo = Car(window, 1);
	Car carThree = Car(window, 2);
	Car carFour = Car(window, 3);
	Car carFive = Car(window, 4);

	//�����
	vector <Zombie> zombiesList;
	for (int i = 0; i < 10; ++i) {
		Zombie temp = Zombie(window, numberWays[i]);
		zombiesList.push_back(temp);
	}
	//������ ���� �� ����� 0 �����
	auto currentInRun = 0;		
	//���� ���� �����, �� ������ ��������
    //������� (��� 5 �������)
	vector<vector<int>> numberZombieInLine(5);

	for (auto i = 0; i < numberWays.size(); i++) {
		if (numberWays[i] == 1) {
			numberZombieInLine[0].push_back(i);
		}
		if (numberWays[i] == 2) {
			numberZombieInLine[1].push_back(i);
		}
		if (numberWays[i] == 3) {
			numberZombieInLine[2].push_back(i);
		}
		if (numberWays[i] == 4) {
			numberZombieInLine[3].push_back(i);
		}
		if (numberWays[i] == 5) {
			numberZombieInLine[4].push_back(i);
		}
	}


	//��������
	vector<pair<coordinats, string>> vectorFlowersToRender;
	vector<bool> bulletIsRendering;
	//6 ������ ��� ���������� ��������
	Flower play;
	SunflowersFactory sun_factory;
	PeaFactory pea_factory;
	CabbageFactory cab_factory;
	NutFactory nut_factory;
	BombFactory bomb_factory;
	ActiniaFactory act_factory;
	//���� �������
	std::vector<string> listBullets;
	vector<FlowerPair*> listFlowers;


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		float moneyTime = timeMoney.getElapsedTime().asSeconds();
		if (moneyTime > 5) {
			timeMoney.restart();
			balance += 50;
		}

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//�������� ������� ����
		createBack(window);
		vector <std::string> paths = { "�������.png", "���������.png", "�������.png", "�������.png", "�����.png", "���.png" };
		vector <coordinats> placeCards;
		//��������� �������� ������
		for (int i = 0; i < 6; i++) {
			std::string path = "card" + paths[i];
			auto number_hero = i;
			createHeroCard(window, path, number_hero + 1, placeCards);
		}
		//��������� �����
		createMap(window);
		//�������� ������ �����
		createMenuPause(window);
		//�������� ���� � "����������"
		createPoints(window);

		//���������� �����
		carOne.dx = 0;
		carTwo.dx = 0;
		carThree.dx = 0;
		carFour.dx = 0;
		carFive.dx = 0;
		if (!carOne.isRun())
		    carOne.update(window, time, 0);
		if (!carTwo.isRun())
		    carTwo.update(window, time, 1);
		if (!carThree.isRun())
		    carThree.update(window, time, 2);
		if (!carFour.isRun())
		    carFour.update(window, time, 3);
		if (!carFive.isRun())
		    carFive.update(window, time, 4);
		
		//���������� �����
		int secondsFromStart = timerStart.getElapsedTime().asSeconds();
		//���� ������� ����� ��������� �����, �� ��������� ���
		if (currentInRun != 10) {
			if ((secondsFromStart > timingsToGoZombie[currentInRun]) && (currentInRun <= 9)) {
				zombiesList[currentInRun].dx = -0.01;
				zombiesList[currentInRun].update(window, time);
				zombiesList[currentInRun].statusAviliable = false;
				zombiesList[currentInRun].isLive = true;
				zombiesList[currentInRun].isEaten = false;
				currentInRun++;
				timerStart.restart();
			}
		}
		//����������� �� ������ ���� ���, ��� ��� ���� (� �� ���)
		for (int i = 0; i < zombiesList.size(); ++i) {
			if ((zombiesList[i].statusAviliable == false) && (zombiesList[i].isEaten == false)) {
				if (zombiesList[i].isLive == false) 
					continue;
				zombiesList[i].dx = -0.01;
				zombiesList[i].update(window, time);
			}
		}
	
        //����������� �������� �� �����
		for (int i = 0; i < vectorFlowersToRender.size(); i++) {
			if (listFlowers[i]->physic->health > 0)
			    heroToField(window, vectorFlowersToRender[i].second, vectorFlowersToRender[i].first);
		}

		////////////////////////////////////////////////////////
		//����� ��������//
		bool needToShoot = true;
		//���� �� ���� ������ (�� 5)
		for (auto k = 0; k < 5; k++) {
			//���� ���� �� ���� �� ���� ����� ���� �� �����, �� ������ ��������
			for (auto i = 0; i < numberZombieInLine[k].size(); ++i) {
				//����� ������ �����, ����� ������ �������������
				if ((zombiesList[numberZombieInLine[k][i]].statusAviliable == false)&&(zombiesList[numberZombieInLine[k][i]].isLive == true)) {
					//������ ��� ������� �� ���� ����� �������� � �������� �� ��������
					for (int j = 0; j < vectorFlowersToRender.size(); j++) {
						if (listFlowers[j]->image->reprinting == false) {
							coordinats tempCoordinats = vectorFlowersToRender[j].first;
							string nameFlower = vectorFlowersToRender[j].second;
							int xHigh = 296;
							int yLeft = 162;
							int CageX = (tempCoordinats.x+20 - xHigh) / 92;
							int CageY = (tempCoordinats.y+20 - yLeft) / 107;
							//���� �������� � ���� ������, �� ��������� ��� ��������
							if (CageY == k) {
								listFlowers[j]->physic->zombieInWay = true;
								listFlowers[j]->image->posWeaponX = 296 + CageX * 92 - 20 + 100;
								listFlowers[j]->image->posWeaponY = 162 + CageY * 107;
								listFlowers[j]->image->reprinting = true;
								timeToCooldaun.restart();
								}
							}
						}
					}
				}
			}
		
		///////////////////////////////////////////////////////
		//��� �������� (�� ���) �� ����� �������������� ������ ��������, ���� �� ��� �������� �����
		for (int i=0; i < listFlowers.size(); ++i) {
			if ((listFlowers[i]->physic->zombieInWay == true)&&((listFlowers[i]->physic->health > 0))) {
				bulletIsRendering[i] = true;
			}
		}

		//������������ ��� ����
		for (int i = 0; i < bulletIsRendering.size(); ++i) {
			if (bulletIsRendering[i]) {
				if ((listFlowers[i]->physic->health > 0) && (listFlowers[i]->image->currentPicture != "model���������.png") && (listFlowers[i]->image->currentPicture != "model���.png") && (listFlowers[i]->image->currentPicture != "model�����.png")) {
					listFlowers[i]->image->dx = 0.1;
					listFlowers[i]->image->updateBullet(window, time);
					}
				}
			}
	

		//������� ���� ���� ����� (���� ���� ���������)
		for (int i = 0; i < 5; ++i) {
			for (int k = 0; k < numberZombieInLine[i].size(); ++k){
			//��� ����� �����
				if (zombiesList[numberZombieInLine[i][k]].isLive == true) {
					for (int j = 0; j < listFlowers.size(); j++)
						if ((zombiesList[numberZombieInLine[i][k]].x < listFlowers[j]->image->posWeaponX) && ((listFlowers[j]->physic->health > 0))) {
							//����� ������ ���������
							if (((vectorFlowersToRender[j].first.y-142)/107 == i)) {
									//�������� ���� �� ��������
									zombiesList[numberZombieInLine[i][k]].getDamage(listFlowers[j]->physic);
									if (zombiesList[numberZombieInLine[i][k]].health <= 0) {
										zombiesList[numberZombieInLine[i][k]].isLive = false;
										//���������� �������� ��� ��������
										listFlowers[j]->physic->zombieInWay = false;
								}
								listFlowers[j]->image->reprinting = false;
								//���� ����� ������� � ��������, �� ����� ��� ���������
								if (zombiesList[numberZombieInLine[i][k]].x <= vectorFlowersToRender[j].first.x + 60) {
									zombiesList[numberZombieInLine[i][k]].isEaten = true;
									zombiesList[numberZombieInLine[i][k]].setNextPictureEating(window);
									zombiesList[numberZombieInLine[i][k]].setDamage(listFlowers[j]->physic);
									//� ���� ��� �� ������������ ��� ������
								}
							}
						}
				}
			}
		}


		//���� ������������� ����� ��������� � ��������������� �����, �� ��� ���������� ���������
		//����������� ��� ����!
		int x1 = carOne.x + 32;
		int x2 = carTwo.x + 32;
		int x3 = carThree.x + 32;
		int x4 = carFour.x + 32;
		int x5 = carFive.x + 32;
		carOne.carIsRunning(window, x1, zombiesList, numberZombieInLine[0], time);
		carTwo.carIsRunning(window, x2, zombiesList, numberZombieInLine[1], time);
		carThree.carIsRunning(window, x3, zombiesList, numberZombieInLine[2], time);
		carFour.carIsRunning(window, x4, zombiesList, numberZombieInLine[3], time);
		carFive.carIsRunning(window, x5, zombiesList, numberZombieInLine[4], time);


		//////////////////////////////////////////////////////////
		//������� ������� ���� ��� ������� ����� ������
		//������� ������������ ��������
		bool tempBool = true;
		if (!heroIsReadyToBeStandToFeld) {
			Vector2i pixelPos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(pixelPos);
			Event eventClick;
			while (window.pollEvent(eventClick)) {
				if (eventClick.type == Event::MouseButtonPressed)
					if (eventClick.key.code == Mouse::Left) {
						for (auto i = 0; i < 6; i++)
						{
							if (isHitCard(placeCards[i], pos)) {
								//������� ��������
								heroPath = paths[i];
								//��������� �������� ���� ��� ���� ���������
								heroIsReadyToBeStandToFeld = true;
								tempBool = false;
								break;
							}
						}
					}
				if (!tempBool) break;
			}
			if (!tempBool) continue;
		}
		/////////////////////////////////////////////////////


		//������� ��������� ����� �� ����
		if (heroIsReadyToBeStandToFeld) {
			Vector2i fieldPos = Mouse::getPosition(window);
			Vector2f posField = window.mapPixelToCoords(fieldPos);
			Event eventToField;
			while (window.pollEvent(eventToField)) {
				if (eventToField.type == Event::MouseButtonPressed)
					if (eventToField.key.code == Mouse::Left) {
						//���������� ������
						int xStart = 296;
						int yStart = 162;
						int CageX = (posField.x - xStart) / 92;
						int CageY = (posField.y - yStart) / 107;
						//������ ����� �� ������� �����
						if (posField.x > 1128) break;
						if (FIELD_GAME_STATUS[CageY][CageX] == false)
							break;
						else
						{
							//�������� � ����� ������ � ��������� ��������� �����
							coordinats temp;
							temp.x = 296 + CageX * 92 - 20;
							temp.y = 162 + CageY * 107 -20;
							if (heroPath == "�������.png")
								temp.x -= 15;
							heroToField(window, "model"+heroPath, temp);
							pair<coordinats, string> tempPair(temp, "model" + heroPath);
							FlowerPair* x;
							if (heroPath == "���������.png") {
								x = callObjectSunflower(play, sun_factory);
								if (balance - 50 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 50;
							}
							if (heroPath == "�������.png") {
								x = callObjectCabbage(play, cab_factory);
								if (balance - 100 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 100;
							}
							if (heroPath == "���.png") {
								x = callObjectNut(play, nut_factory);
								if (balance - 50 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 50;
							}
							if (heroPath == "�������.png") {
								x = callObjectPea(play, pea_factory);
								if (balance - 100 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 100;
							}
							if (heroPath == "�����.png") {
								x = callObjectBomb(play, bomb_factory);
								if (balance - 25 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 25;
							}
							if (heroPath == "�������.png") {
								x = callObjectActinia(play, act_factory);
								if (balance - 175 < 0) {
									heroIsReadyToBeStandToFeld = false; break;
								}
								balance -= 175;
							}
							FIELD_GAME_STATUS[CageY][CageX] = false;
							vectorFlowersToRender.push_back(tempPair);
							listFlowers.push_back(x);
							bulletIsRendering.push_back(false);
							//����� ��� ���������
							heroIsReadyToBeStandToFeld = false;
							break;
						}
					}
			}
		}
		
		//������� ������ �� �����
		//�������� �� (600; 45)
		string sumString = std::to_string(balance);
		int startX = 600;
		int startY = 45;
		for (int i = 0; i < sumString.size(); ++i) {
			string filename;
			if (sumString[i] == '0') {
				filename = "0.png";
			}
			if (sumString[i] == '1') {
				filename = "1.png";
			}
			if (sumString[i] == '2') {
				filename = "2.png";
			}
			if (sumString[i] == '3') {
				filename = "3.png";
			}
			if (sumString[i] == '4') {
				filename = "4.png";
			}
			if (sumString[i] == '5') {
				filename = "5.png";
			}
			if (sumString[i] == '6') {
				filename = "6.png";
			}
			if (sumString[i] == '7') {
				filename = "7.png";
			}
			if (sumString[i] == '8') {
				filename = "8.png";
			}
			if (sumString[i] == '9') {
				filename = "9.png";
			}
			//��������� ����
			Image number;
			number.loadFromFile(filename);
			Texture map;
			map.loadFromImage(number);
			Sprite s_map;
			s_map.setTexture(map);
			s_map.setPosition(startX, startY);
			startX += 50;
			window.draw(s_map);
		}


		//////////////////////////////////////////////////////////
		bool isNext = true;
		string gameOverSprite;
		//���� ���� �� ���� �� ����� ����� �� ��������, �� ���������
		for (auto i = 0; i < zombiesList.size(); i++) {
			if (zombiesList[i].x < 195) {
				//��������� �������� ���������
				Image mapLose;
				mapLose.loadFromFile("��������.png");
				Texture map;
				map.loadFromImage(mapLose);
				Sprite loser;
				loser.setTexture(map);
				//� ������ �����
				loser.setPosition(0, 0);
				window.draw(loser);
			}
		}
		///////////////////////////////////////////////////////////
		//������� ������
		bool flag = true;
		int i = 0;
		for (i; i < zombiesList.size(); ++i) {
			if ((zombiesList[i].health <= 0)&&(zombiesList[i].statusAviliable == false)) continue;
			else break;
		}
		
		if (i == zombiesList.size()) {
			//��������� �������� ������
			Image mapWin;
			mapWin.loadFromFile("������.jpg");
			Texture map;
			map.loadFromImage(mapWin);
			Sprite winner;
			winner.setTexture(map);
			//� ������ �����
			winner.setPosition(0, 0);
			window.draw(winner);
		}
		//////////////////////////////////////////////////////////

		window.setSize(sf::Vector2u(550, 340));
		window.display();
	}

	return 0;

}