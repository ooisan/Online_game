#include <Siv3d.hpp>
#include "Char.hpp"
#include "Common.hpp"

//*******************//
//       Normal
//*******************//

Normal::Normal(Hero& _hero)
{
	hero = _hero;
	herop2 = hero.getP2body();
	d_watch.start();
	setP2body(p2world.createCircle(P2BodyType::Kinematic, hero.getP2body().getPos(), 5));

}

bool Normal::update()
{
	getP2body().setVelocity(Vec2(1000, 0));
	getP2body().draw();
	if (d_watch.s() > 1)
	{
		return false;
	}else
	{
		return true;
	}
}

//*******************//
//       ob
//*******************//

ob::ob()
{
	obj = p2world.createRect(P2BodyType::Static, Scene::Center() + Vec2(0, 2400), 4400, P2Material{.friction=1.0});
	kabes.push_back(p2world.createRect(P2BodyType::Static, Scene::Center() + Vec2(4000, 0), 3600, P2Material{ .friction = 1.0 }));
	kabes.push_back(p2world.createRect(P2BodyType::Static, Scene::Center() + Vec2(-4000, 0), 3600, P2Material{ .friction = 1.0 }));
}

void ob::update()
{
	obj.draw();
	for(const auto& kabe:kabes)
	{
		kabe.draw();
	}
}


//*******************//
//       Hero
//*******************//

Hero::Hero()
{
	maxHp = 100;
	Hp = maxHp;
	size = 10;
	circle = p2world.createCircle(P2BodyType::Dynamic , Scene::Center(),10, P2Material{ .friction = 1.0 });
	speed = 200;
}

void Hero::update()
{
	if(KeyQ.down())
	{
		bullets.push_back(new Normal(circle.getPos()));
	}
	Vec2 vector = Vec2((KeyRight.pressed() - KeyLeft.pressed()) * speed, 0 /*(KeyDown.pressed() - KeyUp.pressed()) * speed*/);
	circle.applyForce(vector);

	Print << circle.getPos();
	if(KeySpace.pressed()&&circle.getPos().y>618/*p2world.getCollisions().contains(P2ContactPair(ob::obj.id(),circle.id()))*/)
	{
		circle.applyForce(Vec2(0, -1200));
	}
	//if (circle.intersects(Rect(0, 500, 800, 1800))&& (490 - circle.center.y)<3)
	//{
	//	circle.moveBy(0,490 - circle.center.y);
	//}
	Circle(Scene::CenterF(), 5).draw();
	circle.draw();

	circle.setVelocity(Vec2(circle.getVelocity().x * 0.96, circle.getVelocity().y));

	for (auto it = bullets.begin(); it != bullets.end();)
	{
		// 円がクリックされたらその地点を表す要素を削除
		if (!( * it)->update())
		{
			// 現在のイテレータが指す要素を削除し、イテレータを進める
			it = bullets.erase(it);
		}
		else
		{
			// イテレータを進める
			++it;
		}
	}
}
void Hero::draw()
{
	Rect(20, 20, 600 * ( Hp / maxHp), 20).draw(Palette::Green);
}

P2Body& Hero::getP2body()
{
	return circle;
}
