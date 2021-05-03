#include "DxLib.h"




#include <stdio.h> // セーブ用
#pragma warning(disable:4996) // fopen



#include <math.h>  // 切り上げ計算で使用






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





static int selecting_mainmenu = 1;







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



int hero2HPnow = 14;
int hero2HPmax = 30;





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


int kasol2Target = 0;
int kasol3Target = 0;



int tempHandle;
int destMovable;


enum direction { upward, rightward, downward, leftward };
enum direction hero1_direction = downward;

enum mode { MODE_OP, MODE_LOAD, MODE_INITIAL, MODE_MAP, 
	
	MODE_TOWN, 
	
	MODE_Shop_Main, MODE_Shop_weapon_main, MODE_Shop_weapon_buy	, MODE_Shop_weapon_sell, MODE_Shop_weapon_buyOld,
	MODE_Shop_armor_main, MODE_Shop_armor_buy, MODE_Shop_armor_sell, MODE_Shop_armor_buyOld, 
	MODE_Shop_akusesari_main, MODE_Shop_item_main,
	
	MODE_MENU, 
	
	MODE_narabikae_select1, MODE_narabikae_select2,
	
	MODE_ITEM_TYPE, MODE_ITEM_MENU, MODE_ITEM_MENU_FRONT	,
	MODE_ITEMweapon_MENU, MODE_ITEMweapon_MENU_FRONT, MODE_ITEM_WHOM, MODE_ITEM_WHOM_FRONT, 
	
	MODE_EQUIP_MAIN,	MODE_EQUIP_EDIT, MODE_EQUIP_EDIT2,
	MODE2_EQUIP_HAND, MODE2_EQUIP_SHIELD, MODE2_EQUIP_HELM, MODE2_EQUIP_ARMOR,
	
	MODE_SAVE_MENU, MODE_saving_Now,
	
	MODE_BATTLE_COMMAND, MODE_BATTLE_NOW, MODE_BATTLE_WIN, BATTLE_Agility_proc,

	MODE_Guild_Main, MODE_Guild_Responce, MODE_Guild_Remove,
	
	itemModeMain, itemModeTarget, skillMode,
 };
enum mode mode_scene = MODE_MAP;



int yakusouKosuu = 5;
int dokukesiKosuu = 3;
int soesiKosuu = 4;











int NaraSele1 = 0;

int NaraSele2 = 0;


int uketKyara = 1; // 戦闘中で、何人目がダメージ受けてるか。「1」で1人目。

int pageSyori = 0;


// アイテム種類番号
int siyouType = 0;
int wepoType = 1;
int tateType = 2;
int kabutoType = 3;

int PorEflag[20];

int tempPass = 0;





// これは文字数バッファなど。（モード番号ではない。）
#define MAX_LOADSTRING 100
#define MAX_LENGTH 300 // 要素数に注意 


int afterShop = 0;

int shopAct = 0;

int sinamonoList = 0;

int popFlagTown = 0;
TCHAR popMsg[MAX_LENGTH] = TEXT("aaaa");


const int partymax = 3; // 本当は4だけどテストのため1時的に3
int whatuse = 0;

int beforeselect = 1; // なんらかの選択肢で直前に選んだ選択肢の番号。画面更新用に使う。


int whatedit = 0; // 装備コマンドなど、編集をするいろいろな作業用
int whatedit2 = 0; // ひとつの画面内に、前画面用カーソルを残す場合の処理変数



int uwadumeFlag = 1; // 1なら上詰めする。0ならオフ。デバッグモード用 // バグッたら0に戻すこと

int akikosuu;
int akiHairetu[5];
int itemHairetu[50];
int itemTypeHairetu[50];



int event_tekiFast = 0;

int event_tekiSoutou = 0;

int uwagaki = 0;


int goukeiItem = 0;

int whomCHARA = 1;
int whomTargetID1 = 0;
int whomTargetID2 = 0;


int whomTargetID1party = 0;
int whomTargetID1hikae = 0;


int filterFlag = 0;

int FontYoffset = 30;

int idTemp = 0;
int battleID = 0;
int globalTempA = 0;
int timerFlag = 0;
int enemyAlldeadFlag = 0;// 0なら、敵はまだ全滅してない。1で敵が全滅。

int whoAction = 5; // 0 なら主人公の攻撃。1なら敵の攻撃。試作用のとりあえずのフラグ。

int tourokuMapChip = 2;

int sankaAgility[BATTLE_Agility_proc]; // 素早さ配列
int iremonoAgilityHairetu[BATTLE_Agility_proc]; // 入れ物すばやさ配列
int actionOrder[BATTLE_Agility_proc]; // 行動順配列
int iremonoOrderHairetu[BATTLE_Agility_proc]; // 入れ物こうどうじゅん配列
int mikataAgility[BATTLE_Agility_proc]; // 味方の隊列での素早さ配列。「並び替え」で隊列順が変わるので。
int tekiTairetuAgility[BATTLE_Agility_proc]; // 敵の隊列での素早さ配列。戦闘時のソートで使うので。

// 装備の材質:

enum item_material
{
	mateWood,
	mateLether,
	mateCopper,
	mateBronze,

	mateIron,
	mateRichMetal,
	mateElse,
	mateNothing,
};


enum equip_type
{
	sword,
	spear,
	axe,
	crab,
	bow,
	rod,
	typeNothing,
	typeElse,

};





// グローバル変数:

int IsNewGame = 1; // 初めてこのゲームを起動するとき、1である。一度でもセーブすれば2になる。


int battleTimeFlag = 0; // 戦闘中のコマンド決定後の自動進行に使用。1だと自動進行。0で停止。

enum resource_embedded_flag { on, off };
enum resource_embedded_flag resource_embedded_var = off;


int makeNakamaNinzu = 5; // プログラマーの作った仲間キャラの人数
int tourokuNakama = 4 - 1; // 実際の人数より1少ない // ギルドに登録されてる仲間の人数なので変数


int partyNinzuDone = 2, enemyNinzu = 1;
int partyNinzuTemp = partyNinzuDone;

int sankaNinzu = partyNinzuDone + enemyNinzu;


int hikaeNinzu = 2;


int partyNarabijyun[15] = { 0,1,-1,-1, -1 }; // パーティ隊列の並び替えの処理に使う予定
int partyNarabijyunBefore[15];
int partyNarabijyunAfter[15];



int hikaeNarabijyun[10] = { 2,3,-1, -1, -1 }; // ギルドの処理に使う予定

int monsterNarabijyun[5] = { 0,1,2,3,4 }; // モンスターの戦闘中の行動順の処理に使う予定



int guildResFlag = 0;

struct item_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int power;
	int item_type;
};


struct item_have
{
	int have_def_id;
	int have_kosuu;
};


struct weapon_have
{
	int have_def_id;
	int have_kosuu;
};





struct weapon_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower;// 攻撃力


};


struct shield_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower;// 攻撃力

};


struct shield_have
{
	int have_def_id;
	int have_kosuu;
};


struct helm_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower;// 攻撃力


};



struct helm_have
{
	int have_def_id;
	int have_kosuu;
};


struct armor_def
{
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower;// 攻撃力


};

struct armor_have
{
	int have_def_id;
	int have_kosuu;
};


int equipWeaponPower;

int bouguyaSina[10][10]; // 


struct monster_def
{
	int monster_id;
	TCHAR monster_name[MAX_LENGTH];
	int mon_hp_max;
	int mon_agility;

	int mon_attackPower;


	int mon_gold;
	int mon_exp;
};


// 味方パーティ構造体 (モンスター構造体の流用)
struct heros_def
{
	int heros_id;
	TCHAR heros_name[MAX_LENGTH];
	int heros_hp;
	int heros_hp_max;
	int heros_agility;

