#include "Scene.h"

#include "../Objects/Enemy/BoxEnemy.h"
#include "../Objects/Bomb/Bomb.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include "../Utility/Vector2D.h"

//�R���X�g���N�^
Scene::Scene() : objects(), image(NULL), sound(NULL), UI_image(NULL), Time10(0), Time1(0), animation_count(0), i(0), j(0)
{
	for (int i = 0; i <= 11; i++)
	{
		animation[i] = NULL;
	}
	animation_count = 3600;
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�摜�̓ǂݍ���
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

	//�w�i�摜�̓ǂݍ���
	image = LoadGraph("Resource/Images/BackGround.png");

	//�������ԉ摜�̓ǂݍ���
	Time10 = LoadGraph("Resource/Images/score/6.png");
	Time1 = LoadGraph("Resource/Images/score/0.png");

	//BGM�̓ǂݍ���
	sound = LoadSoundMem("Resource/sounds/Evaluation/BGM_arrows.wav");

	//BGM�̍Đ�
	PlaySoundMem(sound, DX_PLAYTYPE_LOOP, TRUE);

	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 60.0f));

	//Enemy�𐶐�����
	//y���W�̈ʒu�������_���ɂ���
	int rand = GetRand(3);
	if (rand == 0)
	{
		rand = 1;
	}


	//- (rand * 100)
	//�n�R�e�L
	CreateObject<BoxEnemy>(Vector2D(320.0f, 400.0f));
	
	//�G���[�`�F�b�N
	for (int i = 0; i <= 11; i++)
	{
		if (animation[i] == -1)
		{
			throw("UI�̉摜������܂���\n");
		}
	}

}

//�X�V����
void Scene::Update()
{

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//Z�L�[�������ꂽ�Ƃ��G�̒e�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		Vector2D enemylocation = objects[1]->GetLocation();

	}

		//�v���C���[�̈ʒu�ɔ��e�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		//�v���C���[�̈ʒu���擾
		Vector2D playerlocation = objects[0]->GetLocation();

		Bomb* bomb = CreateObject<Bomb>(Vector2D(playerlocation.x,120.0f));

		//���e�̕�����ݒ�
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

	//�I�u�W�F�N�g���m�̂����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0.0f, 0.0f, 640.0f, 480.0f, image, TRUE);

	//�^�C�}�[�̕\��
	DrawRotaGraphF(10, 400, 1.0, 0, Time10, TRUE, FALSE);
	DrawRotaGraphF(20, 400, 1.0, 0, Time1, TRUE, FALSE);

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Scene::Finalize()
{
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̊J��
	objects.clear();
}

//�����蔻��`�F�b�N�擾(��`�̒��S�œ����蔻������)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

