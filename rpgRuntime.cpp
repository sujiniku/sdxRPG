#include "DxLib.h"

int Key[256]; // �L�[��������Ă���t���[�������i�[����

// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}


int jumpRyoku1 = 50;

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);




	int mapchip1Handle = LoadGraph("GameData\\mapchip\\mapchip_grass.bmp");
	int mapchip2Handle = LoadGraph("GameData\\mapchip\\mapchip_wall.bmp");


	DrawGraph(30, 0, mapchip1Handle, true);



	int monPosiX = 4; int monPosiY = 3; // �}�b�v��Ń����X�^�[�̂�����W



	int map1table[10][10] = {
		{ 1,1,1,1,1,1,1,1,1,1 }, //0 y
	{ 1,0,0,0,0,0,0,0,0,1 }, //1
	{ 1,0,0,0,0,0,0,0,0,1 }, //2
	{ 1,0,0,0,0,0,0,0,0,1 }, //3
	{ 1,0,0,0,0,0,0,0,0,1 }, //4
	{ 1,0,0,0,0,0,0,0,0,1 }, //5
	{ 1,1,1,1,1,1,0,0,1,1 }  //6
	};



	int x_mapDraw = 0;
	int y_mapDraw = 0;

	int hero1HPnow = 20;
	int hero1HPmax = 50;

	char name1[] = "�S���U���X" ;

	int koboHandle = LoadGraph("GameData\\monster_graphic\\kobo.png");

	int xPosi = 2;
	int yPosi = 2;



	int moving = 0; //�L�����`�b�v�摜���ړ����Ȃ�0

	int keyFlagUp = 0;
	int keyFlagDown = 0;
	int keyFlagRight = 0;
	int keyFlagLeft = 0;

	int keyFlagUpRight = 0;

	int keyFlagX = 0;
	int keyFlagZ = 0;


	int nyuuryokuMatiLR = 30;
	int nyuuryokuMatiUD = 30;

	int nyuuryokuMatiX = 30;
	int nyuuryokuMatiZ = 30;


	int waitKasol = 30;


	int  kasolTarget = 0;
	int  kasol2Target = 0; 
	int  kasol3Target = 0;


	int monchipDownHandle = LoadGraph("GameData\\charachip\\enemy_dot.bmp");

	int charachipUpHandle = LoadGraph("GameData\\charachip\\hero_dot_up.bmp");
	int charachipDownHandle = LoadGraph("GameData\\charachip\\hero_dot_down.bmp");
	int charachipLeftHandle = LoadGraph("GameData\\charachip\\hero_dot_left.bmp");
	int charachipRightHandle = LoadGraph("GameData\\charachip\\hero_dot_right.bmp");

	int  tempHandle;
	int destMovable;

	DrawGraph(30 * xPosi, 30 * yPosi, charachipRightHandle, true);



	enum direction { upward, rightward, downward, leftward };
	enum direction hero1_direction = downward;

	enum mode { mapMode, menuMode , itemMode, skillMode };
	enum mode scene = mapMode;



	int yakusouKosuu = 5;
	int dokukesiKosuu = 3;
	int soesiKosuu = 4;


	while (1) {
		if (ProcessMessage() != 0) { // ���b�Z�[�W����
			break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}




		// �}�b�v�`��
		for (x_mapDraw = 0; x_mapDraw <= 9; ++x_mapDraw)
		{
			for (y_mapDraw = 0; y_mapDraw <= 6; ++y_mapDraw)
			{
				if (map1table[y_mapDraw][x_mapDraw] == 0) {
					DrawGraph(30 * x_mapDraw, 30 * y_mapDraw, mapchip1Handle, true);
				}
				if (map1table[y_mapDraw][x_mapDraw] == 1) {
					DrawGraph(30 * x_mapDraw, 30 * y_mapDraw, mapchip2Handle, true);
				}
			}

		}


		DrawGraph(30 * monPosiX, 30 * monPosiY, monchipDownHandle, true);



		// �L�����`�b�v�`��
		{
			// �ʂ̌����̉摜�ŏ㏑��
			if (hero1_direction == rightward) {
				tempHandle = charachipRightHandle;

				// �O��
				if (nyuuryokuMatiLR > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi, tempHandle, true);
				}

				// ����
				if (nyuuryokuMatiLR <= 20 && nyuuryokuMatiLR > 10) {
					DrawGraph(30 * xPosi + 10, 30 * yPosi, tempHandle, true);
				}

				// �㔼
				if (nyuuryokuMatiLR <= 10 && nyuuryokuMatiLR >= 1) {
					DrawGraph(30 * xPosi + 20, 30 * yPosi, tempHandle, true);
				}
			}

			if (hero1_direction == leftward) {

				if (nyuuryokuMatiLR > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi, charachipLeftHandle, true);
				}

				if (nyuuryokuMatiLR <= 20 && nyuuryokuMatiLR > 10) {
					DrawGraph(30 * xPosi - 10, 30 * yPosi, charachipLeftHandle, true);
				}


				if (nyuuryokuMatiLR <= 10 && nyuuryokuMatiLR >= 1) {
					DrawGraph(30 * xPosi - 20, 30 * yPosi, charachipLeftHandle, true);
				}

			}



			if (hero1_direction == downward) {

				if (nyuuryokuMatiUD > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi - 0, charachipDownHandle, true);
				}

				if (nyuuryokuMatiUD <= 20 && nyuuryokuMatiUD > 10) {
					DrawGraph(30 * xPosi, 30 * yPosi + 10, charachipDownHandle, true);
				}


				if (nyuuryokuMatiUD <= 10 && nyuuryokuMatiUD >= 1) {
					DrawGraph(30 * xPosi, 30 * yPosi + 20, charachipDownHandle, true);
				}

			}


			if (hero1_direction == upward) {

				if (nyuuryokuMatiUD > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi + 0, charachipUpHandle, true);
				}

				if (nyuuryokuMatiUD <= 20 && nyuuryokuMatiUD > 10) {
					DrawGraph(30 * xPosi, 30 * yPosi - 10, charachipUpHandle, true);
				}


				if (nyuuryokuMatiUD <= 10 && nyuuryokuMatiUD >= 1) {
					DrawGraph(30 * xPosi, 30 * yPosi - 20, charachipUpHandle, true);
				}

			}

		}


		if (scene == mapMode) {
			// �ړ��L�[�̃t���O����
			{
				// �L�������E�Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyFlagRight == 0 && moving == 0) {
						if (map1table[yPosi][xPosi + 1] == 1) { destMovable = 0; }
						if (map1table[yPosi][xPosi + 1] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = rightward;
							keyFlagRight = 1;
							nyuuryokuMatiLR = 30;
						}
					}
					// �J�E���g����
					if (keyFlagRight == 1 && nyuuryokuMatiLR > 0) {
						nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
					}
					// �ړ��̏I������
					if (keyFlagRight == 1 && nyuuryokuMatiLR <= 0) {
						keyFlagRight = 0;
						nyuuryokuMatiLR = 30;
						xPosi++;                       // �E��1�}�X�����ړ�
						moving = 0;
					}
				}

				// ���Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyFlagLeft == 0 && moving == 0) {
						if (map1table[yPosi][xPosi - 1] == 1) { destMovable = 0; }
						if (map1table[yPosi][xPosi - 1] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = leftward;
							keyFlagLeft = 1;
							nyuuryokuMatiLR = 30;
						}
					}
					// �J�E���g����
					if (keyFlagLeft == 1 && nyuuryokuMatiLR > 0) {
						nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
					}
					// �ړ��̏I������
					if (keyFlagLeft == 1 && nyuuryokuMatiLR <= 0) {
						keyFlagLeft = 0;
						nyuuryokuMatiLR = 30;
						xPosi--;                       // ����1�}�X�����ړ�
						moving = 0;
					}

				}


				// ���Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyFlagDown == 0 && moving == 0) {
						if (map1table[yPosi + 1][xPosi] == 1) { destMovable = 0; }
						if (map1table[yPosi + 1][xPosi] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = downward;
							keyFlagDown = 1;
							nyuuryokuMatiUD = 30;
						}
					}
					// �J�E���g����
					// keyFlag�͕ʂ̃u���b�N�ŗ��p���Ă�̂ŁA�K�� moving ==1 ���K�v
					if (keyFlagDown == 1 && nyuuryokuMatiUD > 0 && moving == 1) {
						nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
					}
					// �ړ��̏I������
					if (keyFlagDown == 1 && nyuuryokuMatiUD <= 0) {
						keyFlagDown = 0;
						nyuuryokuMatiUD = 30;
						yPosi++;                       // ����1�}�X�����ړ�
						moving = 0;
					}
				}


				// ��Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyFlagUp == 0 && moving == 0) {
						if (map1table[yPosi - 1][xPosi] == 1) { destMovable = 0; }
						if (map1table[yPosi - 1][xPosi] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = upward;
							keyFlagUp = 1;
							nyuuryokuMatiUD = 30;
						}
					}
					// �J�E���g����

					// keyFlag�͕ʂ̃u���b�N�ŗ��p���Ă�̂ŁA�K�� moving ==1 ���K�v
					if (keyFlagUp == 1 && nyuuryokuMatiUD > 0 && moving == 1) {
						nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
					}
					// �ړ��̏I������
					if (keyFlagUp == 1 && nyuuryokuMatiUD <= 0 && moving == 1) {
						keyFlagUp = 0;
						nyuuryokuMatiUD = 30;
						yPosi--;                       // ���1�}�X�����ړ�
						moving = 0;
					}
				}


				// �����X�^�[�����̃G���J�E���g����
				{
					int monMesX = 400; int monMesY = 350; // ���b�Z�[�W���̕\���ʒu

					



					if (xPosi == monPosiX && yPosi == monPosiY) {
						DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
							GetColor(0, 0, 0), 1);
						DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "�����X�^�[�����ꂽ������"); // ������`�悷��

						// �����X�^�[�摜 // �f�o�b�O�p
						DrawGraph(300, 95, koboHandle, true);
					}

					if (!(xPosi == monPosiX && yPosi == monPosiY)) {
						DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
							GetColor(0, 0, 0), 1);
						DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "�e�X�g�p���b�Z�[�W"); // ������`�悷��

					}

					//DrawFormatString(400, 350, GetColor(255, 255, 255), "hhhh�����X�^�[�����ꂽ������"); // ������`�悷��

				} // �����X�^�[��������

			}

			// ���j���[����̋A�菈���̂���

			{
				if (nyuuryokuMatiX > 0) {
					nyuuryokuMatiX = nyuuryokuMatiX - 1;
				}

				if (nyuuryokuMatiX <= 0) {
					nyuuryokuMatiX = 0;
				}
			}

			// if �c��ҋ@���[���ŁA�����X�{�^���������ꂽ��Athen ���j���[��ʂɑJ��
			if (CheckHitKey(KEY_INPUT_X) == 1 && scene == mapMode && keyFlagX == 0 && nyuuryokuMatiX == 0) {
				keyFlagX = 1;
				scene = menuMode;
				nyuuryokuMatiX = 30;
			}


			DrawBox(100, 250, 100 + 150, 250 + 40 + 100,
				GetColor(150, 150, 255), 1);

			DrawFormatString(100, 250, GetColor(255, 255, 255), "���W[%d,%d]", xPosi, yPosi); // ������`�悷��

		} // map ���[�h�̏I���


		if (scene == menuMode) {
			int HPX = 300; int HPY = 50;

			DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 100,
				GetColor(150, 150, 255), 1);


			DrawFormatString(HPX +20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", name1); // ������`�悷��
			DrawFormatString(HPX +20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", hero1HPnow, hero1HPmax); // ������`�悷��

		

			DrawBox(100, 250, 100 + 150, 250 + 40 + 100,
				GetColor(150, 150, 255), 1);

			//DrawFormatString(100, 250, GetColor(255, 255, 255), "���W[%d,%d]", x, y); // ������`�悷��


			if (keyFlagX == 1) {

				DrawFormatString(100, 250 + 40, GetColor(255, 255, 255), "�J�E���g %d", nyuuryokuMatiX); // ������`�悷��
				nyuuryokuMatiX = nyuuryokuMatiX - 1;
			}

			if (CheckHitKey(KEY_INPUT_X) == 0 && keyFlagX == 1 && nyuuryokuMatiX == 0) {
				keyFlagX = 2; // �}�b�v�ɖ߂邽�߂�x�{�^���̓��͉\���
				DrawFormatString(100, 250, GetColor(255, 255, 255), "���W[%d,%d]", xPosi, yPosi); // ������`�悷��
				DrawFormatString(100, 250 + 40, GetColor(255, 255, 255), "X��t�\"); // ������`�悷��
			}



			if (keyFlagX == 2) {
				// �E�B���h�E��
					DrawBox(100, 250 + kasolTarget * 40, 100 + 80, 250 + kasolTarget * 40 +40,
						GetColor(250, 150, 150), 1);

					// �R�}���h��
				DrawFormatString(100+20, 250, GetColor(255, 255, 255), "����"); // ������`�悷��
				DrawFormatString(100+20, 250 + 40, GetColor(255, 255, 255), "���Z"); // ������`�悷��



				// �\���L�[���͎�

				// �J�[�\������Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyFlagUp == 0 && moving == 0) {
						//if (map1table[y - 1][x] == 1) { destMovable = 0; }
						//if (map1table[y - 1][x] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						//if (destMovable == 1) {
							moving = 1;
							//hero1_direction = upward;
							keyFlagUp = 1;
							waitKasol = 20;
						//}
					}
					// �J�E���g����
					if (keyFlagUp == 1 && waitKasol > 0) {
						waitKasol = waitKasol - 1;
					}
					// �ړ��̏I������
					if (keyFlagUp == 1 && waitKasol <= 0) {
						keyFlagUp = 0;
						waitKasol = 30;
						kasolTarget--;                       // ���1�}�X�����ړ�
						moving = 0;
					}


					if (kasolTarget < 0) {
						kasolTarget = 0;
					}

					if (kasolTarget >= 3) {
						kasolTarget = 3;
					}
					moving = 0;
				}




				// �J�[�\�������Ɉړ�
				{
					// �ړ���\��n�̓���ۂ̔���
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyFlagDown == 0 && moving == 0) {
						//if (map1table[y + 1][x] == 1) { destMovable = 0; }
						//if (map1table[y + 1][x] == 0) { destMovable = 1; }

						// ����\�Ȃ�t���O�ݒ�
						//if (destMovable == 1) {
							moving = 1;
							//hero1_direction = downward;
							keyFlagDown = 1;
							waitKasol = 20;
						//}
					}
					// �J�E���g����
					if (keyFlagDown == 1 && waitKasol > 0) {
						waitKasol = waitKasol - 1;
					}
					// �ړ��̏I������
					if (keyFlagDown == 1 && waitKasol <= 0) {
						keyFlagDown = 0;
						waitKasol = 20;
						kasolTarget++;                       // ����1�}�X�����ړ�
						moving = 0;
					}


					if (kasolTarget < 0) {
						kasolTarget = 0;
					}

					if (kasolTarget >= 3) {
						kasolTarget = 3;
					}

					moving = 0;


				}


				if (CheckHitKey(KEY_INPUT_Z) == 1) {

					if (kasolTarget == 0) {
						scene = itemMode;
						DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "�����I�т܂���������"); // ������`�悷��
						nyuuryokuMatiZ = 30;
						keyFlagZ = 0;
					}

					if (kasolTarget == 1) {
						scene = skillMode;
						DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "���Z��I�т܂���������"); // ������`�悷��
						keyFlagZ = 0;
					}

				}
			}



			if (CheckHitKey(KEY_INPUT_X) == 1 && keyFlagX == 2) {
				scene = mapMode;
				keyFlagX = 0; // �g���I������̂Ń[���ɖ߂� 
				nyuuryokuMatiX = 30;

				DrawFormatString(100, 250, GetColor(255, 255, 255), "���W[%d,%d]", xPosi, yPosi); // ������`�悷��

			}


		} // menu �̏I���


		if (scene == itemMode) {
			int HPX = 300; int HPY = 50;

			DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 100,
				GetColor(150, 150, 255), 1);


			DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", name1); // ������`�悷��
			DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", hero1HPnow, hero1HPmax); // ������`�悷��





			int itemWindX = 450;
			int itemWindY = 50;

			// ����̕`��
			DrawBox(itemWindX, itemWindY, itemWindX + 80+40, itemWindY + 180,
				GetColor(100, 100, 250), 1);

			// �J�[�\���`��
			DrawBox(itemWindX, itemWindY + kasol2Target * 40, itemWindX + 80, itemWindY + kasol2Target * 40 + 40,
				GetColor(250, 150, 150), 1);


			DrawFormatString(itemWindX, itemWindY + 40 * 0, GetColor(255, 255, 255), "�� %d",yakusouKosuu); // ������`�悷��
			DrawFormatString(itemWindX, itemWindY + 40 * 1, GetColor(255, 255, 255), "�ŏ����� %d", dokukesiKosuu); // ������`�悷��




			if (CheckHitKey(KEY_INPUT_X) == 1 ) {
				

				// ����͎g��Ȃ��̂ŁA��������œh��Ԃ����ƂŔ�\���ɂ��Ă���B
				DrawBox(itemWindX, itemWindY, itemWindX + 150, itemWindY + 180,
					GetColor(0, 0, 0), 1);


				scene = menuMode; 
				keyFlagX = 1; // �g���I������̂Ń[���ɖ߂� // 0�ł͂Ȃ�1�ɂ��Ȃ��ƃo�O
				nyuuryokuMatiX = 30;

				waitKasol = 30;
				DrawFormatString(250, 250+50, GetColor(255, 255, 255), "�����߂�"); // ������`�悷��


			}


			if (keyFlagZ == 0  && nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // ������`�悷��


			}
			DrawFormatString(200, 250 + 150 - 50, GetColor(0, 0, 0), "������"); // ������`�悷��
			DrawFormatString(200, 250 + 150 - 50, GetColor(255, 255, 255), "%d",nyuuryokuMatiZ); // ������`�悷��


	


			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyFlagZ == 0) {
				// ��������œh��Ԃ��Ĕ�\���ɂ���B
				// DrawBox(350, 50, 350 + 150, 50 + 180,
				//	GetColor(0, 0, 0), 1);

				keyFlagZ = 1;
				// waitKasol = 20;
				//}

				// �����ɒ��ĂȂ��o�O
				DrawFormatString(itemWindX, 250 + 150 -20, GetColor(255, 255, 255), "kkkkkkk"); // ������`�悷��


			}
			// �J�E���g����
			if (keyFlagZ == 1 && nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				DrawFormatString(250, 250 + 150, GetColor(255, 255, 255), "aaa567"); // ������`�悷��
			}
			// ���s�����ƃJ�E���g�I������
			if (keyFlagZ == 1 && nyuuryokuMatiZ <= 0) {
				keyFlagZ = 0;
				nyuuryokuMatiZ = 30;

				if (kasol2Target == 0) {
					if (yakusouKosuu > 0) {
						yakusouKosuu = yakusouKosuu - 1;
						hero1HPnow = hero1HPnow + 5;

					}
					if (yakusouKosuu <= 0) {
						yakusouKosuu = 0;
					}

				}

				if (kasol2Target == 1) {
					if (dokukesiKosuu > 0) {
						dokukesiKosuu = dokukesiKosuu - 1;
						hero1HPnow = hero1HPnow + 2;
					}
					if (dokukesiKosuu <= 0) {
						dokukesiKosuu = 0;
					}

				}

			}



			


			// �\���L�[���͎�

			// �J�[�\������Ɉړ�
			{
				// �ړ���\��n�̓���ۂ̔���
				if (CheckHitKey(KEY_INPUT_UP) == 1 && keyFlagUp == 0 && moving == 0) {
					//if (map1table[y - 1][x] == 1) { destMovable = 0; }
					//if (map1table[y - 1][x] == 0) { destMovable = 1; }

					// ����\�Ȃ�t���O�ݒ�
					//if (destMovable == 1) {
					moving = 1;
					//hero1_direction = upward;
					keyFlagUp = 1;
					waitKasol = 20;
					//}
				}
				// �J�E���g����
				if (keyFlagUp == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}
				// �ړ��̏I������
				if (keyFlagUp == 1 && waitKasol <= 0) {
					keyFlagUp = 0;
					waitKasol = 30;
					kasol2Target--;                       // ���1�}�X�����ړ�
					moving = 0;
				}


				if (kasol2Target < 0) {
					kasol2Target = 0;
				}

				if (kasol2Target >= 3) {
					kasol2Target = 3;
				}

			}




			// �J�[�\�������Ɉړ�
			{
				// �ړ���\��n�̓���ۂ̔���
				if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyFlagDown == 0 && moving == 0) {
					//if (map1table[y + 1][x] == 1) { destMovable = 0; }
					//if (map1table[y + 1][x] == 0) { destMovable = 1; }

					// ����\�Ȃ�t���O�ݒ�
					//if (destMovable == 1) {
					moving = 1;
					//hero1_direction = downward;
					keyFlagDown = 1;
					waitKasol = 20;
					//}
				}
				// �J�E���g����
				if (keyFlagDown == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}
				// �ړ��̏I������
				if (keyFlagDown == 1 && waitKasol <= 0) {
					keyFlagDown = 0;
					waitKasol = 20;
					kasol2Target++;                       // ����1�}�X�����ړ�
					moving = 0;
				}


				if (kasol2Target < 0) {
					kasol2Target = 0;
				}

				if (kasol2Target >= 3) {
					kasol2Target = 3;
				}
			}
		}





		if (scene == skillMode) {
			if (CheckHitKey(KEY_INPUT_X) == 1) {
				scene = menuMode;
				keyFlagX = 1; // �g���I������̂Ń[���ɖ߂� // 0�ł͂Ȃ�1�ɂ��Ȃ��ƃo�O
				nyuuryokuMatiX = 30;

				DrawFormatString(250, 250 + 50*2, GetColor(255, 255, 255), "���Z����߂�"); // ������`�悷��

			}
		}


		


		ScreenFlip(); //����ʂ�\��ʂɔ��f
	}



	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}