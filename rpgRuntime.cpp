#include "DxLib.h"

int Key[256]; // キーが押されているフレーム数を格納する

// キーの入力状態を更新する
int gpUpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}


int jumpRyoku1 = 50;

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // ウィンドウモードに設定

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);




	int mapchip1Handle = LoadGraph("GameData\\mapchip\\mapchip_grass.bmp");
	int mapchip2Handle = LoadGraph("GameData\\mapchip\\mapchip_wall.bmp");


	DrawGraph(30, 0, mapchip1Handle, true);



	int monPosiX = 4; int monPosiY = 3; // マップ上でモンスターのいる座標



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

	char name1[] = "ゴンザレス" ;

	int koboHandle = LoadGraph("GameData\\monster_graphic\\kobo.png");

	int xPosi = 2;
	int yPosi = 2;



	int moving = 0; //キャラチップ画像が移動中なら0

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
		if (ProcessMessage() != 0) { // メッセージ処理
			break;//ウィンドウの×ボタンが押されたらループを抜ける
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}




		// マップ描画
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



		// キャラチップ描画
		{
			// 個別の向きの画像で上書き
			if (hero1_direction == rightward) {
				tempHandle = charachipRightHandle;

				// 前半
				if (nyuuryokuMatiLR > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi, tempHandle, true);
				}

				// 中盤
				if (nyuuryokuMatiLR <= 20 && nyuuryokuMatiLR > 10) {
					DrawGraph(30 * xPosi + 10, 30 * yPosi, tempHandle, true);
				}

				// 後半
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
			// 移動キーのフラグ処理
			{
				// キャラを右に移動
				{
					// 移動先予定地の入場可否の判定
					if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyFlagRight == 0 && moving == 0) {
						if (map1table[yPosi][xPosi + 1] == 1) { destMovable = 0; }
						if (map1table[yPosi][xPosi + 1] == 0) { destMovable = 1; }

						// 入場可能ならフラグ設定
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = rightward;
							keyFlagRight = 1;
							nyuuryokuMatiLR = 30;
						}
					}
					// カウント処理
					if (keyFlagRight == 1 && nyuuryokuMatiLR > 0) {
						nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
					}
					// 移動の終了処理
					if (keyFlagRight == 1 && nyuuryokuMatiLR <= 0) {
						keyFlagRight = 0;
						nyuuryokuMatiLR = 30;
						xPosi++;                       // 右へ1マスだけ移動
						moving = 0;
					}
				}

				// 左に移動
				{
					// 移動先予定地の入場可否の判定
					if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyFlagLeft == 0 && moving == 0) {
						if (map1table[yPosi][xPosi - 1] == 1) { destMovable = 0; }
						if (map1table[yPosi][xPosi - 1] == 0) { destMovable = 1; }

						// 入場可能ならフラグ設定
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = leftward;
							keyFlagLeft = 1;
							nyuuryokuMatiLR = 30;
						}
					}
					// カウント処理
					if (keyFlagLeft == 1 && nyuuryokuMatiLR > 0) {
						nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
					}
					// 移動の終了処理
					if (keyFlagLeft == 1 && nyuuryokuMatiLR <= 0) {
						keyFlagLeft = 0;
						nyuuryokuMatiLR = 30;
						xPosi--;                       // 左へ1マスだけ移動
						moving = 0;
					}

				}


				// 下に移動
				{
					// 移動先予定地の入場可否の判定
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyFlagDown == 0 && moving == 0) {
						if (map1table[yPosi + 1][xPosi] == 1) { destMovable = 0; }
						if (map1table[yPosi + 1][xPosi] == 0) { destMovable = 1; }

						// 入場可能ならフラグ設定
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = downward;
							keyFlagDown = 1;
							nyuuryokuMatiUD = 30;
						}
					}
					// カウント処理
					// keyFlagは別のブロックで流用してるので、必ず moving ==1 が必要
					if (keyFlagDown == 1 && nyuuryokuMatiUD > 0 && moving == 1) {
						nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
					}
					// 移動の終了処理
					if (keyFlagDown == 1 && nyuuryokuMatiUD <= 0) {
						keyFlagDown = 0;
						nyuuryokuMatiUD = 30;
						yPosi++;                       // 下へ1マスだけ移動
						moving = 0;
					}
				}


				// 上に移動
				{
					// 移動先予定地の入場可否の判定
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyFlagUp == 0 && moving == 0) {
						if (map1table[yPosi - 1][xPosi] == 1) { destMovable = 0; }
						if (map1table[yPosi - 1][xPosi] == 0) { destMovable = 1; }

						// 入場可能ならフラグ設定
						if (destMovable == 1) {
							moving = 1;
							hero1_direction = upward;
							keyFlagUp = 1;
							nyuuryokuMatiUD = 30;
						}
					}
					// カウント処理

					// keyFlagは別のブロックで流用してるので、必ず moving ==1 が必要
					if (keyFlagUp == 1 && nyuuryokuMatiUD > 0 && moving == 1) {
						nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
					}
					// 移動の終了処理
					if (keyFlagUp == 1 && nyuuryokuMatiUD <= 0 && moving == 1) {
						keyFlagUp = 0;
						nyuuryokuMatiUD = 30;
						yPosi--;                       // 上へ1マスだけ移動
						moving = 0;
					}
				}


				// モンスター遭遇のエンカウント判定
				{
					int monMesX = 400; int monMesY = 350; // メッセージ欄の表示位置

					



					if (xPosi == monPosiX && yPosi == monPosiY) {
						DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
							GetColor(0, 0, 0), 1);
						DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "モンスターが現れた未実装"); // 文字を描画する

						// モンスター画像 // デバッグ用
						DrawGraph(300, 95, koboHandle, true);
					}

					if (!(xPosi == monPosiX && yPosi == monPosiY)) {
						DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
							GetColor(0, 0, 0), 1);
						DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "テスト用メッセージ"); // 文字を描画する

					}

					//DrawFormatString(400, 350, GetColor(255, 255, 255), "hhhhモンスターが現れた未実装"); // 文字を描画する

				} // モンスター遭遇処理

			}

			// メニューからの帰り処理のため

			{
				if (nyuuryokuMatiX > 0) {
					nyuuryokuMatiX = nyuuryokuMatiX - 1;
				}

				if (nyuuryokuMatiX <= 0) {
					nyuuryokuMatiX = 0;
				}
			}

			// if 残り待機がゼロで、さらにXボタンが押されたら、then メニュー画面に遷移
			if (CheckHitKey(KEY_INPUT_X) == 1 && scene == mapMode && keyFlagX == 0 && nyuuryokuMatiX == 0) {
				keyFlagX = 1;
				scene = menuMode;
				nyuuryokuMatiX = 30;
			}


			DrawBox(100, 250, 100 + 150, 250 + 40 + 100,
				GetColor(150, 150, 255), 1);

			DrawFormatString(100, 250, GetColor(255, 255, 255), "座標[%d,%d]", xPosi, yPosi); // 文字を描画する

		} // map モードの終わり


		if (scene == menuMode) {
			int HPX = 300; int HPY = 50;

			DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 100,
				GetColor(150, 150, 255), 1);


			DrawFormatString(HPX +20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", name1); // 文字を描画する
			DrawFormatString(HPX +20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", hero1HPnow, hero1HPmax); // 文字を描画する

		

			DrawBox(100, 250, 100 + 150, 250 + 40 + 100,
				GetColor(150, 150, 255), 1);

			//DrawFormatString(100, 250, GetColor(255, 255, 255), "座標[%d,%d]", x, y); // 文字を描画する


			if (keyFlagX == 1) {

				DrawFormatString(100, 250 + 40, GetColor(255, 255, 255), "カウント %d", nyuuryokuMatiX); // 文字を描画する
				nyuuryokuMatiX = nyuuryokuMatiX - 1;
			}

			if (CheckHitKey(KEY_INPUT_X) == 0 && keyFlagX == 1 && nyuuryokuMatiX == 0) {
				keyFlagX = 2; // マップに戻るためのxボタンの入力可能状態
				DrawFormatString(100, 250, GetColor(255, 255, 255), "座標[%d,%d]", xPosi, yPosi); // 文字を描画する
				DrawFormatString(100, 250 + 40, GetColor(255, 255, 255), "X受付可能"); // 文字を描画する
			}



			if (keyFlagX == 2) {
				// ウィンドウ欄
					DrawBox(100, 250 + kasolTarget * 40, 100 + 80, 250 + kasolTarget * 40 +40,
						GetColor(250, 150, 150), 1);

					// コマンド欄
				DrawFormatString(100+20, 250, GetColor(255, 255, 255), "道具"); // 文字を描画する
				DrawFormatString(100+20, 250 + 40, GetColor(255, 255, 255), "特技"); // 文字を描画する



				// 十字キー入力時

				// カーソルを上に移動
				{
					// 移動先予定地の入場可否の判定
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyFlagUp == 0 && moving == 0) {
						//if (map1table[y - 1][x] == 1) { destMovable = 0; }
						//if (map1table[y - 1][x] == 0) { destMovable = 1; }

						// 入場可能ならフラグ設定
						//if (destMovable == 1) {
							moving = 1;
							//hero1_direction = upward;
							keyFlagUp = 1;
							waitKasol = 20;
						//}
					}
					// カウント処理
					if (keyFlagUp == 1 && waitKasol > 0) {
						waitKasol = waitKasol - 1;
					}
					// 移動の終了処理
					if (keyFlagUp == 1 && waitKasol <= 0) {
						keyFlagUp = 0;
						waitKasol = 30;
						kasolTarget--;                       // 上へ1マスだけ移動
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




				// カーソルを下に移動
				{
					// 移動先予定地の入場可否の判定
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyFlagDown == 0 && moving == 0) {
						//if (map1table[y + 1][x] == 1) { destMovable = 0; }
						//if (map1table[y + 1][x] == 0) { destMovable = 1; }

						// 入場可能ならフラグ設定
						//if (destMovable == 1) {
							moving = 1;
							//hero1_direction = downward;
							keyFlagDown = 1;
							waitKasol = 20;
						//}
					}
					// カウント処理
					if (keyFlagDown == 1 && waitKasol > 0) {
						waitKasol = waitKasol - 1;
					}
					// 移動の終了処理
					if (keyFlagDown == 1 && waitKasol <= 0) {
						keyFlagDown = 0;
						waitKasol = 20;
						kasolTarget++;                       // 下へ1マスだけ移動
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
						DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "道具を選びました未実装"); // 文字を描画する
						nyuuryokuMatiZ = 30;
						keyFlagZ = 0;
					}

					if (kasolTarget == 1) {
						scene = skillMode;
						DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "特技を選びました未実装"); // 文字を描画する
						keyFlagZ = 0;
					}

				}
			}



			if (CheckHitKey(KEY_INPUT_X) == 1 && keyFlagX == 2) {
				scene = mapMode;
				keyFlagX = 0; // 使い終わったのでゼロに戻す 
				nyuuryokuMatiX = 30;

				DrawFormatString(100, 250, GetColor(255, 255, 255), "座標[%d,%d]", xPosi, yPosi); // 文字を描画する

			}


		} // menu の終わり


		if (scene == itemMode) {
			int HPX = 300; int HPY = 50;

			DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 100,
				GetColor(150, 150, 255), 1);


			DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", name1); // 文字を描画する
			DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", hero1HPnow, hero1HPmax); // 文字を描画する





			int itemWindX = 450;
			int itemWindY = 50;

			// 道具欄の描画
			DrawBox(itemWindX, itemWindY, itemWindX + 80+40, itemWindY + 180,
				GetColor(100, 100, 250), 1);

			// カーソル描画
			DrawBox(itemWindX, itemWindY + kasol2Target * 40, itemWindX + 80, itemWindY + kasol2Target * 40 + 40,
				GetColor(250, 150, 150), 1);


			DrawFormatString(itemWindX, itemWindY + 40 * 0, GetColor(255, 255, 255), "薬草 %d",yakusouKosuu); // 文字を描画する
			DrawFormatString(itemWindX, itemWindY + 40 * 1, GetColor(255, 255, 255), "毒消し薬 %d", dokukesiKosuu); // 文字を描画する




			if (CheckHitKey(KEY_INPUT_X) == 1 ) {
				

				// 道具欄は使わないので、道具欄を黒で塗りつぶすことで非表示にしている。
				DrawBox(itemWindX, itemWindY, itemWindX + 150, itemWindY + 180,
					GetColor(0, 0, 0), 1);


				scene = menuMode; 
				keyFlagX = 1; // 使い終わったのでゼロに戻す // 0ではなく1にしないとバグ
				nyuuryokuMatiX = 30;

				waitKasol = 30;
				DrawFormatString(250, 250+50, GetColor(255, 255, 255), "道具から戻り"); // 文字を描画する


			}


			if (keyFlagZ == 0  && nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // 文字を描画する


			}
			DrawFormatString(200, 250 + 150 - 50, GetColor(0, 0, 0), "■■■"); // 文字を描画する
			DrawFormatString(200, 250 + 150 - 50, GetColor(255, 255, 255), "%d",nyuuryokuMatiZ); // 文字を描画する


	


			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyFlagZ == 0) {
				// 道具欄を黒で塗りつぶして非表示にする。
				// DrawBox(350, 50, 350 + 150, 50 + 180,
				//	GetColor(0, 0, 0), 1);

				keyFlagZ = 1;
				// waitKasol = 20;
				//}

				// ここに着てないバグ
				DrawFormatString(itemWindX, 250 + 150 -20, GetColor(255, 255, 255), "kkkkkkk"); // 文字を描画する


			}
			// カウント処理
			if (keyFlagZ == 1 && nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				DrawFormatString(250, 250 + 150, GetColor(255, 255, 255), "aaa567"); // 文字を描画する
			}
			// 実行処理とカウント終了処理
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



			


			// 十字キー入力時

			// カーソルを上に移動
			{
				// 移動先予定地の入場可否の判定
				if (CheckHitKey(KEY_INPUT_UP) == 1 && keyFlagUp == 0 && moving == 0) {
					//if (map1table[y - 1][x] == 1) { destMovable = 0; }
					//if (map1table[y - 1][x] == 0) { destMovable = 1; }

					// 入場可能ならフラグ設定
					//if (destMovable == 1) {
					moving = 1;
					//hero1_direction = upward;
					keyFlagUp = 1;
					waitKasol = 20;
					//}
				}
				// カウント処理
				if (keyFlagUp == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}
				// 移動の終了処理
				if (keyFlagUp == 1 && waitKasol <= 0) {
					keyFlagUp = 0;
					waitKasol = 30;
					kasol2Target--;                       // 上へ1マスだけ移動
					moving = 0;
				}


				if (kasol2Target < 0) {
					kasol2Target = 0;
				}

				if (kasol2Target >= 3) {
					kasol2Target = 3;
				}

			}




			// カーソルを下に移動
			{
				// 移動先予定地の入場可否の判定
				if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyFlagDown == 0 && moving == 0) {
					//if (map1table[y + 1][x] == 1) { destMovable = 0; }
					//if (map1table[y + 1][x] == 0) { destMovable = 1; }

					// 入場可能ならフラグ設定
					//if (destMovable == 1) {
					moving = 1;
					//hero1_direction = downward;
					keyFlagDown = 1;
					waitKasol = 20;
					//}
				}
				// カウント処理
				if (keyFlagDown == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}
				// 移動の終了処理
				if (keyFlagDown == 1 && waitKasol <= 0) {
					keyFlagDown = 0;
					waitKasol = 20;
					kasol2Target++;                       // 下へ1マスだけ移動
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
				keyFlagX = 1; // 使い終わったのでゼロに戻す // 0ではなく1にしないとバグ
				nyuuryokuMatiX = 30;

				DrawFormatString(250, 250 + 50*2, GetColor(255, 255, 255), "特技から戻り"); // 文字を描画する

			}
		}


		


		ScreenFlip(); //裏画面を表画面に反映
	}



	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}