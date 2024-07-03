#include "BoxEnemy.h"
#include "DxLib.h"

//コンストラクタ
BoxEnemy::BoxEnemy() : animation_count(0), direction(0.0f), directionrand(GetRand(1))
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
BoxEnemy::~BoxEnemy()
{

}

//初期化処理
void BoxEnemy::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");


	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコテキの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, -0.5f);

	//移動速度をランダムに決める
	int speedrand = GetRand(10);
	if (speedrand <= 5)
	{
		speedrand = 5;
	}

	direction = Vector2D((speedrand / 10.0f), 0.0f);

	//向きに合わせて進行方向を変化させる
	if (directionrand == 1)
	{
		direction.x *= 1.0f;
	}
	else
	{
		direction.x *= -1.0f;
	}
}

//更新処理
void BoxEnemy::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void BoxEnemy::Draw() const
{
	//画像反転フラグ
	int flip_flag = FALSE;

	//進行方向によって、反転状態を決定する

	if (directionrand == 1)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//情報を基にハコテキ画像を描画する
	DrawRotaGraphF(location.x, location.y, 0.7f, radian, image, TRUE, flip_flag);

	//デバッグ用
#if _DEBUG
	//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(0, 255, 0), FALSE);

#endif
}

//終了時処理
void BoxEnemy::Finalize()
{
	//使用した画像を開放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void BoxEnemy::OnHitCollision(GameObject* hit_object)
{
	int i;
	//当たった時の処理
	for (i = 255; i == 0; i--)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, i);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//移動処理
void BoxEnemy::Movement()
{
	//画面端に到達したら、進行方向を反転する
	if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void BoxEnemy::AnimationControl()
{
	//アニメーションカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
		//30フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントのリセット
		animation_count = 0;

		//画面の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}