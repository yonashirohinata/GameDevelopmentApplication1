#include "Bomb.h"
#include "DxLib.h"
#include "../../Utility/InputControl.h"
#include <cmath>

//コンストラクタ
Bomb::Bomb() : animation_count(0), direction(0.0f), velocity(0.0f), flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
}

//デストラクタ
Bomb::~Bomb()
{

}

//初期化処理
void Bomb::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Image/Blast/1.png");
	animation[1] = LoadGraph("Resource/Image/Blast/2.png");
	animation[1] = LoadGraph("Resource/Image/Blast/3.png");

	//初期画像の設定
	image = animation[0];

	//エラーチェック
	if (image == -1)
	{
		throw("爆弾の画像がありません");
	}
	
	//爆弾の方向を設定
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		radian = -3.14 / 4;
		flip_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		radian = 3.14 / 4;
		flip_flag = FALSE;
	}
	else
	{
		radian = 3.14 / 2;
		flip_flag = FALSE;
	}

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期進行方向の設定
	direction = Vector2D(0.0f, 1.0f);
}

//更新処理
void Bomb::Update()
{
	//移動処理
	Movement();
}

//描画処理
void Bomb::Draw() const
{
	
	//情報を基に爆弾画像を描画する
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, flip_flag);

	//デバッグ用
#if _DEBUG
	//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(255, 0, 0), FALSE);

#endif

}

//終了時処理
void Bomb::Finalize()
{
	//使用した画像を開放
	DeleteGraph(image);
}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{
	direction = 0.0f;
	AnimeControl();
}

//新方向法を設定する関数
void Bomb::SetDirection(const Vector2D& direction)
{
	this->direction = direction;
	this->velocity = direction * 5.0f;
}

//移動処理
void Bomb::Movement()
{
	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void Bomb::AnimeControl()
{
	//カウントのリセット
	animation_count = 0;

	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
			if (animation_count == 20)
			{
				image = animation[2];
			}
			if (animation_count == 40)
			{
				image = animation[3];
			}
		}
		else
		{
			image = animation[0];
		}
	}
}
