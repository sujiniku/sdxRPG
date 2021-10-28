#include "DxLib.h"


#include <stdio.h> // セーブ用
#pragma warning(disable:4996) // fopen


#include <math.h>  // 切り上げ計算で使用

int waitheal = 0; // 回復の表示中の長さ
int damepyon = 0; // 戦闘中にダメージをピョンと動かすアレ
int tekidame = 0; // 敵のダメージ受けてる間だけオン
int mikatadame = 0; // mikataのダメージ受けてる間だけオン

int senkaFlag = 0;

int wind1R = 50;
int wind1G = 50;
int wind1B = 150;

int window1color = GetColor(wind1R, wind1G, wind1B); // ウィンドウのほか、カーソルのベース色でも使う可能性があるので変数化。
void window1Draw(int X1, int Y1, int X2, int Y2) {
	DrawBox(X1, Y1, X2, Y2,
		window1color, 1);

	DrawBox(X1, Y1, X2, Y2, GetColor(255, 255, 255), 0);

}

int darkwindow1color = GetColor(wind1R /2, wind1G /2, wind1B /2);
void darkwindow1Draw(int X1, int Y1, int X2, int Y2) {
	DrawBox(X1, Y1, X2, Y2,
		darkwindow1color, 1);

	DrawBox(X1, Y1, X2, Y2, GetColor(255/2, 255/2, 255/2), 0);

}

int debugFlag = 0;

int casolu1R = 250; // l と 1 の区別のため u 追加
int casolu1G = 150;
int casolu1B = 150;

int KasolColor = GetColor(casolu1R, casolu1G, casolu1B);
void redCasol1(int X1, int Y1, int X2, int Y2) {
	DrawBox(X1, Y1, X2, Y2,
		KasolColor, 1);
}



int TimeKasolCount = 0;

void tenmetu(int X1, int Y1, int X2, int Y2) {

	double redVal = 0;

	double spanBlink = 120.0;

	if (TimeKasolCount < (int)spanBlink) {
		redVal = TimeKasolCount;
	}
	if (TimeKasolCount >= (int)spanBlink) {
		redVal = spanBlink * 2 - TimeKasolCount;
	}


	int whiteMax = 180;

	DrawBox(X1, Y1, X2, Y2,

		GetColor(wind1R + (whiteMax - wind1R) * (redVal / spanBlink),
			wind1G + (whiteMax - wind1G) * (redVal / spanBlink),
			wind1B + 1 * (whiteMax - wind1B) * (redVal / spanBlink)),
		1);

	DrawBox(X1, Y1, X2, Y2, GetColor(255, 255, 255), 0);


	TimeKasolCount = TimeKasolCount + 1;
	if (TimeKasolCount > spanBlink * 2) {
		TimeKasolCount = 0;
	}

}


void tenmetuStop(int X1, int Y1, int X2, int Y2) {

	double redVal = 0;

	double spanBlink = 120.0;

	if (TimeKasolCount < (int)spanBlink) {
		redVal = TimeKasolCount;
	}
	if (TimeKasolCount >= (int)spanBlink) {
		redVal = spanBlink * 2 - TimeKasolCount;
	}

	redVal = spanBlink / 2;

	int whiteMax = 180;

	DrawBox(X1, Y1, X2, Y2,

		GetColor(wind1R + (whiteMax - wind1R) * (redVal / spanBlink),
			wind1G + (whiteMax - wind1G) * (redVal / spanBlink),
			wind1B + 1 * (whiteMax - wind1B) * (redVal / spanBlink)),
		1);


	if (TimeKasolCount > spanBlink * 2) {
		TimeKasolCount = 0;
	}

}



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


int battlewait = 30;
//int battleTraFlag = 0;
int keyHaijyo = 0;


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


int toubouTyokugo = 0;


int xPosi = 2;
int yPosi = 2;


int moving = 0; //キャラチップ画像が移動中なら0

int keyEnableUp = 0;
int keyEnableDown = 0;
int keyEnableRight = 0;
int keyEnableLeft = 0;

int keyEnableUpRight = 0;

int keyEnableX = 0;
int keyEnableZ = 0;


int waitTime1 = 60;
int waitTime2 = 30;


int nyuuryokuMatiLR = waitTime1;
int nyuuryokuMatiUD = waitTime1;

int nyuuryokuMatiX = waitTime1;
int nyuuryokuMatiZ = waitTime1;


int nyuuryokuMatiUp = waitTime1;
int nyuuryokuMatiDown = waitTime1;


int nyuuryokuMatiRight = waitTime1;
int nyuuryokuMatiLeft = waitTime1;


int waitKasol = waitTime1;


int kasol2Target = 0;
int kasol3Target = 0;


int tempHandle;
int destMovable;


enum direction { upward, rightward, downward, leftward };
enum direction hero1_direction = downward;

enum mode {
	MODE_OP, MODE_LOAD, MODE_INITIAL, MODE_MAP,

	MODE_TOWN,

	MODE_Shop_Main, MODE_Shop_weapon_main, MODE_Shop_weapon_buy, MODE_Shop_weapon_sell, MODE_Shop_weapon_buyOld,
	MODE_Shop_armor_main, MODE_Shop_armor_buy, MODE_Shop_armor_sell, MODE_Shop_armor_buyOld,
	MODE_Shop_akusesari_main, MODE_Shop_item_main,

	MODE_MENU,

	MODE_narabikae_select1, MODE_narabikae_select2,

	MODE_ITEM_TYPE, MODE_ITEM_MENU, MODE_ITEM_MENU_FRONT,
	MODE_ITEMweapon_MENU, MODE_ITEMweapon_MENU_FRONT, MODE_ITEM_WHOM, MODE_ITEM_WHOM_FRONT,

	MODE_EQUIP_MAIN, MODE_EQUIP_EDIT, MODE_EQUIP_EDIT2,


	MODE_SAVE_MENU, MODE_saving_Now,

	MODE_BATTLE_COMMAND, MODE_BATTLE_NOW, MODE_BATTLE_WIN, BATTLE_Agility_proc,

	MODE_Guild_Main, MODE_Guild_Responce, MODE_Guild_Remove,

	itemModeMain, itemModeTarget, skillMode,
};
enum mode mode_scene = MODE_MAP;


enum mode2 {
	MODE2_EQUIP_UnDef, // 未定義対応
	MODE2_EQUIP_HAND1,
	MODE2_EQUIP_SHIELD,
	MODE2_EQUIP_HELM,
	MODE2_EQUIP_ARMOR
};
enum mode2 mode2_scene = MODE2_EQUIP_HAND1;

int mode3_scene = 0 ;


int yakusouKosuu = 5;
int dokukesiKosuu = 3;
int soesiKosuu = 4;


int NaraSele1 = 0;

int NaraSele2 = 0;


int uketKyara = 1; // 戦闘中で、何人目がダメージ受けてるか。「1」で1人目。

int pageSyori = 0;


// アイテム種類番号
int siyouType = 10; // 0～9番はシステム処理用に確保

int soubiOffset = 11; // wepoTypeと同番号だが、拡張性や可読性を考え、別変数を用意

int wepoType = soubiOffset ; // 11
int tateType = soubiOffset + 1; // 12;
int kabutoType = soubiOffset + 2; // 13;

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



struct soubi_have
{
	int have_type;
	int have_def_id;
	int have_kosuu;
};


struct soubi_def
{
	int def_type;
	int def_id;
	TCHAR def_name[MAX_LENGTH];
	int material;
	int equip_type;
	int equipPower[20];// 攻撃力や防御力などに使用


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

int healflag = 0;
int healti = 0;
int healkioku = 0; // 回復したあと、数秒の表示を記憶するため。


// 味方パーティ構造体 (モンスター構造体の流用)
struct heros_def
{
	int heros_id;
	TCHAR heros_name[MAX_LENGTH];
	int heros_hp;
	int heros_hpdiff;


	int heros_hp_max;
	int heros_agility;

	int heros_gold; // ウィザードリィみたいに各キャラごとにゴールドを持てるようになってる。
	int heros_exp;

	int heros_HP0_flag;

	int PartyIn;

	int heroSoubi[20];
	int heroSoubiKasol[20];

	// 装備品 // 不要
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

	int heros_para[20]; // 攻撃力や守備力の用を合計20、用意。

};

int kougekiPara = 1;
int syubiPara = 2;


enum next_attack_flag { next_is_hero, next_is_enemy };
enum next_attack_flag next_attack_var = next_is_hero;


static int encount_monters_id = 2;


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




int dameKei = 0; // ダメージ計算を1回数だけ行うためのフラグ


// アイテムメニューでのカーソル位置の計算用
void item_select() {

	if (selecting_item < 1) {
		selecting_item = 1;
	}

	if (selecting_item > goukeiItem) {
		selecting_item = goukeiItem;
	}

	selecting_item_x = ((selecting_item - 1) % 2) + 1;
	selecting_item_y = ((selecting_item - 1) / 2) + 1;


	// 矢印キーの入力前後でカーソルが同じ位置のままだったら、画面を更新しないための処理
	selecting_itemAfter = selecting_item;


	// 矢印キーの入力前後でカーソルが同じ位置のままだったら、画面を更新しない
	// 画面のチラツキ防止のため

	if (selecting_itemBefore != selecting_itemAfter) {
		//InvalidateRect(hWnd, NULL, FALSE);
		//UpdateWindow(hWnd);
	}
}


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


void menu_CharaSelectDraw() {

	// 画像の読み込み「image2」は変数名。これが背景フィルター。
	if (filterFlag == 0) {

		//Image image2(L"filter.png");

		// 画像の描画。 ダミー変数 graphics を仲介して描画する必要がある.

		//graphics.DrawImage(&image2, 0, 0, image2.GetWidth(), image2.GetHeight());
		filterFlag = 1;
	}


	int winX1 = 10;
	int winY1 = 100;
	int winX2 = 300;
	int winY2 = 200;


	int StatsHPbaseX = winX1 + 120; int StatsHPbaseY = winY1 + 30;
	int offsetY = 120;


	for (int j = 0; j <= partyNinzuDone - 1; ++j) {

		// 背景の青

		window1Draw(winX1, winY1 + offsetY * j,
			winX2, winY2 + offsetY * j);

		if (mode_scene == MODE_ITEM_WHOM) {
			// カーソル
			if (whomTargetID1 == j) {
				
				tenmetu(winX1, winY1 + offsetY * (whomTargetID1),
					winX2, winY2 + offsetY * (whomTargetID1));

				//MessageBox(NULL, TEXT("デバッグ。"), TEXT("テスト"), MB_OK);

			}
		}


		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), heros_def_list[partyNarabijyun[j]].heros_name);
		DrawFormatString(StatsHPbaseX, StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		lstrcpy(mojibuf, TEXT("HP"));
		DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_hp);
		DrawFormatString(StatsHPbaseX + 30, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


		int revwait = 120 - waitheal;

		if (healflag == 1 && healkioku == j) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), healti); // heros_def_list[partyNarabijyun[j]].heros_hpdiff);
			DrawFormatString(StatsHPbaseX + 30 +20, StatsHPbaseY -20 + offsetY * j  +20 - 2 * revwait, GetColor(10, 255, 10), mojibuf); // 文字を描画する

		}

		if (healflag == 2 && healkioku == j) {

			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), healti); // heros_def_list[partyNarabijyun[j]].heros_hpdiff);
			DrawFormatString(StatsHPbaseX + 30 +20, StatsHPbaseY - 20 + offsetY * j - (60) / 6, GetColor(10, 255, 10), mojibuf); // 文字を描画する

		}


		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("/ %d"), heros_def_list[partyNarabijyun[j]].heros_hp_max);
		DrawFormatString(StatsHPbaseX + 30 * 2, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_HP0_flag);
		DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


		if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag == 1) {
			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("戦闘不能"));
			DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		}

	} // end for
}


void menu_CharaSelectDraw2() {


	// 画像の読み込み「image2」は変数名。これが背景フィルター。
	if (filterFlag == 0) {

		//Image image2(L"filter.png");

		// 画像の描画。 ダミー変数 graphics を仲介して描画する必要がある.

		//graphics.DrawImage(&image2, 0, 0, image2.GetWidth(), image2.GetHeight());
		filterFlag = 1;
	}


	int shiftTemp = 140;

	int StatsHPbaseX = 130 + shiftTemp; int StatsHPbaseY = 130; // +100 した
	int offsetY = 120;


	for (int j = 0; j <= partyNinzuDone - 1; ++j) {
		// 背景の青

		window1Draw(10 + shiftTemp, 100 + offsetY * j, // +140
			300 + shiftTemp, 200 + offsetY * j);

		if (mode_scene == MODE_ITEM_WHOM) {
			// カーソル
			if (whomTargetID1 == j) {

				tenmetu(10 + 10, 100 + 10 + 120 * (whomTargetID1),
					300 - 10, 100 + 70 + 120 * (whomTargetID1));

				//MessageBox(NULL, TEXT("デバッグ。"), TEXT("テスト"), MB_OK);

			}
		}

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), heros_def_list[partyNarabijyun[j]].heros_name);
		DrawFormatString(StatsHPbaseX, StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		lstrcpy(mojibuf, TEXT("HP"));
		DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_hp);
		DrawFormatString(StatsHPbaseX + 30, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("/ %d"), heros_def_list[partyNarabijyun[j]].heros_hp_max);
		DrawFormatString(StatsHPbaseX + 30 * 2, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[j]].heros_HP0_flag);
		DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


		if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag == 1) {

			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("戦闘不能"));
			DrawFormatString(StatsHPbaseX, StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

		}

	}

}


