#pragma once
class Bg
{
public:
	Bg();
	~Bg();

	void Init(int handle,int bgHandle);
	void End();
	void Update();
	void Draw();

private:
	int m_handle;
	int m_bgHandle;
	int m_graphChipNumX;
};

