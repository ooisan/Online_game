# include <Siv3D.hpp> // OpenSiv3D v0.6.3
#include "Common.hpp"
#include "Char.hpp"
void Main()
{
	Window::SetFullscreen(true);
	p2world.setGravity(800);
	Hero hero;
	ob obj;
	Camera2D cm;
	cm.setParameters(Camera2DParameters::NoControl());
	while (System::Update())
	{
		hero.draw();
		const auto ct = cm.createTransformer();
		//cm.setCenter(hero.getP2body().getPos());
		cm.setTargetCenter(hero.getP2body().getPos());
		obj.update();
		//Rect rect=Rect(0, 500, 800, 500).draw();
		hero.update();
		p2world.update();
		cm.update();
	}
}
