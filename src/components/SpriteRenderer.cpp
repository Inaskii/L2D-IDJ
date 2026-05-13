#include "../../include/SpriteRenderer.h"
#include "../../include/GameObject.h"


SpriteRenderer::SpriteRenderer(GameObject &associated)
	: Component(associated),
		sprite(),
		frameCountW(1),
		frameCountH(1)
{
}

SpriteRenderer::SpriteRenderer(GameObject &associated, std::string file, int frameCountW, int frameCountH)
	: Component(associated),
		sprite(),
		frameCountW(frameCountW),
		frameCountH(frameCountH)
{
	Open(file);
}
void SpriteRenderer::Start(){}

void SpriteRenderer::Open(std::string file)
{
	sprite.Open(file);
	SetFrame(0);
	if(!sprite.isOpen()) std::cout<<"Erro ao abrir " << file<<std::endl;
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH)
{
	if (frameCountW <= 0) frameCountW = 1;
	if (frameCountH <= 0) frameCountH = 1;

	sprite.setFrameCount(this->frameCountW, this->frameCountH);
	SetFrame(0);
}

void SpriteRenderer::Update(float dt)
{
}

void SpriteRenderer::Render()
{
	if (!sprite.isOpen()) {
		return;
	}

	sprite.Render(
			associated.box.x,
			associated.box.y,
				associated.box.w,
				associated.box.h,
				rad2Deg(associated.rotation));
}

		void SpriteRenderer::NotifyCollision(GameObject& other)
		{
		}

void SpriteRenderer::SetFrame(int frame)
{
	if (!sprite.isOpen()) {
		return;
	}

	int totalFrames = frameCountW * frameCountH;


	frame %= totalFrames;
	if (frame < 0) {
		frame += totalFrames;
	}

	int frameWidth = sprite.GetWidth() / frameCountW;
	int frameHeight = sprite.GetHeigth() / frameCountH;
	int frameX = (frame % frameCountW) * frameWidth;
	int frameY = (frame / frameCountW) * frameHeight;

	sprite.SetClip(frameX, frameY, frameWidth, frameHeight);

	associated.box.w = frameWidth;
	associated.box.h = frameHeight;
}
void SpriteRenderer::SetCameraFollower(bool b)
{
	sprite.cameraFollower = b;
}

void SpriteRenderer::FlipX(bool f)
{
	sprite.FlipX(f);
}
void SpriteRenderer::FlipY(bool f)
{
	sprite.FlipY(f);
}