// 戦闘への突入の処理 // のちのマップ判定で呼びだすので、戦闘突入とマップ判定の順序は固定のこと。
void battle_start() {

	// MessageBox(NULL, TEXT("battle_enemy_startにいる。"), TEXT("キーテスト"), MB_OK);

	// 以下、定型文
	key_remain = 0;

	monster_hp = monster_def_list[encount_monters_id - 1].mon_hp_max;

	_stprintf_s(monster_name, MAX_LENGTH, TEXT("%s"), monster_def_list[encount_monters_id - 1].monster_name);
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
	
			// わからんが、たぶん大事なので残す
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
		// pre_guild(hWnd); // のちのちのギルド実装のため残す

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

		// 拡張のため残す
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
		} // for 
	}
}


static int hero1_already_attack_flag = 0;
static int enemy_already_attack_flag = 0;

static int battle_key = 1;

static int damage_HeroAttack = 1;
static int damage_EnemyAttack = 0;


void heroside_attack() {
	tekidame = 1;
	damepyon = 0;

	int pnCommon = partyNarabijyun[actionOrder[globalTempA]];

	if (heros_def_list[pnCommon].heros_HP0_flag == 0) {
		// 主人公たちの攻撃

		/* 乱数の種 */			
		// wWinMain で定義済み
			
		/* サイコロ */
		damage_HeroAttack = rand() % 6 + 2 + heros_def_list[pnCommon].heros_para[kougekiPara];

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


void enemy_attack() {
	tekidame = 0;
	damepyon = 0;

	// 敵たちの攻撃
	/* 乱数の種 */
		// wWinMain で定義済み

	int pnCommon = partyNarabijyun[actionOrder[globalTempA]];

	// ダメージ計算式
	/* サイコロ */
	damage_EnemyAttack = rand() % (6 / 2) + 10 + 2 * monster_def_list[encount_monters_id - 1].mon_attackPower
		- heros_def_list[partyNarabijyun[0]].heros_para[syubiPara];


	if (damage_EnemyAttack <= 0) {
		damage_EnemyAttack = 0;
	}

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
		}
	}
	// MessageBox(NULL, TEXT("いまそこ。"), TEXT("キーテスト"), MB_OK);

}


char strCount[64];


void keyEnableReset() {

	keyEnableZ = 0;
	keyEnableX = 0;

	keyEnableUp = 0;
	keyEnableDown = 0;

	nyuuryokuMatiZ = waitTime1;
	nyuuryokuMatiX = waitTime1;

	nyuuryokuMatiUp = waitTime1 / 2;
	nyuuryokuMatiDown = waitTime1 / 2;

}


int toubouSeikou = 0;


struct tykou {
	struct soubi_def Stype[20];
};

static struct tykou soubihin[20]; // 構造体配列の宣言
static struct tykou* Asoubuhin = &soubihin[20];



struct tykou2 {
	struct soubi_have Stype[10];
};

struct tykou2 soubiSyoji[20]; // 構造体配列の宣言

static struct tykou2* AsoubuSyoji = &soubiSyoji[10];


