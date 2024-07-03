#pragma once

#include "../GameObjects.h"
#include "../../Utility/Vector2D.h"

class Bomb : public GameObject
{
private:
	
	Vector2D direction;			//進行方向
	Vector2D velocity;			//速度
	int animation[3];
	int animation_count;		//アニメーション時間
	int flip_flag;

public:
	Bomb();
	~Bomb();

	//初期化処理
	virtual void Initialize() override;
	//更新処理
	virtual void Update() override;
	//描画処理
	virtual void Draw() const override;
	//終了時処理
	virtual void Finalize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

	//進行方向指定処理
	void SetDirection(const Vector2D& direction);

private:
	//移動処理
	void Movement();

	//
	void AnimeControl();
};