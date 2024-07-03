#include "BoxEnemy.h"
#include "DxLib.h"

//�R���X�g���N�^
BoxEnemy::BoxEnemy() : animation_count(0), direction(0.0f), directionrand(GetRand(1))
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
BoxEnemy::~BoxEnemy()
{

}

//����������
void BoxEnemy::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");


	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�R�e�L�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, -0.5f);

	//�ړ����x�������_���Ɍ��߂�
	int speedrand = GetRand(10);
	if (speedrand <= 5)
	{
		speedrand = 5;
	}

	direction = Vector2D((speedrand / 10.0f), 0.0f);

	//�����ɍ��킹�Đi�s������ω�������
	if (directionrand == 1)
	{
		direction.x *= 1.0f;
	}
	else
	{
		direction.x *= -1.0f;
	}
}

//�X�V����
void BoxEnemy::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void BoxEnemy::Draw() const
{
	//�摜���]�t���O
	int flip_flag = FALSE;

	//�i�s�����ɂ���āA���]��Ԃ����肷��

	if (directionrand == 1)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//������Ƀn�R�e�L�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 0.7f, radian, image, TRUE, flip_flag);

	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(0, 255, 0), FALSE);

#endif
}

//�I��������
void BoxEnemy::Finalize()
{
	//�g�p�����摜���J��
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void BoxEnemy::OnHitCollision(GameObject* hit_object)
{
	int i;
	//�����������̏���
	for (i = 255; i == 0; i--)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, i);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�ړ�����
void BoxEnemy::Movement()
{
	//��ʒ[�ɓ��B������A�i�s�����𔽓]����
	if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�A�j���[�V��������
void BoxEnemy::AnimationControl()
{
	//�A�j���[�V�����J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
		//30�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//��ʂ̐؂�ւ�
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