void itemList(struct tykou soubuhin[10], struct tykou2 soubiSyoji[20], int kasolFlag) {

	darkFlag = 1;
	darkFlag = 0;

	window1Draw(10, 100, 600, 400);

	// カーソル描画設定
	int spanY = FontYoffset;
	int Y0 = 120;

	// こっちは覗き見なのでカーソルはオフに


	if (kasolFlag == 1) {
		tenmetu(20 + (selecting_item_x - 1) * 300, Y0 + (selecting_item_y - 1) * spanY, 250 + (selecting_item_x - 1) * 300, Y0 + spanY + (selecting_item_y - 1) * spanY);
	}

	goukeiItem = 0;

	int column = 2;

	int xcommon;
	int ycommon;

	// 表示フラグ
	int ViewFlag[10]; // 0はシステム用, 1が使用品, 2が武器、3がタテ、4がカブト
	
	// int ViewFlagItem = 1;
	// int ViewFlagWeapon = 0;
	// int ViewFlagShield = 0;
	// int ViewFlagHelm = 0;

	if (mode_scene == MODE_ITEMweapon_MENU || mode_scene == MODE_ITEM_MENU || mode_scene == MODE_ITEM_TYPE) {
	
		// 安全のため一旦0に
		ViewFlag[1] = 0;  // ViewFlagItem = 0;
		ViewFlag[2] = 0;  // ViewFlagWeapon = 0;
		ViewFlag[3] = 0;  // ViewFlagShield = 0;
		ViewFlag[4] = 0;  // ViewFlagHelm = 0;

		// 表示フラグ設定
		if (mode_scene == MODE_ITEM_MENU || (selecting_mainmenu == 1 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 1;  // ViewFlagItem = 1;
			ViewFlag[2] = 0;  // ViewFlagWeapon = 0;
			ViewFlag[3] = 0;  // ViewFlagShield = 0;
			ViewFlag[4] = 0;  // ViewFlagHelm = 0;
		}

		if (mode_scene == MODE_ITEMweapon_MENU || (selecting_mainmenu == 2 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 0;  // ViewFlagItem = 0;
			ViewFlag[2] = 1;  // ViewFlagWeapon = 1;
			ViewFlag[3] = 1;  // ViewFlagShield = 1;
			ViewFlag[4] = 1;  // ViewFlagHelm = 1;
		}

		if ((selecting_mainmenu == 3 && mode_scene == MODE_ITEM_TYPE)) {
			ViewFlag[1] = 0;   //ViewFlagItem = 0;
			ViewFlag[2] = 0;   //ViewFlagWeapon = 0;
			ViewFlag[3] = 0;   //ViewFlagShield = 0;
			ViewFlag[4] = 0;   //ViewFlagHelm = 0;
		}

	}

	int LimintTemp = goukeiItem;
	goukeiItem = 0;


	// アイテム配列のクリア。前の残骸が残る場合があるので。
	itemHairetu[0] = -99;


	int itemIDcount = 0; // for文の外で使うので、消したらダメ

	// 使用品の配列代入
	if (ViewFlag[1]) {

		LimintTemp = goukeiItem;

		for (idTemp = 1; idTemp <= 3; idTemp = idTemp + 1)
		{

			if (item_have_list[idTemp].have_kosuu != 0) {

				goukeiItem = goukeiItem + 1;

				{
					itemHairetu[itemIDcount] = idTemp;
					itemTypeHairetu[itemIDcount] = siyouType;
					itemIDcount = itemIDcount + 1;
				}
			}
		} // 使用品の配列代入
	}

	// 
	for (int tempVal1 = 2; tempVal1 <= 4; tempVal1 = tempVal1 +1) {

		if (ViewFlag[tempVal1]) {

			LimintTemp = goukeiItem;

			// 装備品の配列代入
			for (idTemp = 1; idTemp <= 2; idTemp = idTemp + 1)
			{

				int	localSouType = soubiOffset + tempVal1 - 2;
				if ((soubiSyoji[idTemp].Stype[localSouType]).have_kosuu != 0) {


					goukeiItem = goukeiItem + 1;

					{
						itemHairetu[itemIDcount] = idTemp;
						itemTypeHairetu[itemIDcount] = localSouType;
						itemIDcount = itemIDcount + 1;
					}
				}
			} // 装備品の配列代入
		}

	}

	itemTypeHairetu[itemIDcount] = -99; // 終了を意味する数。

	// 道具コマンドの道具表示や武器表示など
	{
		for (int temp = 0; temp <= 10; temp = temp + 1) {

			int temp2 = temp + pageSyori * 6;

			if (itemTypeHairetu[temp2] == -99) {
				lstrcpy(mojibuf, TEXT("   "));

				DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf); // 文字を描画する
				break;
			}

			xcommon = 30 + 300 * floor((temp) % column);
			ycommon = 130 + spanY * floor((temp) / column);

			if (itemTypeHairetu[temp2] == siyouType) {
				lstrcpy(mojibuf, item_def_list[itemHairetu[temp2]].def_name);
			}
			if (itemTypeHairetu[temp2] == wepoType
				|| itemTypeHairetu[temp2] == tateType
				|| itemTypeHairetu[temp2] == kabutoType
				) {

				int locType;

				locType = itemTypeHairetu[temp2];// 意味は下記コメントの内容	

				/*		// このコメントは上記の説明なので消すな
				if (itemTypeHairetu[temp2] == wepoType) {
					locType = wepoType;

				}
				if (itemTypeHairetu[temp2] == tateType) {
					locType = tateType;
				}
				if (itemTypeHairetu[temp2] == kabutoType) {
					locType = kabutoType;
				}
				*/

				lstrcpy(mojibuf, (soubihin[itemHairetu[temp2]].Stype[locType]).def_name);

			}

			DrawFormatString(xcommon, ycommon, GetColor(255, 255, 255), mojibuf);

			// 個数欄の背景クリア用
			lstrcpy(mojibuf, TEXT("   "));
			DrawFormatString(280 + 100 * 2 + 50, 200 + 30 * (temp + 1), GetColor(255, 255, 255), mojibuf);


			if (itemTypeHairetu[temp2] == siyouType) {
				// 道具の個数表示. 表示は後処理のDrawFormat で一括
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), item_have_list[itemHairetu[temp2]].have_kosuu);
			}

			int locType = itemTypeHairetu[temp2];
			if (itemTypeHairetu[temp2] == wepoType || itemTypeHairetu[temp2] == tateType
				|| itemTypeHairetu[temp2] == kabutoType
				) {
				// 装備品の個数表示. 表示は後処理のDrawFormat で一括
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d "), (soubiSyoji[itemHairetu[temp2]].Stype[locType]).have_kosuu);
			}

			// 上記代入を実際に表示する
			DrawFormatString(xcommon + 130, ycommon, GetColor(255, 255, 255), mojibuf);

		}
	} // 道具コマンドの道具表示や武器表示など

	itemIDcount = 0;
} // itemlist



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



	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			(soubihin[temp].Stype[wepoType]).def_id = 0;
			lstrcpy((soubihin[temp].Stype[wepoType]).def_name, TEXT("--------"));
			(soubihin[temp].Stype[wepoType]).material = mateNothing;
			(soubihin[temp].Stype[wepoType]).equip_type = typeNothing;
			(soubihin[temp].Stype[wepoType]).equipPower[kougekiPara] = 0; // 攻撃力
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			(soubihin[temp].Stype[wepoType]).def_id = 1;
			lstrcpy((soubihin[temp].Stype[wepoType]).def_name, TEXT("鉄の槍"));
			(soubihin[temp].Stype[wepoType]).material = mateIron;
			(soubihin[temp].Stype[wepoType]).equip_type = spear;
			(soubihin[temp].Stype[wepoType]).equipPower[kougekiPara] = 107; // 攻撃力	
			continue;
		}

		if (temp == 2) {
			(soubihin[temp].Stype[wepoType]).def_id = 2;
			lstrcpy((soubihin[temp].Stype[wepoType]).def_name, TEXT("鉄のメイス"));
			(soubihin[temp].Stype[wepoType]).material = mateIron;
			// weapon_def_list[temp].equip_type = spear;
			(soubihin[temp].Stype[wepoType]).equipPower[kougekiPara] = 44; // 攻撃力
			continue;
		}
	}


		//防具の定義 タテ
	// 計算量が2乗時間のアルゴリズムだけど、とりあえず編集性やバグ耐性を優先し、計算時間は考慮しない。
	// どうしても計算時間を短縮したいなら、ifをswitch-breakに置き換えれば、読み込み時間を若干、減らせるか。
	for (int temp = 0; temp <= 10; temp = temp + 1) {

		if (temp == 0) {
			(soubihin[temp].Stype[tateType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[tateType]).def_name, TEXT("--------"));
			(soubihin[temp].Stype[tateType]).material = mateNothing;
			(soubihin[temp].Stype[tateType]).equip_type = typeNothing;
			(soubihin[temp].Stype[tateType]).equipPower[syubiPara] = 0; // 攻撃力
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			(soubihin[temp].Stype[tateType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[tateType]).def_name, TEXT("木の盾"));
			(soubihin[temp].Stype[tateType]).material = mateNothing;
			(soubihin[temp].Stype[tateType]).equip_type = typeNothing;
			(soubihin[temp].Stype[tateType]).equipPower[syubiPara] = 5; // 攻撃力	
			continue;
		}

		if (temp == 2) {
			(soubihin[temp].Stype[tateType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[tateType]).def_name, TEXT("鉄の盾"));
			(soubihin[temp].Stype[tateType]).material = mateNothing;
			(soubihin[temp].Stype[tateType]).equip_type = typeNothing;
			(soubihin[temp].Stype[tateType]).equipPower[syubiPara] = 30; // 攻撃力
			continue;
		}
	}


		//防具の定義 カブト	
		// 計算量が2乗時間のアルゴリズムだけど、とりあえず編集性やバグ耐性を優先し、計算時間は考慮しない。	
		// どうしても計算時間を短縮したいなら、ifをswitch-breakに置き換えれば、読み込み時間を若干、減らせるか。
	for (int temp = 0; temp <= 10; temp = temp + 1) {
		int locType = kabutoType;
		if (temp == 0) {
			(soubihin[temp].Stype[locType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[locType]).def_name, TEXT("--------"));
			(soubihin[temp].Stype[locType]).material = mateNothing;
			(soubihin[temp].Stype[locType]).equip_type = typeNothing;
			(soubihin[temp].Stype[locType]).equipPower[syubiPara] = 0; // 攻撃力
			continue; // 計算時間の節約のため
		}

		if (temp == 1) {
			(soubihin[temp].Stype[locType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[locType]).def_name, TEXT("木の帽子"));
			(soubihin[temp].Stype[locType]).material = mateNothing;
			(soubihin[temp].Stype[locType]).equip_type = typeNothing;
			(soubihin[temp].Stype[locType]).equipPower[syubiPara] = 50; // 攻撃力	
			continue;
		}

		if (temp == 2) {
			(soubihin[temp].Stype[locType]).def_id = temp;
			lstrcpy((soubihin[temp].Stype[locType]).def_name, TEXT("鉄のカブト"));
			(soubihin[temp].Stype[locType]).material = mateNothing;
			(soubihin[temp].Stype[locType]).equip_type = typeNothing;
			(soubihin[temp].Stype[locType]).equipPower[syubiPara] = 20; // 攻撃力
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

		int locType = wepoType;
		soubiSyoji[temp].Stype[locType].have_def_id = temp + 1;

		if (temp == 0) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0; // --------
		}

		if (temp == 1) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0;
		}

		if (temp == 2) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 3;
		}
	}



	for (int temp = 0; temp <= 15 - 1; temp++) {

		//
		int locType = tateType;
		soubiSyoji[temp].Stype[locType].have_def_id = temp + 1;

		if (temp == 0) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0; // --------
		}

		if (temp == 1) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 1;
		}

		if (temp == 2) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0;
		}
	}


	for (int temp = 0; temp <= 15 - 1; temp++) {

		//
		int locType = kabutoType;
		soubiSyoji[temp].Stype[kabutoType].have_def_id = temp + 1;

		if (temp == 0) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0; // --------
		}

		if (temp == 1) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 5;
		}

		if (temp == 2) {
			(soubiSyoji[temp].Stype[locType]).have_kosuu = 0;
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
			monster_def_list[temp].mon_hp_max = 90;
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
			heros_def_list[temp].heros_hp = 132; // 20;
			heros_def_list[temp].heros_hp_max = 185;
			heros_def_list[temp].heros_agility = 56;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 1;


			heros_def_list[temp].heroSoubi[wepoType] = 1;
			heros_def_list[temp].heroSoubiKasol[wepoType] = 0;

			heros_def_list[temp].heroSoubi[tateType] = 0;
			heros_def_list[temp].heroSoubi[tateType] = 1;

			heros_def_list[temp].heros_para[kougekiPara] = (soubihin[heros_def_list[temp].heroSoubi[wepoType]].Stype[wepoType]).equipPower[kougekiPara];

			heros_def_list[temp].heros_para[syubiPara] = (soubihin[heros_def_list[temp].heroSoubi[tateType]].Stype[tateType]).equipPower[syubiPara]
				+ (soubihin[heros_def_list[temp].heroSoubi[kabutoType]].Stype[kabutoType]).equipPower[syubiPara]
				;
			
		}

		if (temp == 1) {
			lstrcpy(heros_def_list[temp].heros_name, TEXT("ピエ－ル"));
			heros_def_list[temp].heros_hp = 108; //  18;
			heros_def_list[temp].heros_hp_max = 150;
			heros_def_list[temp].heros_agility = 100;

			heros_def_list[temp].heros_exp = 0;

			heros_def_list[temp].heros_HP0_flag = 0;
			heros_def_list[temp].PartyIn = 1;



			heros_def_list[temp].heroSoubi[wepoType] = 2;
			heros_def_list[temp].heroSoubi[tateType] = 0;


			heros_def_list[temp].heros_subiRyoku = (soubihin[heros_def_list[temp].heroSoubi[tateType]].Stype[tateType]).equipPower[syubiPara];

			heros_def_list[temp].heros_para[kougekiPara] = (soubihin[heros_def_list[temp].heroSoubi[wepoType]].Stype[wepoType]).equipPower[kougekiPara];
			heros_def_list[temp].heros_para[syubiPara] = (soubihin[heros_def_list[temp].heroSoubi[tateType]].Stype[tateType]).equipPower[syubiPara];



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

		if (keyEnableZ == 0 && nyuuryokuMatiZ > 0) {
			nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

		}
		if (nyuuryokuMatiZ <= 0) {
			nyuuryokuMatiZ = 0;
			keyEnableZ = 1;
		}

		if (nyuuryokuMatiX > 0) {
			nyuuryokuMatiX = nyuuryokuMatiX - 1;

		}

		if (nyuuryokuMatiX <= 0) {
			nyuuryokuMatiX = 0;
			keyEnableX = 1;

		}


		if (keyEnableUp == 0 && nyuuryokuMatiUp > 0) {
			nyuuryokuMatiUp = nyuuryokuMatiUp - 1;
			
		}
		if (nyuuryokuMatiUp <= 0) {
			nyuuryokuMatiUp = 0;
			keyEnableUp = 1;			
		}

		if (nyuuryokuMatiDown > 0) {
			nyuuryokuMatiDown = nyuuryokuMatiDown - 1;
		}

		if (nyuuryokuMatiDown <= 0) {
			nyuuryokuMatiDown = 0;
			keyEnableDown = 1;
		}


		if (keyEnableLeft == 0 && nyuuryokuMatiLeft > 0) {
			nyuuryokuMatiLeft = nyuuryokuMatiLeft - 1;

		}
		if (nyuuryokuMatiLeft <= 0) {
			nyuuryokuMatiLeft = 0;
			keyEnableLeft = 1;
			

		}

		if (nyuuryokuMatiRight > 0) {
			nyuuryokuMatiRight = nyuuryokuMatiRight - 1;

		}

		if (nyuuryokuMatiRight <= 0) {
			nyuuryokuMatiRight = 0;
			keyEnableRight = 1;

		}



		// マップ描画

		int mapChipWidthX = 30;
		int mapChipWidthY = 30;

		for (x_mapDraw = 0; x_mapDraw <= 9; ++x_mapDraw)
		{
			for (y_mapDraw = 0; y_mapDraw <= 6; ++y_mapDraw)
			{
				if (map1table[y_mapDraw][x_mapDraw] == 0) {
					DrawGraph(mapChipWidthX * x_mapDraw, mapChipWidthY * y_mapDraw, mapchip1Handle, false);
				}
				if (map1table[y_mapDraw][x_mapDraw] == 1) {
					DrawGraph(mapChipWidthX * x_mapDraw, mapChipWidthY * y_mapDraw, mapchip2Handle, false);
				}
			}

		}


		DrawGraph(mapChipWidthX * monPosiX, mapChipWidthY * monPosiY, monchipDownHandle, false);



		// キャラチップ描画
		{
			int charaChipWidthX = 30; // 直後ifの外でも使うのでブロック外で定義。
			int charaChipWidthY = 30;

			if (xPosi == monPosiX && yPosi == monPosiY) {

				// モンスター画像 クリーン用
				DrawGraph(charaChipWidthX * monPosiX, charaChipWidthY * monPosiY, blackchipHandle, false);

			}



			// 個別の向きの画像で上書き

			double baiX = waitTime1 / charaChipWidthX;
			double baiY = waitTime1 / charaChipWidthY;

			if (hero1_direction == rightward) {

				tempHandle = charachipRightHandle;
				DrawGraph(charaChipWidthX * xPosi + 0 + (waitTime1 - nyuuryokuMatiLR) / baiX, charaChipWidthY * yPosi, tempHandle, false);
			}

			if (hero1_direction == leftward) {
				tempHandle = charachipLeftHandle;
				DrawGraph(charaChipWidthX * xPosi + 0 - (waitTime1 - nyuuryokuMatiLR) / baiX, charaChipWidthY * yPosi, tempHandle, false);

			}



			if (hero1_direction == downward) {
				tempHandle = charachipDownHandle;
				DrawGraph(charaChipWidthX * xPosi + 0, charaChipWidthY * yPosi + (waitTime1 - nyuuryokuMatiUD) / baiY, tempHandle, false);

			}

			if (hero1_direction == upward) {
				tempHandle = charachipUpHandle;
				DrawGraph(charaChipWidthX * xPosi + 0, charaChipWidthY * yPosi - (waitTime1 - nyuuryokuMatiUD) / baiY, tempHandle, false);
			}

		}


		if (mode_scene == MODE_MAP) {
			// 移動キーのフラグ処理
			{
				int mapsizeX = 10; int mapsizeY = 7;
				
				{ // 移動のモジュール

					// キャラを右に移動
					if (xPosi < mapsizeX && yPosi < mapsizeY + 1 ) { // y判定 が+1 してるのはデバッグ用
						// 移動先予定地の入場可否の判定
						if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1 && moving == 0) {
							if (map1table[yPosi][xPosi + 1] == 1) { destMovable = 0; }
							if (map1table[yPosi][xPosi + 1] == 0) { destMovable = 1; }

							// 入場可能ならフラグ設定
							if (destMovable == 1) {
								moving = 1;
								hero1_direction = rightward;
								keyEnableRight = 0;
								nyuuryokuMatiLR = waitTime1;
							}
						}
						// カウント処理
						if (moving == 1 && nyuuryokuMatiLR > 0) {
							nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
						}
						// 移動の終了処理
						if (hero1_direction == rightward && moving == 1 && nyuuryokuMatiLR <= 0) {
							keyEnableRight = 1; // moving 回復までに時間が掛かるので、ここは1に。

							nyuuryokuMatiLR = waitTime1;
							nyuuryokuMatiLeft = waitTime1;
							nyuuryokuMatiRight = waitTime1;


							xPosi++;     // 右へ1マスだけ移動
							moving = 0;
						}
					} // 右移動

					// 左に移動
					if (xPosi < mapsizeX + 1 && yPosi < mapsizeY + 1 ) {      // y判定 が+1 してるのはデバッグ用
						// 移動先予定地の入場可否の判定
						if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1 && moving == 0) {
							if (map1table[yPosi][xPosi - 1] == 1) { destMovable = 0; }
							if (map1table[yPosi][xPosi - 1] == 0) { destMovable = 1; }

							// 入場可能ならフラグ設定
							if (destMovable == 1) {
								moving = 1;
								hero1_direction = leftward;
								keyEnableLeft = 0;
								nyuuryokuMatiLR = waitTime1;
							}
						}
						// カウント処理
						if (moving == 1 && nyuuryokuMatiLR > 0) {
							nyuuryokuMatiLR = nyuuryokuMatiLR - 1;
						}
						// 移動の終了処理
						if (hero1_direction == leftward && moving == 1 && nyuuryokuMatiLR <= 0) {
							keyEnableLeft = 1;

							nyuuryokuMatiLR = waitTime1;
							nyuuryokuMatiLeft = waitTime1;
							nyuuryokuMatiRight = waitTime1;

							xPosi--;    // 左へ1マスだけ移動
							moving = 0;
						}
					}// 左に移動

					// 下に移動
					if (xPosi < mapsizeX  && yPosi < mapsizeY ) {
						// 移動先予定地の入場可否の判定
						if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1 && moving == 0) {
							if (map1table[yPosi + 1][xPosi] == 1) { destMovable = 0; }
							if (map1table[yPosi + 1][xPosi] == 0) { destMovable = 1; }

							// 入場可能ならフラグ設定
							if (destMovable == 1) {
								moving = 1;
								hero1_direction = downward;
								keyEnableDown = 0;


								nyuuryokuMatiUD = waitTime1;
								nyuuryokuMatiUp = waitTime1;
								nyuuryokuMatiDown = waitTime1;

							}
						}

						// カウント処理
						// keyEnableは別のブロックで流用してるので、必ず moving ==1 が必要
						if (nyuuryokuMatiUD > 0 && moving == 1) {
							nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
						}
						// 移動の終了処理
						if (hero1_direction == downward && nyuuryokuMatiUD <= 0) {
							keyEnableDown = 1;

							nyuuryokuMatiUD = waitTime1;
							nyuuryokuMatiUp = waitTime1;
							nyuuryokuMatiDown = waitTime1;

							yPosi++;     // 下へ1マスだけ移動
							moving = 0;
						}
					}// 下に移動


					// 上に移動
					if (xPosi < mapsizeX  && yPosi < mapsizeY + 1) {
						// 移動先予定地の入場可否の判定
						if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1 && moving == 0) {
							if (map1table[yPosi - 1][xPosi] == 1) { destMovable = 0; }
							if (map1table[yPosi - 1][xPosi] == 0) { destMovable = 1; }

							// 入場可能ならフラグ設定
							if (destMovable == 1) {
								moving = 1;
								hero1_direction = upward;
								keyEnableUp = 0;

								nyuuryokuMatiUD = waitTime1;
								nyuuryokuMatiUp = waitTime1;
								nyuuryokuMatiDown = waitTime1;

							}
						}
						// カウント処理

						// keyEnableは別のブロックで流用してるので、必ず moving ==1 が必要
						if (nyuuryokuMatiUD > 0 && moving == 1) {
							nyuuryokuMatiUD = nyuuryokuMatiUD - 1;
						}
						// 移動の終了処理
						if (hero1_direction == upward && nyuuryokuMatiUD <= 0 && moving == 1) {
							keyEnableUp = 1;

							nyuuryokuMatiUD = waitTime1;
							nyuuryokuMatiUp = waitTime1;
							nyuuryokuMatiDown = waitTime1;

							yPosi--;     // 上へ1マスだけ移動
							moving = 0;
						}
					}// 上に移動
				}// 移動

				// 逃亡処理のフラグ設定っぽい
				if (destMovable == 1 && moving == 1 && toubouTyokugo > 0) {
					toubouTyokugo = toubouTyokugo - 1;
					destMovable = 0;
				}
				if (toubouTyokugo <= 0) {
					toubouSeikou = 0;
					toubouTyokugo = 0;
				}

				// モンスター遭遇のエンカウント判定
				{
					int monMesX = 400; int monMesY = 350; // メッセージ欄の表示位置


					if (xPosi == monPosiX && yPosi == monPosiY && toubouTyokugo == 0) {
						battle_start();
						mode_scene = MODE_BATTLE_COMMAND;

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

				} // モンスター遭遇処理
			}

			// if 残り待機がゼロで、さらにXボタンが押されたら、then メニュー画面に遷移
			if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1) {
				keyEnableX = 0;
				mode_scene = MODE_MENU;
				nyuuryokuMatiX = waitTime1;
			}

			window1Draw(100, 250, 100 + 150, 250 + 40 + 100);

			DrawFormatString(100, 250, GetColor(255, 255, 255), "座標[%d,%d]", xPosi, yPosi); // 文字を描画する

		} // map モードの終わり


		if (mode_scene == MODE_BATTLE_COMMAND || mode_scene == MODE_BATTLE_NOW || mode_scene == MODE_BATTLE_WIN) {

			int monMesX = 400; int monMesY = 350; // メッセージ欄の表示位置
			DrawBox(monMesX, monMesY, monMesX + 250, monMesY + 40,
				GetColor(0, 0, 0), 1);
			DrawFormatString(monMesX, 350, GetColor(255, 255, 255), "モンスターが現れた"); // 文字を描画する

			// モンスター画像 
			if (mode_scene == MODE_BATTLE_COMMAND || mode_scene == MODE_BATTLE_NOW) {

				DrawGraph(300, 95, koboHandle, true);
			}


			if (mode_scene == MODE_BATTLE_COMMAND) {
				int tem1X = 100; int Xwidth = 100;
				int tem1Y = 240;

				int yohakuY = 10;
				window1Draw(tem1X - yohakuY, tem1Y - yohakuY,
					tem1X + Xwidth + yohakuY, tem1Y + 40 + 40 + yohakuY);

				// カーソル
				tenmetu(tem1X, tem1Y + (selecting_mainmenu - 1) * 40,
					tem1X + Xwidth, tem1Y + 10 + (selecting_mainmenu - 1) * 40 + 30);

				DrawFormatString(tem1X + 20, tem1Y + 10, GetColor(255, 255, 255), "戦う"); // 文字を描画する
				DrawFormatString(tem1X + 20, tem1Y + 10 + 40, GetColor(255, 255, 255), "逃げる"); // 文字を描画する
			}


			// 敵関係のパラメ－タ表示
			int monX = 450;
			int monY = 150;

			tekiTairetuAgility[0] = monster_def_list[encount_monters_id - 1].mon_agility;


			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("HP %d"), monster_hp);
			DrawFormatString(monX, monY, GetColor(255, 255, 255), mojibuf); // 文字を描画する

			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%s"), monster_name);
			DrawFormatString(monX, monY + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

			_stprintf_s(mojibuf, MAX_LENGTH, TEXT("素早さ %d"), tekiTairetuAgility[0]);
			DrawFormatString(monX, monY + 20 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する


			int windowTempA = 410 + 100; // y の位置
			int chara_window_size_x = 140;

			// _itot_s(your_money , p,200, 10); // 難しい関数なので保管

			int offsetBattleX = 170;
			int tempVAl;


			for (int iTemp = 0; iTemp <= partyNinzuDone - 1; iTemp++)
			{

				window1Draw(10 + iTemp * offsetBattleX, 350,
					10 + iTemp * offsetBattleX + 150, 470);

				tempVAl = partyNarabijyun[iTemp];


				/* キャラのステータス */
				DrawFormatString(20 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 10,
					GetColor(255, 255, 255), heros_def_list[tempVAl].heros_name); // 文字を描画する


				lstrcpy(mojibuf, TEXT("HP"));
				DrawFormatString(20 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), heros_def_list[tempVAl].heros_hp);
				DrawFormatString(50 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("/ %d"), heros_def_list[tempVAl].heros_hp_max);
				DrawFormatString(50 + 30 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				lstrcpy(mojibuf, TEXT("素早さ"));
				DrawFormatString(20 + iTemp * offsetBattleX, windowTempA - chara_window_size_x + 40 + 30, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), sankaAgility[tempVAl]);			
				DrawFormatString(50 + iTemp * offsetBattleX + 30, windowTempA - chara_window_size_x + 40 + 30, GetColor(255, 255, 255), mojibuf); // 文字を描画する

			}


			for (idTemp = 0; idTemp <= partyNinzuDone - 1; idTemp = idTemp + 1)
			{
				// パーティにいないキャラごと、読み取る。
				// パーティキャラの抽出は、後工程で行う。
				mikataAgility[idTemp] = heros_def_list[idTemp].heros_agility;
			}


			// これ戦闘用ソート
			for (idTemp = 0; idTemp <= partyNinzuDone - 1; idTemp = idTemp + 1)
			{
				// ここでパーティキャラだけ素早さを抽出している。mikataAgi は非パーティキャラを含んでるので、この工程が必要。
				sankaAgility[idTemp] = mikataAgility[partyNarabijyun[idTemp]]; // sankaAgil はまだ並び替え前

			}

			for (idTemp = 0; idTemp <= enemyNinzu - 1; idTemp = idTemp + 1)
			{
				sankaAgility[partyNinzuDone + idTemp] = tekiTairetuAgility[idTemp];

			}


			for (int loctempQ = 0; loctempQ <= partyNinzuDone + enemyNinzu - 1; ++loctempQ)
			{
				iremonoAgilityHairetu[loctempQ] = sankaAgility[loctempQ]; // iremonoAgi と sanka は同内容

				iremonoOrderHairetu[loctempQ] = loctempQ;
			} // 初期値の代入


			// ソートで実装

			for (int loctempB = 0; loctempB <= (partyNinzuDone - 1 + enemyNinzu - 1) + 1; ++loctempB)
			{
				for (int loctempA = loctempB; loctempA <= (partyNinzuDone - 1 + enemyNinzu - 1) + 1; ++loctempA)
				{
					if (iremonoAgilityHairetu[loctempB] >= iremonoAgilityHairetu[loctempA + loctempB]) {

						// 何もしていない
					//	iremonoAgilityHairetu[loctempB] = iremonoAgilityHairetu[loctempB];
					//	iremonoAgilityHairetu[loctempA + loctempB] = iremonoAgilityHairetu[loctempA + loctempB];
						// 教育用に上コード2行は残す

					}
					// locAのほうが内側です。
					if (iremonoAgilityHairetu[loctempB] < iremonoAgilityHairetu[loctempA + loctempB]) {

						int tempSwapA, tempSwapB;

						tempSwapA = iremonoAgilityHairetu[loctempB];
						tempSwapB = iremonoAgilityHairetu[loctempA + loctempB];

						iremonoAgilityHairetu[loctempB] = tempSwapB;
						iremonoAgilityHairetu[loctempA + loctempB] = tempSwapA;


						int tempOrderSwapA, tempOrderSwapB;

						tempOrderSwapA = iremonoOrderHairetu[loctempB];
						tempOrderSwapB = iremonoOrderHairetu[loctempA + loctempB];

						iremonoOrderHairetu[loctempB] = tempOrderSwapB;
						iremonoOrderHairetu[loctempA + loctempB] = tempOrderSwapA;

						// デバッグ文の「irem」では入れ物オーダー配列である。
					}
				}
			} // ここまでソート


			for (int loctempA = 0; loctempA <= partyNinzuDone - 1 + enemyNinzu; ++loctempA)
			{
				actionOrder[loctempA] = iremonoOrderHairetu[loctempA];
			}


			int mikataPE = 1; int tekiPE = 2;
			for (int loctempA = 0; loctempA <= partyNinzuDone - 1 + enemyNinzu; ++loctempA)
			{
				if (actionOrder[loctempA] <= partyNinzuDone - 1) {
					PorEflag[loctempA] = mikataPE;
					// actionOrder[loctempA] = actionOrder[loctempA];
				}

				if (actionOrder[loctempA] > partyNinzuDone - 1) {
					PorEflag[loctempA] = tekiPE;
					// actionOrder[loctempA] = -9;
				}

			}


	// 素早さ配列の表示テスト
			int agilityProcMonitorX = 370;
			int agilityProcMonitorY = 180;


			if (debugFlag == 1) {
				lstrcpy(mojibuf, TEXT("素早さ配列"));

				DrawFormatString(agilityProcMonitorX, agilityProcMonitorY, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), iremonoAgilityHairetu[tempMonitor]);

					DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				}
				// 戦闘デバッグ文の描画プログラム


				// 行動順配列の表示テスト 
				lstrcpy(mojibuf, TEXT("行動順配列"));
				DrawFormatString(agilityProcMonitorX, agilityProcMonitorY + 50, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				lstrcpy(mojibuf, TEXT("irem"));
				DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), iremonoOrderHairetu[tempMonitor]);
					DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30, GetColor(255, 255, 255), mojibuf); // 文字を描画する
				}


				// 行動順配列の表示テスト // こっちはactionOrder
				lstrcpy(mojibuf, TEXT("act"));

				DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("v%d"), actionOrder[tempMonitor]);

					DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する
				}

				lstrcpy(mojibuf, TEXT("PE f"));

				DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30 * 3, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), PorEflag[tempMonitor]);

					DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30 * 3, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				}

				lstrcpy(mojibuf, TEXT("Ac tp"));

				DrawFormatString(agilityProcMonitorX - 10, agilityProcMonitorY + 40 + 30 * 4, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				for (int tempMonitor = 0; tempMonitor <= sankaNinzu - 1; ++tempMonitor) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d"), actionOrder[tempMonitor]);

					DrawFormatString(agilityProcMonitorX + 30 + tempMonitor * 30, agilityProcMonitorY + 40 + 30 * 4, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				}
			} // ここまでデバッグ文


			if (mode_scene == MODE_BATTLE_NOW) {

				int battleMassBaseX = 150; int battleMassBaseY = 410 - 180; // 410 は「windowTempA」

				int pnCommon = partyNarabijyun[actionOrder[globalTempA]];

				if (heros_def_list[pnCommon].heros_HP0_flag == 0) {
					if (actionOrder[globalTempA] <= partyNinzuDone - 1) {

						_stprintf_s(mojibuf, TEXT("%s の攻撃！"), heros_def_list[pnCommon].heros_name);
						DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // 文字を描画する

						// デバッグ文
						if (debugFlag == 1) {
							_stprintf_s(mojibuf, TEXT("gte %d"), globalTempA);
							_stprintf_s(mojibuf, TEXT("AG %d"), actionOrder[globalTempA]);
							_stprintf_s(mojibuf, TEXT("pag並び %d"), partyNarabijyun[actionOrder[globalTempA]]);							
						} // ここまでデバ文

					}
				}

				if (heros_def_list[partyNarabijyun[actionOrder[globalTempA]]].heros_HP0_flag == 1) {
					if (actionOrder[globalTempA] <= partyNinzuDone - 1) {
						_stprintf_s(mojibuf, TEXT("%s は戦闘不能で動けない"), heros_def_list[partyNarabijyun[actionOrder[globalTempA]]].heros_name);
						DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}
				}

				if (actionOrder[globalTempA] >= partyNinzuDone) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("敵の攻撃！ "));
					DrawFormatString(battleMassBaseX, battleMassBaseY, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				}



				// DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "戦うテスト"); // 文字を描画する

				if (PorEflag[globalTempA] == tekiPE) {
					if (encount_mons_alive == 1) {

						// enemy atack で　tekidame =0 にされてる
						if (damepyon < 10 && tekidame == 0) {
							damepyon = damepyon + 1;
						}

						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d ダメージ"), damage_EnemyAttack);
						DrawFormatString(30, 350 - 5 * damepyon, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}
				}

				if (PorEflag[globalTempA] == mikataPE) {
					if (encount_mons_alive == 1 || encount_mons_alive == 0) {

						// hero atack で　tekidame =1 にされてる
						if (damepyon < 10 && tekidame == 1) {
							damepyon = damepyon + 1;
						}

						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d ダメージ"), damage_HeroAttack);
						DrawFormatString(monX + 10, monY - 30 - 5 * damepyon, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}
				}

			}// now



			// 十字キー入力時
			if (keyHaijyo == 0) {
				// カーソルを上に移動

				{

					// 移動の終了処理
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
						keyEnableUp = 0;
						nyuuryokuMatiUp = waitTime1;
						selecting_mainmenu--;  // 上へ1マスだけ移動
					}

					// 数値が微妙に違うので、リファクタ統合するな
					if (selecting_mainmenu < 0) {
						selecting_mainmenu = 0;
					}

					if (selecting_mainmenu >= 3) {
						selecting_mainmenu = 3;
					}
				}


				// カーソルを下に移動
				{

					// 移動の終了処理
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
						keyEnableDown = 0;
						nyuuryokuMatiDown = waitTime1;
						selecting_mainmenu++;                       // 下へ1マスだけ移動
					}


					if (selecting_mainmenu < 1) {
						selecting_mainmenu = 1;
					}

					if (selecting_mainmenu >= 3) {
						selecting_mainmenu = 3;
					}

				}
			} //if (keyHaijyo == 0)


			// ターン開始
			if (CheckHitKey(KEY_INPUT_Z) == 1 && selecting_mainmenu == 1 && keyHaijyo == 0 				
				&& mode_scene != MODE_BATTLE_NOW       // これが無いと連打でターン再開してしまう
				&& mode_scene != MODE_BATTLE_WIN ) { // これが無いと連打でターン再開してしまう

				// MessageBox(NULL, TEXT("test。"), TEXT("場所テスト"), MB_OK);

				TimeKasolCount = 0;

				keyHaijyo = 1;
				battlewait = 100;

				dameKei = 0;

				damage_EnemyAttack = 0;
				damage_HeroAttack = 0;

				mode_scene = MODE_BATTLE_NOW;		

			}

			battlewait = battlewait - 1;


			


			if (mode_scene == MODE_BATTLE_WIN) {
			
				DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "倒した"); // 文字を描画する

				int senkaX = 250; int senkaY = 150;
				window1Draw(senkaX, senkaY, senkaX + 150, senkaY + 120 );

				int offsetY2 = FontYoffset;
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Exp: %d"), monster_def_list[encount_monters_id - 1].mon_exp);
				DrawFormatString(senkaX + 10, senkaY + offsetY2 * 1, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("Gold: %d"), monster_def_list[encount_monters_id - 1].mon_gold);
				DrawFormatString(senkaX + 10, senkaY + offsetY2 * 2, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				keyHaijyo = 1; // 戦闘コマンドが実行されないよう、まだ排除中

				toubouTyokugo = 5;


				if (battlewait <= 0 && senkaFlag == 0) {

					globalTempA = 0; // ターン終了処理

					// MessageBox(NULL, TEXT("敵倒した。"), TEXT("場所テスト"), MB_OK);

					// カネと経験値の更新
					your_money = your_money + monster_def_list[encount_monters_id - 1].mon_gold;

					for (int temp = 0; temp <= partyNinzuDone - 1; temp = temp + 1) {

						// 登録キャラが多い場合を想定して（歴史SLGなど）、全キャラは走査しない。							
						// MessageBox(NULL, TEXT("敵倒した。"), TEXT("場所テスト"), MB_OK);

						heros_def_list[partyNarabijyun[temp]].heros_exp = heros_def_list[partyNarabijyun[temp]].heros_exp + monster_def_list[encount_monters_id - 1].mon_exp;

					}					
					senkaFlag = 1;
				}


				if (CheckHitKey(KEY_INPUT_Z) == 1 && senkaFlag == 1) {
					globalTempA = 0; // ターン終了

					keyEnableReset();
					keyHaijyo = 0;
					mode_scene = MODE_MAP;// テスト用に倒した扱いなので
				}
			} // win


			if (mode_scene == MODE_BATTLE_NOW && dameKei == 0) {

				if (PorEflag[globalTempA] == 1	) {

					if (encount_mons_alive == 1) {
						heroside_attack();
						dameKei = 1;
					}
				}

				if (PorEflag[globalTempA] == tekiPE) {
					if (encount_mons_alive == 1) {

						enemy_attack();
						dameKei = 1;
					}
				}
			}

			// 次行動者(globalTempA )をセット
			if (battlewait <= 0 && mode_scene == MODE_BATTLE_NOW && dameKei == 1) {
				battlewait = 0;
				dameKei = 0;

				if (monster_hp <= 0) {			
					mode_scene = MODE_BATTLE_WIN;
					battlewait = 60.0 * 2.0;
				}
				if (monster_hp > 0) {

					if (globalTempA <= (partyNinzuDone - 1 + enemyNinzu - 1) + 1 && dameKei == 0) {

						// MessageBox(NULL, TEXT("aaa"), TEXT("場所テスト"), MB_OK);

						globalTempA = globalTempA + 1;
						battlewait = 60.0 * 2.0;
					}



					// ターン終了					
					if (globalTempA >= (partyNinzuDone - 1 + enemyNinzu - 1) + 1 + 1) {

						// MessageBox(NULL, TEXT("qwerty"), TEXT("場所テスト"), MB_OK);
						damage_EnemyAttack = 0;
						damage_HeroAttack = 0;

						globalTempA = 0;

						damepyon = 0;
						mode_scene = MODE_BATTLE_COMMAND;											
					}
				}
				keyHaijyo = 0;
			} // battlewait が0の状態





			if (CheckHitKey(KEY_INPUT_Z) == 1 && selecting_mainmenu == 2 && keyHaijyo == 0) {

				keyHaijyo = 1;

				TimeKasolCount = 0;
				DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "逃げるのに成功"); // 文字を描画する
				toubouSeikou = 1;
				toubouTyokugo = 5;

			}

			if (toubouSeikou == 1) {
				DrawFormatString(monMesX, 350 + 30, GetColor(255, 255, 255), "逃げるのに成功"); // 文字を描画する

			}

			if (toubouSeikou == 1 && TimeKasolCount == 60) {
				keyHaijyo = 0;
				mode_scene = MODE_MAP;

			}
		}


		if (mode_scene == MODE_MENU) {
			int HPX = 300; int HPY = 50;
			int shiftY = 80;
			// ウィンドウ欄

			window1Draw(HPX, HPY, HPX + 150, HPY + 100 *2);

			for (int temp = 0; temp <= partyNinzuDone - 1; temp = temp + 1) {
				DrawFormatString(HPX + 20, HPY + 20 * 0 + shiftY * temp, GetColor(255, 255, 255), "%s", heros_def_list[partyNarabijyun[temp]].heros_name); // 文字を描画する			
				DrawFormatString(HPX + 20, HPY + 20 * 1 + shiftY * temp, GetColor(255, 255, 255), "HP %d / %d", heros_def_list[partyNarabijyun[temp]].heros_hp, heros_def_list[partyNarabijyun[temp]].heros_hp_max); // 文字を描画する
				DrawFormatString(HPX + 20 * 3, HPY + 20 * 2 + shiftY * temp, GetColor(255, 255, 255), "EXP %d", heros_def_list[partyNarabijyun[temp]].heros_exp); // 文字を描画する

			}

			
			window1Draw(480, 380, 600, 470);
			DrawFormatString(500, 400, GetColor(255, 255, 255), "所持金"); // 文字を描画する
			DrawFormatString(500, 400 + 30, GetColor(255, 255, 255), "%d G", your_money); // 文字を描画する


			// コマンドウィンドウの基準位置
			int XXX = 100;  int YYY = 250;
			window1Draw(XXX, YYY, XXX + 150, YYY + 40 + 150);

			if (keyEnableX == 0) {

				DrawFormatString(100, 250 + 40, GetColor(255, 255, 255), "カウント %d", nyuuryokuMatiX); // 文字を描画する
				nyuuryokuMatiX = nyuuryokuMatiX - 1;
			}

			if (nyuuryokuMatiX <= 0) {
				keyEnableX = 1;
				nyuuryokuMatiX = 0;

			}


			if (keyEnableX == 1) {
				// 点滅カーソル				
				tenmetu(XXX, YYY + (selecting_mainmenu - 1) * 40, XXX + 80, YYY + (selecting_mainmenu - 1) * 40 + 40);

				
				// コマンド欄			
				for (int j = 0; j <= 4; ++j) {

					// ここに共通する前段階の作業を記述;

					// 非共通;
					if (j == 0) { lstrcpy(mojibuf, TEXT("道具")); }
					if (j == 1) { lstrcpy(mojibuf, TEXT("装備")); }
					if (j == 2) { lstrcpy(mojibuf, TEXT("技能")); }
					if (j == 3) { lstrcpy(mojibuf, TEXT("セーブ")); }
					if (j == 4) { lstrcpy(mojibuf, TEXT("並び替え")); }

					// ここに共通する後段階の作業を記述;
					DrawFormatString(XXX + 20, YYY + 40 * j, GetColor(255 , 255 , 255), mojibuf); // 文字を描画する

				}


				// 十字キー入力時

				// カーソルを上に移動
				{

					// 移動の終了処理
					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
						keyEnableUp = 0;
						nyuuryokuMatiUp = waitTime1;
						selecting_mainmenu--;     // 上へ1マスだけ移動

					}


					if (selecting_mainmenu < 0) {
						selecting_mainmenu = 0;
					}

					if (selecting_mainmenu >= 3) {
						selecting_mainmenu = 3;
					}
				}


				// カーソルを下に移動
				{

					// 移動の終了処理
					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
						keyEnableDown = 0;
						nyuuryokuMatiDown = waitTime1;
						selecting_mainmenu++;    // 下へ1マスだけ移動
					}


					if (selecting_mainmenu < 1) {
						selecting_mainmenu = 1;
					}

					if (selecting_mainmenu >= 3) {
						selecting_mainmenu = 3;
					}

				}


				if (CheckHitKey(KEY_INPUT_Z) == 1) {

					if (selecting_mainmenu == 1) {
						//mode_scene = itemModeMain;
						mode_scene = MODE_ITEM_TYPE;
						DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "道具を選びました未実装"); // 文字を描画する

						keyEnableReset();
					}

					if (selecting_mainmenu == 2) {
						mode_scene = MODE_EQUIP_MAIN;
						nyuuryokuMatiZ = waitTime1;

						DrawFormatString(100 + 170, 250, GetColor(255, 255, 255), "装備を選びました未実装"); // 文字を描画する
						keyEnableReset();
					}


					if (selecting_mainmenu == 3) {
						MessageBox(NULL, TEXT("特技を使うためのコマンド（※未実装）。"), TEXT("テスト"), MB_OK);

						// 今後の未実装部分なので消すな
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

									//WideCharToMultiByte(CP_ACP, 0, item_def_list[temp].def_name, -1, aaa, sizeof(aaa), NULL, NULL); // 難しい関数をコピペ用に保管
									fprintf(fp2, "%s の個数: %d \n", aaa, item_have_list[temp].have_kosuu);
								}

								// 装備品の武器の所持数
								for (int temp = 0; temp <= 3 - 1; ++temp) {
									fprintf(fp2, "%s の個数: %d \n", aaa, weapon_have_list[temp].have_kosuu);
								}

								// 装備品の盾の所持数
								for (int temp = 0; temp <= 3 - 1; ++temp) {
									fprintf(fp2, "%s の個数: %d \n", aaa, shield_have_list[temp].have_kosuu);
								}

								// 装備品のカブトの所持数
								for (int temp = 0; temp <= 3 - 1; ++temp) {
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

			if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1) {
				mode_scene = MODE_MAP;

				keyEnableReset();
			}
		} // menu の終わり


		if (mode_scene == MODE_ITEM_TYPE) {

			window1Draw(10, 10, 610, 80);

			if (mode_scene != MODE_ITEM_TYPE) {

				tenmetu(20 + (selecting_mainmenu - 1) * 100, 20,
					100 + (selecting_mainmenu - 1) * 100, 70);
			}

			if (mode_scene == MODE_ITEM_TYPE) {

				tenmetu(20 + (selecting_mainmenu - 1) * (100 + 10), 20 + 20,
					100 + (selecting_mainmenu - 1) * (100 + 10), 70);
			}


			// 道具～セーブ のメニュー欄
			int	menuComBaseX = 20; int menuComOffsetPerX = 100;
			int menuComBaseY = 20;

			if (mode_scene == MODE_ITEM_TYPE) {

				for (int j = 0; j <= 2; ++j) {

					// 非共通;
					if (j == 0) { lstrcpy(mojibuf, TEXT("消耗品")); }
					if (j == 1) { lstrcpy(mojibuf, TEXT("装備品")); }
					if (j == 2) { lstrcpy(mojibuf, TEXT("大事なもの")); }

					// ここに共通する後段階の作業を記述;

					DrawFormatString(menuComBaseX + (menuComOffsetPerX + 10) * j, menuComBaseY + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				}
			}


			if (mode_scene == MODE_MENU || mode_scene == MODE_ITEM_TYPE) {

				/* 所持金の表示欄 */

				window1Draw(500, 250, 600, 350);

				int GoldViewBaseX = 510; int GoldViewBaseY = 260;

				lstrcpy(mojibuf, TEXT("所持金"));
				DrawFormatString(GoldViewBaseX, GoldViewBaseY, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("%d G"), your_money);
				DrawFormatString(GoldViewBaseX, GoldViewBaseY + 40, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				// _itot_s(your_money , p,200, 10); // 難しい関数なのでコピペ用に残す


				/* キャラのステータス欄 */
				menu_CharaSelectDraw2();

			}


			// 道具～セーブ のメニュー欄
			int XXX = 100;  int YYY = 250;

			int darkWinX = 10; int darkWinY = 250;
			tekidame = 0;

			if (damepyon <= XXX && tekidame == 0) {
				damepyon = damepyon + 5;
			}

			darkwindow1Draw(darkWinX +XXX - damepyon, darkWinY, darkWinX + 110 + XXX - damepyon, darkWinY + 200);
			tenmetuStop(darkWinX, darkWinY, darkWinX + 110, darkWinY + 30);


			for (int j = 0; j <= 4; ++j) {

				// ここに共通する前段階の作業を記述;

				// 非共通;
				if (j == 0) { lstrcpy(mojibuf, TEXT("道具")); }
				if (j == 1) { lstrcpy(mojibuf, TEXT("装備")); }
				if (j == 2) { lstrcpy(mojibuf, TEXT("技能")); }
				if (j == 3) { lstrcpy(mojibuf, TEXT("セーブ")); }
				if (j == 4) { lstrcpy(mojibuf, TEXT("並び替え")); }

				// ここに共通する後段階の作業を記述;
				DrawFormatString(darkWinX + 20, darkWinY + 40 * j, GetColor(255 * 2 / 3, 255 * 2 / 3, 255 * 2 / 3), mojibuf); // 文字を描画する

			}


			if (mode_scene == MODE_ITEM_TYPE) {
				itemList(soubihin, soubiSyoji,0 );
		
			} // itemlist


			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1) {


				if (selecting_mainmenu == 1) {
					// MessageBox(NULL, TEXT("消耗品とか。"), TEXT("キーテスト"), MB_OK);

					selecting_item = 1;
					selecting_item_x = ((selecting_item - 1) % 2) + 1;
					selecting_item_y = ((selecting_item - 1) / 2) + 1;

					mode_scene = MODE_ITEM_MENU; // MODE_ITEM_MENU;

				}


				if (selecting_mainmenu == 2) {
					// MessageBox(NULL, TEXT("装備品の確認。未実装。装備コマンドとは別"), TEXT("テスト"), MB_OK);
					selecting_item = 1;
					selecting_item_x = ((selecting_item - 1) % 2) + 1;
					selecting_item_y = ((selecting_item - 1) / 2) + 1;


					mode_scene = MODE_ITEMweapon_MENU;
				}


				if (selecting_mainmenu == 3) {
					MessageBox(NULL, TEXT("大事なもの（※未実装）。"), TEXT("テスト"), MB_OK);

				}

				keyEnableReset();
			}


			if (CheckHitKey(KEY_INPUT_X) == 1 && nyuuryokuMatiX <= 0 && keyEnableX == 1) {

				{
					key_remain = 0;
					damepyon = 0;

					mode_scene = MODE_MENU;
					keyEnableX = 0;
					nyuuryokuMatiX = waitTime1;
				}
				keyEnableUp = 0;

				keyEnableDown = 0;

				kasol2Target = 0;
				selecting_mainmenu = 1;
			}


			// カーソルを←に移動
			{

				// 移動の終了処理
				if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1) {
					keyEnableLeft = 0;
					nyuuryokuMatiLeft = waitTime1;
					selecting_mainmenu--;      // 上へ1マスだけ移動

				}


				if (selecting_mainmenu < 0) {
					selecting_mainmenu = 0;
				}

				if (selecting_mainmenu >= 3) {
					selecting_mainmenu = 3;
				}
			}


			// カーソルをmigi に移動
			{

				// 移動の終了処理
				if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1) {

					// MessageBox(NULL, TEXT("大事なもの（※未実装）。"), TEXT("テスト"), MB_OK);

					keyEnableRight = 0;
					nyuuryokuMatiRight = waitTime1;
					selecting_mainmenu++;     // 下へ1マスだけ移動
				}


				if (selecting_mainmenu < 1) {
					selecting_mainmenu = 1;
				}

				if (selecting_mainmenu >= 3) {
					selecting_mainmenu = 3;
				}

			}
		}


		if (mode_scene == MODE_ITEM_WHOM) {

			darkFlag = 1;
			darkFlag = 0;

			// ここまで、背景フィルターで隠される。

			// Graphics 型の命令の読み込みのためにダミー変数 graphics を宣言.
			//Graphics graphics(hdc);

			// 画像の描画。 ダミー変数 graphics を仲介して描画する必要がある.
			//graphics.DrawImage(&image1, 0, 0, image1.GetWidth(), image1.GetHeight());

			// 画像の読み込み「image2」は変数名。これが背景フィルター。
			if (filterFlag == 0) {

				//Image image2(L"filter.png");

				// 画像の描画。 ダミー変数 graphics を仲介して描画する必要がある.

				//graphics.DrawImage(&image2, 0, 0, image2.GetWidth(), image2.GetHeight());
				filterFlag = 1;
			}

			menu_CharaSelectDraw();
		}


		if (mode_scene == itemModeTarget) {

			int itemWindX = 450;
			int itemWindY = 50;


			// デバッグ用
			DrawFormatString(itemWindX, 250 + 150 - 20, GetColor(255, 255, 255), "kkkkkkk"); // 文字を描画する

			// カウント処理
			if (keyEnableZ == 2 && nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;
				keyEnableZ = 3;
				// デバッグ用
				DrawFormatString(250, 250 + 150, GetColor(255, 255, 255), "aaa567"); // 文字を描画する
			}


			if (nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

			}

			if (nyuuryokuMatiZ <= 0) {
				nyuuryokuMatiZ = 0;

			}

			int HPX = 300; int HPY = 50;

			window1Draw(HPX, HPY, HPX + 150, HPY + 340 + 50);


			// カーソル
			tenmetu(HPX, HPY + kasol3Target * 60, HPX + 130, HPY + 50 + kasol3Target * 60);

			DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // 文字を描画する			
			DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // 文字を描画する

			DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // 文字を描画する
			DrawFormatString(HPX + 20, HPY + 20 * (3 + 1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // 文字を描画する


			if (nyuuryokuMatiX > 0) {
				nyuuryokuMatiX = nyuuryokuMatiX - 1;

			}

			if (nyuuryokuMatiX <= 0) {
				nyuuryokuMatiX = 0;
				keyEnableX = 1;

			}

			// 十字キー入力時
			// カーソルを上に移動
			{
				// 移動先予定地の入場可否の判定
				if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 0 && moving == 0) {

					// 入場可能ならフラグ設定
	
					moving = 1;

					keyEnableUp = 1;
					waitKasol = 20;
					
				}

				// カウント処理
				if (keyEnableUp == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}

				// 移動の終了処理
				if (keyEnableUp == 1 && waitKasol <= 0) {
					keyEnableUp = 0;
					waitKasol = waitTime1;
					kasol3Target--;      // 上へ1マスだけ移動
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
				if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 0 && moving == 0) {

					// 入場可能ならフラグ設定
	
					moving = 1;

					keyEnableDown = 1;
					waitKasol = 20;
		
				}
				// カウント処理
				if (keyEnableDown == 1 && waitKasol > 0) {
					waitKasol = waitKasol - 1;
				}
				// 移動の終了処理
				if (keyEnableDown == 1 && waitKasol <= 0) {
					keyEnableDown = 0;
					waitKasol = 20;
					kasol3Target++;   // 下へ1マスだけ移動
					moving = 0;
				}


				if (kasol3Target < 0) {
					kasol3Target = 0;
				}

				if (kasol3Target >= 3) {
					kasol3Target = 3;
				}
			}


			if (CheckHitKey(KEY_INPUT_X) == 1 && nyuuryokuMatiX <= 0) {
				keyEnableReset();

				// コピペ用にほかのイコールも残しとく
				// mode_scene = itemModeMain; // mode_scene == MODE_ITEM_TYPE
				mode_scene = MODE_ITEM_MENU; // mode_scene == MODE_ITEM_TYPE

				nyuuryokuMatiX = waitTime1;
			}

			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1) {

				// 実行処理とカウント終了処理

				keyEnableReset();

				int HPX = 300; int HPY = 50;

				DrawFormatString(HPX + 20, HPY + 20 * 0, GetColor(255, 255, 255), "%s", heros_def_list[0].heros_name); // 文字を描画する			
				DrawFormatString(HPX + 20, HPY + 20 * 1, GetColor(255, 255, 255), "HP %d/%d", heros_def_list[0].heros_hp, heros_def_list[0].heros_hp_max); // 文字を描画する

				DrawFormatString(HPX + 20, HPY + 20 * 3, GetColor(255, 255, 255), "%s", heros_def_list[1].heros_name); // 文字を描画する
				DrawFormatString(HPX + 20, HPY + 20 * (3 + 1), GetColor(255, 255, 255), "HP %d/%d", heros_def_list[1].heros_hp, heros_def_list[1].heros_hp_max); // 文字を描画する


				if (item_have_list[kasol2Target + 1].have_kosuu > 0) {
					item_have_list[kasol2Target + 1].have_kosuu = item_have_list[kasol2Target + 1].have_kosuu - 1;

					if (kasol2Target == 0) {
						healflag = 1;
						healti = 5;
						heros_def_list[kasol3Target].heros_hp = heros_def_list[kasol3Target].heros_hp + healti;

					}

					if (kasol2Target == 1) {
						healflag = 1;
						healti = 2;
						heros_def_list[kasol3Target].heros_hp = heros_def_list[kasol3Target].heros_hp + healti;
					}

				}

				if (item_have_list[kasol2Target + 1].have_kosuu <= 0) {
					item_have_list[kasol2Target + 1].have_kosuu = 0;
				}

			}

		}


		if (mode_scene == MODE_ITEM_MENU || mode_scene == MODE_ITEMweapon_MENU) {

			itemList(soubihin, soubiSyoji,1);
		} // end


		// こっちはボタン操作
		if ((mode_scene == MODE_ITEM_MENU || mode_scene == MODE_ITEMweapon_MENU) && key_remain > 0) {


			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1) {

				whatuse = itemHairetu[selecting_item - 1]; // 

				key_remain = 0;

				if (whatuse == -99) {
					break; // 		
				}

				if (mode_scene == MODE_ITEM_MENU) {
					mode_scene = MODE_ITEM_WHOM; // 		
				}

				nyuuryokuMatiZ = waitTime1;
				keyEnableZ = 0;
			}


			if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1) {
				//MessageBox(NULL, TEXT("Xが押されました。"), TEXT("キーテスト"), MB_OK);

				mode_scene = MODE_ITEM_TYPE;

				nyuuryokuMatiX = waitTime1;
				key_remain = 1;
				keyEnableReset();
			}


			// カーソルを上に移動
			{
				// 移動先予定地の入場可否の判定
				if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
					keyEnableUp = 0;

					nyuuryokuMatiUD = waitTime1;
					nyuuryokuMatiUp = waitTime1;
					nyuuryokuMatiDown = waitTime1;

					// 個別の処理
					if (itemHairetu[1] == -99) {
						break; // 		
					}
					selecting_item = selecting_item - 2; // 方向ごとに違う

					// これはリファクタせずにカッコ内に入れたままにすること if文の外に出せないので
					item_select();
					moving = 0;
				}
			}


			// カーソルを下に移動
			{
				// 移動先予定地の入場可否の判定
				if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
					keyEnableDown = 0;

					nyuuryokuMatiUD = waitTime1;
					nyuuryokuMatiUp = waitTime1;
					nyuuryokuMatiDown = waitTime1;

					// 個別の処理

					if (itemHairetu[1] == -99) {
						break; // 		
					}
					selecting_item = selecting_item + 2; // 方向ごとに違う

					// これはリファクタせずにカッコ内に入れたままにすること
					item_select();
					moving = 0;
				}
			}


			// キャラを右に移動
			{
				// 移動先予定地の入場可否の判定
				if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && keyEnableRight == 1) {
					keyEnableRight = 0;

					nyuuryokuMatiLR = waitTime1;
					nyuuryokuMatiLeft = waitTime1;
					nyuuryokuMatiRight = waitTime1;

					//
					if (itemHairetu[1] == -99) {
						break; // 		
					}
					selecting_item = selecting_item + 1; // 方向ごとに違う

					// これはリファクタせずにカッコ内に入れたままにすること
					item_select();
					moving = 0;
				}

			}

			// 左に移動
			{
				// 移動先予定地の入場可否の判定
				if (CheckHitKey(KEY_INPUT_LEFT) == 1 && keyEnableLeft == 1) {
					keyEnableLeft = 0;

					nyuuryokuMatiLR = waitTime1;
					nyuuryokuMatiLeft = waitTime1;
					nyuuryokuMatiRight = waitTime1;

					//
					if (itemHairetu[1] == -99) {
						break; // 		
					}
					selecting_item = selecting_item - 1; // 方向ごとに違う

					// これはリファクタせずにカッコ内に入れたままにすること
					item_select();
					moving = 0;
				}
			}

		}


		if (mode_scene == MODE_ITEM_WHOM) {
			if (healflag == 1) {
				waitheal = waitheal - 1;
			}
			if (waitheal <= 100 && waitheal > 0 ) {

				waitheal = waitheal - 1;
				healflag = 2; // 表示関数で使うので残しておくこと
			}
			if (waitheal <= 0 && healflag != 0) {
				// MessageBox(NULL, TEXT("テスト"), TEXT("キーテスト"), MB_OK);
				waitheal = 0;
				healflag = 0;
			}


			int tempVal;

			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && key_remain == 1) {

				//MessageBox(NULL, TEXT("いまココ1"), TEXT("メッセージ"), MB_OK);
				keyEnableReset();

				key_remain = 0;
				whomTargetID1 = whomCHARA - 1;
				item_have_list[0].have_kosuu = 0;

				// ここはアイテム使用時の効果

				// 薬草の効果
				if (whatuse == 1) {

					//MessageBox(NULL, TEXT("いまココ1"), TEXT("メッセージ"), MB_OK);

					tempVal = partyNarabijyun[whomTargetID1];

					if (heros_def_list[tempVal].heros_hp < heros_def_list[tempVal].heros_hp_max) {
						if (item_have_list[whatuse].have_kosuu <= 0) {
							mode_scene = MODE_ITEM_MENU;

						}

						healti = 5; healflag = 1; waitheal = 120;
						heros_def_list[tempVal].heros_hp = heros_def_list[tempVal].heros_hp + healti;


						healkioku = partyNarabijyun[whomTargetID1];

						if (heros_def_list[tempVal].heros_hp > heros_def_list[tempVal].heros_hp_max) {
							heros_def_list[tempVal].heros_hp = heros_def_list[tempVal].heros_hp_max;
						}

						item_have_list[whatuse].have_kosuu = item_have_list[whatuse].have_kosuu - 1;

					}
				}


				// 毒消しの効果
				if (whatuse == 2) {

					// MessageBox(NULL, TEXT("いまココ1"), TEXT("メッセージ"), MB_OK);
					if (heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp < heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp_max) {

						if (item_have_list[whatuse].have_kosuu <= 0) {
							mode_scene = MODE_ITEM_MENU;

							break;
						}

						healti = 1; healflag = 1;

						heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp = heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp + healti;

						healkioku = partyNarabijyun[whomTargetID1];

						if (heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp > heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp_max) {
							heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp = heros_def_list[whomTargetID1].heros_hp_max;
						}

						item_have_list[whatuse].have_kosuu = item_have_list[whatuse].have_kosuu - 1;

					}

				}


				// 不死鳥の尾の効果
				if (whatuse == 3) {

					heros_def_list[partyNarabijyun[whomTargetID1]].heros_HP0_flag = 0;

					heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp = heros_def_list[partyNarabijyun[whomTargetID1]].heros_hp + 3;

					//MessageBox(NULL, TEXT("いまココaaaa"), TEXT("メッセージ"), MB_OK);


					if (item_have_list[whatuse].have_kosuu <= 0) {
						mode_scene = MODE_ITEM_MENU;
	
					}

					if (heros_def_list[whomTargetID1].heros_hp > heros_def_list[whomTargetID1].heros_hp_max) {
						heros_def_list[whomTargetID1].heros_hp = heros_def_list[whomTargetID1].heros_hp_max;
					}

					item_have_list[whatuse].have_kosuu = item_have_list[whatuse].have_kosuu - 1;

				}

				if (item_have_list[whatuse].have_kosuu <= 0) {
					item_have_list[whatuse].have_kosuu = 0;
				}

				nyuuryokuMatiX = waitTime1;
				nyuuryokuMatiZ = waitTime1;
			}


			if (CheckHitKey(KEY_INPUT_X) == 1 && nyuuryokuMatiX <= 0) {
				// MessageBox(NULL, TEXT("Xが押されました。"), TEXT("キーテスト"), MB_OK);
				keyEnableReset();


				filterFlag = 0;
				mode_scene = MODE_ITEM_MENU;

				nyuuryokuMatiX = waitTime1;
				nyuuryokuMatiZ = waitTime1;

			}


			if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {
				// MessageBox(NULL, TEXT("上が押されました。"), TEXT("キーテスト"), MB_OK);
				whomCHARA = whomCHARA - 1;

				if (whomCHARA > partyNinzuDone) {
					whomCHARA = partyNinzuDone;
				}
				else if (whomCHARA < 1) {
					whomCHARA = 1;
				}
				whomTargetID1 = whomCHARA - 1;

				beforeselect = whomCHARA;
			}


			if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {
				// MessageBox(NULL, TEXT("↓が押されました。"), TEXT("キーテスト"), MB_OK);
				whomCHARA = whomCHARA + 1;

				if (whomCHARA >= partyNinzuDone) {
					whomCHARA = partyNinzuDone;
				}
				else if (whomCHARA < 1) {
					whomCHARA = 1;
				}
				whomTargetID1 = whomCHARA - 1;

				beforeselect = whomCHARA;
			}

		} // アイテム対象者フロントの終わり


		if (mode_scene == MODE_EQUIP_MAIN) {

			// グラフィック関係
			{
				// 装備の表示欄
				// メインモードは装備キャラの選択モードである

				int StatsHPbaseX = 130;
				int StatsHPbaseY = 130;
				int offsetY = 120;

				// 背景の青

				window1Draw(10, 350, 500, 400);

				lstrcpy(mojibuf,
					TEXT("装備を変更するキャラを選んでください。"));

				DrawFormatString(15, 350 + 10, GetColor(255, 255, 255), mojibuf); // 文字を描画する


				for (int j = 0; j <= partyNinzuDone - 1; ++j) {
					// 背景の青

					window1Draw(10, 100 + offsetY * j, 300, 200 + offsetY * j);	

					// カーソル
					if (whomTargetID1 == j) {

						tenmetu(10, 100 + offsetY * (whomTargetID1),
							300, 200 + offsetY * (whomTargetID1));

					}

					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("%s"),
						heros_def_list[partyNarabijyun[j]].heros_name);

					DrawFormatString(StatsHPbaseX,
						StatsHPbaseY - 25 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					lstrcpy(mojibuf, TEXT("HP"));
					DrawFormatString(StatsHPbaseX, StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("%d"),
						heros_def_list[partyNarabijyun[j]].heros_hp);

					DrawFormatString(StatsHPbaseX + 30,
						StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("/ %d"),
						heros_def_list[partyNarabijyun[j]].heros_hp_max);

					DrawFormatString(StatsHPbaseX + 30 * 2,
						StatsHPbaseY + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					_stprintf_s(
						mojibuf, MAX_LENGTH, TEXT("%d"),
						heros_def_list[partyNarabijyun[j]].heros_HP0_flag);

					DrawFormatString(StatsHPbaseX,
						StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する


					if (heros_def_list[partyNarabijyun[j]].heros_HP0_flag == 1) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("戦闘不能"));

						DrawFormatString(StatsHPbaseX,
							StatsHPbaseY + 40 + offsetY * j, GetColor(255, 255, 255), mojibuf); // 文字を描画する

					}

					if (debugFlag == 1) {
						_stprintf_s(mojibuf, MAX_LENGTH, TEXT("mode: %d"), mode_scene);
						DrawFormatString(130 * 2, 300, GetColor(255, 255, 255), mojibuf); // 文字を描画する
					}
				}

				// そのキャラの装備項目の選択がサブモード

			}// グラフィック関係

			if (keyEnableZ == 0 && nyuuryokuMatiZ >= 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

			}

			if (keyEnableZ == 0 && nyuuryokuMatiZ <= 0) {
				keyEnableZ = 1;

				// デバッグ用
				// MessageBox(NULL, TEXT("ここにいる。"), TEXT("キーテスト"), MB_OK);
			}

			if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1) {

				key_remain = 0;
				whomTargetID1 = whomCHARA - 1;
				
				mode_scene = MODE_EQUIP_EDIT;
				beforeselect = 0;
				keyEnableReset();
			}

			if (nyuuryokuMatiX > 0) {
				nyuuryokuMatiX = nyuuryokuMatiX - 1;

			}

			if (keyEnableX == 0 && nyuuryokuMatiX <= 0) {
				nyuuryokuMatiX = 0;
				keyEnableX = 1;

			}


			if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1) {

				filterFlag = 0;
				mode_scene = MODE_MENU;

				nyuuryokuMatiX = waitTime1;
				key_remain = 0;
				keyEnableReset();
			}


			if (CheckHitKey(KEY_INPUT_UP) == 1) {

				// MessageBox(NULL, TEXT("上が押されました。"),
			// TEXT("キーテスト"), MB_OK);
				whomCHARA = whomCHARA - 1;

				if (whomCHARA > partyNinzuDone) {
					whomCHARA = partyNinzuDone;
				}
				else if (whomCHARA < 1) {
					whomCHARA = 1;
				}
				whomTargetID1 = whomCHARA - 1;


				beforeselect = whomCHARA;
			}


			if (CheckHitKey(KEY_INPUT_DOWN) == 1) {

				// MessageBox(NULL, TEXT("↓が押されました。"),
				// TEXT("キーテスト"), MB_OK);
				whomCHARA = whomCHARA + 1;

				if (whomCHARA >= partyNinzuDone) {
					whomCHARA = partyNinzuDone;
				}
				else if (whomCHARA < 1) {
					whomCHARA = 1;
				}
				whomTargetID1 = whomCHARA - 1;


				beforeselect = whomCHARA;
			}

		} // equip モードの終わり



		if (mode_scene == MODE_EQUIP_EDIT || mode_scene == MODE_EQUIP_EDIT2) {
			// 装備の表示欄
			// メインモードは装備キャラの選択モードである
			// MessageBox(NULL, TEXT("aaaaココ1"), TEXT("メッセージ"), MB_OK);


			int StatsHPbaseX = 130;
			int StatsHPbaseY = 130;
			int offsetY = 120;


			// 背景の青
			window1Draw(10, 100, 350, 300 + 40);

			// カーソル
			if (mode_scene == MODE_EQUIP_EDIT) {
				tenmetu(90, (110 + 20) + 20 * (whatedit), 300 - 10,
					(110 + 20) + 20 * (1 + whatedit));
			}
			if (mode_scene == MODE_EQUIP_EDIT2) {
				tenmetuStop(90, (110 + 20) + 20 * (whatedit), 300 - 10,
					(110 + 20) + 20 * (1 + whatedit));
			}


			// 文字
			int soubiYbase = 110; int soubiYper = 20;

			lstrcpy(mojibuf, heros_def_list[partyNarabijyun[whomTargetID1]].heros_name);

			DrawFormatString(15, soubiYbase + soubiYper * 0, GetColor(255, 255, 255), mojibuf); // 文字を描画する


			int stypeOffset = soubiOffset - 1; //10;
			for (int temp = 1; temp <= 7; temp = temp + 1) {

				int afterOffTemp = stypeOffset + temp;

				if (temp == 1) {
					lstrcpy(mojibuf1, TEXT("武器"));
					lstrcpy(mojibuf2,

						soubihin[
							heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[afterOffTemp]
						].Stype[afterOffTemp].def_name);

				}

				if (temp == 2) {
					lstrcpy(mojibuf1, TEXT("盾"));
					lstrcpy(mojibuf2,

						soubihin[
							heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[afterOffTemp]
						].Stype[afterOffTemp].def_name);
				}

				if (temp == 3) {
					lstrcpy(mojibuf1, TEXT("頭"));
					lstrcpy(mojibuf2,
						soubihin[
							heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[afterOffTemp]
						].Stype[afterOffTemp].def_name);

				}

				if (temp == 4) {
					lstrcpy(mojibuf1, TEXT("身体"));
					lstrcpy(mojibuf2, TEXT("--------"));
				}

				if (temp == 5) {
					lstrcpy(mojibuf1, TEXT("腕"));
					lstrcpy(mojibuf2, TEXT("--------"));
				}

				if (temp == 6) {
					lstrcpy(mojibuf1, TEXT("装飾品1"));
					lstrcpy(mojibuf2, TEXT("--------"));
				}

				if (temp == 7) {
					lstrcpy(mojibuf1, TEXT("装飾品2"));
					lstrcpy(mojibuf2, TEXT("--------"));
				}

				DrawFormatString(15, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf1); // 文字を描画する
				DrawFormatString(90, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf2); // 文字を描画する

			}

			int temp = 8;

			lstrcpy(mojibuf1, TEXT("攻撃力"));
			DrawFormatString(15, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf1); // 文字を描画する

			_stprintf_s(mojibuf2, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[kougekiPara]);
			DrawFormatString(90 + 50, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf2); // 文字を描画する


			temp = 9;
			lstrcpy(mojibuf1, TEXT("守備力"));
			DrawFormatString(15, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf1); // 文字を描画する

			_stprintf_s(mojibuf2, MAX_LENGTH, TEXT("%d"), heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[syubiPara]);
			DrawFormatString(90 + 50, soubiYbase + soubiYper * temp, GetColor(255, 255, 255), mojibuf2); // 文字を描画する


			// たぶんウィンドウ背景の青
			window1Draw(10, 350, 500, 400);

			lstrcpy(mojibuf, TEXT("変更したい装備を選んでください。"));
			DrawFormatString(15, 350 + 10, GetColor(255, 255, 255), mojibuf); // 文字を描画する


			if (mode_scene == MODE_EQUIP_EDIT) {
				int locType;

				locType = soubiOffset + whatedit;
				/*
				// 下記は上記のリファクタ

				if (whatedit == 0) {
					locType = wepoType;
				}
				if (whatedit == 1) {
					locType = tateType;
				}
				if (whatedit == 2) {
					locType = kabutoType;
				}
				*/


				int tempSoubi = heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType];

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("装備威力 %d"), 0); // 未定義エラーを防ぐための初期化

				if (locType == wepoType) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("装備威力 %d"), (soubihin[tempSoubi].Stype[locType]).equipPower[kougekiPara]);
				}
				if (locType == tateType || locType == kabutoType) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("装備威力 %d"), (soubihin[tempSoubi].Stype[locType]).equipPower[syubiPara]);
				}

				DrawFormatString(15 + 300 * 0, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

			}


			if (debugFlag == 1) {
				// デバッグ文。装備個数ズレのバグ調査。
				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("whatedit2: %d"), whatedit2);
				DrawFormatString(15, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("iHw2: %d"), itemHairetu[whatedit2]);
				DrawFormatString(15 + 130, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT("wHL: %d"), weapon_have_list[heros_def_list[partyNarabijyun[whomTargetID1]].heros_weapon1].have_def_id);
				DrawFormatString(15 + 130 + 100, 350 + 10 + 20, GetColor(255, 255, 255), mojibuf); // 文字を描画する

			}


			if (nyuuryokuMatiZ > 0) {
				nyuuryokuMatiZ = nyuuryokuMatiZ - 1;

			}
			if (keyEnableZ == 0 && nyuuryokuMatiZ <= 0) {

				nyuuryokuMatiZ = 0;
				keyEnableZ = 1;

			}

			if (nyuuryokuMatiX > 0) {
				nyuuryokuMatiX = nyuuryokuMatiX - 1;

			}
			if (keyEnableX == 0 && nyuuryokuMatiX <= 0) {

				nyuuryokuMatiX = 0;
				keyEnableX = 1;

			}


			if (mode_scene == MODE_EQUIP_EDIT) {
				
				{
					if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1
						&& mode_scene == MODE_EQUIP_EDIT) {

						keyEnableReset();
						// MessageBox(NULL, TEXT("いまココ1"), TEXT("メッセージ"), MB_OK);

						key_remain = 0;
						whomTargetID1 = whomCHARA - 1;

						whatedit2 = 0;

						mode_scene = MODE_EQUIP_EDIT2;

	
						mode2_scene = MODE2_EQUIP_UnDef; // 未定義対応のため、とりあえず武器に初期化
						mode3_scene = 0;


						mode3_scene = whatedit + 11; // 装備品データベースは11番から
						whatedit2 = heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubiKasol[mode3_scene];
					}


					if (CheckHitKey(KEY_INPUT_X) == 1 && keyEnableX == 1 && mode_scene == MODE_EQUIP_EDIT) {

						filterFlag = 0;
						mode_scene = MODE_EQUIP_MAIN;
						keyEnableReset();
					}


					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {

						// MessageBox(NULL, TEXT("上が押されました。"),
					// TEXT("キーテスト"), MB_OK);
						whatedit = whatedit - 1;

						if (whatedit >= 5) {
							whatedit = 5;
						}
						else if (whatedit < 01) {
							whatedit = 0;
						}

						keyEnableReset();
					}


					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {

						// MessageBox(NULL, TEXT("↓が押されました。"),
						// TEXT("キーテスト"), MB_OK);
						whatedit = whatedit + 1;

						if (whatedit >= 5) {
							whatedit = 5;
						}
						else if (whatedit < 0) {
							whatedit = 0;
						}

						keyEnableReset();
					}

				}

			}


			int sentakuKougekiR = 0; //(soubihin[itemHairetu[whatedit2]].Stype[wepoType]).equipPower[kougekiPara];

			if (mode_scene == MODE_EQUIP_EDIT2) {

				if (CheckHitKey(KEY_INPUT_X) == 1) {

					filterFlag = 0;

					heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubiKasol[mode3_scene ] = whatedit2;

					
					mode_scene = MODE_EQUIP_EDIT;
					keyEnableReset();
				}

				int souWInXsta = 400;
				int souWInXend = 580;

				// 装備用アイテムのリスト表示
				// 背景の青

				window1Draw(souWInXsta, 100, souWInXend, 300);

				tenmetu(souWInXsta + 20, (110 + 20) + 20 * (whatedit2), souWInXend - 30,
					(110 + 20) + 20 * (1 + whatedit2));

				weapon_have_list[0].have_kosuu = 0;


				// 移植中
				int itemskip = 0;
				goukeiItem = 0;

				int itemIDcount = 0;
				int column = 1; // 装備コマンドの武器防具リストは1行なので

				int xcommon;
				int ycommon;


				int locType;
				locType =  mode3_scene;
	
				{

					// idTemp は装備品種類に対応. 0 が武器, 1がタテ 
					for (idTemp = 0; idTemp <= 2; idTemp = idTemp + 1)
					{
						itemHairetu[idTemp] = 0; // これないと、装備品が減ったとき残骸が残る。[]内がidTempであることに注意
					}

					for (idTemp = 0; idTemp <= 2; idTemp = idTemp + 1)
					{

						if ((soubiSyoji[idTemp].Stype[locType]).have_kosuu != 0) {

							xcommon = souWInXsta + 300 * floor((idTemp - itemskip) % column);
							ycommon = 130 + 20 * floor((idTemp - itemskip) / column);

							// アイテム名の表示
							lstrcpy(mojibuf, (soubihin[idTemp].Stype[locType]).def_name);
							DrawFormatString(xcommon, ycommon, GetColor(255, 255, 255), mojibuf); // 文字を描画する

							// 個数の表示
							_stprintf_s(mojibuf, MAX_LENGTH, TEXT("x %d"), (soubiSyoji[idTemp].Stype[locType]).have_kosuu);
							DrawFormatString(xcommon + 130, ycommon, GetColor(255, 255, 255), mojibuf); // 文字を描画する


							goukeiItem = goukeiItem + 1;

							itemHairetu[itemIDcount] = idTemp; // これはボタン操作側で使う
							itemIDcount = itemIDcount + 1; // これは上コードで使う

						}
	
						if ((soubiSyoji[idTemp].Stype[locType]).have_kosuu == 0) {
							itemskip = itemskip + 1;
							itemHairetu[itemIDcount] = 0; // これないと、装備部位を変えたとき残骸が残る。
						}
					}


					if (CheckHitKey(KEY_INPUT_UP) == 1 && keyEnableUp == 1) {

						// MessageBox(NULL, TEXT("上が押されました。"),
					// TEXT("キーテスト"), MB_OK);
						whatedit2 = whatedit2 - 1;

						if (whatedit2 >= 5) {
							whatedit2 = 5;
						}
						else if (whatedit2 < 01) {
							whatedit2 = 0;
						}

						keyEnableReset();
					}


					if (CheckHitKey(KEY_INPUT_DOWN) == 1 && keyEnableDown == 1) {

						whatedit2 = whatedit2 + 1;

						if (whatedit2 >= 5) {
							whatedit2 = 5;
						}
						else if (whatedit2 < 0) {
							whatedit2 = 0;
						}

						keyEnableReset();
					}


					if (CheckHitKey(KEY_INPUT_Z) == 1 && nyuuryokuMatiZ <= 0 && keyEnableZ == 1
						&& mode_scene == MODE_EQUIP_EDIT2) {

						keyEnableReset();

						key_remain = 0;


						int temp;

						int hensu = heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType];


						if (locType == wepoType) {
							// 攻撃力の更新
							heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[kougekiPara] =
								(soubihin[itemHairetu[whatedit2]].Stype[locType]).equipPower[kougekiPara];

						}
						sentakuKougekiR = (soubihin[itemHairetu[whatedit2]].Stype[wepoType]).equipPower[kougekiPara]; // 表示でも使うので再利用

						(soubiSyoji[hensu].Stype[locType]).have_kosuu =
							(soubiSyoji[hensu].Stype[locType]).have_kosuu + 1; // 装備してた武器が1個増えるように


						if (whatedit2 < goukeiItem) {

							//itemHairetu
							(soubiSyoji[itemHairetu[whatedit2]].Stype[locType]).have_kosuu
								= (soubiSyoji[itemHairetu[whatedit2]].Stype[locType]).have_kosuu - 1; // 


						}
						if (whatedit2 >= goukeiItem) {
							// 何も選択してない状態なので、何も減らない
							//weapon_have_list[whatedit2 + 1].have_kosuu = weapon_have_list[whatedit2 + 1].have_kosuu - 1;  // カーソル選択中だった武器が1個減る
						}


						if (whatedit2 < goukeiItem) {
							heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType] =
						
								soubihin[itemHairetu[whatedit2]].Stype[locType].def_id; // 

						}
						if (whatedit2 >= goukeiItem) {
							heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType] =
								soubihin[0].Stype[locType].def_id; // 装備の更新をしたい
						}



						/////////////

						if (locType == tateType || locType == kabutoType) {

							// 防具の更新 // すでにしてある

							//(soubihin[heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[locType]].Stype[locType]).equipPower[syubiPara] =
							//	(soubihin[heros_def_list[itemHairetu[whatedit2]].heroSoubi[locType]].Stype[locType]).equipPower[syubiPara]
							//	;


							// 防御力の更新
							heros_def_list[partyNarabijyun[whomTargetID1]].heros_para[syubiPara] = // 現在の値

								(soubihin[(heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[tateType])].Stype[tateType]).equipPower[syubiPara]
								+ (soubihin[(heros_def_list[partyNarabijyun[whomTargetID1]].heroSoubi[kabutoType])].Stype[kabutoType]).equipPower[syubiPara]
								;

						}

						//////////

						(soubiSyoji[0].Stype[locType]).have_kosuu = 0;

					}

				} // ウェポン

			}

			if (mode_scene == MODE_EQUIP_EDIT2) {

				int locType;
				locType = mode3_scene;

				_stprintf_s(mojibuf, MAX_LENGTH, TEXT(""), 0); // 未定義エラー文を防ぐための初期化

				if (locType == wepoType) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("装備威力 %d"), (soubihin[itemHairetu[whatedit2]].Stype[locType]).equipPower[kougekiPara]);
				}

				if (locType == tateType || locType == kabutoType) {
					_stprintf_s(mojibuf, MAX_LENGTH, TEXT("装備威力 %d"), (soubihin[itemHairetu[whatedit2]].Stype[locType]).equipPower[syubiPara]);
				}

				DrawFormatString(15 + 300, 350 + 10, GetColor(255, 255, 255), mojibuf); // 文字を描画する

			}
		} // end of MODE_EQUIP_ 手～頭


		if (mode_scene == skillMode) {
			if (CheckHitKey(KEY_INPUT_X) == 1) {
				mode_scene = MODE_MENU;
				keyEnableX = 1; // 使い終わったのでゼロに戻す // 0ではなく1にしないとバグ
				nyuuryokuMatiX = waitTime1;

				DrawFormatString(250, 250 + 50 * 2, GetColor(255, 255, 255), "特技から戻り"); // 文字を描画する

			}
		}

		key_remain = 1;

		ScreenFlip(); //裏画面を表画面に反映
	}



	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}