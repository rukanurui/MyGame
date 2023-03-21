#pragma once

class BaseScene
{
public:
	//åªç›èCê≥íÜÇÃÇΩÇﬂégópÇπÇ∏
	virtual void Initialize();
	
	virtual void Update();

	virtual void Draw();

	virtual void Finalize();

	virtual ~BaseScene() = default;
};

