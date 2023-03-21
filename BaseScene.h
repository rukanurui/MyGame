#pragma once

class BaseScene
{
public:
	//現在修正中のため使用せず
	virtual void Initialize();
	
	virtual void Update();

	virtual void Draw();

	virtual void Finalize();

	virtual ~BaseScene() = default;
};

