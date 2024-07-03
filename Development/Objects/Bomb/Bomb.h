#pragma once

#include "../GameObjects.h"
#include "../../Utility/Vector2D.h"

class Bomb : public GameObject
{
private:
	
	Vector2D direction;			//�i�s����
	Vector2D velocity;			//���x
	int animation[3];
	int animation_count;		//�A�j���[�V��������
	int flip_flag;

public:
	Bomb();
	~Bomb();

	//����������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update() override;
	//�`�揈��
	virtual void Draw() const override;
	//�I��������
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	//�i�s�����w�菈��
	void SetDirection(const Vector2D& direction);

private:
	//�ړ�����
	void Movement();

	//
	void AnimeControl();
};