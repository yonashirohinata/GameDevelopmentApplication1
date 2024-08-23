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
	//�A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png");
	eye_animation = rm->GetImages("Resource/Images/eyes.png");

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	//���C���[�̐ݒ�
	z_layer = 5;

	//�����̐ݒ�
	mobility = eMobilityType::Movable;
}

void EnemyBase::Update(float delta_second)
{
	switch (enemy_state)
	{
		case eEnemyState::STAY:
			//�摜�̐ݒ�
			Stay(delta_second);
			break;
		case TERRITORY:
			//�꒣���Ԃ̈ړ�����
			Territory(delta_second);
			//�A�j���[�V��������
			AnimationControl(delta_second);
			break;
		case CHASE:
			//�ǐՏ�Ԃ̈ړ�����
			Chase(delta_second);
			//�A�j���[�V��������
			AnimationControl(delta_second);
			break;
		case IZIKE:
			//�C�W�P��Ԃ̈ړ�����
			Izike(delta_second);
			//�A�j���[�V��������
			AnimationControl(delta_second);
			break;
		case eDIE:
			//���S���̈ړ�����
			Die(delta_second);
			//�A�j���[�V��������
			AnimationControl(delta_second);
			break;
		default:
			break;
	}
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void EnemyBase::Finalize()
{
	//���I�z��̉��
	move_animation.clear();
	eye_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	//���������I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		//�����蔻���񂨎擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		//�ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		//Enemy����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point = this->location;
		Vector2D dv = this->location - near_point;

		//�߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		//diff�̕������߂�
		location += dv.Normalize() * diff;
	}

	//�v���C���[���p���[�A�b�v��Ԃ��A���������I�u�W�F�N�g���v���C���[��������
	if (/*�v���C���[���p���[�A�b�v����������*/hit_object->GetCollision().object_type == eObjectType::player)
	{
		enemy_state = eEnemyState::eDIE;
	}
}

/// <summry>
/// �G�l�~�[�̏�Ԃ��擾����
/// </summry>
/// <returns>�G�l�~�[�̏��</returns>
eEnemyState EnemyBase::GetEnemyState() const
{
	return enemy_state;
}

void EnemyBase::Movement(float delta_second)
{
	
}

/// <summry>
/// �A�j���[�V��������
/// </summry>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::AnimationControl(float delta_second)
{
	//�ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		//�摜�̐ݒ�
		int dir_num = (int)now_direction_state;
		if (0 <= dir_num && dir_num < 4)
		{
			image = move_animation[(dir_num * 3) + animation_num[animation_count]];
		}
	}
}