	int heros_gold; // ウィザードリィみたいに各キャラごとにゴールドを持てるようになってる。
	int heros_exp;

	int heros_HP0_flag;

	int PartyIn;


	int heros_weapon1;
	int heros_weapon2;
	int heros_shield;
	int heros_helm;
	int heros_yoroi;
	int heros_kote;
	int heros_sousyoku1;
	int heros_sousyoku2;
	int heros_sousyoku3;


	int heros_bukiKougekiRyoku;
	int heros_subiRyoku;

};



enum next_attack_flag { next_is_hero, next_is_enemy };
enum next_attack_flag next_attack_var = next_is_hero;


static int encount_monters_id = 1;


struct monsterTairetu_def
{
	int monsterTairetu[10];
};






static int selecting_item = 1;
static int selecting_item_x = 1;
static int selecting_item_y = 1;

static int selecting_itemBefore = 1;
static int selecting_itemAfter = 1;


// 戦闘中に使用する変数。 モンスター定義とは別物。
static TCHAR monster_name[30];
static int monster_hp = 10;



static int enemy_alive[2] = { 1, 1 }; // 1なら生きてる。0なら死亡。とりあえず2匹ぶん
// カッコ内は敵の番号。0番から数えている。

static int encount_mons_alive = 1;


HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名


TCHAR mojibuf[MAX_LENGTH] = TEXT("はじめから");


// 装備欄の記述用に、3つbufを確保
TCHAR mojibuf1[MAX_LENGTH] = TEXT("はじめから");
TCHAR mojibuf2[MAX_LENGTH] = TEXT("はじめから");
TCHAR mojibuf3[MAX_LENGTH] = TEXT("はじめから");




static TCHAR filename_temp[100]; // ファイル読み書きで使う一時的なファイル名









static int mode2_mode_scene = 0;

static int selecting_OP = 1;

static int 
;


static int cursol_stop;
static int your_money = 0;



static TCHAR drawTalkString1[MAX_LENGTH] = TEXT("temp_talk1"); // 会話欄の1行目
static TCHAR drawTalkString2[MAX_LENGTH] = TEXT("temp_talk2"); // 会話欄の2行目
static TCHAR drawTalkString3[MAX_LENGTH] = TEXT("temp_talk3"); // 会話欄の3行目


static int game_event1_end;
static int game_event2_end;

static int game_event1_end_dummuy;


static int key_remain = 1;


static int chara_x;
static int chara_y;

static int before_chara_x; // 退却処理で1歩前に戻るときに使う。
static int before_chara_y; //


static int start_x = 4;
static int start_y = 3;






// マップのサイズの変数
static int map_x_size = 10;
static int map_y_size = 7;


// 進行先の壁判定のアルゴリズム用の変数
static int desti_x; // 進行先(destination)の壁判定のためのx座標変数 "desiti" means the destination.
static int desti_y; // 進行先の壁判定のためのx座標変数


// maptable の初期化 // 中身はとりあえず0. 安全のため、オーバーフロー時の影響を防ぐ。
static int maptable[10][10] = {
	{ 0,0,0,0,0,0,0,0,0,0 }, //0 y
	{ 0,0,0,0,0,0,0,0,0,0 }, //1
	{ 0,0,0,0,0,0,0,0,0,0 }, //2
	{ 0,0,0,0,0,0,0,0,0,0 }, //3
	{ 0,0,0,0,0,0,0,0,0,0 }, //4
	{ 0,0,0,0,0,0,0,0,0,0 }, //5
	{ 0,0,0,0,0,0,0,0,0,0 }  //6
};


struct map_def
{
	int map_table[10][10];
	//int mapTransGoto[10][10][10];
};

static struct map_def map_def_list[8];




int MapTrans_position_x_map1to_map2 = 7;
int MapTrans_position_y_map1to_map2 = 6;


int town_X = 3;
int town_Y = 5;


static int MapTrans_position_x = MapTrans_position_x_map1to_map2;
static int MapTrans_position_y = MapTrans_position_y_map1to_map2;


struct MapTrans_def
{
	int MapTrans_id;

	int in_Where_Map;
	int to_Where_Map;

	int positionX; // その遷移のあるX座標
	int positionY;

	int chara_positionX; // 遷移先マップでのキャラの開始時点でのX座標
	int chara_positionY;

};


// マップ遷移用の構造体変数の作成
static struct MapTrans_def MapTrans_def_list[8];





// map2 のデータ

int map2table[10][10] = {
	{ 1,1,0,1,0,0,0,0,0,1 }, //0 x
	{ 0,0,0,0,0,0,0,0,0,0 }, //1
	{ 0,0,0,0,0,0,0,0,0,0 }, //2
	{ 0,0,0,0,0,0,0,0,0,1 }, //3
	{ 0,0,0,0,0,0,0,0,0,0 }, //4
	{ 0,0,0,0,0,0,0,0,0,0 }, //5
	{ 0,1,1,1,1,1,0,0,1,0 }  //6
};


// int MapTrans_position_x_map2to_map1 = 2;
// int MapTrans_position_y_map2to_map1 = 0;



static int selecting_battle_mainmenu = 1;

static	int where_map = 1; // 最初のマップ

static int mapTrans_flag_is = 1;


// モンスターの位置。とりあえず2匹ぶん // なおフィールドマップにいる
static int positionX_enemy[5];
static int positionY_enemy[5];

int tekiSuu = 2; // イベント処理用に、このエリアの敵パーティ数を算出。
int gekiha_tekiSuu = 0;


static int TimeCount = 0; // 主に自動進行（敵の行動など）に使用
static int keyCount = 0; // 主にキー入力の時間制限に使用












// アイテム処理の構造体変数の作成
static struct item_def item_def_list[8]; // アイテム処理の構造体配列の宣言
static struct item_have item_have_list[8];




// 装備品の処理の構造体配列の作成
static struct weapon_def weapon_def_list[15]; // 武器処理の構造体配列の宣言
static struct weapon_have weapon_have_list[15];

static struct shield_def shield_def_list[15]; // シールド処理の構造体配列の宣言
static struct shield_have shield_have_list[15];


static struct helm_def helm_def_list[15]; // カブト処理の構造体配列の宣言
static struct helm_have helm_have_list[15];


static struct armor_def armor_def_list[15]; // ヨロイ処理の構造体配列の宣言
static struct armor_have armor_have_list[15];



// 戦闘遭遇用の構造体変数の作成
static struct monster_def monster_def_list[8];

static struct heros_def heros_def_list[8];






static struct monsterTairetu_def monsterTairetu_def_list[50];

int darkFlag = 0;





// 戦闘への突入の処理 // のちのマップ判定で呼びだすので、戦闘突入とマップ判定の順序は固定のこと。
void battle_start() {

	// MessageBox(NULL, TEXT("battle_enemy_startにいる。"), TEXT("キーテスト"), MB_OK);

	// 以下、定型文
	key_remain = 0;

	monster_hp = monster_def_list[encount_monters_id - 1].mon_hp_max;

	tekiTairetuAgility[0] = monster_def_list[encount_monters_id - 1].mon_agility;

	encount_mons_alive = 1;
	selecting_battle_mainmenu = 1;
	enemyAlldeadFlag = 0;

	mode_scene = MODE_BATTLE_COMMAND;


}










// モンスターとの遭遇判定
void check_encount_enemy(HWND hWnd) {

	if (where_map == 2) {
		for (int i = 0; i <= 1; i = i + 1)
		{
			if (enemy_alive[i] == 1) {
				if (chara_x == positionX_enemy[i] && chara_y == positionY_enemy[i]) {

					encount_monters_id = i + 1;	// ここに、誰と遭遇したかを記述

					// スライム encount id が 1番
					// コボルと id 2番

					battle_start();
				}
			}
		}
	}

}



