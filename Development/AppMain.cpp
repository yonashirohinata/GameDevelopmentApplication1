#include "DxLib.h"
#include "../BombingHunter/Sample/Utility/InputControl.h"
#include "Scene/Scene.h"

//���C���֐�(�v���O�����͂�������n�܂�܂��B)
int WINAPI WinMain(_In_ HINSTANCE hInastance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//Window���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//�E�B���h�E�T�C�Y(���F640px�A�c�F480px)��ݒ�
	SetGraphMode(640, 480, 32);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		//�ُ�����m
		return -1;
	}

	//���[�J���ϐ���`
	Scene* scene = new Scene();			//�V�[�����
	int result = 0;						//�I����ԏ��

	//�`���𗠉�ʂ���n�߂�悤�Ɏw�肷��
	SetDrawScreen(DX_SCREEN_BACK);

	try
	{
		//�V�[���̏�����
		scene->Initialize();

		//���C�����[�v(�E�B���h�E�ُ̈픭 or ESC�L�[�������ꂽ��A���[�v�I��)
		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
		{
			//���͋@�\�̍X�V
			InputControl::Update();

			//�V�[���̍X�V����
			scene->Update();

			//��ʂ̏�����
			ClearDrawScreen();

			//�V�[���̕`�揈��
			scene->Draw();

			//����ʂ̓��e��\��ʂɔ��f����
			ScreenFlip();
		}
	}
	catch (const char* error_log)
	{
		//�G���[����Log.txt�ɏo�͂���
		OutputDebugString(error_log);
		//�ُ��ԂɕύX����
		result = -1;
	}

	//�V�[�����̍폜������
	if (scene != nullptr)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}

	//DX���C�u�����̏I��������
	DxLib_End();

	//�I����Ԃ�ʒm
	return result;
}