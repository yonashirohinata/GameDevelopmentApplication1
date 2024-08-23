#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

// プレイヤー状態
enum eEnemyState
{
	STAY,			//待機状態
	TERRITORY,		//縄張り状態
	CHASE,			//追跡状態
	IZIKE,			//イジケ状態
	eDIE,			//死亡状態
};

/// <summary>
/// エネミークラス
/// </summary>
class EnemyBase : public GameObject
{
private:
	// エネミー状態
	enum eDirectionState
	{
		UP,				//上
		RIGHT,			//右
		DOWN,			//下
		LEFT,			//左
	};
private:
	std::vector<int> move_animation;
	std::vector<int> eye_animation;
	Vector2D velocity;
	eEnemyState enemy_state;
	eDirectionState now_direction_state;
	float animation_time;
	int animation_count;
	float change_time;
	float change_count;

	const int animation_num[4] = { 0,1,2,1, };

public:
	EnemyBase();
	virtual ~EnemyBase();
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

	/// <summary>
	/// エネミーの状態を取得する
	/// </summary>
	/// <returns>エネミーの状態</returns>
	eEnemyState GetEnemyState() const;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);

	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);

private:
	/// <summary>
	/// 敵モード制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void EnemyModeChange(float delta_second);

	/// <summary>
	/// 敵待機状態
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Stay(float delta_second);

	/// <summary>
	/// 敵イジケ状態
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Izike(float delta_second);

	/// <summary>
	/// 敵死亡状態
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Die(float delta_second);

public:
	/// <summary>
	/// 敵縄張り状態
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Territory(float delta_second);

	/// <summary>
	/// 敵追跡状態
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Chase(float delta_second);

};