void Akihaikeisan() {

	// int kousinNarabijyun[5];

	partyNinzuDone = partyNinzuTemp;


	int skip = 0;
	for (int temp = 0; temp < partymax; temp++)
	{
		if (partyNarabijyun[temp] >= 0) {
			// kousinNarabijyun[temp - skip] = partyNarabijyun[temp];
		}

		if (partyNarabijyun[temp] < 0) {

			akiHairetu[skip] = temp;

			skip = skip + 1;
		}
	}

}


void hikaeKeisan() {
	// これが加わる
	int skip = 0; // remove 命令でもskipを流用する。
	{
		for (int temp = 0; temp <= tourokuNakama; temp = temp + 1) {

			if (heros_def_list[temp].PartyIn == 0) {
				hikaeNarabijyun[skip] = temp;
				skip = skip + 1; // 代入し終わってから、skipを増やす。次のメンバー用なので。
			}

			if (heros_def_list[temp].PartyIn == 1) {
				// 何もしない
			}

		}

		// hikaeNinzu = tourokuNakama - skip;
		hikaeNarabijyun[skip] = -1;

	}

}



void pre_guild() {

	//MessageBox(NULL, TEXT("ギルドのテスト中。\n"), TEXT("キーテスト"), MB_OK);

	key_remain = 0;

	whomTargetID1 = 0; whomCHARA = 1;
	whomTargetID1party = 0; whomTargetID1hikae = 0;

	Akihaikeisan();


	// 控えメンバーの配列処理の準備
	{
		if (uwadumeFlag == 1) {

			int skip = 0;
			for (int temp = 0; temp <= tourokuNakama; temp = temp + 1) {

				if (heros_def_list[temp].PartyIn == 0) {
					hikaeNarabijyun[skip] = temp;
					skip = skip + 1; // 代入し終わってから、skipを増やす。次のメンバー用なので。
				}

				if (heros_def_list[temp].PartyIn == 1) {
					// 何もしない
				}

			}

			hikaeNarabijyun[skip] = -1;
		}
	}


	mode_scene = MODE_Guild_Main;


}


void check_encount_town() {

	if (where_map == 1 && chara_x == town_X && chara_y == town_Y) {


		popFlagTown = 1;
		lstrcpy(popMsg, TEXT("パーティの編成をできます。"));

		mode_scene = MODE_TOWN;
		// pre_guild(hWnd);


	}
}










void check_MapTransition() {
	//MessageBox(NULL, TEXT("マップ遷移の判定にいる。"), TEXT("キーテスト"), MB_OK);

	if (chara_x == MapTrans_def_list[(where_map)-1].positionX && chara_y == MapTrans_def_list[where_map - 1].positionY)
	{
		//MessageBox(NULL, TEXT("マップ遷移の直前にいる。"), TEXT("キーテスト"), MB_OK);		

		chara_x = MapTrans_def_list[where_map - 1].chara_positionX;
		chara_y = MapTrans_def_list[where_map - 1].chara_positionY;

		where_map = MapTrans_def_list[where_map - 1].to_Where_Map; // マップを移動先に上書き

		//mapTrans_flag_is = 1; // 移動先にマップ遷移が存在するか



		desti_x = chara_x; // 移動先のリセット		
		desti_y = chara_y;



		// ここから先、移動先のマップ描画のための処理

		// 移動先マップにあるマップ遷移の情報を書く
		MapTrans_position_x = MapTrans_def_list[where_map - 1].positionX;
		MapTrans_position_y = MapTrans_def_list[where_map - 1].positionY;


		// maptableに移動先マップを代入
		int x_map = 0, y_map = 0;

		for (x_map = 0; x_map <= 9; ++x_map)
		{
			for (y_map = 0; y_map <= 6; ++y_map)
			{
				// 代入内容は、移動先マップの代入をすることに注意

				for (int i = 0; i <= tourokuMapChip - 1; ++i) { // 全マップをチェック
					if (where_map == i + 1) {
						maptable[y_map][x_map] = map_def_list[i].map_table[y_map][x_map];
					}
				}

			}
		}


	}
}




static int hero1_already_attack_flag = 0;
static int enemy_already_attack_flag = 0;

static int battle_key = 1;

static int damage_HeroAttack = 1;
static int damage_EnemyAttack = 0;

void heroside_attack() {

	int pnCommon = partyNarabijyun[actionOrder[globalTempA]];


	if (heros_def_list[pnCommon].heros_HP0_flag == 0) {
		// 主人公たちの攻撃


		{

			/* 乱数の種 */
			// wWinMain で定義済み


			/* サイコロ */
			damage_HeroAttack = rand() % 6 + 2 + heros_def_list[pnCommon].heros_bukiKougekiRyoku;

			// 敵にダメージ
			monster_hp = monster_hp - damage_HeroAttack;

			// モンスターの死亡の処理
			if (monster_hp < 1) {
				monster_hp = 0;

				enemy_alive[(encount_monters_id)-1] = 0; // フィールド上の敵の除去

				encount_mons_alive = 0; // 現在戦闘中の敵を死亡にフラグ設定

			}


		}
	}

}



void enemy_attack() {

	// 敵たちの攻撃
	{

		/* 乱数の種 */
		// wWinMain で定義済み

		/* サイコロ */
		damage_EnemyAttack = rand() % (6 / 2) + 0 + 2 * monster_def_list[encount_monters_id - 1].mon_attackPower;

		// 隊列1人目にダメージ
		if (heros_def_list[partyNarabijyun[0]].heros_HP0_flag != 1) {

			heros_def_list[partyNarabijyun[0]].heros_hp = heros_def_list[partyNarabijyun[0]].heros_hp - damage_EnemyAttack;
			uketKyara = 1;
		}

		if (heros_def_list[partyNarabijyun[0]].heros_HP0_flag == 1 && partyNinzuDone >= 2) {

			heros_def_list[partyNarabijyun[1]].heros_hp = heros_def_list[partyNarabijyun[1]].heros_hp - damage_EnemyAttack;
			uketKyara = 2;
		}

		if (heros_def_list[partyNarabijyun[0]].heros_HP0_flag == 1
			&& partyNinzuDone >= 3
			&& heros_def_list[partyNarabijyun[1]].heros_HP0_flag == 1) {

			heros_def_list[partyNarabijyun[2]].heros_hp = heros_def_list[partyNarabijyun[2]].heros_hp - damage_EnemyAttack;
			uketKyara = 3;
		}



		int tempVal;
		for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
			// MessageBox(NULL, TEXT("いまfoそこ。"), TEXT("キーテスト"), MB_OK);
			tempVal = partyNarabijyun[temp];

			if (heros_def_list[tempVal].heros_hp < 1) {
				heros_def_list[tempVal].heros_hp = 0;

				// 戦闘不能フラグがオン
				heros_def_list[tempVal].heros_HP0_flag = 1;
			} // heros_def_list[partyNarabijyun[temp]].
		}


	}
	// MessageBox(NULL, TEXT("いまそこ。"), TEXT("キーテスト"), MB_OK);



}



char strCount[64];
























// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // ウィンドウモードに設定

	// SetUseSoftwareRenderModeFlag(TRUE); // ソフトウェアレンダリングのテスト

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);







	// mode_scene = MODE_OP;










	int mapchip1Handle = LoadGraph("GameData\\mapchip\\mapchip_grass.bmp");
	int mapchip2Handle = LoadGraph("GameData\\mapchip\\mapchip_wall.bmp");




	int koboHandle = LoadGraph("GameData\\monster_graphic\\kobo.png");
	int monchipDownHandle = LoadGraph("GameData\\charachip\\enemy_dot.bmp");
	int blackchipHandle = LoadGraph("GameData\\charachip\\blackchip.bmp");


	int blackbackHandle = LoadGraph("GameData\\picture\\blackBigBack.bmp");



	int charachipUpHandle = LoadGraph("GameData\\charachip\\hero_dot_up.bmp");
	int charachipDownHandle = LoadGraph("GameData\\charachip\\hero_dot_down.bmp");
	int charachipLeftHandle = LoadGraph("GameData\\charachip\\hero_dot_left.bmp");
	int charachipRightHandle = LoadGraph("GameData\\charachip\\hero_dot_right.bmp");







	// アイテムの情報
	int tourokuItem = 3;
	for (int temp = 0; temp <= tourokuItem; temp++) {

		item_def_list[temp].def_id = temp;
		item_def_list[temp].item_type = siyouType;

		if (temp == 0) {
			//薬草の定義
			lstrcpy(item_def_list[temp].def_name, TEXT("--------"));
		}

		if (temp == 1) {
			//薬草の定義
			lstrcpy(item_def_list[temp].def_name, TEXT("薬草"));
		}

		if (temp == 2) {
			lstrcpy(item_def_list[temp].def_name, TEXT("毒消し草"));
		}

		if (temp == 3) {
			lstrcpy(item_def_list[temp].def_name, TEXT("不死鳥の尾")); // 漢字の理由は字数の節約			
		}

	}



	//武器の定義
	// 計算量が2乗時間のアルゴリズムだけど、とりあえず編集性やバグ耐性を優先し、計算時間は考慮しない。
	// どうしても計算時間を短縮したいなら、ifをswitch-breakに置き換えれば、読み込み時間を若干、減らせるか。
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			weapon_def_list[temp].def_id = 0;
			lstrcpy(weapon_def_list[temp].def_name, TEXT("--------"));
			weapon_def_list[temp].material = mateNothing;
			weapon_def_list[temp].equip_type = typeNothing;
			weapon_def_list[temp].equipPower = 0; // 攻撃力
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			weapon_def_list[temp].def_id = 1;
			lstrcpy(weapon_def_list[temp].def_name, TEXT("鉄の槍"));
			weapon_def_list[temp].material = mateIron;
			weapon_def_list[temp].equip_type = spear;
			weapon_def_list[temp].equipPower = 107; // 攻撃力	
			continue;
		}

		if (temp == 2) {
			weapon_def_list[temp].def_id = 2;
			lstrcpy(weapon_def_list[temp].def_name, TEXT("鉄のメイス"));
			weapon_def_list[temp].material = mateIron;
			// weapon_def_list[temp].equip_type = spear;
			weapon_def_list[temp].equipPower = 44; // 攻撃力
			continue;
		}


	}


	//防具の定義 タテ
