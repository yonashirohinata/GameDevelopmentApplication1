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
		case eDIE:
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
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		//当たり判定情報お取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		//最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		//Enemyからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point = this->location;
		Vector2D dv = this->location - near_point;

		//めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		//diffの分だけ戻る
		location += dv.Normalize() * diff;
	}

	//プレイヤーがパワーアップ状態かつ、当たったオブジェクトがプレイヤーだったら
	if (/*プレイヤーがパワーアップした時かつ*/hit_object->GetCollision().object_type == eObjectType::player)
	{
		enemy_state = eEnemyState::eDIE;
	}
}

/// <summry>
/// エネミーの状態を取得する
/// </summry>
/// <returns>エネミーの状態</returns>
eEnemyState EnemyBase::GetEnemyState() const
{
	return enemy_state;
}

void EnemyBase::Movement(float delta_second)
{
	
}

/// <summry>
/// アニメーション制御
/// </summry>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::AnimationControl(float delta_second)
{
	//移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		//画像の設定
		int dir_num = (int)now_direction_state;
		if (0 <= dir_num && dir_num < 4)
		{
			image = move_animation[(dir_num * 3) + animation_num[animation_count]];
		}
	}
}