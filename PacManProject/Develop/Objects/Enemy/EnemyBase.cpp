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
		case DIE:
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
}