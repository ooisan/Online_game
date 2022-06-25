#pragma once
#include<Siv3d.hpp>

class Bullet
{a
public:
	Bullet(Hero& _hero, P2Body& _herop2)
		:hero(_hero)
		, herop2(_hero.getP2body())
	{
	}
	virtual bool update() = 0;
	P2Body& getP2body()
	{
		return obj;
	};

	void setP2body(P2Body p2body)
	{
		obj = p2body;
	}
	virtual ~Bullet(){};
protected:
	P2Body obj;
	Stopwatch d_watch;
	Hero& hero;
	P2Body& herop2;
};

class Normal:public Bullet
{
public:
	Normal(Hero& hero);
	bool update()override;
private:

};

class ob
{
public:
	ob();

	void update();

	inline static P2Body obj;
	inline static Array<P2Body> kabes;
};

class Hero
{
public:
	Hero();
	void update();
	void draw();
	P2Body& getP2body();

private:

	double maxHp;
	double Hp;
	double Mp;
	double speed;
	Vec2 pos;
	double size;
	P2Body circle;
	Array<Bullet*> bullets;

};
