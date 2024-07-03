#include "Scene.h"

#include "../Objects/Enemy/BoxEnemy.h"
#include "../Objects/Bomb/Bomb.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include "../Utility/Vector2D.h"

//コンストラクタ
Scene::Scene() : objects(), image(NULL), sound(NULL), UI_image(NULL), Time10(0), Time1(0), animation_count(0), i(0), j(0)
{
	for (int i = 0; i <= 11; i++)
	{
		animation[i] = NULL;
	}
	animation_count = 3600;
}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Score/0.png");
	animation[1] = LoadGraph("Resource/Images/Score/1.png");
	animation[2] = LoadGraph("Resource/Images/Score/2.png");
	animation[3] = LoadGraph("Resource/Images/Score/3.png");
	animation[4] = LoadGraph("Resource/Images/Score/4.png");
	animation[5] = LoadGraph("Resource/Images/Score/5.png");
	animation[6] = LoadGraph("Resource/Images/Score/6.png");
	animation[7] = LoadGraph("Resource/Images/Score/7.png");
	animation[8] = LoadGraph("Resource/Images/Score/8.png");
	animation[9] = LoadGraph("Resource/Images/Score/9.png");
	animation[10] = LoadGraph("Resource/Images/Score/font-21.png");
	animation[11] = LoadGraph("Resource/Images/Score/hs.png");

	//背景画像の読み込み
	image = LoadGraph("Resource/Images/BackGround.png");

	//初期時間画像の読み込み
	Time10 = LoadGraph("Resource/Images/score/6.png");
	Time1 = LoadGraph("Resource/Images/score/0.png");

	//BGMの読み込み
	sound = LoadSoundMem("Resource/sounds/Evaluation/BGM_arrows.wav");

	//BGMの再生
	PlaySoundMem(sound, DX_PLAYTYPE_LOOP, TRUE);

	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 60.0f));

	//Enemyを生成する
	//y座標の位置をランダムにする
	int rand = GetRand(3);
	if (rand == 0)
	{
		rand = 1;
	}


	//- (rand * 100)
	//ハコテキ
	CreateObject<BoxEnemy>(Vector2D(320.0f, 400.0f));
	
	//エラーチェック
	for (int i = 0; i <= 11; i++)
	{
		if (animation[i] == -1)
		{
			throw("UIの画像がありません\n");
		}
	}

}

//更新処理
void Scene::Update()
{

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//Zキーが押されたとき敵の弾を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		Vector2D enemylocation = objects[1]->GetLocation();

	}

		//プレイヤーの位置に爆弾を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		//プレイヤーの位置を取得
		Vector2D playerlocation = objects[0]->GetLocation();

		Bomb* bomb = CreateObject<Bomb>(Vector2D(playerlocation.x,120.0f));

		//爆弾の方向を設定
		if (InputControl::GetKey(KEY_INPUT_LEFT))
		{
			bomb->SetDirection(Vector2D(-1.0f, 1.0f));
		}
		else if (InputControl::GetKey(KEY_INPUT_RIGHT))
		{
			bomb->SetDirection(Vector2D(1.0f, 1.0f));
		}
		else
		{
			bomb->SetDirection(Vector2D(0.0f,1.0f));
		}
	}

	//オブジェクト同士のあたり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

}

//描画処理
void Scene::Draw() const
{
	//背景画像の描画
	DrawExtendGraph(0.0f, 0.0f, 640.0f, 480.0f, image, TRUE);

	//タイマーの表示
	DrawRotaGraphF(10, 400, 1.0, 0, Time10, TRUE, FALSE);
	DrawRotaGraphF(20, 400, 1.0, 0, Time1, TRUE, FALSE);

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
void Scene::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の開放
	objects.clear();
}

//当たり判定チェック取得(矩形の中心で当たり判定を取る)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