// 計算量が2乗時間のアルゴリズムだけど、とりあえず編集性やバグ耐性を優先し、計算時間は考慮しない。
// どうしても計算時間を短縮したいなら、ifをswitch-breakに置き換えれば、読み込み時間を若干、減らせるか。
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			shield_def_list[temp].def_id = temp;
			lstrcpy(shield_def_list[temp].def_name, TEXT("--------"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 0; // 攻撃力
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			shield_def_list[temp].def_id = temp;
			lstrcpy(shield_def_list[temp].def_name, TEXT("木の盾"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 5; // 攻撃力	
			continue;
		}

		if (temp == 2) {
			shield_def_list[temp].def_id = temp;
			lstrcpy(shield_def_list[temp].def_name, TEXT("鉄の盾"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 10; // 攻撃力
			continue;
		}
	}



	//防具の定義 カブト
// 計算量が2乗時間のアルゴリズムだけど、とりあえず編集性やバグ耐性を優先し、計算時間は考慮しない。
// どうしても計算時間を短縮したいなら、ifをswitch-breakに置き換えれば、読み込み時間を若干、減らせるか。
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			helm_def_list[temp].def_id = temp;
			lstrcpy(helm_def_list[temp].def_name, TEXT("--------"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 0; // 攻撃力
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			helm_def_list[temp].def_id = temp;
			lstrcpy(helm_def_list[temp].def_name, TEXT("木の帽子"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 5; // 攻撃力	
			continue;
		}

		if (temp == 2) {
			helm_def_list[temp].def_id = temp;
			lstrcpy(helm_def_list[temp].def_name, TEXT("鉄のカブト"));
			helm_def_list[temp].material = mateNothing;
			helm_def_list[temp].equip_type = typeNothing;
			helm_def_list[temp].equipPower = 10; // 攻撃力
			continue;
		}
	}


	//防具の定義 ヨロイ
// 計算量が2乗時間のアルゴリズムだけど、とりあえず編集性やバグ耐性を優先し、計算時間は考慮しない。
// どうしても計算時間を短縮したいなら、ifをswitch-breakに置き換えれば、読み込み時間を若干、減らせるか。
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("--------"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 0; // 攻撃力
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("皮の服"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 2; // 攻撃力
			continue;
		}

		if (temp == 2) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("木のヨロイ"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 5; // 攻撃力
			continue;
		}


		if (temp == 3) {
			armor_def_list[temp].def_id = temp;
			lstrcpy(armor_def_list[temp].def_name, TEXT("鎖かたびら"));
			armor_def_list[temp].material = mateNothing;
			armor_def_list[temp].equip_type = typeNothing;
			armor_def_list[temp].equipPower = 10; // 攻撃力
			continue;
		}


	}


	//所持アイテムの個数などの初期値
	for (int temp = 0; temp <= tourokuItem; temp++) {

		item_have_list[temp].have_def_id = temp + 1;

		if (temp == 0) {
			item_have_list[temp].have_kosuu = 0;
		}
		if (temp == 1) {
			item_have_list[temp].have_kosuu = 5;
		}

		if (temp == 2) {
			item_have_list[temp].have_kosuu = 4;
		}

		if (temp == 3) {
			item_have_list[temp].have_kosuu = 2;
		}
	}


	//所持の装備品の個数などの初期値
	for (int temp = 0; temp <= 15 - 1; temp++) {

		weapon_have_list[temp].have_def_id = temp + 1;

		if (temp == 0) {
			weapon_have_list[temp].have_kosuu = 0;
		}

		if (temp == 1) {
			weapon_have_list[temp].have_kosuu = 0;
		}

		if (temp == 2) {
			weapon_have_list[temp].have_kosuu = 0;
		}
	}


	//初期装備の武器

	int equipInitialWeaponId = 1;
	equipWeaponPower = weapon_def_list[equipInitialWeaponId].equipPower;


	// mapの情報
	for (int temp = 0; temp <= 1; temp++) {

		if (temp == 0) {
			// map1 にあるマップ遷移の情報
			MapTrans_def_list[temp].MapTrans_id = 1; // そのマップ中で何番目か？
			MapTrans_def_list[temp].in_Where_Map = 1; // map 何番?
			MapTrans_def_list[temp].to_Where_Map = 2;
			MapTrans_def_list[temp].positionX = 7;
			MapTrans_def_list[temp].positionY = 6;

			MapTrans_def_list[temp].chara_positionX = 2;
			MapTrans_def_list[temp].chara_positionY = 1;
		}

		if (temp == 1) {
			// map2 にあるマップ遷移の情報
			MapTrans_def_list[temp].MapTrans_id = 1;
			MapTrans_def_list[temp].in_Where_Map = 2; // map 何番?
			MapTrans_def_list[temp].to_Where_Map = 1;
			MapTrans_def_list[temp].positionX = 2;
			MapTrans_def_list[temp].positionY = 0;

			MapTrans_def_list[temp].chara_positionX = 7;
			MapTrans_def_list[temp].chara_positionY = 4;
		}
	}


	// モンスターの定義	
	for (int temp = 0; temp <= 1; temp++) {

		if (temp == 0) {
			lstrcpy(monster_def_list[temp].monster_name, TEXT("スライム"));
			monster_def_list[temp].mon_hp_max = 12;
			monster_def_list[temp].mon_agility = 13;
			monster_def_list[temp].monster_id = 1;
			monster_def_list[temp].mon_gold = 1;
			monster_def_list[temp].mon_exp = 2;
			monster_def_list[temp].mon_attackPower = 0;
		}

		if (temp == 1) {
			lstrcpy(monster_def_list[temp].monster_name, TEXT("コボルト"));
			monster_def_list[temp].mon_hp_max = 125;
			monster_def_list[temp].mon_agility = 76;
			monster_def_list[temp].monster_id = 2;
			monster_def_list[temp].mon_gold = 10;
			monster_def_list[temp].mon_exp = 5;
			monster_def_list[temp].mon_attackPower = 1;
		}

	}


	// キャラクターの定義
	for (int temp = 0; temp <= makeNakamaNinzu + 1; temp++) {

		if (temp == 0) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("エロス"));
			heros_def_list[temp].heros_hp = 32; // 20;
			heros_def_list[temp].heros_hp_max = 25;
			heros_def_list[temp].heros_agility = 56;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 1;


			heros_def_list[temp].heros_weapon1 = 1;

			heros_def_list[temp].heros_shield = 2;
			heros_def_list[temp].heros_bukiKougekiRyoku = weapon_def_list[heros_def_list[temp].heros_weapon1].equipPower;

		}

		if (temp == 1) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("ピエ－ル"));
			heros_def_list[temp].heros_hp = 108; //  18;
			heros_def_list[temp].heros_hp_max = 18;
			heros_def_list[temp].heros_agility = 100;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 1;


			heros_def_list[temp].heros_weapon1 = 2;
			heros_def_list[temp].heros_shield = 0;

			heros_def_list[temp].heros_bukiKougekiRyoku = weapon_def_list[heros_def_list[temp].heros_weapon1].equipPower;

		}

		if (temp == 2) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("ゴンザレス"));
			heros_def_list[temp].heros_hp = 5; // 55;
			heros_def_list[temp].heros_hp_max = 55;
			heros_def_list[temp].heros_agility = 55;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 0;

			heros_def_list[temp].heros_shield = 1;
		}

		if (temp == 3) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("ペドロ"));
			heros_def_list[temp].heros_hp = 10;// 12;
			heros_def_list[temp].heros_hp_max = 34;
			heros_def_list[temp].heros_agility = 23;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 0;

			heros_def_list[temp].heros_shield = 0;
		}


		if (temp == 4) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("テスト用キャラ"));
			heros_def_list[temp].heros_hp = 10;// 12;
			heros_def_list[temp].heros_hp_max = 34;
			heros_def_list[temp].heros_agility = 23;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 0;
		}

	}

	akikosuu = partymax - partyNinzuDone;

	partyNarabijyun[0] = 0; // 
	partyNarabijyun[1] = 1;
	partyNarabijyun[2] = -1; // マイナス番なら、そこで終了


	// ニューゲームの時点で、戦闘不能フラグを更新
	for (int temp = 0; temp < tourokuNakama; ++temp) {

		if (heros_def_list[temp].heros_hp < 1) {
			heros_def_list[temp].heros_hp = 0;

			// 戦闘不能フラグをオン
			heros_def_list[temp].heros_HP0_flag = 1;
		}

		if (heros_def_list[temp].heros_hp >= 1) {
			// 戦闘不能フラグをOFF
			heros_def_list[temp].heros_HP0_flag = 0;
		}


	}


	int tempHairetu[BATTLE_Agility_proc + 1]; // 使わないかも?

	tempHairetu[0] = 0;
	tempHairetu[1] = -99;
	memcpy(monsterTairetu_def_list[0].monsterTairetu, tempHairetu, sizeof(tempHairetu));

	tempHairetu[0] = 1;
	tempHairetu[1] = -99;
	memcpy(monsterTairetu_def_list[1].monsterTairetu, tempHairetu, sizeof(tempHairetu));







	while (1) {
		if (ProcessMessage() != 0) { // メッセージ処理
			break;//ウィンドウの×ボタンが押されたらループを抜ける
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}



		ClearDrawScreen();



		// マップ描画
		for (x_mapDraw = 0; x_mapDraw <= 9; ++x_mapDraw)
		{
			for (y_mapDraw = 0; y_mapDraw <= 6; ++y_mapDraw)
			{
				if (map1table[y_mapDraw][x_mapDraw] == 0) {
					DrawGraph(30 * x_mapDraw, 30 * y_mapDraw, mapchip1Handle, false);
				}
				if (map1table[y_mapDraw][x_mapDraw] == 1) {
					DrawGraph(30 * x_mapDraw, 30 * y_mapDraw, mapchip2Handle, false);
				}
			}

		}


		DrawGraph(30 * monPosiX, 30 * monPosiY, monchipDownHandle, false);



		// キャラチップ描画
		{
			if (xPosi == monPosiX && yPosi == monPosiY) {


				// モンスター画像 クリーン洋
				DrawGraph(30 * monPosiX , 30 * monPosiY, blackchipHandle, false);

				//DrawGraph(30 * monPosiX + 50, 30 * monPosiY, monchipDownHandle, true);


			}



			// 個別の向きの画像で上書き
			if (hero1_direction == rightward) {
				tempHandle = charachipRightHandle;

				// 前半
				if (nyuuryokuMatiLR > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi, tempHandle, false);
				}

				// 中盤
				if (nyuuryokuMatiLR <= 20 && nyuuryokuMatiLR > 10) {
					DrawGraph(30 * xPosi + 10, 30 * yPosi, tempHandle, false);
				}

				// 後半
				if (nyuuryokuMatiLR <= 10 && nyuuryokuMatiLR >= 1) {
					DrawGraph(30 * xPosi + 20, 30 * yPosi, tempHandle, false);
				}
			}

			if (hero1_direction == leftward) {

				if (nyuuryokuMatiLR > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi, charachipLeftHandle, false);
				}

				if (nyuuryokuMatiLR <= 20 && nyuuryokuMatiLR > 10) {
					DrawGraph(30 * xPosi - 10, 30 * yPosi, charachipLeftHandle, false);
				}


				if (nyuuryokuMatiLR <= 10 && nyuuryokuMatiLR >= 1) {
					DrawGraph(30 * xPosi - 20, 30 * yPosi, charachipLeftHandle, false);
				}

			}



			if (hero1_direction == downward) {

				if (nyuuryokuMatiUD > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi - 0, charachipDownHandle, false);
				}

				if (nyuuryokuMatiUD <= 20 && nyuuryokuMatiUD > 10) {
					DrawGraph(30 * xPosi, 30 * yPosi + 10, charachipDownHandle, false);
				}


				if (nyuuryokuMatiUD <= 10 && nyuuryokuMatiUD >= 1) {
					DrawGraph(30 * xPosi, 30 * yPosi + 20, charachipDownHandle, false);
				}

			}


			if (hero1_direction == upward) {

				if (nyuuryokuMatiUD > 20) {
					DrawGraph(30 * xPosi, 30 * yPosi + 0, charachipUpHandle, false);
				}

				if (nyuuryokuMatiUD <= 20 && nyuuryokuMatiUD > 10) {
					DrawGraph(30 * xPosi, 30 * yPosi - 10, charachipUpHandle, false);
				}


				if (nyuuryokuMatiUD <= 10 && nyuuryokuMatiUD >= 1) {
					DrawGraph(30 * xPosi, 30 * yPosi - 20, charachipUpHandle, false);
				}

			}

		}


		if (mode_scene == MODE_MAP) {
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
			if (CheckHitKey(KEY_INPUT_X) == 1 && mode_scene == MODE_MAP && keyFlagX == 0 && nyuuryokuMatiX == 0) {
				keyFlagX = 1;
				mode_scene = MODE_MENU;
				nyuuryokuMatiX = 30;
			}


			DrawBox(100, 250, 100 + 150, 250 + 40 + 100,
				GetColor(150, 150, 255), 1);

			DrawFormatString(100, 250, GetColor(255, 255, 255), "座標[%d,%d]", xPosi, yPosi); // 文字を描画する

		} // map モードの終わり


		if (mode_scene == MODE_MENU) {
			int HPX = 300; int HPY = 50;

			// ウィンドウ欄
			DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 100,
				GetColor(150, 150, 255), 1);


			DrawFormatString(HPX +20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // 文字を描画する			
			DrawFormatString(HPX +20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // 文字を描画する


			DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // 文字を描画する
			DrawFormatString(HPX + 20, HPY + 20 * (3+1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // 文字を描画する




			DrawBox(100, 250, 100 + 150, 250 + 40 + 100,
				GetColor(150, 150, 255), 1);

			//DrawFormatString(100, 250, GetColor(255, 255, 255), "座標[%d,%d]", x, y); // 文字を描画する


			if (keyFlagX == 1) {

				DrawFormatString(100, 250 + 40, GetColor(255, 255, 255), "カウント %d", nyuuryokuMatiX); // 文字を描画する
				nyuuryokuMatiX = nyuuryokuMatiX - 1;
			}

			if (nyuuryokuMatiX <= 0) {

				nyuuryokuMatiX = 0;

			}



			if (CheckHitKey(KEY_INPUT_X) == 0 && keyFlagX == 1 && nyuuryokuMatiX == 0) {
				keyFlagX = 2; // マップに戻るためのxボタンの入力可能状態
				DrawFormatString(100, 250, GetColor(255, 255, 255), "座標[%d,%d]", xPosi, yPosi); // 文字を描画する
				DrawFormatString(100, 250 + 40, GetColor(255, 255, 255), "X受付可能"); // 文字を描画する
			}



			if (keyFlagX == 2) {
				// カーソル
					DrawBox(100, 250 + (selecting_mainmenu -1) * 40, 100 + 80, 250 + (selecting_mainmenu - 1) * 40 +40,
						GetColor(250, 150, 150), 1);

					// コマンド欄
				DrawFormatString(100+20, 250, GetColor(255, 255, 255), "道具"); // 文字を描画する
				DrawFormatString(100+20, 250 + 40, GetColor(255, 255, 255), "装備"); // 文字を描画する



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
						selecting_mainmenu--;                       // 上へ1マスだけ移動
						moving = 0;
					}


					if (selecting_mainmenu < 0) {
						selecting_mainmenu = 0;
					}

					if (selecting_mainmenu >= 3) {
						selecting_mainmenu = 3;
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
						selecting_mainmenu++;                       // 下へ1マスだけ移動
						moving = 0;
					}


					if (selecting_mainmenu < 1) {
						selecting_mainmenu = 1;
					}

					if (selecting_mainmenu >= 3) {
						selecting_mainmenu = 3;
					}

					moving = 0;


				}


				if (CheckHitKey(KEY_INPUT_Z) == 1) {

					if (selecting_mainmenu == 1) {
						mode_scene = itemModeMain;
						DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "道具を選びました未実装"); // 文字を描画する
						nyuuryokuMatiZ = 30;
						keyFlagZ = 0;
					}

					if (selecting_mainmenu == 2) {
						mode_scene = MODE_EQUIP_MAIN;
						DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "装備を選びました未実装"); // 文字を描画する
						keyFlagZ = 0;
					}




					if (selecting_mainmenu == 3) {
						MessageBox(NULL, TEXT("特技を使うためのコマンド（※未実装）。"), TEXT("テスト"), MB_OK);

						// mode_scene = MODE_SKILL_MAIN;

					}


					if (selecting_mainmenu == 4) {

						mode_scene = MODE_SAVE_MENU;


						// OP画面の設定のセーブ
						FILE* fp1;

						fp1 = fopen("OPSetting.txt", "w");
						{
							fprintf(fp1, "ニューゲームかどうか: %d \n", 2); // 2なら「つづきから」に設定
						}
						fclose(fp1);


						// セーブするよ
						// ゲーム内データのセーブ
						FILE* fp2;
						{
							fp2 = fopen("savedata1.txt", "w");
							if ((fp2 = fopen("savedata1.txt", "w")) == NULL) {
								MessageBox(NULL, TEXT("セーブが失敗しました。対象ファイルが存在しないようです。"), TEXT("メッセージ"), MB_OK);
								break;
							}
							else {
								fprintf(fp2, "現在マップ番号: %d \n", where_map);
								fprintf(fp2, "キャラ位置x座標: %d \n", chara_x);
								fprintf(fp2, "キャラ位置y座標: %d \n", chara_y);


								// heros_def_list[partyNarabijyun[j]].heros_name
								fprintf(fp2, "パーティ人数: %d \n", partyNinzuDone);
								for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
									fprintf(fp2, "パーティ %d 人目のID: %d \n", temp + 1, partyNarabijyun[temp]);
								}

								fprintf(fp2, "控え人数: %d \n", hikaeNinzu);
								for (int temp = 0; temp <= hikaeNinzu - 1; ++temp) {
									fprintf(fp2, "控え %d 人目のID: %d \n", temp + 1, hikaeNarabijyun[temp]);
								}

								// ロードの都合により、HPのforは最大HPのforとは統合しないこと。
								for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
									fprintf(fp2, "パーティ内キャラ %d 番目の現HP: %d \n", temp + 1, heros_def_list[partyNarabijyun[temp]].heros_hp);
								}

								for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
									fprintf(fp2, "パーティ内キャラ %d 番目の最大HP: %d \n", temp + 1, heros_def_list[partyNarabijyun[temp]].heros_hp_max);
								}


								for (int temp = 0; temp <= partyNinzuDone - 1; ++temp) {
									fprintf(fp2, "パーティキャラ %d 番目の武器: %d \n", temp + 1, weapon_def_list[
										heros_def_list[partyNarabijyun[temp]].heros_weapon1].def_id);
								}


								// 登録仲間のパラメーター。　一部はパーティパラと重複する
								for (int temp = 0; temp <= tourokuNakama; ++temp) {
									fprintf(fp2, "登録キャラ %d 番目の現HP: %d \n", temp + 1, heros_def_list[temp].heros_hp);
								}

								for (int temp = 0; temp <= tourokuNakama; ++temp) {
									fprintf(fp2, "登録キャラ %d 番目の最大HP: %d \n", temp + 1, heros_def_list[temp].heros_hp_max);
								}

								for (int temp = 0; temp <= tourokuNakama; ++temp) {
									fprintf(fp2, "登録キャラ %d 番目の武器: %d \n", temp + 1, weapon_def_list[
										heros_def_list[temp].heros_weapon1].def_id);
								}

								for (int temp = 0; temp <= tourokuNakama; ++temp) {
									fprintf(fp2, "登録キャラ %d 番目の盾: %d \n", temp + 1, shield_def_list[
										heros_def_list[temp].heros_shield].def_id);
								}

								for (int temp = 0; temp <= tourokuNakama; ++temp) {
									fprintf(fp2, "登録キャラ %d 番目の兜: %d \n", temp + 1, helm_def_list[
										heros_def_list[temp].heros_helm].def_id);
								}

								for (int temp = 0; temp <= tourokuNakama; ++temp) {
									fprintf(fp2, "登録キャラ %d 番目の経験値: %d \n", temp + 1, heros_def_list[temp].heros_exp);
								}


								fprintf(fp2, "所持金: %d G\n", your_money);

								char aaa[100];


								// アイテム類の所持数


								// 使用品の所持数
								for (int temp = 0; temp <= 3 - 1; ++temp) {
									//WideCharToMultiByte(CP_ACP, 0, item_def_list[temp].def_name, -1, aaa, sizeof(aaa), NULL, NULL);
									fprintf(fp2, "%s の個数: %d \n", aaa, item_have_list[temp].have_kosuu);
								}

								// 装備品の武器の所持数
								for (int temp = 0; temp <= 3 - 1; ++temp) {
									//WideCharToMultiByte(CP_ACP, 0, weapon_def_list[temp].def_name, -1, aaa, sizeof(aaa), NULL, NULL);
									fprintf(fp2, "%s の個数: %d \n", aaa, weapon_have_list[temp].have_kosuu);
								}

								// 装備品の盾の所持数
								for (int temp = 0; temp <= 3 - 1; ++temp) {
									//WideCharToMultiByte(CP_ACP, 0, shield_def_list[temp].def_name, -1, aaa, sizeof(aaa), NULL, NULL);
									fprintf(fp2, "%s の個数: %d \n", aaa, shield_have_list[temp].have_kosuu);
								}


								// 装備品のカブトの所持数
								for (int temp = 0; temp <= 3 - 1; ++temp) {
									//WideCharToMultiByte(CP_ACP, 0, helm_def_list[temp].def_name, -1, aaa, sizeof(aaa), NULL, NULL);
									fprintf(fp2, "%s の個数: %d \n", aaa, helm_have_list[temp].have_kosuu);
								}


								fclose(fp2);
							}
						}

						TimeCount = 0;
						mode_scene = MODE_saving_Now; // セーブ終了後にタイマーでしばらく表示。
						// MessageBox(NULL, TEXT("いまここ"), TEXT("メッセージ"), MB_OK);



					}


					if (selecting_mainmenu == 5) {
						// MessageBox(NULL, TEXT("並び替えをするためのコマンド（※未実装）。"), TEXT("テスト"), MB_OK);

						for (int temp = 0; temp <= partyNinzuDone - 1; temp = temp + 1) {
							partyNarabijyunBefore[temp] = partyNarabijyun[temp];
							partyNarabijyunAfter[temp] = partyNarabijyun[temp];
						}

						whomTargetID1 = 0;
						mode_scene = MODE_narabikae_select1;

					
					}




				}
			}



			if (CheckHitKey(KEY_INPUT_X) == 1 && keyFlagX == 2) {
				mode_scene = MODE_MAP;
				keyFlagX = 0; // 使い終わったのでゼロに戻す 
				nyuuryokuMatiX = 30;

				DrawFormatString(100, 250, GetColor(255, 255, 255), "座標[%d,%d]", xPosi, yPosi); // 文字を描画する

			}


		} // menu の終わり


		if (mode_scene == itemModeMain) {
			int HPX = 300; int HPY = 50;

			DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 100,
				GetColor(150, 150, 255), 1);



			DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // 文字を描画する			
			DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // 文字を描画する

			// DrawFormatString(HPX +20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // 文字を描画する





			DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // 文字を描画する
			DrawFormatString(HPX + 20, HPY + 20 * (3 + 1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // 文字を描画する





			int itemWindX = 450;
			int itemWindY = 50;

			// 道具欄の描画
			DrawBox(itemWindX, itemWindY, itemWindX + 80+40, itemWindY + 180,
				GetColor(100, 100, 250), 1);

			// カーソル描画
			DrawBox(itemWindX, itemWindY + kasol2Target * 40, itemWindX + 80, itemWindY + kasol2Target * 40 + 40,
				GetColor(250, 150, 150), 1);


			DrawFormatString(itemWindX, itemWindY + 40 * 0, GetColor(255, 255, 255), "薬草 %d", item_have_list[1].have_kosuu); // 文字を描画する
			DrawFormatString(itemWindX, itemWindY + 40 * 1, GetColor(255, 255, 255), "毒消し薬 %d", item_have_list[2].have_kosuu); // 文字を描画する



			// MatiX を見るのはターゲット選択からの戻り用
			if (CheckHitKey(KEY_INPUT_X) == 1 && nyuuryokuMatiX <= 0 ) {
				

				// 道具欄は使わないので、道具欄を黒で塗りつぶすことで非表示にしている。
				DrawBox(itemWindX, itemWindY, itemWindX + 150, itemWindY + 180,
					GetColor(0, 0, 0), 1);


				mode_scene = MODE_MENU; 
				keyFlagX = 1; // 使い終わったので1にしないとバグ
				nyuuryokuMatiX = 30;

				waitKasol = 30;
				DrawFormatString(250, 250+50, GetColor(255, 255, 255), "道具から戻り"); // 文字を描画する


			}


			if (keyFlagZ == 0  && nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // 文字を描画する


			}
			if (nyuuryokuMatiZ <= 0) {
				nyuuryokuMatiZ = 0;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // 文字を描画する


			}

			if (nyuuryokuMatiX > 0) {
				nyuuryokuMatiX = nyuuryokuMatiX - 1;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // 文字を描画する
			}

			if (nyuuryokuMatiX <= 0) {
				nyuuryokuMatiX = 0;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // 文字を描画する


			}




			// デバッグ用
			DrawFormatString(200, 250 + 150 - 50, GetColor(0, 0, 0), "■■■"); // 文字を描画する
			DrawFormatString(200, 250 + 150 - 50, GetColor(255, 255, 255), "%d",nyuuryokuMatiZ); // 文字を描画する


	


			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyFlagZ == 1) {
				if (kasol2Target==0 && item_have_list[1].have_kosuu >= 1) {

					keyFlagZ = 2;
					nyuuryokuMatiZ = 30;
					mode_scene = itemModeTarget;
				}

				if (kasol2Target == 1 && item_have_list[2].have_kosuu >= 1) {

					keyFlagZ = 2;
					nyuuryokuMatiZ = 30;
					mode_scene = itemModeTarget;
				}


			}

			// カウント処理
			if (nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				// デバッグ用
				DrawFormatString(250, 250 + 150, GetColor(255, 255, 255), "aaa567"); // 文字を描画する
			}

			if (nyuuryokuMatiZ <= 0 && keyFlagZ == 0) {
				keyFlagZ = 1;
				nyuuryokuMatiZ = 0;
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



		if (mode_scene == itemModeTarget) {

			int itemWindX = 450;
			int itemWindY = 50;


			// mode_scene = itemModeTarget;



			// 道具欄を黒で塗りつぶして非表示にする。
			// DrawBox(350, 50, 350 + 150, 50 + 180,
			//	GetColor(0, 0, 0), 1);

			// keyFlagZ = 1;
			// waitKasol = 20;
			//}

			// デバッグ用
			DrawFormatString(itemWindX, 250 + 150 - 20, GetColor(255, 255, 255), "kkkkkkk"); // 文字を描画する

			// カウント処理
			if (keyFlagZ == 2 && nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;
				keyFlagZ = 3;
				// デバッグ用
				DrawFormatString(250, 250 + 150, GetColor(255, 255, 255), "aaa567"); // 文字を描画する
			}



			if (nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // 文字を描画する
			}

			if (nyuuryokuMatiZ <= 0) {
				nyuuryokuMatiZ = 0;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // 文字を描画する
			}


			int HPX = 300; int HPY = 50;

			DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 50,
				GetColor(150, 150, 255), 1);

			// カーソル
			DrawBox(HPX, HPY + kasol3Target * 60, HPX + 130, HPY + 50 + kasol3Target * 60,
				GetColor(255, 150, 150), 1);






			DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // 文字を描画する			
			DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // 文字を描画する

			DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // 文字を描画する
			DrawFormatString(HPX + 20, HPY + 20 * (3 + 1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // 文字を描画する







			if (nyuuryokuMatiX > 0) {
				nyuuryokuMatiX = nyuuryokuMatiX - 1;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // 文字を描画する
			}

			if (nyuuryokuMatiX <= 0) {
				nyuuryokuMatiX = 0;

				//DrawFormatString(250, 250 + 150 -50, GetColor(255, 255, 255), "ttttttt"); // 文字を描画する


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
					kasol3Target--;                       // 上へ1マスだけ移動
					moving = 0;
				}


				if (kasol3Target < 0) {
					kasol3Target = 0;
				}

				if (kasol3Target >= 3) {
					kasol3Target = 3;
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
					kasol3Target++;                       // 下へ1マスだけ移動
					moving = 0;
				}


				if (kasol3Target < 0) {
					kasol3Target = 0;
				}

				if (kasol3Target >= 3) {
					kasol3Target = 3;
				}
			}



			if (CheckHitKey(KEY_INPUT_X) == 1 &&  nyuuryokuMatiX <= 0) {
				keyFlagX = 0;
				keyFlagZ = 0; // 戻りで使うので設定

				mode_scene = itemModeMain;
				nyuuryokuMatiX = 30;
			}

			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyFlagZ == 3) {


				// 実行処理とカウント終了処理
				
					keyFlagZ = 2;
					nyuuryokuMatiZ = 30;
					nyuuryokuMatiX = 0;

					int HPX = 300; int HPY = 50;

					//DrawBox(HPX, HPY, HPX + 150, HPY + 340 + 100,
					//	GetColor(150, 150, 255), 1);


					DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // 文字を描画する			
					DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // 文字を描画する


					DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // 文字を描画する
					DrawFormatString(HPX + 20, HPY + 20 * (3 + 1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // 文字を描画する



					if (item_have_list[kasol2Target +1].have_kosuu > 0) {
						item_have_list[kasol2Target + 1].have_kosuu = item_have_list[kasol2Target + 1].have_kosuu - 1;

						if (kasol2Target == 0) {
							
							heros_def_list[kasol3Target].heros_hp = heros_def_list[kasol3Target].heros_hp + 5;
						}

						if (kasol2Target == 1) {

							heros_def_list[kasol3Target].heros_hp = heros_def_list[kasol3Target].heros_hp + 2;
						}


					}
					if (item_have_list[kasol2Target + 1].have_kosuu <= 0) {
						item_have_list[kasol2Target + 1].have_kosuu = 0;
					}





				// mode_scene = itemModeTarget;

			}




		}











		if (mode_scene == MODE_EQUIP_MAIN) {


			// グラフィック関係
			{
				// 装備の表示欄
				// メインモードは装備キャラの選択モードである

				// MainGraFrontMenu();

				//BrushBlue_set();

				//BrushPink_set();

				// Rectangle(hdc, 20 + (selecting_mainmenu - 1) * 100, 20,
				//	100 + (selecting_mainmenu - 1) * 100, 70);

				int StatsHPbaseX = 130;
				int StatsHPbaseY = 130;
				int offsetY = 120;


				// 背景の青
				//SelectObject(hdc, blue_thin_1);

				DrawBox(10, 350, 500, 400,
					GetColor(150, 150, 255), 1);

				//Rectangle(hdc, 10, 350, 500, 400);

				//SetBkMode(hdc, TRANSPARENT);
				lstrcpy(mojibuf,
					TEXT("装備を変更するキャラを選んでください。"));
				//TextOut(hdc, 15, 350 + 10, mojibuf, lstrlen(mojibuf));
				DrawFormatString(15, 350 + 10, GetColor(255, 255, 255), mojibuf); // 文字を描画する



				for (int j = 0; j <= partyNinzuDone - 1; ++j) {
					// 背景の青
					// SelectObject(hdc, blue_thin_1);
					//Rectangle(hdc, 10, 100 + offsetY * j, 300,
					//	200 + offsetY * j);


					DrawBox(10, 100 + offsetY * j, 300, 200 + offsetY * j,
						GetColor(150, 150, 255), 1);


					// カーソル
					if (whomTargetID1 == j) {
						//BrushPink_set();

						//Rectangle(hdc,
						//	10 + 10, 100 + 10 + 120 * (whomTargetID1),
						//	300 - 10, 100 + 70 + 120 * (whomTargetID1));


						DrawBox(10 + 10, 100 + 10 + 120 * (whomTargetID1),
							300 - 10, 100 + 70 + 120 * (whomTargetID1),
							GetColor(255, 150, 150), 1);


					}

					//SetBkMode(hdc, TRANSPARENT);

					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("%s"),
						heros_def_list[partyNarabijyun[j]].heros_name);
					//TextOut(hdc, StatsHPbaseX,
					//	StatsHPbaseY - 25 + offsetY * j, mojibuf,
					//	lstrlen(mojibuf));


					DrawFormatString(StatsHPbaseX,
						StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する



					lstrcpy(mojibuf, TEXT("HP"));
					//TextOut(hdc, StatsHPbaseX, StatsHPbaseY + offsetY * j,
					//	mojibuf, lstrlen(mojibuf));

					DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する






					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("%d"),
						heros_def_list[partyNarabijyun[j]].heros_hp);
					//TextOut(hdc, StatsHPbaseX + 30,
					//	StatsHPbaseY + offsetY * j, mojibuf,
					//	lstrlen(mojibuf));

					DrawFormatString(StatsHPbaseX + 30,
						StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する




					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("/ %d"),
						heros_def_list[partyNarabijyun[j]].heros_hp_max);
					//TextOut(hdc, StatsHPbaseX + 30 * 2,
					//	StatsHPbaseY + offsetY * j, mojibuf,
					//	lstrlen(mojibuf));



					DrawFormatString(StatsHPbaseX + 30 * 2,
						StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する



					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("%d"),
						heros_def_list[partyNarabijyun[j]].heros_HP0_flag);
					//TextOut(hdc, StatsHPbaseX,
					//	StatsHPbaseY + 40 + offsetY * j, mojibuf,
					//	lstrlen(mojibuf));


					DrawFormatString(StatsHPbaseX,
						StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する






					if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag ==
						1) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("戦闘不能"));
						//TextOut(hdc, StatsHPbaseX,
						//	StatsHPbaseY + 40 + offsetY * j, mojibuf,
						//	lstrlen(mojibuf));

						DrawFormatString(StatsHPbaseX,
							StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する




					}


					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("mode: %d"), mode_scene);
					//TextOut(hdc, 130 * 2, 300, mojibuf, lstrlen(mojibuf));

					DrawFormatString(130 * 2, 300, GetColor(255, 255, 255), mojibuf); // 文字を描画する




				}

				// そのキャラの装備項目の選択がサブモード
			}// グラフィック関係


			if (CheckHitKey(KEY_INPUT_Z) == 1 && key_remain ==1) {
			
				key_remain = 0;
				whomTargetID1 = whomCHARA - 1;

				//mode_scene = MODE_EQUIP_EDIT;
				beforeselect = 0;
			
			}


			if (CheckHitKey(KEY_INPUT_X) == 1 ) {

				filterFlag = 0;
				mode_scene = MODE_MENU;

				nyuuryokuMatiX = 30;
				key_remain = 0;
				keyFlagX = 1;
			}

		} // equip モードの終わり
















		if (mode_scene == skillMode) {
			if (CheckHitKey(KEY_INPUT_X) == 1) {
				mode_scene = MODE_MENU;
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