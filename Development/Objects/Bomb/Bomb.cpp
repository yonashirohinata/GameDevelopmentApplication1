#include "Bomb.h"
#include "DxLib.h"
#include "../../Utility/InputControl.h"
#include <cmath>

//�R���X�g���N�^
Bomb::Bomb() : animation_count(0), direction(0.0f), velocity(0.0f), flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
}

//�f�X�g���N�^
Bomb::~Bomb()
{

}

//����������
void Bomb::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Image/Blast/1.png");
	animation[1] = LoadGraph("Resource/Image/Blast/2.png");
	animation[1] = LoadGraph("Resource/Image/Blast/3.png");

	//�����摜�̐ݒ�
	image = animation[0];

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("���e�̉摜������܂���");
	}
	
	//���e�̕�����ݒ�
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

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����i�s�����̐ݒ�
	direction = Vector2D(0.0f, 1.0f);
}

//�X�V����
void Bomb::Update()
{
	//�ړ�����
	Movement();
}

//�`�揈��
void Bomb::Draw() const
{
	
	//������ɔ��e�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, flip_flag);

	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(255, 0, 0), FALSE);

#endif

}

//�I��������
void Bomb::Finalize()
{
	//�g�p�����摜���J��
	DeleteGraph(image);
}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	direction = 0.0f;
	AnimeControl();
}

//�V�����@��ݒ肷��֐�
void Bomb::SetDirection(const Vector2D& direction)
{
	this->direction = direction;
	this->velocity = direction * 5.0f;
}

//�ړ�����
void Bomb::Movement()
{
	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�A�j���[�V��������
void Bomb::AnimeControl()
{
	//�J�E���g�̃��Z�b�g
	animation_count = 0;

	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�摜�̐؂�ւ�
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
