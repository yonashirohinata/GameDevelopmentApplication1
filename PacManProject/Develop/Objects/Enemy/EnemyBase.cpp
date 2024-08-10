#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

EnemyBase::EnemyBase() : 
	move_animation(),
	eye_animation(),
	velocity(1.0f),
	enemy_state(eEnemyState::STAY),
	now_direction_state(eDirectionState::LEFT),
	animation_time(0.0f),
	animation_count(0),
	change_time(0.0f),
	change_count(0.0f)
{

}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Initialize()
{
	//アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png");
	eye_animation = rm->GetImages("Resource/Images/eyes.png");

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	//レイヤーの設定
	z_layer = 5;

	//可動性の設定
	mobility = eMobilityType::Movable;
}

void EnemyBase::Update(float delta_second)
{
	switch (enemy_state)
	{
		case eEnemyState::STAY:
			//画像の設定
			Stay(delta_second);
			break;
		case TERRITORY:
			//縄張り状態の移動処理
			Territory(delta_second);
			//アニメーション制御
			AnimationControl(delta_second);
			break;
		case CHASE:
			//追跡状態の移動処理
			Chase(delta_second);
			//アニメーション制御
			AnimationControl(delta_second);
			break;
		case IZIKE:
			//イジケ状態の移動処理
			Izike(delta_second);
			//アニメーション制御
			AnimationControl(delta_second);
			break;
		case DIE:
			//死亡時の移動処理
			Die(delta_second);
			//アニメーション制御
			AnimationControl(delta_second);
			break;
		default:
			break;
	}
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	//親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

void EnemyBase::Finalize()
{
	//動的配列の解放
	move_animation.clear();
	eye_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	//当たったオブジェクトが壁だったら
}